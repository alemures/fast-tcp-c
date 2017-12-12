#ifndef FT_READER_H
#define FT_READER_H

#include <stdbool.h>

struct ft_reader {
    unsigned char *buffer;
    int bufferLength;
    int offset;
    int bytesRead;
    int messageLength;
    int offsetChunk;

    int buffersRead;
};

struct ft_reader *ft_readerCreate();
unsigned char **ft_readerRead(struct ft_reader *reader, unsigned char *chunk, int effectiveChunkLength);
bool ft_readerReadMessageLength(struct ft_reader *reader, unsigned char *chunk, int effectiveChunkLength);
bool ft_readerReadMessageContent(struct ft_reader *reader, unsigned char *chunk, int effectiveChunkLength);
void ft_readerCreateBuffer(struct ft_reader *reader);
void ft_readerDestroy(struct ft_reader *reader);

#endif // FT_READER_H
