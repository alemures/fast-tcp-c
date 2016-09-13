#include <stdio.h>
#include <string.h>
#include "../lib/util.h"

int main(int argc, char *argv[]) {
    utilLogDebug("Hell yeah!");
    utilLogInfo("Hell yeah!");
    utilLogWarning("Hell yeah!");
    utilLogError("Hell yeah!");

    char array[] = "aaaa";

    utilWriteInt(1, array);
    utilPrintBytes(array, 5);

    printf("%d\n", utilReadInt(array));
    return 0;
}
