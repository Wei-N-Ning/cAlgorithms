//
// Created by wein on 4/4/18.
//

#include <string.h>
#include <assert.h>
#include <stdio.h>

#include <admToStr.h>

#define BUF_SIZE 32

void RunTinyTests();

static char buf[BUF_SIZE];

void setUp() {
    memset(buf, 0, BUF_SIZE);
}

void test_expectBytesConvertedToUniqueString() {
    assert(1 == BytesToUniqueString(0x1, buf, BUF_SIZE));
    assert(0 == strcmp("B", buf));

    assert(6 == BytesToUniqueString(0x111000, buf, BUF_SIZE));
    assert(0 == strcmp("AAABBB", buf));

    assert(7 == BytesToUniqueString(0x111000111, buf, 7));
    assert(0 == strcmp("BBBAAAB", buf));
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
