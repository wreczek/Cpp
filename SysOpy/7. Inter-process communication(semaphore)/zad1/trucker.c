#include "shared_utils.h"

int shared_memory_id;
int sem_id;
int X, K, M;

void SIGINT_handler(int signum){
    printf("Finished unloading.\n");
    exit(EXIT_SUCCESS);
}

void arrival(){      // ARRIVAL
    printf("Truck just arrived: %lo\n", current_time());
}

void waiting(){      // WAITING
    printf("Truck is ready for loading: %lo\n", current_time());
}

void take_package(){ // LOADING
    pid_t client_pid = client_info[0].pid;
    long client_time = client_info[0].time;
    int weight = client_info[0].weight;
    printf("Package %d from %d was processed for %lo.\n", weight, client_pid, current_time()-client_time);
}

void empty_the_truck(){   // DEPARTURE
    printf("Track is full: %lo\n", current_time());
}

void clean_memory() {
    if(shmdt(trucker) < 0) error("Detach shared memory.\n");
    if(sem_id != 0) {
        semctl(sem_id, 0, IPC_RMID);
    }
    if(id_of_shared_memory != 0) {
        shmctl(id_of_shared_memory, IPC_RMID, NULL);
    }
}

/// Paczka masa:         1..N
/// Ciezarowka masa:     1..X
/// Tasma liczba paczek: 1..K
/// Tasma masa paczek:   1..M

/// ID pracownikow - PID
/// Tasmy transportowe trzymamy w pamieci wspolnej
/// Pamiec wspolna i semafory tworzy i usuwa program trucker
/// obsluguje SIGINT do usuwania pamiec wspolna i semafory
/// jesli uruchamiamy najpierw loadera zwraca wyjatek(perror?)
/// gdy trucker konczy prace blokuje semafor tasmy dla pracownikow, laduje to co zostalo na tasmie (W POSIXie jeszcze informuje pracownikow
///      aby ze swojej strony pozamykali procesy synchronizacyjne i pousuwac je
/**
Trucker wypisuje cyklicznie:
    1. Podjechanie ciezarowki.
    2. Czekanie na zaladowanie paczki.
    3. Ladowanie do ciezarowki:
        - PID
        - roznica czasu od polozenia na tasme do zaladowania do ciezarowki
        - ilosc zajetych i wolnych miejsc
    4. Brak miejsca - odjazd i wyladowanie ciezarowki.
**/

/// Kazdy komunikat ciezarowki lub pracownika zawiera znacznik czasowy z dokladnoscia do mikrosekund - clock_gettime z flag¹ CLOCK_MONOTONIC
/// Zwalnianie z tasmy informuje o liczbie wolnych miejsc oraz jednostek

void init_trucker(){
    // co jest do chuja
	key_t key = ftok(PROJECT_PATH, PROJECT_ID);
	sem_id 	  = semget(key, 
}

int main(int argv, char ** argc){
    if (argv != 4)  error("Bad args number");
    X = atoi(argc[1]);
    K = atoi(argc[2]);
    M = atoi(argc[3]);

    init_trucker();

    release_sem(sem_id);

    while(1){
        take_sem(sem_id); // zajmujemy, przekazemy jeszzcze N

        switch(trucker.status){
        case ARRIVAL:
            arrival();
            trucker.status = ?
            break;
        case WAITING:
            waiting();
            trucker.status = ?
            break;
        case LOADING:
            take_package();
            trucker.status = ?
            break;
        case DEPARTURE:
            empty_the_truck();
            trucker.status = ?
            break;
        }

        release_sem(sem_id); // zwalniamy, przekazemy jeszcze N
    }

    return 0;
}
