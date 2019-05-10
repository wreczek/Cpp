#ifndef SHARED_UTILS_H
#define SHARED_UTILS_H

#define PROJECT_PATH getenv("HOME")
#define PROJECT_ID 0xDADA

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
//#include <sys/sem.h>
//#include <sys/ipc.h>
#include <sys/types.h>
//#include <sys/shm.h>

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

struct Trucker{
    trucker_status status;
    int client_pid;

} *trucker;

void error(char * msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

long current_time(){
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return time.tv_nsec;
}

#endif // SHARED_UTILS_H
