#include "shared_utils.h"

int loaders_num;
int sem_id;
key_t key;
int shmid;
int N;

void awaiting_for_conveyor(){ // AWAITING
    sleep(3);
    printf("%d is waiting for the production tape to be released: %lo", getpid(), current_time());
}

void put_package_on_conveyor(int w){ // SHIPING
    sleep(3);
    while (!is_conveyor_available()){
        awaiting_for_conveyor();
    }

    printf("Placed %d weighted package by %d: %lo\n", N, getpid(), current_time());
    printf("%d: There is %d/%d[kg] space and %d/%d units left: %lo.\n",
            getpid(),
            conveyor->curr_m,
            conveyor->M,
            conveyor->curr_k,
            conveyor->K,
            current_time()
    );
    int current = conveyor->current_insert;
    conveyor->times[current] = current_time();
    conveyor->pids[current] = getpid();
    conveyor->weights[current] = w;
    conveyor->curr_k += 1;
    conveyor->curr_m += w;
    conveyor->current_insert = (conveyor->current_insert + 1) % conveyor->K;
}

void init_loaders(){
    if ((key = ftok(PROJECT_PATH, PROJECT_ID)) < 0) /* --> */       error("ftok");
    if ((shmid = shmget(key, sizeof(struct Conveyor), S_IRWXU)) < 0)error("shmget");
    if ((conveyor = shmat(shmid, NULL, 0)) == (void*) -1) /* --> */ error("shmat");
    if ((sem_id = semget(key, 0, 0)) < 0) /* --> */                 error("semget");
}

void limited_action(int C, int w){
    for (int i = C; i >= 0; --i){
        put_package_on_conveyor(w);
    }
    exit(0);
}

void infinite_action(int w){
    while(1){
        put_package_on_conveyor(w);
    }
    exit(0);
}

int main(int argc, char ** argv){
    if (argc > 4 || argc < 2)  error("Bad args number");
    N = atoi(argv[1]);
    loaders_num = atoi(argv[2]);
    init_loaders();

    if (argc == 4){ // arg C provided
        int C = atoi(argv[3]);
        for(int i = 0; i < loaders_num; ++i){
            if (!fork()){
/// Pracowników uruchamiamy fork i exec - argument programu
                limited_action(C, i+1);
                exit(0);
            }
        }
    }
    else { // arg C not provided
        for(int i = 0; i < loaders_num; ++i){
            if (!fork()){
                infinite_action(i+1);
                exit(0); // potrzebne?
            }
        }
    }

    while(wait(0)){
        if(errno != ECHILD)
            break;
    }
    return 0;
}
