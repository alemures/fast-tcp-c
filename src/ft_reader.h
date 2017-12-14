#ifndef FT_READER_H
#define FT_READER_H

#include <stddef.h>
#include <stdbool.h>

struct ft_reader {
    unsigned char *buffer;
    size_t bufferLength;
    size_t offset;
    size_t bytesRead;
    unsigned int messageLength;
    size_t offsetChunk;
};

struct ft_reader *ft_readerCreate();
// Returns -1 if chunk couldn't be processed
int ft_readerRead(struct ft_reader *reader, unsigned char *chunk, size_t effectiveChunkLength, unsigned char **buffers);
bool ft_readerReadMessageLength(struct ft_reader *reader, unsigned char *chunk, size_t effectiveChunkLength);
bool ft_readerReadMessageContent(struct ft_reader *reader, unsigned char *chunk, size_t effectiveChunkLength);
void ft_readerCreateBuffer(struct ft_reader *reader);
void ft_readerDestroy(struct ft_reader *reader);

#endif // FT_READER_H
