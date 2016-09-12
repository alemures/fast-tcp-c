#include <stdlib.h>
#include <string.h>
#include "Serializer.h"
#include "Message.h"
#include "Utils.h"

char *serialize(char *event, short eventLength, char *data, short dataLength, char mt, char dt, unsigned int messageId) {
    int messageLength = 8 + 2 + eventLength + 4 + dataLength;

    char *buffer = (char *) malloc(4 + messageLength);
    int offset = 0;

    writeInt(messageLength, buffer, offset);
    offset += 4;

    buffer[offset++] = VERSION;
    buffer[offset++] = 0;
    buffer[offset++] = dt;
    buffer[offset++] = mt;

    writeInt(messageId, buffer, offset);
    offset += 4;

    writeShort(eventLength, buffer, offset);
    offset += 2;

    memcpy(buffer + offset, event, eventLength);
    offset += eventLength;

    writeInt(dataLength, buffer, offset);
    offset += 4;

    memcpy(buffer + offset, data, dataLength);

    return buffer;
}

struct Message *deserialize(char *buffer) {

}
