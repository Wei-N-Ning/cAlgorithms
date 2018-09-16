//
// Created by wein on 3/4/18.
//

#include <cci/cciArrayList.h>

#include <assert.h>
#include <stdio.h>

void Prt(cciArrayList_t *al) {
    for (size_t i=0; i < al->size; ++i) {
        printf("%d, ", CCIValue_GETINT(CCI_AlGet(al, i)));
    }
    printf("\n");
}

void AssertArrayList(cciArrayList_t *al, const int *expected) {
    for (size_t i=0; i < al->size; ++i) {
        if (CCIValue_GETINT(CCI_AlGet(al, i)) != expected[i]) {
            printf("Unexpected array list members:\n");
            Prt(al);
            assert(0);
        }
    }
}

void RunTinyTests();

void test_createAndDelete() {
    cciArrayList_t *al = CCI_AlNew();
    assert(al);
    CCI_AlDelete(al);
};

void test_expectInitialCapacity() {
    cciArrayList_t *al = CCI_AlNew();
    assert(8 == al->capacity);
    CCI_AlDelete(al);
}

void test_givenEmptyArrayListCanNotGet() {
    cciArrayList_t *al = CCI_AlNew();
    CCI_AlBack(al);
    assert(CCI_ARRAYLIST_INDEXERROR == al->errCode);
    CCI_AlDelete(al);
}

void test_emplaceBackExpectValueAtBack() {
    cciArrayList_t *al = CCI_AlNew();
    CCI_AlEmplaceBack(al, CCIValue_newInt(11));
    assert(11 == CCIValue_GETINT(CCI_AlBack(al)));
    CCI_AlDelete(al);
}

void test_emplaceBackExpectValueAtIndex() {
    cciArrayList_t *al = CCI_AlNew();
    CCI_AlEmplaceBack(al, CCIValue_newInt(0xDE));
    CCI_AlEmplaceBack(al, CCIValue_newInt(0xAD));
    CCI_AlEmplaceBack(al, CCIValue_newInt(0xBE));
    CCI_AlEmplaceBack(al, CCIValue_newInt(0xEF));
    assert(0xAD == CCIValue_GETINT(CCI_AlGet(al, 1)));
    assert(0xBE == CCIValue_GETINT(CCI_AlGet(al, 2)));
    CCI_AlDelete(al);
}

void test_givenInvalidIndexCanNotGet() {
    cciArrayList_t *al = CCI_AlNew();
    CCI_AlEmplaceBack(al, CCIValue_newInt(0xDE));
    CCI_AlEmplaceBack(al, CCIValue_newInt(0xAD));
    CCI_AlGet(al, 1001);
    assert(CCI_ARRAYLIST_INDEXERROR == al->errCode);
    CCI_AlDelete(al);
}

void test_givenInvalidIndexCanNotSet() {
    cciArrayList_t *al = CCI_AlNew();
    CCI_AlEmplaceBack(al, CCIValue_newInt(0xDE));
    CCI_AlEmplaceBack(al, CCIValue_newInt(0xAD));
    CCI_AlSet(al, 1001, CCIValue_newInt(0xBEEF));
    assert(CCI_ARRAYLIST_INDEXERROR == al->errCode);
    CCI_AlDelete(al);
}

void test_appendValuesExpectCapacityIncreased() {
    cciArrayList_t *al = CCI_AlNew();
    CCI_AlEmplaceBack(al, CCIValue_newInt(1));
    CCI_AlEmplaceBack(al, CCIValue_newInt(1));
    CCI_AlEmplaceBack(al, CCIValue_newInt(1));
    CCI_AlEmplaceBack(al, CCIValue_newInt(1));
    CCI_AlEmplaceBack(al, CCIValue_newInt(1));
    assert(16 == al->capacity);
    CCI_AlDelete(al);
}

void test_reserveExpectCapacityIncreased() {
    cciArrayList_t *al = CCI_AlNew();
    // if new capacity is not greater than the current value, this function does nothing
    CCI_AlReserve(al, 6);
    assert(8 == al->capacity);
    CCI_AlReserve(al, 24);
    assert(24 == al->capacity);
    CCI_AlDelete(al);
}

void test_popBackExpectNewBack() {
    cciArrayList_t *al = CCI_AlNew();
    CCI_AlEmplaceBack(al, CCIValue_newInt(1));
    CCI_AlEmplaceBack(al, CCIValue_newInt(2));
    CCI_AlEmplaceBack(al, CCIValue_newInt(3));
    CCI_AlEmplaceBack(al, CCIValue_newInt(4));
    assert(4 == CCIValue_GETINT(CCI_AlBack(al)));
    CCI_AlPopBack(al);
    assert(3 == CCIValue_GETINT(CCI_AlBack(al)));
    CCI_AlPopBack(al);
    assert(2 == CCIValue_GETINT(CCI_AlBack(al)));
    CCI_AlDelete(al);
}

void test_insertExpectNewValues() {
    cciArrayList_t *al = CCI_AlNew();
    CCI_AlEmplaceBack(al, CCIValue_newInt(1));
    CCI_AlEmplaceBack(al, CCIValue_newInt(2));
    CCI_AlEmplaceBack(al, CCIValue_newInt(3));
    CCI_AlEmplaceBack(al, CCIValue_newInt(4));
    assert(3 == CCIValue_GETINT(CCI_AlGet(al, 2)));
    CCI_AlInsert(al, 2, CCIValue_newInt(1001));
    assert(5 == al->size);
    assert(3 == CCIValue_GETINT(CCI_AlGet(al, 2)));
    assert(1001 == CCIValue_GETINT(CCI_AlGet(al, 3)));
    CCI_AlDelete(al);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
