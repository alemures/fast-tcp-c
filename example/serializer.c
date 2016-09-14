#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/serializer.h"
#include "../lib/util.h"

int main(int argc, char *argv[]) {
    unsigned char number[6];
    utilWriteInt48(50000000, number);

    unsigned char *buffer = serializerSerialize("The event", 9, number, 6, MT_DATA, DT_INT, 1);
    utilPrintBytes(buffer, serializerBufferLength(buffer));

    printf("dt: %d\n", serializerDeserializeDt(buffer));
    printf("mt: %d\n", serializerDeserializeMt(buffer));
    printf("messageId: %d\n", serializerDeserializeMessageId(buffer));

    char *event = serializerDeserializeEvent(buffer);
    printf("event: \"%s\" -> ", event);
    utilPrintBytes(event, serializerDeserializeEventLength(buffer));
    free(event);

    if (serializerDeserializeDt(buffer) == DT_STRING) {
        char *data = serializerDeserializeDataAsString(buffer);
        printf("data: \"%s\" -> ", data);
        free(data);
    } else if (serializerDeserializeDt(buffer) == DT_INT) {
        printf("data: %ld -> ", serializerDeserializeDataAsInt48(buffer));
    }

    char *data = serializerDeserializeDataAsBuffer(buffer);
    utilPrintBytes(data, serializerDeserializeDataLength(buffer));
    free(data);

    free(buffer);

    return 0;
}
