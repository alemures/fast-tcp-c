#ifndef SERIALIZER_H
#define SERIALIZER_H 1

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

char *serialize(char *event, short eventLength, char *data, short dataLength, char mt, char dt, unsigned int messageId);

#endif
