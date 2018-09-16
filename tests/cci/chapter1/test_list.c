//
// Created by wein on 3/3/18.
//

#include <cciList.h>

#include <assert.h>

void RunTinyTests();

void test_createAndDelete() {
    cciList_t *l = NewList();
    assert(l);
    assert(0 == l->size);
    DeleteList(l);
};

void test_appendIntExpectNewSize() {
    cciList_t *l = NewList();
    Append(l, newInt(134));
    Append(l, newInt(134));
    assert(2 == l->size);
    DeleteList(l);
}

void test_appendIntExpectValue() {
    cciList_t *l = NewList();
    Append(l, newInt(-1));
    Append(l, newInt(10));
    Append(l, newInt(20));
    assert(-1 == GETINT(Get(l, 0)));
    assert(10 == GETINT(Get(l, 1)));
    assert(20 == GETINT(Get(l, 2)));
    DeleteList(l);
}

void test_givenInvalidIndexCanNotAppend() {
    cciList_t *l = NewList();
    Append(l, newInt(-1));
    Get(l, 999);
    assert(CCILIST_INDEX_ERROR == l->errCode);
    DeleteList(l);
}

void test_insertIntExpectPosAndValue() {
    cciList_t *l = NewList();
    Append(l, newInt(-1));
    Append(l, newInt(10));
    Append(l, newInt(20));
    Insert(l, 1, newInt(33));
    assert(33 == GETINT(Get(l, 2)));
    assert(20 == GETINT(Get(l, 3)));
    DeleteList(l);
}

void test_givenInvalidIndexCanNotInsert() {
    cciList_t *l = NewList();
    Append(l, newInt(-1));
    Append(l, newInt(10));
    Append(l, newInt(20));
    Insert(l, 4, newInt(33));
    assert(CCILIST_INDEX_ERROR == l->errCode);
    DeleteList(l);
}

void test_removeExpectNewSize() {
    cciList_t *l = NewList();
    Append(l, newInt(-1));
    Append(l, newInt(10));
    Append(l, newInt(20));
    Remove(l, 0);
    assert(2 == l->size);
    DeleteList(l);
}

void test_removeFromEmptyListExpectFail() {
    cciList_t *l = NewList();
    Remove(l, 22);
    assert(CCILIST_INDEX_ERROR == l->errCode);
    DeleteList(l);
}

void test_removeExpectNewValueAtIndex() {
    cciList_t *l = NewList();
    Append(l, newInt(-1));
    Append(l, newInt(10));
    Append(l, newInt(20));
    assert(-1 == GETINT(Get(l, 0)));
    Remove(l, 0);
    assert(10 == GETINT(Get(l, 0)));
    DeleteList(l);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
