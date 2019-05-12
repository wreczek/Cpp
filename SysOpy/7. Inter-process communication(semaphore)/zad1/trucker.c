#include "shared_utils.h"

key_t key;
int shmid;
int sem_id;
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
    printf("Truck is ready for loading: %lo\n", current_time());
    conveyor->t_status = LOADING;
}

void take_package(){ // LOADING
    sleep(1);
    int current = conveyor->current_remove;
    pid_t client_pid = conveyor->pids[current];
    long client_time = conveyor->times[current];
    int weight = conveyor->weights[current];
    if (conveyor->truck_left_space >= weight){
        conveyor->curr_k += 1;
        conveyor->curr_m += weight;
        conveyor->pids[current] = -1;   // zebym wiedzial ze puste
        conveyor->truck_left_space -= weight;
        conveyor->current_remove = (current + 1) % K;
        printf("Package %d from %d was being processed for %lo.\n",
                weight,
                client_pid,
                current_time()-client_time
        );
        printf("There is %d weight left and %d places.\n",
                M - conveyor->curr_m,
                K - conveyor->curr_k
        );
    }
    else {
        conveyor->t_status = DEPARTURE;
    }
}

void empty_the_truck(){   // DEPARTURE
    sleep(1);
    printf("Truck is full %d/%d: %lo\n",
            conveyor->curr_k,
            K,
            current_time()
    );
    conveyor->truck_left_space = X;
    conveyor->t_status = ARRIVAL;
}

void clean_memory() {
    conveyor->t_status = ARRIVAL;
    while (!is_conveyor_empty()){
        if (conveyor->t_status == DEPARTURE)
            empty_the_truck();
        else
            take_package();
    }
    if(shmdt(conveyor) < 0) error("Detach shared memory.\n");
    if(sem_id != 0)         semctl(sem_id, 0, IPC_RMID);
    if(shmid != 0)          shmctl(shmid, IPC_RMID, NULL);
}

void init_trucker(){
    signal(SIGINT, SIGINT_handler);
    atexit(clean_memory);

	if ((key    = ftok(PROJECT_PATH, PROJECT_ID)) < 0)      /* --> */                    error("ftok");
	if ((shmid  = shmget(key, sizeof(struct Conveyor), S_IRWXU|IPC_CREAT|IPC_EXCL)) < 0) error("shmget");
    if ((conveyor = shmat(shmid, NULL, 0)) == (void*) -1)   /* --> */                    error("shmat");
	if ((sem_id = semget(key, 2, IPC_CREAT | IPC_EXCL)) < 0)  /* --> */                  error("semget");

	union semun args[2];
	args[0].val = M;
	args[1].val = K;

	if (semctl(sem_id, 0, SETVAL, args[0]) < 0)  /* --> */                                 error("semtctl 1");
    if (semctl(sem_id, 1, SETVAL, args[1]) < 0)  /* --> */                                 error("semtctl 2");
    printf("#### ---- 2 ---- ####\n");
    conveyor->t_status = ARRIVAL;
    conveyor->K = K;
    conveyor->curr_k = 0;
    conveyor->M = M;
    conveyor->curr_m = 0;
    conveyor->current_insert = 0;
    conveyor->current_remove = 0;
    conveyor->pids = calloc(K, sizeof(pid_t));
    conveyor->times = calloc(K, sizeof(long));
    conveyor->weights = calloc(K, sizeof(int));
    conveyor->pids = calloc(K, sizeof(pid_t));
    conveyor->truck_left_space = X;
    printf("#### ---- 3 ---- ####\n");
}

int main(int argv, char ** argc){
    if (argv != 4)  error("Bad args number");
    X = atoi(argc[1]);
    K = atoi(argc[2]);
    M = atoi(argc[3]);

    init_trucker();

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
