#include <stdlib.h>
#include <string.h>
#include "ft_reader.h"
#include "ft_util.h"

struct ft_reader *ft_readerCreate() {
    struct ft_reader *reader = (struct ft_reader *) malloc(sizeof(struct ft_reader));
    if (reader == NULL) return NULL;
    reader->buffer = NULL;
    return reader;
}

// TODO: Return variable length array of buffers (length is also necessary)
unsigned char *ft_readerRead(struct ft_reader *reader, unsigned char *chunk, int effectiveChunkLength) {
    reader->offsetChunk = 0;
    unsigned char **buffers = (unsigned char **) malloc(1);

    while(reader->offsetChunk < effectiveChunkLength) {
        if (reader->bytesRead < 4) {
            if (ft_readerReadMessageLength(reader, chunk, effectiveChunkLength)) {
                ft_readerCreateBuffer(reader);
            } else {
                break;
            }
        }

        if (reader->bytesRead < reader->bufferLength && !ft_readerReadMessageContent(reader, chunk, effectiveChunkLength)) {
            break;
        }

        // Buffer ready, store it and keep reading the chunk
        buffers[0] = reader->buffer;
        reader->bufferLength = 0;
        reader->offset = 0;
        reader->bytesRead = 0;
        reader->messageLength = 0;
    }

    return buffers[0];
}

bool ft_readerReadMessageLength(struct ft_reader *reader, unsigned char *chunk, int effectiveChunkLength) {
    for (; reader->offsetChunk < effectiveChunkLength && reader->bytesRead < 4; reader->offsetChunk++, reader->bytesRead++) {
        reader->messageLength |= chunk[reader->offsetChunk] << (reader->bytesRead * 8);
    }

    return reader->bytesRead == 4;
}

bool ft_readerReadMessageContent(struct ft_reader *reader, unsigned char *chunk, int effectiveChunkLength) {
    int bytesToRead = reader->bufferLength - reader->bytesRead;
    int bytesInChunk = effectiveChunkLength - reader->offsetChunk;
    int end = bytesToRead > bytesInChunk ? effectiveChunkLength : reader->offsetChunk + bytesToRead;

    memcpy(reader->buffer + reader->offset, chunk + reader->offsetChunk, end - reader->offsetChunk);

    int bytesActuallyRead = end - reader->offsetChunk;

    reader->bytesRead += bytesActuallyRead;
    reader->offset += bytesActuallyRead;
    reader->offsetChunk = end;

    return reader->bytesRead == reader->bufferLength;
}

void ft_readerCreateBuffer(struct ft_reader *reader) {
    reader->bufferLength = 4 + reader->messageLength;
    reader->buffer = (unsigned char *) malloc(reader->bufferLength);
    ft_utilWriteInt(reader->messageLength, reader->buffer);
    reader->offset += 4;
}

void ft_readerDestroy(struct ft_reader *reader) {
    if (reader->buffer != NULL) {
        free(reader->buffer);
    }
    free(reader);
}
