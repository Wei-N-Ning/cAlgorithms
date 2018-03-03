//
// Created by wein on 3/3/18.
//

#include <stdio.h>

#include <cciList.h>
#include <tinyCUnit.h>

int main(int argc, char **argv) {
    InitializeTinyTests();

    NewTinyTest("create and delete list") ((void) {
        cciList_t *l = NewList();
        AssertTrue(l);
        AssertEqual(0, l->size);
        DeleteList(l);
    });

    NewTinyTest("append int, expect new size") ((void) {
        cciList_t *l = NewList();
        AppendInt(l, 134);
        AppendInt(l, 134);
        AssertEqual(2, l->size);
        DeleteList(l);
    });

    NewTinyTest("append int, expect value") ((void) {
        cciList_t *l = NewList();
        AppendInt(l, -1);
        AppendInt(l, 10);
        AppendInt(l, 20);
        AssertEqual(10, GetInt(l, 1));
        AssertEqual(20, GetInt(l, 2));
        DeleteList(l);
    });

    NewTinyTest("given invalid index and append, expect errCode") ((void) {
        cciList_t *l = NewList();
        AppendInt(l, -1);
        GetInt(l, 999);
        AssertEqual(CCILIST_INDEX_ERROR, l->errCode);
        DeleteList(l);
    });

    NewTinyTest("insert int, expect pos and value") ((void) {
        cciList_t *l = NewList();
        AppendInt(l, -1);
        AppendInt(l, 10);
        AppendInt(l, 20);
        InsertInt(l, 1, 33);
        AssertEqual(33, GetInt(l, 2));
        AssertEqual(20, GetInt(l, 3));
        DeleteList(l);
    });

    NewTinyTest("givne invalid index and insert, expect errCode") ((void) {
        cciList_t *l = NewList();
        AppendInt(l, -1);
        AppendInt(l, 10);
        AppendInt(l, 20);
        InsertInt(l, 4, 33);
        AssertEqual(CCILIST_INDEX_ERROR, l->errCode);
        DeleteList(l);
    });

    NewTinyTest("remove, expect new size") ((void) {
        cciList_t *l = NewList();
        AppendInt(l, -1);
        AppendInt(l, 10);
        AppendInt(l, 20);
        Remove(l, 0);
        AssertEqual(2, l->size);
        DeleteList(l);
    });

    NewTinyTest("remove from empty list, expect errCode") ((void) {
        cciList_t *l = NewList();
        Remove(l, 22);
        AssertEqual(CCILIST_INDEX_ERROR, l->errCode);
        DeleteList(l);
    });

    NewTinyTest("remove, expect new value at index") ((void) {
        cciList_t *l = NewList();
        AppendInt(l, -1);
        AppendInt(l, 10);
        AppendInt(l, 20);
        AssertEqual(-1, GetInt(l, 0));
        Remove(l, 0);
        AssertEqual(10, GetInt(l, 0));
        DeleteList(l);
    });

    RunTinyTests();
    return 0;
}
