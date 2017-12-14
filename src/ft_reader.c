#include <stdlib.h>
#include <string.h>
// In header file: <stddef.h> <stdbool.h>
#include "ft_reader.h"
#include "ft_util.h"

struct ft_reader *ft_readerCreate() {
    struct ft_reader *reader = (struct ft_reader *) malloc(sizeof(struct ft_reader));
    if (reader == NULL) return NULL;
    reader->buffer = NULL;
    reader->bufferLength = 0;
    reader->offset = 0;
    reader->bytesRead = 0;
    reader->messageLength = 0;
    reader->offsetChunk = 0;
    return reader;
}

int ft_readerRead(struct ft_reader *reader, unsigned char *chunk, size_t effectiveChunkLength, unsigned char **buffers) {
    int buffersRead = 0;
    reader->offsetChunk = 0;

    while(reader->offsetChunk < effectiveChunkLength) {
        if (reader->bytesRead < 4) {
            if (ft_readerReadMessageLength(reader, chunk, effectiveChunkLength)) {
                ft_readerCreateBuffer(reader);
                if (reader->buffer == NULL) {
                    reader->offset = 0;
                    reader->bytesRead = 0;
                    reader->messageLength = 0;
                    return -1;
                }
            } else {
                break;
            }
        }

        if (reader->bytesRead < reader->bufferLength && !ft_readerReadMessageContent(reader, chunk, effectiveChunkLength)) {
            break;
        }

        // Buffer ready, store it and keep reading the chunk
        buffers[buffersRead++] = reader->buffer;
        reader->buffer = NULL;
        reader->offset = 0;
        reader->bytesRead = 0;
        reader->messageLength = 0;
    }

    return buffersRead;
}

bool ft_readerReadMessageLength(struct ft_reader *reader, unsigned char *chunk, size_t effectiveChunkLength) {
    for (; reader->offsetChunk < effectiveChunkLength && reader->bytesRead < 4; reader->offsetChunk++, reader->bytesRead++) {
        reader->messageLength |= chunk[reader->offsetChunk] << (reader->bytesRead * 8);
    }

    return reader->bytesRead == 4;
}

bool ft_readerReadMessageContent(struct ft_reader *reader, unsigned char *chunk, size_t effectiveChunkLength) {
    size_t bytesToRead = reader->bufferLength - reader->bytesRead;
    size_t bytesInChunk = effectiveChunkLength - reader->offsetChunk;
    size_t end = bytesToRead > bytesInChunk ? effectiveChunkLength : reader->offsetChunk + bytesToRead;

    memcpy(reader->buffer + reader->offset, chunk + reader->offsetChunk, end - reader->offsetChunk);

    size_t bytesActuallyRead = end - reader->offsetChunk;

    reader->bytesRead += bytesActuallyRead;
    reader->offset += bytesActuallyRead;
    reader->offsetChunk = end;

    return reader->bytesRead == reader->bufferLength;
}

void ft_readerCreateBuffer(struct ft_reader *reader) {
    reader->bufferLength = 4 + reader->messageLength;
    reader->buffer = (unsigned char *) malloc(reader->bufferLength);
    if (reader->buffer == NULL) return;
    ft_utilWriteUInt(reader->messageLength, reader->buffer);
    reader->offset += 4;
}

void ft_readerDestroy(struct ft_reader *reader) {
    if (reader->buffer != NULL) {
        free(reader->buffer);
    }
    free(reader);
}
