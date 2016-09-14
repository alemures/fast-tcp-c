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

unsigned char *serializerSerialize(char *event, short eventLength, unsigned char *data, short dataLength, char mt, char dt, int messageId);
short serializerDeserializeEventLength(unsigned char *buffer);
char *serializerDeserializeEvent(unsigned char *buffer);
int serializerDeserializeDataLength(unsigned char *buffer);
unsigned char *serializerDeserializeDataAsBuffer(unsigned char *buffer);
char *serializerDeserializeDataAsString(unsigned char *buffer);
long  serializerDeserializeDataAsInt48(unsigned char *buffer);
char serializerDeserializeMt(unsigned char *buffer);
char serializerDeserializeDt(unsigned char *buffer);
int serializerDeserializeMessageId(unsigned char *buffer);
int serializerDeserializeMessageLength(unsigned char *buffer);

int serializerBufferLength(unsigned char *buffer);

#endif
