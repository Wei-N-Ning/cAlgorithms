#include <assert.h>
#include <string.h>
#include <memory.h>
#include <stdio.h>

int extractLabels(const char *str, const char *token, char *o_first, char *o_second, int size) {
    const char *splitter = strstr(str, token);
    int firstLen = 0, secondLen = 0, sutLen = strlen(str), tokenLen = strlen(token);
    if (! (splitter && (firstLen = splitter - str) > 0)) {
        return 0;
    }
    secondLen = sutLen - tokenLen - firstLen;
    if (secondLen <= 0) {
        return 0;
    }
    memcpy(o_first, str, (firstLen > size) ? size : firstLen);
    memcpy(o_second, splitter + tokenLen, (secondLen > size) ? size : secondLen);
    return 1;
}

int main() {
    const char *sut = "asd->BSDA";
    const char *splitter = NULL;
    int sutLen = strlen(sut);
    char first[16];
    int firstLen = 0;
    char second[16];
    memset(first, 0, 16);
    memset(second, 0, 16);
    assert(extractLabels(sut, "->", first, second, 15));
    printf("%s->%s\n", first, second);
    return 0;
}
