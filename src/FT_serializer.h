#ifndef FT_SERIALIZER_H
#define FT_SERIALIZER_H

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

unsigned char *FT_SerializerSerialize(char *event, short eventLength, unsigned char *data, short dataLength, char mt, char dt, int messageId);
short FT_SerializerDeserializeEventLength(unsigned char *buffer);
char *FT_SerializerDeserializeEvent(unsigned char *buffer);
int FT_SerializerDeserializeDataLength(unsigned char *buffer);
unsigned char *FT_SerializerDeserializeDataAsBuffer(unsigned char *buffer);
char *FT_SerializerDeserializeDataAsString(unsigned char *buffer);
long long FT_SerializerDeserializeDataAsInt48(unsigned char *buffer);
double FT_SerializerDeserializeDataAsDouble(unsigned char *buffer);
char FT_SerializerDeserializeMt(unsigned char *buffer);
char FT_SerializerDeserializeDt(unsigned char *buffer);
int FT_SerializerDeserializeMessageId(unsigned char *buffer);
int FT_SerializerDeserializeMessageLength(unsigned char *buffer);

int FT_SerializerBufferLength(unsigned char *buffer);

#endif /* FT_SERIALIZER_H */
