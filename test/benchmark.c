#include <stdio.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    struct timeval time;
    gettimeofday(&time, NULL);
    long start = time.tv_usec;
    for (int i = 0; i < 1000; i++) {
    }
    gettimeofday(&time, NULL);
    printf("Benchmark finished in: %ld usec\n", time.tv_usec - start);

    return 0;
}
