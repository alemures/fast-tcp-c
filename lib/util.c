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

void utilWriteShort(short value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
}

void utilWriteInt(int value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
    array[2] = value >> 16;
    array[3] = value >> 24;
}

void utilWriteInt48(long value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
    array[2] = value >> 16;
    array[3] = value >> 24;
    array[4] = value >> 32;
    array[5] = value >> 40;
}

short utilReadShort(unsigned char *array) {
    return array[0] |
            array[1] << 8;
}

int utilReadInt(unsigned char *array) {
    return array[0] |
            array[1] << 8 |
            array[2] << 16 |
            array[3] << 24;
}

long utilReadInt48(unsigned char *array) {
    return array[0] |
            array[1] << 8 |
            array[2] << 16 |
            array[3] << 24 |
            (long)array[4] << 32 |
            (long)array[5] << 40;
}

void utilPrintBytes(char *array, int arrayLength) {
    arrayLength = arrayLength < 170 ? arrayLength : 170;
    char string[arrayLength * 3];
    int i;

    for (i = 0; i < arrayLength; i++) {
        string[i * 3] = hexValues[(array[i] >> 4) & 0xF];
        string[i * 3 + 1] = hexValues[array[i] & 0xF];
        string[i * 3 + 2] = ' ';
    }

    if (arrayLength > 0) {
        string[(i - 1) * 3 + 2] = '\0';
        printf("%s\n", string);
    }
}
