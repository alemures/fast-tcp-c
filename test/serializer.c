#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/FT_serializer.h"
#include "../src/FT_util.h"

int main(int argc, char *argv[]) {
    unsigned char number[8];
    FT_UtilWriteDouble(21.1, number);

    unsigned char *buffer = FT_SerializerSerialize("The event", 9, number, 8, MT_DATA, DT_DOUBLE, 1);
    FT_UtilPrintBytes(buffer, FT_SerializerBufferLength(buffer));

    printf("dt: %d\n", FT_SerializerDeserializeDt(buffer));
    printf("mt: %d\n", FT_SerializerDeserializeMt(buffer));
    printf("messageId: %d\n", FT_SerializerDeserializeMessageId(buffer));

    char *event = FT_SerializerDeserializeEvent(buffer);
    printf("event: \"%s\" -> ", event);
    FT_UtilPrintBytes(event, FT_SerializerDeserializeEventLength(buffer));
    free(event);

    if (FT_SerializerDeserializeDt(buffer) == DT_STRING) {
        char *data = FT_SerializerDeserializeDataAsString(buffer);
        printf("data: \"%s\" -> ", data);
        free(data);
    } else if (FT_SerializerDeserializeDt(buffer) == DT_INT) {
        printf("data: %lld -> ", FT_SerializerDeserializeDataAsInt48(buffer));
    } else if (FT_SerializerDeserializeDt(buffer) == DT_DOUBLE) {
        printf("data: %f -> ", FT_SerializerDeserializeDataAsDouble(buffer));
    }

    char *data = FT_SerializerDeserializeDataAsBuffer(buffer);
    FT_UtilPrintBytes(data, FT_SerializerDeserializeDataLength(buffer));
    free(data);

    free(buffer);

    return 0;
}
