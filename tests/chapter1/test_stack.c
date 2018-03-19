//
// Created by wein on 3/19/18.
//

#include <cciStack.h>
#include <assert.h>

void RunTinyTests();

void assertIEqual(int lhs, cciValue_t value) {
    assert(lhs == GETINT(value));
}

void test_createStack() {
    cciStack_t *st = CreateCCIStack(64);
    assert(st);
    assert(CCIStackEmpty(st));
    DeleteCCIStack(st);
}

void test_pushBackPop() {
    cciStack_t *st = CreateCCIStack(64);
    CCIStackPush(st, newInt(23));
    CCIStackPush(st, newInt(123));
    CCIStackPush(st, newInt(2));
    CCIStackPush(st, newInt(6));
    assertIEqual(6, CCIStackPeek(st));
    assert(! CCIStackEmpty(st));
    assertIEqual(6, CCIStackPop(st));
    assertIEqual(2, CCIStackPop(st));
    assertIEqual(123, CCIStackPop(st));
    assertIEqual(23, CCIStackPop(st));
    DeleteCCIStack(st);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}