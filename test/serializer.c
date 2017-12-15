#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../src/ft_serializer.h"
#include "../src/ft_util.h"

int main(int argc, char *argv[]) {
    unsigned char decimal[8];
    ft_utilWriteDouble(21.1, decimal);

    unsigned char integer[6];
    ft_utilWriteUInt48(125, integer);

    char text[] = "Hello, World!";

    unsigned char boolean[1] = {1};

    unsigned char *buffer = ft_serializerSerialize("The event", 9, decimal, 8, FT_MT_DATA, FT_DT_DECIMAL, 1);
    // unsigned char *buffer = ft_serializerSerialize("The event", 9, integer, 6, FT_MT_DATA, FT_DT_INT, 1);
    // unsigned char *buffer = ft_serializerSerialize("The event", 9, text, strlen(text), FT_MT_DATA, FT_DT_STRING, 1);
    // unsigned char *buffer = ft_serializerSerialize("The event", 9, boolean, 1, FT_MT_DATA, FT_DT_BOOLEAN, 1);
    // unsigned char *buffer = ft_serializerSerialize("The event", 9, NULL, 0, FT_MT_DATA, FT_DT_EMPTY, 1);
    printf("MESSAGE: ");
    ft_utilPrintBytes(buffer, ft_serializerBufferLength(buffer));

    printf("dt: %d\n", ft_serializerDeserializeDt(buffer));
    printf("mt: %d\n", ft_serializerDeserializeMt(buffer));
    printf("messageId: %d\n", ft_serializerDeserializeMessageId(buffer));

    char *event = ft_serializerDeserializeEvent(buffer);
    printf("event: \"%s\" -> ", event);
    ft_utilPrintBytes((unsigned char *)event, ft_serializerDeserializeEventLength(buffer));
    free(event);

    if (ft_serializerDeserializeDt(buffer) == FT_DT_STRING) {
        char *data = ft_serializerDeserializeDataString(buffer);
        printf("data: \"%s\" -> ", data);
        free(data);
    } else if (ft_serializerDeserializeDt(buffer) == FT_DT_INTEGER) {
        printf("data: %lld -> ", ft_serializerDeserializeDataInteger(buffer));
    } else if (ft_serializerDeserializeDt(buffer) == FT_DT_DECIMAL) {
        printf("data: %f -> ", ft_serializerDeserializeDataDecimal(buffer));
    } else if (ft_serializerDeserializeDt(buffer) == FT_DT_BOOLEAN) {
        printf("data: %s -> ", ft_serializerDeserializeDataBoolean(buffer) ? "true" : "false");
    } else if (ft_serializerDeserializeDt(buffer) == FT_DT_EMPTY) {
        printf("data: <empty> -> ");
    }

    unsigned char *data = ft_serializerDeserializeDataBinary(buffer);
    ft_utilPrintBytes(data, ft_serializerDeserializeDataLength(buffer));
    free(data);

    free(buffer);

    return 0;
}
