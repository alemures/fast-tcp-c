#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/serializer.h"
#include "../lib/util.h"

int main(int argc, char *argv[]) {
    char number[6];
    utilWriteInt48(50000000, number);

    char *buffer = serializerSerialize("The event", 9, number, 6, MT_DATA, DT_INT, 1);
    utilPrintBytes(buffer, serializerBufferLength(buffer));

    printf("dt: %d\n", serializerDeserializeDt(buffer));
    printf("mt: %d\n", serializerDeserializeMt(buffer));
    printf("messageId: %d\n", serializerDeserializeMessageId(buffer));
    printf("event: \"%s\" -> ", serializerDeserializeEvent(buffer));
    utilPrintBytes(serializerDeserializeEvent(buffer), serializerDeserializeEventLength(buffer));

    if (serializerDeserializeDt(buffer) == DT_STRING) {
        printf("data: \"%s\" -> ", serializerDeserializeDataAsString(buffer));
    } else if (serializerDeserializeDt(buffer) == DT_INT) {
        printf("data: %ld -> ", serializerDeserializeDataAsInt48(buffer));
    }

    utilPrintBytes(serializerDeserializeDataAsBuffer(buffer), serializerDeserializeDataLength(buffer));

    return 0;
}
