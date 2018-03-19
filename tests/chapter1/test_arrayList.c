//
// Created by wein on 3/4/18.
//

#include <tinyCUnit.h>
#include <cciArrayList.h>

void Prt(cciArrayList_t *al) {
    for (size_t i=0; i < al->size; ++i) {
        printf("%d, ", GETINT(AlGet(al, i)));
    }
    printf("\n");
}

void AssertArrayList(cciArrayList_t *al, const int *expected) {
    for (size_t i=0; i < al->size; ++i) {
        if (GETINT(AlGet(al, i)) != expected[i]) {
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
        AlEmplaceBack(al, newInt(11));
        AssertEqual(11, GETINT(AlBack(al)));
        AlDelete(al);
    });

    NewTinyTest("emplace back, expect value at index") ((void) {
        cciArrayList_t *al = AlNew();
        AlEmplaceBack(al, newInt(0xDE));
        AlEmplaceBack(al, newInt(0xAD));
        AlEmplaceBack(al, newInt(0xBE));
        AlEmplaceBack(al, newInt(0xEF));
        AssertEqual(0xAD, GETINT(AlGet(al, 1)));
        AssertEqual(0xBE, GETINT(AlGet(al, 2)));
        AlDelete(al);
    });

    NewTinyTest("get from invalid index, expect index error") ((void) {
        cciArrayList_t *al = AlNew();
        AlEmplaceBack(al, newInt(0xDE));
        AlEmplaceBack(al, newInt(0xAD));
        AlGet(al, 1001);
        AssertEqual(CCI_ARRAYLIST_INDEXERROR, al->errCode);
        AlDelete(al);
    });

    NewTinyTest("set value on invalid index, expect index error") ((void) {
        cciArrayList_t *al = AlNew();
        AlEmplaceBack(al, newInt(0xDE));
        AlEmplaceBack(al, newInt(0xAD));
        AlSet(al, 1001, newInt(0xBEEF));
        AssertEqual(CCI_ARRAYLIST_INDEXERROR, al->errCode);
        AlDelete(al);
    });

    NewTinyTest("append values, expect capacity increased") ((void) {
        cciArrayList_t *al = AlNew();
        AlEmplaceBack(al, newInt(1));
        AlEmplaceBack(al, newInt(1));
        AlEmplaceBack(al, newInt(1));
        AlEmplaceBack(al, newInt(1));
        AlEmplaceBack(al, newInt(1));
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
        AlEmplaceBack(al, newInt(1));
        AlEmplaceBack(al, newInt(2));
        AlEmplaceBack(al, newInt(3));
        AlEmplaceBack(al, newInt(4));
        AssertEqual(4, GETINT(AlBack(al)));
        AlPopBack(al);
        AssertEqual(3, GETINT(AlBack(al)));
        AlPopBack(al);
        AssertEqual(2, GETINT(AlBack(al)));
        AlDelete(al);
    });

    NewTinyTest("insert, expect new values") ((void) {
        cciArrayList_t *al = AlNew();
        AlEmplaceBack(al, newInt(1));
        AlEmplaceBack(al, newInt(2));
        AlEmplaceBack(al, newInt(3));
        AlEmplaceBack(al, newInt(4));
        AssertEqual(3, GETINT(AlGet(al, 2)));
        AlInsert(al, 2, newInt(1001));
        AssertEqual(5, al->size);
        AssertEqual(3, GETINT(AlGet(al, 2)));
        AssertEqual(1001, GETINT(AlGet(al, 3)));
        AlDelete(al);
    });

    RunTinyTests();
}

void EmplaceBackBenchmark() {
    clock_t before;
    cciArrayList_t *al = AlNew();
    AlEmplaceBack(al, newInt(1));
    AlEmplaceBack(al, newInt(2));
    AlEmplaceBack(al, newInt(3));
    AlEmplaceBack(al, newInt(4));
    before = clock();
    for (int i=0; i <= 100000; ++i) {
        AlEmplaceBack(al, newInt(i));
    }
    printf("\nEmplaceBack() took: %f us\n", (double)(clock() - before));
    AlDelete(al);
}

int main(int argc, char **argv) {
    UnitTests();
    EmplaceBackBenchmark();
    return 0;
}
