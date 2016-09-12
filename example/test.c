#include <stdio.h>
#include <string.h>
#include "../lib/Serializer.h"
#include "../lib/Utils.h"

int main(int argc, char *argv[]) {
    char *buffer = serialize("event", 5, "data", 4, 1, 1, 1);

    printByteArray(buffer, 10);

    return 0;
}
