#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
// In header: <stdint.h>
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

void ft_utilWriteUint16(uint16_t value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
}

void ft_utilWriteUint32(uint32_t value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
    array[2] = value >> 16;
    array[3] = value >> 24;
}

void ft_utilWriteUint48(uint64_t value, unsigned char *array) {
    array[0] = value;
    array[1] = value >> 8;
    array[2] = value >> 16;
    array[3] = value >> 24;
    array[4] = value >> 32;
    array[5] = value >> 40;
}

void ft_utilWriteUint64(uint64_t value, unsigned char *array) {
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
    uint64_t longValue = ft_utilDoubleToUint64(value);
    ft_utilWriteUint64(longValue, array);
}

uint16_t ft_utilReadUint16(unsigned char *array) {
    return array[0] |
            array[1] << 8;
}

uint32_t ft_utilReadUint32(unsigned char *array) {
    return array[0] |
            array[1] << 8 |
            array[2] << 16 |
            array[3] << 24;
}

uint64_t ft_utilReadUint48(unsigned char *array) {
    return array[0] |
            array[1] << 8 |
            array[2] << 16 |
            (uint64_t)array[3] << 24 |
            (uint64_t)array[4] << 32 |
            (uint64_t)array[5] << 40;
}

uint64_t ft_utilReadUint64(unsigned char *array) {
    return array[0] |
            array[1] << 8 |
            array[2] << 16 |
            (uint64_t)array[3] << 24 |
            (uint64_t)array[4] << 32 |
            (uint64_t)array[5] << 40 |
            (uint64_t)array[6] << 48 |
            (uint64_t)array[7] << 56;
}

double ft_utilReadDouble(unsigned char *array) {
    uint64_t longValue = ft_utilReadUint64(array);
    return ft_utilUint64ToDouble(longValue);
}

uint64_t ft_utilDoubleToUint64(double value) {
    uint64_t intValue;
    memcpy(&intValue, &value, sizeof(uint64_t));
    return intValue;
}

double ft_utilUint64ToDouble(uint64_t value) {
    double doubleValue;
    memcpy(&doubleValue, &value, sizeof(double));
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
