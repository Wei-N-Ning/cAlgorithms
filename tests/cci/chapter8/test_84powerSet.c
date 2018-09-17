//
// Created by wein on 4/9/18.
//

#include <stdlib.h>
#include <stdio.h>

#include <cci/cciArrayList.h>
#include <cci/cciHashTable.h>

#define _MAX_VALUE 0xFFFF

void RunTinyTests();

void populateSet(cciArrayList_t *set, size_t num) {
    cciHashTable_t *tb = CCI_NewHashTable(num);
    uint64_t v = 0;
    for (size_t _=num; _-- ; ) {
        v = (uint64_t)random() % _MAX_VALUE;
        while (CCIValue_ISVALID(CCI_IGet(tb, (uint64_t)v))) {
            v = (uint64_t)random() % _MAX_VALUE;
        }
        CCI_ISet(tb, v, CCIValue_newInt(1));
        CCI_AlEmplaceBack(set, CCIValue_newInt(v));
    }
    CCI_DeleteHashTable(tb);
}

void test_nothing() {
    cciArrayList_t *arr = CCI_AlNew();
    populateSet(arr, 7);
    for (size_t i=0; i<arr->size; ++i) {
        printf("%d, ", CCIValue_GETINT(CCI_AlGet(arr, i)));
    }
    CCI_AlDelete(arr);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}