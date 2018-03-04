//
// Created by wein on 3/4/18.
//

#include <tinyCUnit.h>
#include <cciArrayList.h>

void Prt(cciArrayList_t *al) {
    for (int i=0; i < al->size; ++i) {
        printf("%d, ", AlGetInt(al, i));
    }
    printf("\n");
}

void AssertArrayList(cciArrayList_t *al, const int *expected) {
    for (int i=0; i < al->size; ++i) {
        if (AlGetInt(al, i) != expected[i]) {
            printf("Unexpected array list members:\n");
            Prt(al);
            assert(0);
        }
    }
}

void UnitTests() {
    InitializeTinyTests();

    NewTinyTest("create and delete arrayList") ((void) {
        cciArrayList_t *al = AlNew();
        AlDelete(al);
    });

    NewTinyTest("expect initial capacity") ((void) {
        cciArrayList_t *al = AlNew();
        AssertEqual(8, al->capacity);
        AlDelete(al);
    });

    NewTinyTest("get last value from empty arrayList, expect index error") ((void) {
        cciArrayList_t *al = AlNew();
        AlBack(al);
        AssertEqual(CCI_ARRAYLIST_INDEXERROR, al->errCode);
        AlDelete(al);
    });

    NewTinyTest("emplace back, expect value at back") ((void) {
        cciArrayList_t *al = AlNew();
        AlEmplaceBack(al, 11);
        AssertEqual(11, AlBack(al));
        AlDelete(al);
    });

    NewTinyTest("emplace back, expect value at index") ((void) {
        cciArrayList_t *al = AlNew();
        AlEmplaceBack(al, 0xDE);
        AlEmplaceBack(al, 0xAD);
        AlEmplaceBack(al, 0xBE);
        AlEmplaceBack(al, 0xEF);
        AssertEqual(0xAD, AlGetInt(al, 1));
        AssertEqual(0xBE, AlGetInt(al, 2));
        AlDelete(al);
    });

    NewTinyTest("get from invalid index, expect index error") ((void) {
        cciArrayList_t *al = AlNew();
        AlEmplaceBack(al, 0xDE);
        AlEmplaceBack(al, 0xAD);
        AlGetInt(al, 1001);
        AssertEqual(CCI_ARRAYLIST_INDEXERROR, al->errCode);
        AlDelete(al);
    });

    NewTinyTest("set value on invalid index, expect index error") ((void) {
        cciArrayList_t *al = AlNew();
        AlEmplaceBack(al, 0xDE);
        AlEmplaceBack(al, 0xAD);
        AlSetInt(al, 1001, 0xBEEF);
        AssertEqual(CCI_ARRAYLIST_INDEXERROR, al->errCode);
        AlDelete(al);
    });

    NewTinyTest("append values, expect capacity increased") ((void) {
        cciArrayList_t *al = AlNew();
        AlEmplaceBack(al, 1);
        AlEmplaceBack(al, 1);
        AlEmplaceBack(al, 1);
        AlEmplaceBack(al, 1);
        AlEmplaceBack(al, 1);
        AssertEqual(16, al->capacity);
        AlDelete(al);
    });

    NewTinyTest("reserve, expect capacity increased") ((void) {
        cciArrayList_t *al = AlNew();
        // if new capacity is not greater than the current value, this function does nothing
        AlReserve(al, 6);
        AssertEqual(8, al->capacity);
        AlReserve(al, 24);
        AssertEqual(24, al->capacity);
        AlDelete(al);
    });

    NewTinyTest("pop back, expect new back") ((void) {
        cciArrayList_t *al = AlNew();
        AlEmplaceBack(al, 1);
        AlEmplaceBack(al, 2);
        AlEmplaceBack(al, 3);
        AlEmplaceBack(al, 4);
        AssertEqual(4, AlBack(al));
        AlPopBack(al);
        AssertEqual(3, AlBack(al));
        AlPopBack(al);
        AssertEqual(2, AlBack(al));
        AlDelete(al);
    });

    NewTinyTest("insert, expect new values") ((void) {
        cciArrayList_t *al = AlNew();
        AlEmplaceBack(al, 1);
        AlEmplaceBack(al, 2);
        AlEmplaceBack(al, 3);
        AlEmplaceBack(al, 4);
        AssertEqual(3, AlGetInt(al, 2));
        AlInsertInt(al, 2, 1001);
        AssertEqual(5, al->size);
        AssertEqual(3, AlGetInt(al, 2));
        AssertEqual(1001, AlGetInt(al, 3));
        AlDelete(al);
    });

    RunTinyTests();
}

int main(int argc, char **argv) {
    UnitTests();
    return 0;
}
