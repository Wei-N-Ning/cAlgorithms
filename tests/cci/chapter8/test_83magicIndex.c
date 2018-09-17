//
// Created by wein on 4/9/18.
//

#include <stdlib.h>
#include <stdio.h>

#include <cciArrayList.h>
#include <admQuicksort.h>

void RunTinyTests();

void populateArr(int min_, int max_, size_t num, cciArrayList_t *o_arr) {
    for (size_t i=num; i--; ) {
        AlEmplaceBack(o_arr,
                      newInt((int)random() % (max_ - min_) + min_));
    }
    AdmQuicksort(o_arr, PartitionScheme_Lomuto);
}

static void _solve(cciArrayList_t *arr, cciArrayList_t *indices, size_t from, size_t to, cciArrayList_t *o_anwser) {
    if (from < to) {
        size_t mid = from + (to -from) / 2;
        if (GETINT(AlGet(arr, mid)) == mid) {
            AlEmplaceBack(o_anwser, newInt(mid));
        }
        _solve(arr, indices, from, mid, o_anwser);
        _solve(arr, indices, mid + 1, to, o_anwser);
    }
}

void solve(cciArrayList_t *arr, cciArrayList_t *o_answer) {
    cciArrayList_t *indices = AlNew();
    size_t sz = arr->size;
    for (int i=0; i<sz; AlEmplaceBack(indices, newInt(i)), i++) ;
    _solve(arr, indices, 0, sz, o_answer);
    AlDelete(indices);
}

void test_nothing() {
    cciArrayList_t *arr = AlNew();
    cciArrayList_t *answer = AlNew();
    populateArr(0, 12, 12, arr);
    solve(arr, answer);
    for (size_t i=0; i<arr->size; ++i) {
        printf("(%d) %d, ", (int)i, GETINT(AlGet(arr, i)));
    }
    printf("\n");
    for (size_t i=0; i<answer->size; ++i) {
        printf("%d, ", GETINT(AlGet(answer, i)));
    }
    AlDelete(answer);
    AlDelete(arr);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}