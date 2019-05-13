#include "shared_utils.h"

int loaders_num;
int semid;
key_t key;
int shmid;
int N;

void awaiting_for_conveyor(){ // AWAITING
    sleep(3);
    printf("%d is waiting for the production tape to be released: %lo", getpid(), gettime());
}

void put_package_on_conveyor(int w){ // SHIPING
    sleep(3);
    while (!is_conveyor_available()){
        awaiting_for_conveyor();
    }

    take_trucker_sem(semid);
    release_trucker_sem(semid);
    pick_up_the_semaphore(semid);

    while (conveyor->curr_m + w > conveyor->M || conveyor->curr_k + 1 > conveyor->K){}
    int current = conveyor->current_insert;
    conveyor->times[current] = gettime();
    conveyor->pids[current] = getpid();
    conveyor->weights[current] = w;
    conveyor->curr_k += 1;
    conveyor->curr_m += w;

    printf("Placed %dkg by %d. %d/%dkg, %d/%dunits occupied: %lo.\n\n",
            w, getpid(),
            conveyor->curr_m,
            conveyor->M,
            conveyor->curr_k,
            conveyor->K,
            current_time()
    );

    conveyor->current_insert = // insert inkrementujemy na koncu
        (conveyor->current_insert + 1) % conveyor->K;

    while (conveyor->pids[conveyor->current_insert] != -1){}
    release_the_semaphore(semid);
}

void init_loaders(){
    if ((key = ftok(PROJECT_PATH, PROJECT_ID)) == -1) /* --> */     error("ftok");
    if ((shmid = shmget(key, sizeof(struct Conveyor), S_IRWXU)) < 0)error("shmget");
    if ((conveyor = shmat(shmid, NULL, 0)) == (void*) -1) /* --> */ error("shmat");
    if ((semid = semget(key, 0, 0)) < 0) /* --> */                  error("semget");
}

void limited_action(int C, int w){
    for (int i = C-1; i >= 0; --i){
        printf("W petelce, i = %d, pid = %d\n", i, getpid());
        put_package_on_conveyor(w);
        printf("Po wywolaniu puta\n");
    }
    exit(0);
}

void infinite_action(int w){
    while(1){
        put_package_on_conveyor(w);
    }
}

int main(int argc, char ** argv){
    if (argc > 4 || argc <= 2)  error("Bad args number");
    N = atoi(argv[1]);

    s_time = gettime();
    loaders_num = atoi(argv[2]);
    init_loaders();

    if (argc == 4){ // arg C provided
        int C = atoi(argv[3]);
        for(int i = 0; i < loaders_num; ++i){
            if (fork() == 0){
        /// Pracowników uruchamiamy fork i exec - argument programu
                limited_action(C, (i+1)%N);
            }
        }
    }
    else { // arg C not provided
        for(int i = 0; i < loaders_num; ++i){
            if (fork() == 0){
                infinite_action((i+1)%N);
            }
        }
    }

    while(wait(0)){
        if(errno != ECHILD)
            break;
    }
    return 0;
}
