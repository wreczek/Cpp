#include <time.h>

int main(){
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    printf("nsec = %d", time.tv_nsec);

    return 0;
}
