#ifndef UTILS_H
#define UTILS_H 1

void utilLogDebug(char *message);
void utilLogInfo(char *message);
void utilLogWarning(char *message);
void utilLogError(char *message);
void utilLog(char *label, char *message);

void utilWriteInt(int value, char *array);
void utilWriteShort(short value, char *array);
int utilReadInt(char *array);
void utilPrintBytes(char *array, int arrayLength);

#endif
