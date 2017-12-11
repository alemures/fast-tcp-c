#include <stdlib.h>
#include "ft_reader.h"

struct ft_reader *ft_readerCreate() {
    struct ft_reader *reader = (struct ft_reader *) malloc(sizeof(struct ft_reader));
    if (reader == NULL) return NULL;
    reader->buffer = NULL;
    return reader;
}

unsigned char **ft_readerRead(struct ft_reader *reader, unsigned char *chunk, int effectiveChunkLength) {
    reader->offsetChunk = 0;
}

void ft_readerDestroy(struct ft_reader *reader) {
    if (reader->buffer != NULL) {
        free(reader->buffer);
    }
    free(reader);
}
