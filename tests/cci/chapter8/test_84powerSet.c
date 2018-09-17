//
// Created by wein on 4/9/18.
//

#include <stdlib.h>
#include <stdio.h>

#include <cciArrayList.h>
#include <cciHashTable.h>

#define _MAX_VALUE 0xFFFF

void RunTinyTests();

void populateSet(cciArrayList_t *set, size_t num) {
    cciHashTable_t *tb = NewHashTable(num);
    uint64_t v = 0;
    for (size_t _=num; _-- ; ) {
        v = (uint64_t)random() % _MAX_VALUE;
        while (ISVALID(IGet(tb, (uint64_t)v))) {
            v = (uint64_t)random() % _MAX_VALUE;
        }
        ISet(tb, v, newInt(1));
        AlEmplaceBack(set, newInt(v));
    }
    DeleteHashTable(tb);
}

void test_nothing() {
    cciArrayList_t *arr = AlNew();
    populateSet(arr, 7);
    for (size_t i=0; i<arr->size; ++i) {
        printf("%d, ", GETINT(AlGet(arr, i)));
    }
    AlDelete(arr);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}