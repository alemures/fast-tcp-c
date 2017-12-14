#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "ft_util.h"

const char HEX_VALUES[] = "0123456789abcdef";

void ft_utilLogDebug(char *format, ...) {
    char message[64];
    va_list arg;
    va_start (arg, format);
    vsprintf (message, format, arg);
    va_end (arg);

    ft_utilLog("DEBUG", message);
}

void ft_utilLogInfo(char *format, ...) {
    char message[64];
    va_list arg;
    va_start (arg, format);
    vsprintf (message, format, arg);
    va_end (arg);

    ft_utilLog("INFO", message);
}

void ft_utilLogWarning(char *format, ...) {
    char message[64];
    va_list arg;
    va_start (arg, format);
    vsprintf (message, format, arg);
    va_end (arg);

    ft_utilLog("WARNING", message);
}

void ft_utilLogError(char *format, ...) {
    char message[64];
    va_list arg;
    va_start (arg, format);
    vsprintf (message, format, arg);
    va_end (arg);

    ft_utilLog("ERROR", message);
}

void ft_utilLog(char *label, char *message) {
    printf("[%s] %s\n", label, message);
}

void ft_utilWriteUShort(unsigned short value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
}

void ft_utilWriteUInt(unsigned int value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
    array[2] = value >> 16;
    array[3] = value >> 24;
}

void ft_utilWriteUInt48(unsigned long long value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
    array[2] = value >> 16;
    array[3] = value >> 24;
    array[4] = value >> 32;
    array[5] = value >> 40;
}

void ft_utilWriteULong(unsigned long long value, unsigned char *array) {
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
    long long longValue = ft_utilDoubleToULong(value);
    ft_utilWriteULong(longValue, array);
}

unsigned short ft_utilReadUShort(unsigned char *array) {
    return array[0] |
            array[1] << 8;
}

unsigned int ft_utilReadUInt(unsigned char *array) {
    return array[0] |
            array[1] << 8 |
            array[2] << 16 |
            array[3] << 24;
}

unsigned long long ft_utilReadUInt48(unsigned char *array) {
    return array[0] |
            array[1] << 8 |
            array[2] << 16 |
            (unsigned long long)array[3] << 24 |
            (unsigned long long)array[4] << 32 |
            (unsigned long long)array[5] << 40;
}

unsigned long long ft_utilReadULong(unsigned char *array) {
    return array[0] |
            array[1] << 8 |
            array[2] << 16 |
            (unsigned long long)array[3] << 24 |
            (unsigned long long)array[4] << 32 |
            (unsigned long long)array[5] << 40 |
            (unsigned long long)array[6] << 48 |
            (unsigned long long)array[7] << 56;
}

double ft_utilReadDouble(unsigned char *array) {
    long long longValue = ft_utilReadULong(array);
    return ft_utilULongToDouble(longValue);
}

unsigned long long ft_utilDoubleToULong(double value) {
    unsigned long long longValue;
    memcpy(&longValue, &value, sizeof(unsigned long long));
    return longValue;
}

double ft_utilULongToDouble(unsigned long long value) {
    double doubleValue;
    memcpy(&doubleValue, &value, sizeof(unsigned long long));
    return doubleValue;
}

void ft_utilPrintBytes(unsigned char *array, size_t arrayLength) {
    arrayLength = arrayLength < 170 ? arrayLength : 170;
    char string[arrayLength * 3];
    size_t i;

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
