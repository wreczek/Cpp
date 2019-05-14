#include "shared_utils.h"

int N;
int loaders_num;

int t_shmfd;
int l_shmfd;

sem_t * t_sem;
sem_t * l_sem;

void awaiting_for_conveyor(){ // AWAITING
    sleep(3);
    printf("%d is waiting for the production tape to be released: %f", getpid(), gettime());
}

void put_package_on_conveyor(int w){ // SHIPING
    sleep(3);
    while (!is_conveyor_available()){
        awaiting_for_conveyor();
    }

    pick_up_truckers_sem(t_sem); // sprawdzamy, czy kierowca nie odjechal
    release_truckers_sem(t_sem);
    pick_up_loaders_sem(t_sem);

    while (conveyor->curr_m + w > conveyor->M || conveyor->curr_k + 1 > conveyor->K){}
    int current = conveyor->current_insert;
    conveyor->times[current] = gettime();
    conveyor->pids[current] = getpid();
    conveyor->weights[current] = w;
    conveyor->curr_k += 1;
    conveyor->curr_m += w;

    printf("Placed %dkg by %d. %d/%dkg, %d/%dunits occupied: %f.\n\n",
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
    release_loaders_sem(l_sem);
}

void init_loaders(){
    if ((t_shmfd = shm_open(T_SEM_NAME, O_RDWR, S_IRWXU_G)) == -1) /* --------------------------> */ error("shmopen T");
    if ((l_shmfd = shm_open(L_SEM_NAME, O_RDWR, S_IRWXU_G)) == -1) /* --------------------------> */ error("shmopen L");

    if ((conveyor = mmap(NULL, sizeof(Conveyor*), PROT_RD_WR, MAP_SHARED, t_shmfd, 0)) == (void*)-1) error("mmap T");
    if ((acc      = mmap(NULL, sizeof(int*),      PROT_RD_WR, MAP_SHARED, l_shmfd, 0)) == (void*)-1) error("mmap L");

    if ((t_sem = sem_open(T_SEM_NAME, O_RDWR)) == (void*)-1) /* --------------------------------> */ error("sem_open T");
    if ((l_sem = sem_open(L_SEM_NAME, O_RDWR)) == (void*)-1) /* --------------------------------> */ error("sem_open L");
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
