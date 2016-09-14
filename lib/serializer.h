#ifndef SERIALIZER_H
#define SERIALIZER_H 1

extern const char VERSION;

extern const char DT_STRING;
extern const char DT_BUFFER;
extern const char DT_INT;
extern const char DT_DOUBLE;
extern const char DT_OBJECT;

extern const char MT_REGISTER;
extern const char MT_DATA;
extern const char MT_DATA_TO_SOCKET;
extern const char MT_DATA_TO_ROOM;
extern const char MT_DATA_BROADCAST;
extern const char MT_DATA_WITH_ACK;
extern const char MT_ACK;
extern const char MT_JOIN_ROOM;
extern const char MT_LEAVE_ROOM;
extern const char MT_LEAVE_ALL_ROOMS;

char *serializerSerialize(char *event, short eventLength, char *data, short dataLength, char mt, char dt, int messageId);
short serializerDeserializeEventLength(char *buffer);
char *serializerDeserializeEvent(char *buffer);
int serializerDeserializeDataLength(char *buffer);
char *serializerDeserializeDataAsBuffer(char *buffer);
char *serializerDeserializeDataAsString(char *buffer);
long  serializerDeserializeDataAsInt48(char *buffer);
double serializerDeserializeDataAsDouble(char *buffer);
char serializerDeserializeMt(char *buffer);
char serializerDeserializeDt(char *buffer);
int serializerDeserializeMessageId(char *buffer);
int serializerDeserializeMessageLength(char *buffer);

int serializerBufferLength(char *buffer);

#endif
