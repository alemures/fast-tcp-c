#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_util.h"

const char HEX_VALUES[] = "0123456789abcdef";

void ft_utilLogDebug(char *message) {
    ft_utilLog("[DEBUG]", message);
}

void ft_utilLogInfo(char *message) {
    ft_utilLog("[INFO]", message);
}

void ft_utilLogWarning(char *message) {
    ft_utilLog("[WARNING]", message);
}

void ft_utilLogError(char *message) {
    ft_utilLog("[ERROR]", message);
}

void ft_utilLog(char *label, char *message) {
    printf("%s %s\n", label, message);
}

void ft_utilWriteShort(short value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
}

void ft_utilWriteInt(int value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
    array[2] = value >> 16;
    array[3] = value >> 24;
}

void ft_utilWriteInt48(long long value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
    array[2] = value >> 16;
    array[3] = value >> 24;
    array[4] = value >> 32;
    array[5] = value >> 40;
}

void ft_utilWriteLong(long long value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
    array[2] = value >> 16;
    array[3] = value >> 24;
    array[4] = value >> 32;
    array[5] = value >> 40;
    array[6] = value >> 48;
    array[7] = value >> 56;
}

void ft_utilWriteDouble(double value, unsigned char *array) {
    long long longValue = ft_utilDoubleToLong(value);
    ft_utilWriteLong(longValue, array);
}

short ft_utilReadShort(unsigned char *array) {
    return array[0] |
            array[1] << 8;
}

int ft_utilReadInt(unsigned char *array) {
    return array[0] |
            array[1] << 8 |
            array[2] << 16 |
            array[3] << 24;
}

long long ft_utilReadInt48(unsigned char *array) {
    return array[0] |
            array[1] << 8 |
            array[2] << 16 |
            (long long)array[3] << 24 |
            (long long)array[4] << 32 |
            (long long)array[5] << 40;
}

long long ft_utilReadLong(unsigned char *array) {
    return array[0] |
            array[1] << 8 |
            array[2] << 16 |
            (long long)array[3] << 24 |
            (long long)array[4] << 32 |
            (long long)array[5] << 40 |
            (long long)array[6] << 48 |
            (long long)array[7] << 56;
}

double ft_utilReadDouble(unsigned char *array) {
    long long longValue = ft_utilReadLong(array);
    return ft_utilLongToDouble(longValue);
}

long long ft_utilDoubleToLong(double value) {
    long long longValue;
    memcpy(&longValue, &value, sizeof(long long));
    return longValue;
}

double ft_utilLongToDouble(long long value) {
    double doubleValue;
    memcpy(&doubleValue, &value, sizeof(long long));
    return doubleValue;
}

void ft_utilPrintBytes(char *array, int arrayLength) {
    arrayLength = arrayLength < 170 ? arrayLength : 170;
    char string[arrayLength * 3];
    int i;

    for (i = 0; i < arrayLength; i++) {
        string[i * 3] = HEX_VALUES[(array[i] >> 4) & 0xF];
        string[i * 3 + 1] = HEX_VALUES[array[i] & 0xF];
        string[i * 3 + 2] = ' ';
    }

    if (arrayLength > 0) {
        string[(i - 1) * 3 + 2] = '\0';
        printf("%s\n", string);
    }
}
