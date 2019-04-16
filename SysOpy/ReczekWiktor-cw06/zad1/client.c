#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>

int error(char * msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char ** argv){
    if (argc == 1){
        char * cmd;
        size_t len = 0;

        /// WYSLANIE INIT

        while(1){
            ssize_t bufsize = getline(&cmd, &len, stdin);
            printf("%s\n", cmd);

            /// WYSYLANIE ZAPYTAN
        }
    }
    else if (argc == 3){
        /// WYSLANIE INIT
        /// ODczYT Z PLIKU I WYSYLANIE ZAPYTAN Z NIEGO

    }
    else {
        error("Wrong number of args");
    }

    return 0;
}
