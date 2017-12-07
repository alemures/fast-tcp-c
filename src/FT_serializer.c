#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "FT_serializer.h"
#include "FT_util.h"

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

unsigned char *FT_SerializerSerialize(char *event, short eventLength, unsigned char *data, short dataLength, char mt, char dt, int messageId) {
    int messageLength = 8 + 2 + eventLength + 4 + dataLength;

    unsigned char *buffer = (unsigned char *) malloc(sizeof(unsigned char) * (4 + messageLength));
    if (buffer == NULL) return NULL;
    unsigned char *bufferP = buffer;

    FT_UtilWriteInt(messageLength, bufferP);
    bufferP += 4;

    *(bufferP++) = VERSION;
    *(bufferP++) = 0;
    *(bufferP++) = dt;
    *(bufferP++) = mt;

    FT_UtilWriteInt(messageId, bufferP);
    bufferP += 4;

    FT_UtilWriteShort(eventLength, bufferP);
    bufferP += 2;

    memcpy(bufferP, event, eventLength);
    bufferP += eventLength;

    FT_UtilWriteInt(dataLength, bufferP);
    bufferP += 4;

    memcpy(bufferP, data, dataLength);

    return buffer;
}

short FT_SerializerDeserializeEventLength(unsigned char *buffer) {
    return FT_UtilReadShort(buffer + 12);
}

char *FT_SerializerDeserializeEvent(unsigned char *buffer) {
    short eventLength = FT_SerializerDeserializeEventLength(buffer);
    char *event = (char *) malloc(sizeof(char) * eventLength + 1);
    if (event == NULL) return NULL;
    memcpy(event, buffer + 14, eventLength);
    event[eventLength] = '\0';
    return event;
}

int FT_SerializerDeserializeDataLength(unsigned char *buffer) {
    short eventLength = FT_SerializerDeserializeEventLength(buffer);
    return FT_UtilReadInt(buffer + 14 + eventLength);
}

unsigned char *FT_SerializerDeserializeDataAsBuffer(unsigned char *buffer) {
    short eventLength = FT_SerializerDeserializeEventLength(buffer);
    int dataLength = FT_SerializerDeserializeDataLength(buffer);
    unsigned char *data = (unsigned char *) malloc(sizeof(unsigned char) * dataLength);
    if (data == NULL) return NULL;
    memcpy(data, buffer + 14 + eventLength + 4, dataLength);
    return data;
}

char *FT_SerializerDeserializeDataAsString(unsigned char *buffer) {
    short eventLength = FT_SerializerDeserializeEventLength(buffer);
    int dataLength = FT_SerializerDeserializeDataLength(buffer);
    char *data = (char *) malloc(sizeof(char) * (dataLength + 1));
    if (data == NULL) return NULL;
    memcpy(data, buffer + 14 + eventLength + 4, dataLength);
    data[dataLength] = '\0';
    return data;
}

long long FT_SerializerDeserializeDataAsInt48(unsigned char *buffer) {
    short eventLength = FT_SerializerDeserializeEventLength(buffer);
    return FT_UtilReadInt48(buffer + 14 + eventLength + 4);
}

double FT_SerializerDeserializeDataAsDouble(unsigned char *buffer) {
    short eventLength = FT_SerializerDeserializeEventLength(buffer);
    return FT_UtilReadDouble(buffer + 14 + eventLength + 4);
}

char FT_SerializerDeserializeMt(unsigned char *buffer) {
    return buffer[7];
}

char FT_SerializerDeserializeDt(unsigned char *buffer) {
    return buffer[6];
}

int FT_SerializerDeserializeMessageId(unsigned char *buffer) {
    return FT_UtilReadInt(buffer + 8);
}

int FT_SerializerDeserializeMessageLength(unsigned char *buffer) {
    return FT_UtilReadInt(buffer);
}

int FT_SerializerBufferLength(unsigned char *buffer) {
    return 4 + FT_UtilReadInt(buffer);
}

