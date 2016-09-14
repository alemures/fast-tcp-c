#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "../lib/util.h"

int main(int argc, char *argv[]) {
    char array[] = "";
    utilPrintBytes(array, strlen(array));

//    struct timeval time;
//    gettimeofday(&time, NULL);
//    long start = time.tv_usec;
//    int i;
//    for (i = 0; i < 1; i++) {
//    }
//    gettimeofday(&time, NULL);
//    printf("Finished in: %ld usec\n", time.tv_usec - start);

    return 0;
}
