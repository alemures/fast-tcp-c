#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/ft_serializer.h"
#include "../src/ft_util.h"

int main(int argc, char *argv[]) {
    unsigned char number[8];
    ft_utilWriteDouble(21.1, number);

    unsigned char *buffer = ft_serializerSerialize("The event", 9, number, 8, MT_DATA, DT_DOUBLE, 1);
    ft_utilPrintBytes(buffer, ft_serializerBufferLength(buffer));

    printf("dt: %d\n", ft_serializerDeserializeDt(buffer));
    printf("mt: %d\n", ft_serializerDeserializeMt(buffer));
    printf("messageId: %d\n", ft_serializerDeserializeMessageId(buffer));

    char *event = ft_serializerDeserializeEvent(buffer);
    printf("event: \"%s\" -> ", event);
    ft_utilPrintBytes(event, ft_serializerDeserializeEventLength(buffer));
    free(event);

    if (ft_serializerDeserializeDt(buffer) == DT_STRING) {
        char *data = ft_serializerDeserializeDataAsString(buffer);
        printf("data: \"%s\" -> ", data);
        free(data);
    } else if (ft_serializerDeserializeDt(buffer) == DT_INT) {
        printf("data: %lld -> ", ft_serializerDeserializeDataAsInt48(buffer));
    } else if (ft_serializerDeserializeDt(buffer) == DT_DOUBLE) {
        printf("data: %f -> ", ft_serializerDeserializeDataAsDouble(buffer));
    }

    char *data = ft_serializerDeserializeDataAsBuffer(buffer);
    ft_utilPrintBytes(data, ft_serializerDeserializeDataLength(buffer));
    free(data);

    free(buffer);

    return 0;
}
