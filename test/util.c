#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../src/ft_util.h"

void testWriteReadUint16() {
    unsigned char shortBuffer[2];
    uint16_t value = 65535;

    ft_utilWriteUint16(value, shortBuffer);
    uint16_t readValue = ft_utilReadUint16(shortBuffer);

    assert(value == readValue);
}

void testHash() {
    char *str1 = "Test String 1";
    char *str2 = "Test String 2";
    char *str3 = "Test String 1";
    uint32_t seed = 100;

    uint32_t hash1 = ft_utilHash(str1, strlen(str1), seed);
    uint32_t hash2 = ft_utilHash(str2, strlen(str2), seed);
    uint32_t hash3 = ft_utilHash(str3, strlen(str3), seed);

    assert(hash1 != hash2);
    assert(hash1 == hash3);
}

int main(int argc, char *argv[]) {
    ft_utilLogDebug("Hello, debug!");
    ft_utilLogInfo("Hello, info!");
    ft_utilLogWarning("Hello, warning!");
    ft_utilLogError("Hello, error!");

    testWriteReadUint16();
    testHash();

    return 0;
}
