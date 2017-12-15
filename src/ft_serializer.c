#include <stdlib.h>
#include <string.h>
// In header: <stddef.h>
#include "ft_serializer.h"
#include "ft_util.h"

const char FT_VERSION = 1;

const char FT_DT_STRING = 1;
const char FT_DT_BUFFER = 2;
const char FT_DT_INT = 3;
const char FT_DT_DOUBLE = 4;
const char FT_DT_OBJECT = 5;

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

unsigned char *ft_serializerSerialize(char *event, unsigned short eventLength, unsigned char *data, unsigned int dataLength, char mt, char dt, unsigned int messageId) {
    unsigned int messageLength = 8 + 2 + eventLength + 4 + dataLength;

    unsigned char *buffer = (unsigned char *) malloc(4 + messageLength);
    if (buffer == NULL) return NULL;
    unsigned char *bufferP = buffer;

    ft_utilWriteUInt(messageLength, bufferP);
    bufferP += 4;

    *(bufferP++) = FT_VERSION;
    *(bufferP++) = 0;
    *(bufferP++) = dt;
    *(bufferP++) = mt;

    ft_utilWriteUInt(messageId, bufferP);
    bufferP += 4;

    ft_utilWriteUShort(eventLength, bufferP);
    bufferP += 2;

    memcpy(bufferP, event, eventLength);
    bufferP += eventLength;

    ft_utilWriteUInt(dataLength, bufferP);
    bufferP += 4;

    memcpy(bufferP, data, dataLength);

    return buffer;
}

unsigned short ft_serializerDeserializeEventLength(unsigned char *buffer) {
    return ft_utilReadUShort(buffer + 12);
}

char *ft_serializerDeserializeEvent(unsigned char *buffer) {
    unsigned short eventLength = ft_serializerDeserializeEventLength(buffer);
    char *event = (char *) malloc(eventLength + 1);
    if (event == NULL) return NULL;
    memcpy(event, buffer + 14, eventLength);
    event[eventLength] = '\0';
    return event;
}

unsigned int ft_serializerDeserializeDataLength(unsigned char *buffer) {
    unsigned short eventLength = ft_serializerDeserializeEventLength(buffer);
    return ft_utilReadUInt(buffer + 14 + eventLength);
}

unsigned char *ft_serializerDeserializeDataAsBuffer(unsigned char *buffer) {
    unsigned short eventLength = ft_serializerDeserializeEventLength(buffer);
    unsigned int dataLength = ft_serializerDeserializeDataLength(buffer);
    unsigned char *data = (unsigned char *) malloc(dataLength);
    if (data == NULL) return NULL;
    memcpy(data, buffer + 14 + eventLength + 4, dataLength);
    return data;
}

char *ft_serializerDeserializeDataAsString(unsigned char *buffer) {
    unsigned short eventLength = ft_serializerDeserializeEventLength(buffer);
    unsigned int dataLength = ft_serializerDeserializeDataLength(buffer);
    char *data = (char *) malloc(dataLength + 1);
    if (data == NULL) return NULL;
    memcpy(data, buffer + 14 + eventLength + 4, dataLength);
    data[dataLength] = '\0';
    return data;
}

long long ft_serializerDeserializeDataAsInt48(unsigned char *buffer) {
    unsigned short eventLength = ft_serializerDeserializeEventLength(buffer);
    return ft_utilReadUInt48(buffer + 14 + eventLength + 4);
}

double ft_serializerDeserializeDataAsDouble(unsigned char *buffer) {
    unsigned short eventLength = ft_serializerDeserializeEventLength(buffer);
    return ft_utilReadDouble(buffer + 14 + eventLength + 4);
}

char ft_serializerDeserializeMt(unsigned char *buffer) {
    return buffer[7];
}

char ft_serializerDeserializeDt(unsigned char *buffer) {
    return buffer[6];
}

unsigned int ft_serializerDeserializeMessageId(unsigned char *buffer) {
    return ft_utilReadUInt(buffer + 8);
}

unsigned int ft_serializerDeserializeMessageLength(unsigned char *buffer) {
    return ft_utilReadUInt(buffer);
}

size_t ft_serializerBufferLength(unsigned char *buffer) {
    return 4 + ft_utilReadUInt(buffer);
}

