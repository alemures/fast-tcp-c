#include <stdio.h>
#include <string.h>
#include "../lib/serializer.h"
#include "../lib/util.h"

int main(int argc, char *argv[]) {
    char *buffer = serializerSerialize("event", 5, "data", 4, MT_DATA, DT_STRING, 1);
    utilPrintBytes(buffer, serializerBufferLength(buffer));
    return 0;
}
