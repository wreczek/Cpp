#include "shared_utils.h"

int t_shmfd;
int l_shmfd;

sem_t * t_sem;
sem_t * l_sem;

/**
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
*/
void clean_memory(){
    // zebranie paczek
    conveyor->t_status = ARRIVAL; // blokuje przez petle while
    while (!is_conveyor_empty()){
        if (conveyor->t_status == DEPARTURE)
            empty_the_truck();
        else
            take_package();
    }

    // zamykanie/usuwanie zasobow systemowych
    if (sem_close(t_sem) == -1) /* -----------> */ error("sem_close(t_sem)");
    if (sem_close(l_sem) == -1) /* -----------> */ error("sem_close(l_sem)");

    if (sem_unlink(T_SEM_NAME) == -1) /* -----> */ error("sem_unlink T");
    if (sem_unlink(L_SEM_NAME) == -1) /* -----> */ error("sem_unlink L");

    if (munmap(conveyor, sizeof(conveyor)) == -1)  error("munmap T");
    if (munmap(acc,      sizeof(acc))      == -1)  error("munmap L");

    if (shm_unlink(T_SEM_NAME) == -1) /* -----> */ error("shm_unlink T");
    if (shm_unlink(L_SEM_NAME) == -1) /* -----> */ error("shm_unlink L");
}

void init_trucker(){
    // handlers and exit
    if (signal(SIGINT, SIGINT_handler) < 0) /* -> */ error("signal");
    if (atexit(clean_memory) < 0) /* -----------> */ error("atexit");

    // shared memory
    if ((t_shmfd = shm_open(T_SEM_NAME, O_RDWR|O_CREAT|O_EXCL, S_IRWXU|S_IRWXG)) == -1) /* --------------> */ error("shm_open");
    if ((l_shmfd = shm_open(L_SEM_NAME, O_RDWR|O_CREAT|O_EXCL, S_IRWXU|S_IRWXG)) == -1) /* --------------> */ error("shm_open");

    if (ftruncate(t_shmfd, sizeof(Conveyor*)) == -1) /* -------------------------------------------------> */ error("ftruncate");
    if (ftruncate(l_shmfd, sizeof(int*))      == -1) /* -------------------------------------------------> */ error("ftruncate");

    if ((conveyor = mmap(NULL, sizeof(Conveyor*), PROT_READ|PROT_WRITE, MAP_SHARED, t_shmfd, 0) == (void*)-1) error("mmap");
    if ((conveyor = mmap(NULL, sizeof(int*),      PROT_READ|PROT_WRITE, MAP_SHARED, l_shmfd, 0) == (void*)-1) error("mmap");

    // semaphores
    if ((t_sem = sem_open(T_SEM_NAME, O_RDWR|O_CREAT|O_EXCL, S_IRWXU|S_IRWXG, 0)) == (void*)-1) /* ------> */ error("sem_open");
    if ((l_sem = sem_open(L_SEM_NAME, O_RDWR|O_CREAT|O_EXCL, S_IRWXU|S_IRWXG, 0)) == (void*)-1) /* ------> */ error("sem_open");

    // initialization
    conveyor

}

int main(int argc, char ** argv){
    if (argc != 4)  error("bad args number");
    init_trucker();

    release_truckers_sem(t_sem);

    while (1){
        // dzialanie
    }


    return 0;
}
