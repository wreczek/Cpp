#ifndef SHARED_UTILS_H
#define SHARED_UTILS_H

#define MAX_PCKGS_NUM 256
#define PROJECT_ID 0xAAAA
#define PROJECT_PATH getenv("HOME")

#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>

/** Arguments:
    - trucker.c:
        X to pojemnosc tira
        K to max liczba paczek na tasmie
        M to max masa paczek na tasmie
    - loader.c:
        N to maksymalna masa paczki
        loaders_num to liczba loaderow
        C to liczba cykli
*/

long s_time;

union semun {   /* Used in calls to semctl() */
    int                 val;
    struct semid_ds *   buf;
    unsigned short *    array;
#if defined(__linux__)
    struct seminfo *    __buf;
#endif
};

enum trucker_status{
    ARRIVAL,
    WAITING,
    LOADING,
    DEPARTURE
};

enum loader_status{
    SHIPING,
    AWAITING
};

struct Conveyor{
    enum trucker_status t_status;
    int K;       // max liczba sztuk
    int curr_k;  // aktualna liczba sztuk
    int M;       // max waga
    int curr_m;  // aktualna waga
    int current_insert; // miejsce pod ktorym mozemy (po weryfikacji) wsadzic loadera ???
    int current_remove; // stad pierwsza paczka do wziecia
    pid_t pids[MAX_PCKGS_NUM];  // kolejka pidow loaderow
    long times[MAX_PCKGS_NUM];  // czasy polozenia na tasmie
    int weights[MAX_PCKGS_NUM]; // waga poszczegolnych paczek
    int truck_left_space;

} *conveyor;

void error(char * msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

long gettime(){
    struct timeval time;
    gettimeofday(&time,NULL);
    return time.tv_sec*1000000 + time.tv_usec;
}

long current_time(){
    return gettime()-s_time;
}

/// ^^^^^ SEMAPHORES ^^^^^
void pick_up_the_semaphore(int semid){
    struct sembuf sops;
    sops.sem_num = 0;
    sops.sem_op = -1;
    sops.sem_flg = 0;

    if (semop(semid, &sops, 1) < 0)  error("semop1");
}

void release_the_semaphore(int semid){
    struct sembuf sops;
    sops.sem_num = 0;
    sops.sem_op = 1;
    sops.sem_flg = 0;

    if (semop(semid, &sops, 1) < 0)  error("semop2");
}

void take_trucker_sem(int semid){
    struct sembuf * sops = malloc(sizeof(struct sembuf *)); // free(..)
    sops->sem_num = 1;
    sops->sem_op = -1;
    sops->sem_flg = 0;

    if (semop(semid, sops, 1) < 0) error("semop3");
    free(sops);
}

void release_trucker_sem(int semid){
    struct sembuf sops;
    sops.sem_num = 1;
    sops.sem_op = 1;
    sops.sem_flg = 0;

    if (semop(semid, &sops, 1) < 0)  error("semop");
}
/// $$$$$ SEMAPHORES $$$$$

int is_conveyor_available(){
    return conveyor->t_status == WAITING || conveyor->t_status == LOADING;
}

int is_conveyor_empty(){
    return conveyor->pids[conveyor->current_remove] < 0;
}

#endif // SHARED_UTILS_H
