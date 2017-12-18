#ifndef FT_SERIALIZER_H
#define FT_SERIALIZER_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

extern const char FT_VERSION;

extern const char FT_DT_STRING;
extern const char FT_DT_BINARY;
extern const char FT_DT_INTEGER;
extern const char FT_DT_DECIMAL;
extern const char FT_DT_OBJECT;
extern const char FT_DT_BOOLEAN;
extern const char FT_DT_EMPTY;

extern const char FT_MT_ERROR;
extern const char FT_MT_REGISTER;
extern const char FT_MT_DATA;
extern const char FT_MT_DATA_TO_SOCKET;
extern const char FT_MT_DATA_TO_ROOM;
extern const char FT_MT_DATA_BROADCAST;
extern const char FT_MT_DATA_WITH_ACK;
extern const char FT_MT_ACK;
extern const char FT_MT_JOIN_ROOM;
extern const char FT_MT_LEAVE_ROOM;
extern const char FT_MT_LEAVE_ALL_ROOMS;

unsigned char *ft_serializerSerialize(char *event, uint16_t eventLength, unsigned char *data, uint32_t dataLength, char mt, char dt, uint32_t messageId);
uint16_t ft_serializerDeserializeEventLength(unsigned char *buffer);
char *ft_serializerDeserializeEvent(unsigned char *buffer);
uint32_t ft_serializerDeserializeDataLength(unsigned char *buffer);
unsigned char *ft_serializerDeserializeDataBinary(unsigned char *buffer);
char *ft_serializerDeserializeDataString(unsigned char *buffer);
uint64_t ft_serializerDeserializeDataInteger(unsigned char *buffer);
double ft_serializerDeserializeDataDecimal(unsigned char *buffer);
bool ft_serializerDeserializeDataBoolean(unsigned char *buffer);
char ft_serializerDeserializeMt(unsigned char *buffer);
char ft_serializerDeserializeDt(unsigned char *buffer);
uint32_t ft_serializerDeserializeMessageId(unsigned char *buffer);
uint32_t ft_serializerDeserializeMessageLength(unsigned char *buffer);

size_t ft_serializerBufferLength(unsigned char *buffer);

#endif // FT_SERIALIZER_H
