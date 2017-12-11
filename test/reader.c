#include "../src/ft_reader.h"
#include "../src/ft_util.h"

int main(int argc, char *argv[]) {
    struct ft_reader *reader = ft_readerCreate();
    ft_readerDestroy(reader);

    return 0;
}
