//
// Created by wein on 3/2/18.
//

#include <assert.h>

#include <cciStrings.h>

void RunTinyTests();

void test_nothing() {
    assert(1 == placeholder());
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
