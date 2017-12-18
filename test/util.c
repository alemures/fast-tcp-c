#include <stdio.h>
#include <assert.h>
#include "../src/ft_util.h"

void testWriteReadShort() {
    unsigned char shortBuffer[2];
    uint16_t value = 65535;

    ft_utilWriteUint16(value, shortBuffer);
    uint16_t readValue = ft_utilReadUint16(shortBuffer);

    assert(value == readValue);
}

int main(int argc, char *argv[]) {
    ft_utilLogDebug("Hello, debug!");
    ft_utilLogInfo("Hello, info!");
    ft_utilLogWarning("Hello, warning!");
    ft_utilLogError("Hello, error!");

    testWriteReadShort();

    return 0;
}
