//
// Created by wein on 3/19/18.
//

#include <cci/cciStack.h>

#include <assert.h>

void RunTinyTests();

void assertIEqual(int lhs, cciValue_t value) {
    assert(lhs == CCIValue_GETINT(value));
}

void test_createStack() {
    cciStack_t *st = CCI_CreateStack(64);
    assert(st);
    assert(CCI_StackEmpty(st));
    CCI_DeleteStack(st);
}

void test_pushBackPop() {
    cciStack_t *st = CCI_CreateStack(64);
    CCI_StackPush(st, CCIValue_newInt(23));
    CCI_StackPush(st, CCIValue_newInt(123));
    CCI_StackPush(st, CCIValue_newInt(2));
    CCI_StackPush(st, CCIValue_newInt(6));
    assertIEqual(6, CCI_StackPeek(st));
    assert(! CCI_StackEmpty(st));
    assertIEqual(6, CCI_StackPop(st));
    assertIEqual(2, CCI_StackPop(st));
    assertIEqual(123, CCI_StackPop(st));
    assertIEqual(23, CCI_StackPop(st));
    CCI_DeleteStack(st);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}