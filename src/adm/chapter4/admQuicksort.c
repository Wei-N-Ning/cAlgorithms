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
int LomutoPartition(cciArrayList_t *al, int lo, int hi) {
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

int HoarePartition(cciArrayList_t *al, int lo, int hi) {
    cciValue_t toCompare = AlGet(al, lo);
    int lhs = lo;
    int rhs = hi;
    while (1) {
        while (lhs < rhs && GETINT(AlGet(al, lhs)) < GETINT(toCompare)) {
            lhs += 1;
        }
        while (lhs < rhs && GETINT(AlGet(al, rhs)) > GETINT(toCompare)) {
            rhs -= 1;
        }
        if (lhs == rhs) {
            return lhs;
        }
        _swap(al, lhs, rhs);
    }
    return -1;
}

static void _quicksort_lomuto(cciArrayList_t *al, int lo, int hi) {
    int pivot = 0;
    if (lo < hi) {
        pivot = LomutoPartition(al, lo, hi);
        _quicksort_lomuto(al, lo, pivot - 1);
        _quicksort_lomuto(al, pivot + 1, hi);
    }
}

static void _quicksort_hoare(cciArrayList_t *al, int lo, int hi) {
    int pivot = 0;
    if (lo < hi) {
        pivot = HoarePartition(al, lo, hi);
        _quicksort_lomuto(al, lo, pivot - 1);
        _quicksort_lomuto(al, pivot + 1, hi);
    }
}

void AdmQuicksort(cciArrayList_t *al, enum PartitionScheme ps) {
    if (ps == PartitionScheme_Lomuto) {
        _quicksort_lomuto(al, 0, al->size - 1);
    } else if (ps == PartitionScheme_Hoare) {
        _quicksort_hoare(al, 0, al->size - 1);
    }
}
