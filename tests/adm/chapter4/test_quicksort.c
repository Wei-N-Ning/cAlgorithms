//
// Created by wein on 4/1/18.
//

#include <assert.h>
#include <stdio.h>

#include <admQuicksort.h>
#include <cci/cciArrayList.h>

void RunTinyTests();

void test_partitionSmallBaseExpectPivot() {
    cciArrayList_t *al = CCI_AlNew();
    int arr[8] = {314, 15, 9, 26, 535, 89, 79, 32};
    size_t workload = 3;
    for (size_t i=workload; i--; CCI_AlEmplaceBack(al, CCIValue_newInt(arr[workload - i - 1]))) ;
    assert(0 == LomutoPartition(al, 0, al->size - 1));
    assert(2 == LomutoPartition(al, 1, al->size - 1));
    CCI_AlDelete(al);
}

void test_paritionLargeBaseExpectPivot() {
    cciArrayList_t *al = CCI_AlNew();
    int arr[8] = {314, 15, 9, 26, 535, 89, 79, 32};
    size_t workload = 8;
    for (size_t i=workload; i--; CCI_AlEmplaceBack(al, CCIValue_newInt(arr[workload - i - 1]))) ;
    assert(3 == LomutoPartition(al, 0, al->size - 1));
    assert(2 == LomutoPartition(al, 0, 2));
    CCI_AlDelete(al);
}

static void assertAscendingOrder(cciArrayList_t *al) {
    for (size_t i=0; i<al->size - 1; assert(CCIValue_GETINT(CCI_AlGet(al, i)) <= CCIValue_GETINT(CCI_AlGet(al, i + 1))), i++) ;
}

void test_quickSortLomutoExpectNewSequence() {
    cciArrayList_t *al = CCI_AlNew();
    int arr[6] = {3, 14, 15, 9, 26, 535};
    size_t sz = 6;
    for (size_t i=sz; i--; CCI_AlEmplaceBack(al, CCIValue_newInt(arr[sz - i - 1]))) ;
    AdmQuicksort(al, PartitionScheme_Lomuto);
    assertAscendingOrder(al);
    CCI_AlDelete(al);
}

void test_quickSortLomutoIdenticalSequence() {
    cciArrayList_t *al = CCI_AlNew();
    int arr[6] = {3, 3, 3, 3, 3, 3};
    size_t sz = 6;
    for (size_t i=sz; i--; CCI_AlEmplaceBack(al, CCIValue_newInt(arr[sz - i - 1]))) ;
    AdmQuicksort(al, PartitionScheme_Lomuto);
    assertAscendingOrder(al);
    CCI_AlDelete(al);
}

void test_quickSortDescendingSequence() {
    cciArrayList_t *al = CCI_AlNew();
    int arr[6] = {3333, 333, 33, 30, 13, 3};
    size_t sz = 6;
    for (size_t i=sz; i--; CCI_AlEmplaceBack(al, CCIValue_newInt(arr[sz - i - 1]))) ;
    AdmQuicksort(al, PartitionScheme_Lomuto);
    assertAscendingOrder(al);
    CCI_AlDelete(al);
}

void test_quickSortHoare() {
    cciArrayList_t *al = CCI_AlNew();
    int arr[8] = {31, 41, 59, 2, 6, 53, 58, 97};
    size_t sz = 8;
    for (size_t i=sz; i--; CCI_AlEmplaceBack(al, CCIValue_newInt(arr[sz - i - 1]))) ;
    AdmQuicksort(al, PartitionScheme_Hoare);
    assertAscendingOrder(al);
    CCI_AlDelete(al);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
