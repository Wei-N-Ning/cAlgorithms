
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void RunTinyTests();

static const char *sut = "there is no spoon";

int ipow(int base, int exp) {
    int result = base;
    for (int i=1; i<exp; ++i) {
        result *= base;
    }
    return result;
}

static int hashS(const char *s, size_t len) {
    int h = 0;
    for (int i=0; i<len; ++i) {
        h += ipow(26, 32 - (i + 1)) + (int)s[i];
    }

    return h;
}

void test_hashOneStringExpectResult() {
    int h = 0;
    h = hashS(sut, 5);
    assert(h == hashS("there", 5));
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}

