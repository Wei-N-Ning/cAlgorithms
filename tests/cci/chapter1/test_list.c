//
// Created by wein on 3/3/18.
//

#include <cci/cciList.h>

#include <assert.h>

void RunTinyTests();

void test_createAndDelete() {
    cciList_t *l = CCI_NewList();
    assert(l);
    assert(0 == l->size);
    CCI_DeleteList(l);
};

void test_appendIntExpectNewSize() {
    cciList_t *l = CCI_NewList();
    CCI_ListAppend(l, CCIValue_newInt(134));
    CCI_ListAppend(l, CCIValue_newInt(134));
    assert(2 == l->size);
    CCI_DeleteList(l);
}

void test_appendIntExpectValue() {
    cciList_t *l = CCI_NewList();
    CCI_ListAppend(l, CCIValue_newInt(-1));
    CCI_ListAppend(l, CCIValue_newInt(10));
    CCI_ListAppend(l, CCIValue_newInt(20));
    assert(-1 == CCIValue_GETINT(CCI_ListGet(l, 0)));
    assert(10 == CCIValue_GETINT(CCI_ListGet(l, 1)));
    assert(20 == CCIValue_GETINT(CCI_ListGet(l, 2)));
    CCI_DeleteList(l);
}

void test_givenInvalidIndexCanNotCCI_ListAppend() {
    cciList_t *l = CCI_NewList();
    CCI_ListAppend(l, CCIValue_newInt(-1));
    CCI_ListGet(l, 999);
    assert(CCILIST_INDEX_ERROR == l->errCode);
    CCI_DeleteList(l);
}

void test_insertIntExpectPosAndValue() {
    cciList_t *l = CCI_NewList();
    CCI_ListAppend(l, CCIValue_newInt(-1));
    CCI_ListAppend(l, CCIValue_newInt(10));
    CCI_ListAppend(l, CCIValue_newInt(20));
    CCI_ListInsert(l, 1, CCIValue_newInt(33));
    assert(33 == CCIValue_GETINT(CCI_ListGet(l, 2)));
    assert(20 == CCIValue_GETINT(CCI_ListGet(l, 3)));
    CCI_DeleteList(l);
}

void test_givenInvalidIndexCanNotCCI_ListInsert() {
    cciList_t *l = CCI_NewList();
    CCI_ListAppend(l, CCIValue_newInt(-1));
    CCI_ListAppend(l, CCIValue_newInt(10));
    CCI_ListAppend(l, CCIValue_newInt(20));
    CCI_ListInsert(l, 4, CCIValue_newInt(33));
    assert(CCILIST_INDEX_ERROR == l->errCode);
    CCI_DeleteList(l);
}

void test_removeExpectNewSize() {
    cciList_t *l = CCI_NewList();
    CCI_ListAppend(l, CCIValue_newInt(-1));
    CCI_ListAppend(l, CCIValue_newInt(10));
    CCI_ListAppend(l, CCIValue_newInt(20));
    CCI_ListRemove(l, 0);
    assert(2 == l->size);
    CCI_DeleteList(l);
}

void test_removeFromEmptyListExpectFail() {
    cciList_t *l = CCI_NewList();
    CCI_ListRemove(l, 22);
    assert(CCILIST_INDEX_ERROR == l->errCode);
    CCI_DeleteList(l);
}

void test_removeExpectNewValueAtIndex() {
    cciList_t *l = CCI_NewList();
    CCI_ListAppend(l, CCIValue_newInt(-1));
    CCI_ListAppend(l, CCIValue_newInt(10));
    CCI_ListAppend(l, CCIValue_newInt(20));
    assert(-1 == CCIValue_GETINT(CCI_ListGet(l, 0)));
    CCI_ListRemove(l, 0);
    assert(10 == CCIValue_GETINT(CCI_ListGet(l, 0)));
    CCI_DeleteList(l);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
