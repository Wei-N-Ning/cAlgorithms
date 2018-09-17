//
// Created by wein on 4/1/18.
//

#include <assert.h>
#include <stdio.h>

#include <admMergesort.h>
#include <cci/cciArrayList.h>

void RunTinyTests();

void test_sortExpectNewSequence() {
    cciArrayList_t *al = CCI_AlNew();
    int arr[8] = {3, 1, 4, 15, 9, 26, 5, 35};
    int expected[8] = {1, 3, 4, 5, 9, 15, 26, 35};
    for (int i=8; i--; CCI_AlEmplaceBack(al, CCIValue_newInt(arr[i]))) ;
    Mergesort(al);
    for (size_t i=8; i--; assert(CCIValue_GETINT(CCI_AlGet(al, i)) == expected[i])) ;
    CCI_AlDelete(al);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
