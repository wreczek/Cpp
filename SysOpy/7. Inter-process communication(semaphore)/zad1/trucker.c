#include "shared_utils.h"

key_t key;
int shmid;
int semid;
int X, K, M;
int current;

void SIGINT_handler(int signum){
    printf("Finished unloading.\n");
    exit(EXIT_SUCCESS);
}

void arrival(){      // ARRIVAL
    sleep(1);
    printf("Truck just arrived: %lo\n", current_time());
    conveyor->t_status = WAITING;
}

void waiting(){      // WAITING
    sleep(1);
    printf("Current remove = %d, pids[..] = %d\n", conveyor->current_remove, conveyor->pids[conveyor->current_remove]);
    printf("Truck is ready for loading: %lo\n", current_time());
    if (conveyor->pids[conveyor->current_remove] > 0)
        conveyor->t_status = LOADING;
}

void take_package(){ // LOADING
    sleep(1);
    int current = conveyor->current_remove;
    if (conveyor->pids[current] < 0){
        printf("Current remove %d is less than zero: %d.\n", current, (int)conveyor->pids[current]);
        return;
    }

    pid_t client_pid = conveyor->pids[current];
    long client_time = conveyor->times[current];
    int weight = conveyor->weights[current];
    if (conveyor->truck_left_space >= weight){
        conveyor->curr_k -= 1;
        conveyor->curr_m -= weight;
        conveyor->pids[current] = -1;   // zebym wiedzial ze puste
        conveyor->truck_left_space -= weight;
        conveyor->current_remove = (current + 1) % K;
        printf("Package %dkg from %d was being processed for %loμs. %d/%d and %d/%d left.\n",
                weight,
                client_pid,
                gettime()-client_time,
                M - conveyor->curr_m, M,
                K - conveyor->curr_k, K
        );
    }
    if (conveyor->truck_left_space >= weight){
        conveyor->t_status = WAITING;
    }
    else {
        conveyor->t_status = DEPARTURE;
    }
}

void empty_the_truck(){   // DEPARTURE
    take_trucker_sem(semid); // blokujemy wstawianie na tasme
    sleep(1);
    printf("Truck is full %d/%d: %lo\n",
            X-conveyor->truck_left_space,
            X,
            current_time()
    );
    conveyor->truck_left_space = X;
    conveyor->t_status = ARRIVAL;
    release_trucker_sem(semid);
}

void clean_memory() {
    conveyor->t_status = ARRIVAL; // blokuje przez petle while
    //take_trucker_sem(semid);      // blokuje semaforem, nie zwalnia go (chyba tak nie moze byc)
    while (!is_conveyor_empty()){
        if (conveyor->t_status == DEPARTURE)
            empty_the_truck();
        else
            take_package();
    }
    if(shmdt(conveyor) < 0) error("Detach shared memory.\n");
    if(semid != 0)          semctl(semid, 0, IPC_RMID);
    if(shmid != 0)          shmctl(shmid, IPC_RMID, NULL);
}

void init_trucker(){
    if (signal(SIGINT, SIGINT_handler) == SIG_ERR)  error("signal");
    if (atexit(clean_memory) != 0)     error("atexit");
	if ((key    = ftok(PROJECT_PATH, PROJECT_ID)) == -1)    /* --> */            error("ftok");
	if ((shmid  = shmget(key, sizeof(struct Conveyor), S_IRWXU|IPC_CREAT)) < 0)  error("shmget");
    if ((conveyor = shmat(shmid, NULL, 0)) == (void*) -1)   /* --> */            error("shmat");
	if ((semid = semget(key, 2, S_IRWXU|IPC_CREAT)) < 0)  /* --> */              error("semget");

    if (semctl(semid, 0, SETVAL, 0) < 0)  /* --> */                       error("semtctl 1");
    if (semctl(semid, 1, SETVAL, 0) < 0)  /* --> */                       error("semtctl 2");

    conveyor->t_status = ARRIVAL;
    conveyor->K = K;
    conveyor->curr_k = 0;
    conveyor->M = M;
    conveyor->curr_m = 0;
    conveyor->current_insert = 0;
    conveyor->current_remove = 0;
    conveyor->truck_left_space = X;

    for (size_t i = 0; i < K; ++i){
        conveyor->pids[i] = (pid_t) -1;
    }
}

int main(int argv, char ** argc){
    if (argv != 4)  error("Bad args number");
    X = atoi(argc[1]);
    K = atoi(argc[2]);
    M = atoi(argc[3]);
    s_time = gettime();

    init_trucker();

    release_the_semaphore(semid);
    release_trucker_sem(semid);

    while(1){
        switch(conveyor->t_status){
        case ARRIVAL:
            arrival();
            break;
        case WAITING:
            waiting();
            break;
        case LOADING:
            take_package();
            break;
        case DEPARTURE:
            empty_the_truck();
            break;
        }
    }

    return 0;
}
