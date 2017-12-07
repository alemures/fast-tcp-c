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

unsigned char *ft_serializerSerialize(char *event, short eventLength, unsigned char *data, short dataLength, char mt, char dt, int messageId);
short ft_serializerDeserializeEventLength(unsigned char *buffer);
char *ft_serializerDeserializeEvent(unsigned char *buffer);
int ft_serializerDeserializeDataLength(unsigned char *buffer);
unsigned char *ft_serializerDeserializeDataAsBuffer(unsigned char *buffer);
char *ft_serializerDeserializeDataAsString(unsigned char *buffer);
long long ft_serializerDeserializeDataAsInt48(unsigned char *buffer);
double ft_serializerDeserializeDataAsDouble(unsigned char *buffer);
char ft_serializerDeserializeMt(unsigned char *buffer);
char ft_serializerDeserializeDt(unsigned char *buffer);
int ft_serializerDeserializeMessageId(unsigned char *buffer);
int ft_serializerDeserializeMessageLength(unsigned char *buffer);

int ft_serializerBufferLength(unsigned char *buffer);

#endif // FT_SERIALIZER_H
