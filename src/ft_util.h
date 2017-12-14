#ifndef FT_UTILS_H
#define FT_UTILS_H

extern const char HEX_VALUES[];

void ft_utilLogDebug(char *format, ...);
void ft_utilLogInfo(char *format, ...);
void ft_utilLogWarning(char *format, ...);
void ft_utilLogError(char *format, ...);
void ft_utilLog(char *label, char *message);

void ft_utilWriteUShort(unsigned short value, unsigned char *array);
void ft_utilWriteUInt(unsigned int value, unsigned char *array);
void ft_utilWriteUInt48(unsigned long long value, unsigned char *array);
void ft_utilWriteULong(unsigned long long value, unsigned char *array);
void ft_utilWriteDouble(double value, unsigned char *array);

unsigned short ft_utilReadUShort(unsigned char *array);
unsigned int ft_utilReadUInt(unsigned char *array);
unsigned long long ft_utilReadUInt48(unsigned char *array);
unsigned long long ft_utilReadULong(unsigned char *array);
double ft_utilReadDouble(unsigned char *array);

unsigned long long ft_utilDoubleToULong(double value);
double ft_utilULongToDouble(unsigned long long value);

void ft_utilPrintBytes(unsigned char *array, size_t arrayLength);

#endif // FT_UTILS_H
