//
// Created by wein on 4/1/18.
//

#include "admQuicksort.h"

static void _swap(cciArrayList_t *al, int from, int to) {
    if (from == to) {
        return;
    }
    cciValue_t tmp = AlGet(al, from);
    AlSet(al, from, AlGet(al, to));
    AlSet(al, to, tmp);
}

// .........pivot
// -------> j (linear scan)
// --> i (placing the values lower than "pivot")
// ..pivot
int AdmPartition(cciArrayList_t *al, int lo, int hi) {
    cciValue_t toCompare = AlGet(al, hi);
    int i = lo - 1;
    for (int j=lo; j < hi; ++j) {
        if (GETINT(AlGet(al, j)) < GETINT(toCompare)) {
            i += 1;
            _swap(al, i, j);
        }
    }
    _swap(al, i + 1, hi);
    return i + 1;
}

static void _quicksort(cciArrayList_t *al, int lo, int hi) {
    int pivot = 0;
    if (lo < hi) {
        pivot = AdmPartition(al, lo, hi);
        _quicksort(al, lo, pivot - 1);
        _quicksort(al, pivot + 1, hi);
    }
}

void AdmQuicksort(cciArrayList_t *al) {
    _quicksort(al, 0, al->size - 1);
}
