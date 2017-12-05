#ifndef FT_UTILS_H
#define FT_UTILS_H

void FT_UtilLogDebug(char *message);
void FT_UtilLogInfo(char *message);
void FT_UtilLogWarning(char *message);
void FT_UtilLogError(char *message);
void FT_UtilLog(char *label, char *message);

void FT_UtilWriteShort(short value, unsigned char *array);
void FT_UtilWriteInt(int value, unsigned char *array);
void FT_UtilWriteInt48(long long value, unsigned char *array);
void FT_UtilWriteLong(long long value, unsigned char *array);
void FT_UtilWriteDouble(double value, unsigned char *array);

short FT_UtilReadShort(unsigned char *array);
int FT_UtilReadInt(unsigned char *array);
long long FT_UtilReadInt48(unsigned char *array);
long long FT_UtilReadLong(unsigned char *array);
double FT_UtilReadDouble(unsigned char *array);

long long FT_UtilDoubleToLong(double value);
double FT_UtilLongToDouble(long long value);

void FT_UtilPrintBytes(char *array, int arrayLength);

#endif // FT_UTILS_H
