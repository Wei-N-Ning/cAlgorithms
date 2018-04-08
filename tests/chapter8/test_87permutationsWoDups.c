//
// Created by wein on 4/9/18.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <cciArrayList.h>
#include <admQuicksort.h>

void RunTinyTests();

void extractUniqueCharacters(const char *str, cciArrayList_t *o_arr) {
    cciArrayList_t *tmp = AlNew();
    size_t sz = strlen(str);
    char curr = '\0';
    cciValue_t v;
    for (size_t i=0; i<sz; ++i) {
        AlEmplaceBack(tmp, newChar(str[i]));
    }
    AdmQuicksort(tmp, PartitionScheme_Lomuto);
    for (size_t i=0; i<sz; ++i) {
        v = AlGet(tmp, i);
        if (curr != GETCHAR(v)) {
            curr = GETCHAR(v);
            AlEmplaceBack(o_arr, v);
        }
    }
    AlDelete(tmp);
}

void solve(cciArrayList_t *carr, cciArrayList_t *o_parr) {
    ;
}

void test_nothing() {
    cciArrayList_t *arr = AlNew();
    cciArrayList_t *parr = AlNew();
    extractUniqueCharacters("doom1 doom2 doom2016", arr);
    for (size_t i=0; i<arr->size; ++i) {
        printf("%c", GETCHAR(AlGet(arr, i)));
    }
    for (size_t i=parr->size; i--; free(GETPOINTER(AlGet(parr, i), char))) ;
    AlDelete(parr);
    AlDelete(arr);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}