//
// Created by wein on 3/4/18.
//

#include <cci/cciArrayList.h>

#include <assert.h>
#include <stdio.h>

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

void RunTinyTests();

void test_createAndDelete() {
    cciArrayList_t *al = AlNew();
    assert(al);
    AlDelete(al);
};

void test_expectInitialCapacity() {
    cciArrayList_t *al = AlNew();
    assert(8 == al->capacity);
    AlDelete(al);
}

void test_givenEmptyArrayListCanNotGet() {
    cciArrayList_t *al = AlNew();
    AlBack(al);
    assert(CCI_ARRAYLIST_INDEXERROR == al->errCode);
    AlDelete(al);
}

void test_emplaceBackExpectValueAtBack() {
    cciArrayList_t *al = AlNew();
    AlEmplaceBack(al, newInt(11));
    assert(11 == GETINT(AlBack(al)));
    AlDelete(al);
}

void test_emplaceBackExpectValueAtIndex() {
    cciArrayList_t *al = AlNew();
    AlEmplaceBack(al, newInt(0xDE));
    AlEmplaceBack(al, newInt(0xAD));
    AlEmplaceBack(al, newInt(0xBE));
    AlEmplaceBack(al, newInt(0xEF));
    assert(0xAD == GETINT(AlGet(al, 1)));
    assert(0xBE == GETINT(AlGet(al, 2)));
    AlDelete(al);
}

void test_givenInvalidIndexCanNotGet() {
    cciArrayList_t *al = AlNew();
    AlEmplaceBack(al, newInt(0xDE));
    AlEmplaceBack(al, newInt(0xAD));
    AlGet(al, 1001);
    assert(CCI_ARRAYLIST_INDEXERROR == al->errCode);
    AlDelete(al);
}

void test_givenInvalidIndexCanNotSet() {
    cciArrayList_t *al = AlNew();
    AlEmplaceBack(al, newInt(0xDE));
    AlEmplaceBack(al, newInt(0xAD));
    AlSet(al, 1001, newInt(0xBEEF));
    assert(CCI_ARRAYLIST_INDEXERROR == al->errCode);
    AlDelete(al);
}

void test_appendValuesExpectCapacityIncreased() {
    cciArrayList_t *al = AlNew();
    AlEmplaceBack(al, newInt(1));
    AlEmplaceBack(al, newInt(1));
    AlEmplaceBack(al, newInt(1));
    AlEmplaceBack(al, newInt(1));
    AlEmplaceBack(al, newInt(1));
    assert(16 == al->capacity);
    AlDelete(al);
}

void test_reserveExpectCapacityIncreased() {
    cciArrayList_t *al = AlNew();
    // if new capacity is not greater than the current value, this function does nothing
    AlReserve(al, 6);
    assert(8 == al->capacity);
    AlReserve(al, 24);
    assert(24 == al->capacity);
    AlDelete(al);
}

void test_popBackExpectNewBack() {
    cciArrayList_t *al = AlNew();
    AlEmplaceBack(al, newInt(1));
    AlEmplaceBack(al, newInt(2));
    AlEmplaceBack(al, newInt(3));
    AlEmplaceBack(al, newInt(4));
    assert(4 == GETINT(AlBack(al)));
    AlPopBack(al);
    assert(3 == GETINT(AlBack(al)));
    AlPopBack(al);
    assert(2 == GETINT(AlBack(al)));
    AlDelete(al);
}

void test_insertExpectNewValues() {
    cciArrayList_t *al = AlNew();
    AlEmplaceBack(al, newInt(1));
    AlEmplaceBack(al, newInt(2));
    AlEmplaceBack(al, newInt(3));
    AlEmplaceBack(al, newInt(4));
    assert(3 == GETINT(AlGet(al, 2)));
    AlInsert(al, 2, newInt(1001));
    assert(5 == al->size);
    assert(3 == GETINT(AlGet(al, 2)));
    assert(1001 == GETINT(AlGet(al, 3)));
    AlDelete(al);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
