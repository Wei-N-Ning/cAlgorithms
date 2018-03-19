//
// Created by wein on 3/3/18.
//

#include <cciList.h>
#include <tinyCUnit.h>

static void testRoundTripInt() {
    int size = 20000;
    double microsec = 0.0;
    clock_t before, after;
    printf("start integration test: integer round trip (problem size: %d)......", size);
    before = clock();
    cciList_t *l = NewList();
    for (int i=0; i<size; ++i) {
        Append(l, newInt(i));
    }
    after = clock();
    microsec = after - before;
    printf("DONE\n%f s (%f ms)\n", microsec/1000000, microsec/1000);
}

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
        Append(l, newInt(134));
        Append(l, newInt(134));
        AssertEqual(2, l->size);
        DeleteList(l);
    });

    NewTinyTest("append int, expect value") ((void) {
        cciList_t *l = NewList();
        Append(l, newInt(-1));
        Append(l, newInt(10));
        Append(l, newInt(20));
        AssertEqual(-1, GETINT(Get(l, 0)));
        AssertEqual(10, GETINT(Get(l, 1)));
        AssertEqual(20, GETINT(Get(l, 2)));
        DeleteList(l);
    });

    NewTinyTest("given invalid index and append, expect errCode") ((void) {
        cciList_t *l = NewList();
        Append(l, newInt(-1));
        Get(l, 999);
        AssertEqual(CCILIST_INDEX_ERROR, l->errCode);
        DeleteList(l);
    });

    NewTinyTest("insert int, expect pos and value") ((void) {
        cciList_t *l = NewList();
        Append(l, newInt(-1));
        Append(l, newInt(10));
        Append(l, newInt(20));
        Insert(l, 1, newInt(33));
        AssertEqual(33, GETINT(Get(l, 2)));
        AssertEqual(20, GETINT(Get(l, 3)));
        DeleteList(l);
    });

    NewTinyTest("givne invalid index and insert, expect errCode") ((void) {
        cciList_t *l = NewList();
        Append(l, newInt(-1));
        Append(l, newInt(10));
        Append(l, newInt(20));
        Insert(l, 4, newInt(33));
        AssertEqual(CCILIST_INDEX_ERROR, l->errCode);
        DeleteList(l);
    });

    NewTinyTest("remove, expect new size") ((void) {
        cciList_t *l = NewList();
        Append(l, newInt(-1));
        Append(l, newInt(10));
        Append(l, newInt(20));
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
        Append(l, newInt(-1));
        Append(l, newInt(10));
        Append(l, newInt(20));
        AssertEqual(-1, GETINT(Get(l, 0)));
        Remove(l, 0);
        AssertEqual(10, GETINT(Get(l, 0)));
        DeleteList(l);
    });

    RunTinyTests();

    testRoundTripInt();
    return 0;
}
