#ifndef FT_UTILS_H
#define FT_UTILS_H

#include <stdint.h>

extern const char HEX_VALUES[];

void ft_utilLogDebug(char *format, ...);
void ft_utilLogInfo(char *format, ...);
void ft_utilLogWarning(char *format, ...);
void ft_utilLogError(char *format, ...);
void ft_utilLog(char *label, char *message);

void ft_utilWriteUint16(uint16_t value, unsigned char *array);
void ft_utilWriteUint32(uint32_t value, unsigned char *array);
void ft_utilWriteUint48(uint64_t value, unsigned char *array);
void ft_utilWriteUint64(uint64_t value, unsigned char *array);
void ft_utilWriteDouble(double value, unsigned char *array);

uint16_t ft_utilReadUint16(unsigned char *array);
uint32_t ft_utilReadUint32(unsigned char *array);
uint64_t ft_utilReadUint48(unsigned char *array);
uint64_t ft_utilReadUint64(unsigned char *array);
double ft_utilReadDouble(unsigned char *array);

uint64_t ft_utilDoubleToUint64(double value);
double ft_utilUint64ToDouble(uint64_t value);

void ft_utilPrintBytes(unsigned char *array, size_t arrayLength);

#endif // FT_UTILS_H
