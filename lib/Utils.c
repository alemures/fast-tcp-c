#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utils.h"

const char hexValues[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

void logDebug(char *message) {
    print("[DEBUG]", message);
}

void logInfo(char *message) {
    print("[INFO]", message);
}

void logWarning(char *message) {
   print("[WARNING]", message);
}

void logError(char *message) {
    print("[ERROR]", message);
}

void print(char *label, char *message) {
    printf("%s %s\n", label, message);
}

void writeInt(int value, char *buffer, int offset) {
    buffer[offset] = (char) value;
    buffer[offset + 1] = (char) (value >> 8);
    buffer[offset + 2] = (char) (value >> 16);
    buffer[offset + 3] = (char) (value >> 24);
}

void writeShort(short value, char *buffer, int offset) {
    buffer[offset] = (char) value;
    buffer[offset + 1] = (char) (value >> 8);
}

void printByteArray(char *array, int arrayLength) {
    char *string = (char *) malloc(arrayLength * 3);
    int i;

    for (i = 0; i < arrayLength; i++) {
        string[i * 3] = hexValues[(array[i] >> 4) & 0xF];
        string[i * 3 + 1] = hexValues[array[i] & 0xF];
        string[i * 3 + 2] = i < arrayLength - 1 ? ':' : '\0';
    }

    printf("%s\n", string);
    free(string);
}
