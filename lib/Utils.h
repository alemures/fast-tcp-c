#ifndef UTILS_H
#define UTILS_H 1

void logDebug(char *message);
void logInfo(char *message);
void logWarning(char *message);
void logError(char *message);
void print(char *label, char *message);

void writeInt(int value, char *buffer, int offset);
void writeShort(short value, char *buffer, int offset);
void printByteArray(char *array, int arrayLength);

#endif
