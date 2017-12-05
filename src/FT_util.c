#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FT_util.h"

const char hexValues[] = "0123456789abcdef";

void FT_UtilLogDebug(char *message) {
    FT_UtilLog("[DEBUG]", message);
}

void FT_UtilLogInfo(char *message) {
    FT_UtilLog("[INFO]", message);
}

void FT_UtilLogWarning(char *message) {
    FT_UtilLog("[WARNING]", message);
}

void FT_UtilLogError(char *message) {
    FT_UtilLog("[ERROR]", message);
}

void FT_UtilLog(char *label, char *message) {
    printf("%s %s\n", label, message);
}

void FT_UtilWriteShort(short value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
}

void FT_UtilWriteInt(int value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
    array[2] = value >> 16;
    array[3] = value >> 24;
}

void FT_UtilWriteInt48(long long value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
    array[2] = value >> 16;
    array[3] = value >> 24;
    array[4] = value >> 32;
    array[5] = value >> 40;
}

void FT_UtilWriteLong(long long value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
    array[2] = value >> 16;
    array[3] = value >> 24;
    array[4] = value >> 32;
    array[5] = value >> 40;
    array[6] = value >> 48;
    array[7] = value >> 56;
}

void FT_UtilWriteDouble(double value, unsigned char *array) {
    long long longValue = FT_UtilDoubleToLong(value);
    FT_UtilWriteLong(longValue, array);
}

short FT_UtilReadShort(unsigned char *array) {
    return array[0] |
            array[1] << 8;
}

int FT_UtilReadInt(unsigned char *array) {
    return array[0] |
            array[1] << 8 |
            array[2] << 16 |
            array[3] << 24;
}

long long FT_UtilReadInt48(unsigned char *array) {
    return array[0] |
            array[1] << 8 |
            array[2] << 16 |
            (long long)array[3] << 24 |
            (long long)array[4] << 32 |
            (long long)array[5] << 40;
}

long long FT_UtilReadLong(unsigned char *array) {
    return array[0] |
            array[1] << 8 |
            array[2] << 16 |
            (long long)array[3] << 24 |
            (long long)array[4] << 32 |
            (long long)array[5] << 40 |
            (long long)array[6] << 48 |
            (long long)array[7] << 56;
}

double FT_UtilReadDouble(unsigned char *array) {
    long long longValue = FT_UtilReadLong(array);
    return FT_UtilLongToDouble(longValue);
}

long long FT_UtilDoubleToLong(double value) {
    long long longValue;
    memcpy(&longValue, &value, sizeof(long long));
    return longValue;
}

double FT_UtilLongToDouble(long long value) {
    double doubleValue;
    memcpy(&doubleValue, &value, sizeof(long long));
    return doubleValue;
}

void FT_UtilPrintBytes(char *array, int arrayLength) {
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
