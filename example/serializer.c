#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/serializer.h"
#include "../lib/util.h"

int main(int argc, char *argv[]) {
    unsigned char number[8];
    utilWriteDouble(21.1, number);

    unsigned char *buffer = serializerSerialize("The event", 9, number, 8, MT_DATA, DT_DOUBLE, 1);
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
        printf("data: %lld -> ", serializerDeserializeDataAsInt48(buffer));
    } else if (serializerDeserializeDt(buffer) == DT_DOUBLE) {
        printf("data: %f -> ", serializerDeserializeDataAsDouble(buffer));
    }

    char *data = serializerDeserializeDataAsBuffer(buffer);
    utilPrintBytes(data, serializerDeserializeDataLength(buffer));
    free(data);

    free(buffer);

    return 0;
}
