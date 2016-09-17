#ifndef UTILS_H
#define UTILS_H 1

void utilLogDebug(char *message);
void utilLogInfo(char *message);
void utilLogWarning(char *message);
void utilLogError(char *message);
void utilLog(char *label, char *message);

void utilWriteShort(short value, unsigned char *array);
void utilWriteInt(int value, unsigned char *array);
void utilWriteInt48(long long value, unsigned char *array);
void utilWriteLong(long long value, unsigned char *array);
void utilWriteDouble(double value, unsigned char *array);

short utilReadShort(unsigned char *array);
int utilReadInt(unsigned char *array);
long long utilReadInt48(unsigned char *array);
long long utilReadLong(unsigned char *array);
double utilReadDouble(unsigned char *array);

long long utilDoubleToLong(double value);
double utilLongToDouble(long long value);

void utilPrintBytes(char *array, int arrayLength);

#endif
