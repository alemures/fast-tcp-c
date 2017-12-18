#include <stdlib.h>
#include <string.h>
// In header: <stddef.h> <stdint.h>
#include "ft_serializer.h"
#include "ft_util.h"

const char FT_VERSION = 1;

const char FT_DT_STRING = 1;
const char FT_DT_BINARY = 2;
const char FT_DT_INTEGER = 3;
const char FT_DT_DECIMAL = 4;
const char FT_DT_OBJECT = 5;
const char FT_DT_BOOLEAN = 6;
const char FT_DT_EMPTY = 7;

const char FT_MT_ERROR = 0;
const char FT_MT_REGISTER = 1;
const char FT_MT_DATA = 2;
const char FT_MT_DATA_TO_SOCKET = 3;
const char FT_MT_DATA_TO_ROOM = 4;
const char FT_MT_DATA_BROADCAST = 5;
const char FT_MT_DATA_WITH_ACK = 6;
const char FT_MT_ACK = 7;
const char FT_MT_JOIN_ROOM = 8;
const char FT_MT_LEAVE_ROOM = 9;
const char FT_MT_LEAVE_ALL_ROOMS = 10;

unsigned char *ft_serializerSerialize(char *event, uint16_t eventLength, unsigned char *data, uint32_t dataLength, char mt, char dt, uint32_t messageId) {
    uint32_t messageLength = 8 + 2 + eventLength + 4 + dataLength;

    unsigned char *buffer = (unsigned char *) malloc(4 + messageLength);
    if (buffer == NULL) return NULL;
    unsigned char *bufferP = buffer;

    ft_utilWriteUint32(messageLength, bufferP);
    bufferP += 4;

    *(bufferP++) = FT_VERSION;
    *(bufferP++) = 0;
    *(bufferP++) = dt;
    *(bufferP++) = mt;

    ft_utilWriteUint32(messageId, bufferP);
    bufferP += 4;

    ft_utilWriteUint16(eventLength, bufferP);
    bufferP += 2;

    memcpy(bufferP, event, eventLength);
    bufferP += eventLength;

    ft_utilWriteUint32(dataLength, bufferP);
    bufferP += 4;

    memcpy(bufferP, data, dataLength);

    return buffer;
}

uint16_t ft_serializerDeserializeEventLength(unsigned char *buffer) {
    return ft_utilReadUint16(buffer + 12);
}

char *ft_serializerDeserializeEvent(unsigned char *buffer) {
    uint16_t eventLength = ft_serializerDeserializeEventLength(buffer);
    char *event = (char *) malloc(eventLength + 1);
    if (event == NULL) return NULL;
    memcpy(event, buffer + 14, eventLength);
    event[eventLength] = '\0';
    return event;
}

uint32_t ft_serializerDeserializeDataLength(unsigned char *buffer) {
    uint16_t eventLength = ft_serializerDeserializeEventLength(buffer);
    return ft_utilReadUint32(buffer + 14 + eventLength);
}

unsigned char *ft_serializerDeserializeDataBinary(unsigned char *buffer) {
    uint16_t eventLength = ft_serializerDeserializeEventLength(buffer);
    uint32_t dataLength = ft_serializerDeserializeDataLength(buffer);
    unsigned char *data = (unsigned char *) malloc(dataLength);
    if (data == NULL) return NULL;
    memcpy(data, buffer + 14 + eventLength + 4, dataLength);
    return data;
}

char *ft_serializerDeserializeDataString(unsigned char *buffer) {
    uint16_t eventLength = ft_serializerDeserializeEventLength(buffer);
    uint32_t dataLength = ft_serializerDeserializeDataLength(buffer);
    char *data = (char *) malloc(dataLength + 1);
    if (data == NULL) return NULL;
    memcpy(data, buffer + 14 + eventLength + 4, dataLength);
    data[dataLength] = '\0';
    return data;
}

uint64_t ft_serializerDeserializeDataInteger(unsigned char *buffer) {
    uint16_t eventLength = ft_serializerDeserializeEventLength(buffer);
    return ft_utilReadUint48(buffer + 14 + eventLength + 4);
}

double ft_serializerDeserializeDataDecimal(unsigned char *buffer) {
    uint16_t eventLength = ft_serializerDeserializeEventLength(buffer);
    return ft_utilReadDouble(buffer + 14 + eventLength + 4);
}

bool ft_serializerDeserializeDataBoolean(unsigned char *buffer) {
    uint16_t eventLength = ft_serializerDeserializeEventLength(buffer);
    return *(buffer + 14 + eventLength + 4) ? true : false;
}

char ft_serializerDeserializeMt(unsigned char *buffer) {
    return buffer[7];
}

char ft_serializerDeserializeDt(unsigned char *buffer) {
    return buffer[6];
}

uint32_t ft_serializerDeserializeMessageId(unsigned char *buffer) {
    return ft_utilReadUint32(buffer + 8);
}

uint32_t ft_serializerDeserializeMessageLength(unsigned char *buffer) {
    return ft_utilReadUint32(buffer);
}

size_t ft_serializerBufferLength(unsigned char *buffer) {
    return 4 + ft_utilReadUint32(buffer);
}
