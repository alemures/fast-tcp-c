#include <stdio.h>
#include <stdlib.h>
#include "util.h"

const char hexValues[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

void utilLogDebug(char *message) {
    utilLog("[DEBUG]", message);
}

void utilLogInfo(char *message) {
    utilLog("[INFO]", message);
}

void utilLogWarning(char *message) {
   utilLog("[WARNING]", message);
}

void utilLogError(char *message) {
    utilLog("[ERROR]", message);
}

void utilLog(char *label, char *message) {
    printf("%s %s\n", label, message);
}

void utilWriteInt(int value, char *array) {
    array[0] = (char) value;
    array[1] = (char) (value >> 8);
    array[2] = (char) (value >> 16);
    array[3] = (char) (value >> 24);
}

void utilWriteShort(short value, char *array) {
    array[0] = (char) value;
    array[1] = (char) (value >> 8);
}

int utilReadInt(char *array) {
    return (array[0] & 0xFF) |
           (array[1] & 0xFF) >> 8 |
           (array[2] & 0xFF) >> 16 |
           (array[3] & 0xFF) >> 24;
}

void utilPrintBytes(char *array, int arrayLength) {
    char *string = (char *) malloc(arrayLength * 3);
    int i;

    for (i = 0; i < arrayLength; i++) {
        string[i * 3] = hexValues[(array[i] >> 4) & 0xF];
        string[i * 3 + 1] = hexValues[array[i] & 0xF];
        string[i * 3 + 2] = i < arrayLength - 1 ? ' ' : '\0';
    }

    printf("%s\n", string);
    free(string);
}
