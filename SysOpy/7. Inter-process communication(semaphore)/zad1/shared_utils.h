#ifndef SHARED_UTILS_H
#define SHARED_UTILS_H

#define PROJECT_ID 0xDADA
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
#include <sys/wait.h>
#include <sys/types.h>

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
    pid_t *pids;  // kolejka pidow loaderow
    long *times;  // czasy polozenia na tasmie
    int *weights; // waga poszczegolnych paczek
    int truck_left_space;

} *conveyor;

void error(char * msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

long current_time(){
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return time.tv_nsec;
}

void pick_up_the_semaphore(int semid, int value){
    struct sembuf sops[2];// = calloc(2, sizeof(sembuf));
    sops[0].sem_num = 0;
    sops[0].sem_op = -value;
    sops[0].sem_flg = 0;

    sops[1].sem_num = 1;
    sops[1].sem_op = -1;
    sops[1].sem_flg = 0;
    if (semop(semid, sops, 2) < 0)  error("semop");
}

void release_the_semaphore(int semid, int value){
    struct sembuf sops[2];// = calloc(2, sizeof(sembuf));
    sops[0].sem_num = 0;
    sops[0].sem_op = value;
    sops[0].sem_flg = 0;

    sops[1].sem_num = 1;
    sops[1].sem_op = 1;
    sops[1].sem_flg = 0;
    if (semop(semid, sops, 2) < 0)  error("semop");
}

int is_conveyor_available(){
    return conveyor->t_status == WAITING || conveyor->t_status == LOADING;
}

int is_conveyor_empty(){
    return conveyor->pids[conveyor->current_remove] < 0;
}

#endif // SHARED_UTILS_H
