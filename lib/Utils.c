#include <stdio.h>
#include "Utils.h"

void logDebug(char *message) {
    print("[DEBUG]", message);
}

void logInfo(char *message) {
    print("[INFO]", message);
}

void logWarning(char *message) {
   print("[WARNING]", message);
}

void logError(char *message) {
    print("[ERROR]", message);
}

void print(char *label, char *message) {
    printf("%s %s\n", label, message);
}
