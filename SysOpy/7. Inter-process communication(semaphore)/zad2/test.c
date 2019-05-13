#include <time.h>
//#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

#define T_SEM_NAME "/AAA"
#define L_SEM_NAME "/BBB"

int t_shmfd;
int l_shmfd;

sem_t * t_sem;
sem_t * l_sem;

int * acc;

struct D{
    int a;
    int b;
} *d;

typedef struct D D;

void error(char * msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

void clean_memory(){
    // zamykanie/usuwanie zasobow systemowych
    if (sem_close(t_sem) == -1) /* -----------> */ error("sem_close(t_sem)");
    if (sem_close(l_sem) == -1) /* -----------> */ error("sem_close(l_sem)");

    if (sem_unlink(T_SEM_NAME) == -1) /* -------> */ error("sem_unlink T)");
    if (sem_unlink(L_SEM_NAME) == -1) /* -------> */ error("sem_unlink L)");

    if (munmap(d, sizeof(d)) == -1)  error("munmap T");
    if (munmap(acc, sizeof(acc)) == -1)  error("munmap L");

    if (shm_unlink(T_SEM_NAME) == -1) /* -------> */ error("shm_unlink T");
    if (shm_unlink(L_SEM_NAME) == -1) /* -------> */ error("shm_unlink L");
}

void display(){
    int t_valp;
    int l_valp;

    if (sem_getvalue(t_sem, &t_valp) == -1) error("sem_getvalue 1");
    if (sem_getvalue(l_sem, &l_valp) == -1) error("sem_getvalue 2");

    printf("t_sem = %d, l_sem = %d\n", t_valp, l_valp);
}

int main(){
    if (atexit(clean_memory) < 0) /* -----------> */ error("atexit");

    // shared memory
    if ((t_shmfd = shm_open(T_SEM_NAME, O_RDWR|O_CREAT|O_EXCL, S_IRWXU|S_IRWXG)) == -1) /* --------------> */ error("shm_open t");
    if ((l_shmfd = shm_open(L_SEM_NAME, O_RDWR|O_CREAT|O_EXCL, S_IRWXU|S_IRWXG)) == -1) /* --------------> */ error("shm_open l");

    if (ftruncate(t_shmfd, sizeof(D*)) == -1) /* -------------------------------------------------> */ error("ftruncate");
    if (ftruncate(l_shmfd, sizeof(int*)) == -1) /* -------------------------------------------------> */ error("ftruncate");

    if ((d = mmap(NULL, sizeof(D*), PROT_READ|PROT_WRITE, MAP_SHARED, t_shmfd, 0)) == (void*)-1) error("mmap");
    if ((acc = mmap(NULL, sizeof(D*), PROT_READ|PROT_WRITE, MAP_SHARED, l_shmfd, 0)) == (void*)-1) error("mmap");

    // semaphores
    if ((t_sem = sem_open(T_SEM_NAME, O_RDWR|O_CREAT|O_EXCL, S_IRWXU|S_IRWXG, 0)) == (void*)-1) /* -----> */ error("sem_open");
    if ((l_sem = sem_open(L_SEM_NAME, O_RDWR|O_CREAT|O_EXCL, S_IRWXU|S_IRWXG, 0)) == (void*)-1) /* -----> */ error("sem_open");

    display();

    if (sem_post(t_sem) == -1)  error("sem_post trucker");

    display();

    if (sem_wait(t_sem) == -1)  error("sem_wait trucker");

    display();

    if (sem_post(l_sem) == -1)  error("sem_post loader");

    display();

    if (sem_wait(l_sem) == -1)  error("sem_wait loader");

    display();

    return 0;
}
