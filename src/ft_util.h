#ifndef FT_UTILS_H
#define FT_UTILS_H

extern const char HEX_VALUES[];

void ft_utilLogDebug(char *format, ...);
void ft_utilLogInfo(char *format, ...);
void ft_utilLogWarning(char *format, ...);
void ft_utilLogError(char *format, ...);
void ft_utilLog(char *label, char *message);

void ft_utilWriteShort(short value, unsigned char *array);
void ft_utilWriteInt(int value, unsigned char *array);
void ft_utilWriteInt48(long long value, unsigned char *array);
void ft_utilWriteLong(long long value, unsigned char *array);
void ft_utilWriteDouble(double value, unsigned char *array);

short ft_utilReadShort(unsigned char *array);
int ft_utilReadInt(unsigned char *array);
long long ft_utilReadInt48(unsigned char *array);
long long ft_utilReadLong(unsigned char *array);
double ft_utilReadDouble(unsigned char *array);

long long ft_utilDoubleToLong(double value);
double ft_utilLongToDouble(long long value);

void ft_utilPrintBytes(unsigned char *array, int arrayLength);

#endif // FT_UTILS_H
