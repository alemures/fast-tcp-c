#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "serializer.h"
#include "util.h"

const char VERSION = 1;

const char DT_STRING = 1;
const char DT_BUFFER = 2;
const char DT_INT = 3;
const char DT_DOUBLE = 4;
const char DT_OBJECT = 5;

const char MT_REGISTER = 1;
const char MT_DATA = 2;
const char MT_DATA_TO_SOCKET = 3;
const char MT_DATA_TO_ROOM = 4;
const char MT_DATA_BROADCAST = 5;
const char MT_DATA_WITH_ACK = 6;
const char MT_ACK = 7;
const char MT_JOIN_ROOM = 8;
const char MT_LEAVE_ROOM = 9;
const char MT_LEAVE_ALL_ROOMS = 10;

unsigned char *serializerSerialize(char *event, short eventLength, unsigned char *data, short dataLength, char mt, char dt, int messageId) {
    int messageLength = 8 + 2 + eventLength + 4 + dataLength;

    unsigned char *buffer = (unsigned char *) malloc(sizeof(unsigned char) * (4 + messageLength));
    unsigned char *bufferP = buffer;

    utilWriteInt(messageLength, bufferP);
    bufferP += 4;

    *(bufferP++) = VERSION;
    *(bufferP++) = 0;
    *(bufferP++) = dt;
    *(bufferP++) = mt;

    utilWriteInt(messageId, bufferP);
    bufferP += 4;

    utilWriteShort(eventLength, bufferP);
    bufferP += 2;

    memcpy(bufferP, event, eventLength);
    bufferP += eventLength;

    utilWriteInt(dataLength, bufferP);
    bufferP += 4;

    memcpy(bufferP, data, dataLength);

    return buffer;
}

short serializerDeserializeEventLength(unsigned char *buffer) {
    return utilReadShort(buffer + 12);
}

char *serializerDeserializeEvent(unsigned char *buffer) {
    short eventLength = serializerDeserializeEventLength(buffer);
    char *event = (char *) malloc(sizeof(char) * eventLength + 1);
    memcpy(event, buffer + 14, eventLength);
    event[eventLength] = '\0';
    return event;
}

int serializerDeserializeDataLength(unsigned char *buffer) {
    short eventLength = serializerDeserializeEventLength(buffer);
    return utilReadInt(buffer + 14 + eventLength);
}

unsigned char *serializerDeserializeDataAsBuffer(unsigned char *buffer) {
    short eventLength = serializerDeserializeEventLength(buffer);
    int dataLength = serializerDeserializeDataLength(buffer);
    unsigned char *data = (unsigned char *) malloc(sizeof(unsigned char) * dataLength);
    memcpy(data, buffer + 14 + eventLength + 4, dataLength);
    return data;
}

char *serializerDeserializeDataAsString(unsigned char *buffer) {
    short eventLength = serializerDeserializeEventLength(buffer);
    int dataLength = serializerDeserializeDataLength(buffer);
    char *data = (char *) malloc(sizeof(char) * (dataLength + 1));
    memcpy(data, buffer + 14 + eventLength + 4, dataLength);
    data[dataLength] = '\0';
    return data;
}

long serializerDeserializeDataAsInt48(unsigned char *buffer) {
    short eventLength = serializerDeserializeEventLength(buffer);
    return utilReadInt48(buffer + 14 + eventLength + 4);
}

char serializerDeserializeMt(unsigned char *buffer) {
    return buffer[7];
}

char serializerDeserializeDt(unsigned char *buffer) {
    return buffer[6];
}

int serializerDeserializeMessageId(unsigned char *buffer) {
    return utilReadInt(buffer + 8);
}

int serializerDeserializeMessageLength(unsigned char *buffer) {
    return utilReadInt(buffer);
}

int serializerBufferLength(unsigned char *buffer) {
    return 4 + utilReadInt(buffer);
}

