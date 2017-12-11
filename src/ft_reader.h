#ifndef FT_READER_H
#define FT_READER_H

struct ft_reader {
    unsigned char* buffer;
    int offset;
    int bytesRead;
    int messageLength;
    int offsetChunk;
};

struct ft_reader *ft_readerCreate();
unsigned char **ft_readerRead(struct ft_reader *reader, unsigned char *chunk, int effectiveChunkLength);
void ft_readerDestroy(struct ft_reader *reader);


#endif // FT_READER_H
