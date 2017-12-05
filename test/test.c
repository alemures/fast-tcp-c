#include <stdio.h>
#include <sys/time.h>
#include "../src/ft_util.h"

int main(int argc, char *argv[]) {
    struct timeval time;
    gettimeofday(&time, NULL);
    long start = time.tv_usec;
    int i;
    for (i = 0; i < 1000000; i++) {
    }
    gettimeofday(&time, NULL);
    printf("Finished in: %ld usec\n", time.tv_usec - start);

    return 0;
}
