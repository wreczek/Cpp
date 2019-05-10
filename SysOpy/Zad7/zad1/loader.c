#include "shared_utils.h"

enum Client_status status;
int shared_memory_id;
int loaders_num;
int sem_id;
int N;

void put_package_on_conveyor(){ // SHIPING
    printf("Placed %d weighted package by %d: %lo", N, getpid(), current_time());
    // set current_time in client structure
}

void awaiting_for_tape(){
    printf("Awaiting for the production tape to be released: %lo", current_time());
}

void init_loaders(){

}

/// Paczka masa:         1..N
/// Ciezarowka masa:     1..X
/// Tasma liczba paczek: 1..K
/// Tasma masa paczek:   1..M

/// Pracowników uruchamiamy fork i exec - argument programu
/// ID pracownikow - PID
/// Tasmy transportowe trzymamy w pamieci wspolnej
/// Pamiec wspolna i semafory tworzy i usuwa program trucker
/// obsluguje SIGINT do usuwania pamiec wspolna i semafory
/// jesli uruchamiamy najpierw loadera zwraca wyjatek(perror?)
/// gdy trucker konczy prace blokuje semafor tasmy dla pracownikow, laduje to co zostalo na tasmie (W POSIXie jeszcze informuje pracownikow
///      aby ze swojej strony pozamykali procesy synchronizacyjne i pousuwac je

/**
Wypisuje cyklicznie informacje:
    1. Zaladowanie paczki na tasme:
        - N jednostek
        - PID pracownika
        - czas zaladowania
    2. Czekanie na zwolnienie tasmy
**/

/**
Kazdy komunikat pracownika zawiera:
    - znacznik czasowy z dokladnoscia do mikrosekund
    - PID
**/

/// Ladowanie na tasme informuje o liczbie wolnych miejsc oraz jednostek

void limited_action(int C){
    for (int j = C; i >= 0; --j){
        printf("Przebieg petli!\n");
    }
}

void infinite_action(){
    while(1){
        printf("NIESKONCZONOSC!\n");
    }
}

int main(int argc, char ** argv){
    if (argc > 4 || argc < 2)  error("Bad args number");
    N = atoi(argc[1]); // ladunek o takiej masie wrzuca ten pracownik
    loaders_num = atoi(argv[2]);
    init_loaders();

    if (argv == 4){ // arg C provided
        int C = atoi(argv[3]);
        for(int i = 0; i < loaders_num; ++i){
            if (!fork()){
                limited_action(C);
                exit(0);
            }
        }
    }
    else { // arg C not provided
        for(int i = 0; i < loaders_num; ++i){
            if (!fork()){
                infinite_action(C);
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
