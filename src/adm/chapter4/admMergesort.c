//
// Created by wein on 4/1/18.
//

#include "admMergesort.h"

#include <cci/cciQueue.h>

static void _merge(cciArrayList_t *al, size_t from1, size_t to1, size_t from2, size_t to2) {
    cciQueue_t *qu1 = CCI_CreateQueue();
    cciQueue_t *qu2 = CCI_CreateQueue();
    size_t i = from1;
    for (size_t idx=from1; idx<=to1; CCI_Enqueue(qu1, CCI_AlGet(al, idx)), idx++) ;
    for (size_t idx=from2; idx<=to2; CCI_Enqueue(qu2, CCI_AlGet(al, idx)), idx++) ;
    while (! (CCI_QueueEmpty(qu1) || CCI_QueueEmpty(qu2))) {
        if (CCIValue_GETINT(CCI_QueueFront(qu1)) < CCIValue_GETINT(CCI_QueueFront(qu2))) {
            CCI_AlSet(al, i++, CCI_Dequeue(qu1));
        } else {
            CCI_AlSet(al, i++, CCI_Dequeue(qu2));
        }
    }
    while (! CCI_QueueEmpty(qu1)) {
        CCI_AlSet(al, i++, CCI_Dequeue(qu1));
    }
    while (! CCI_QueueEmpty(qu2)) {
        CCI_AlSet(al, i++, CCI_Dequeue(qu2));
    }
    CCI_DeleteQueue(qu1);
    CCI_DeleteQueue(qu2);
}

static void _sortRange(cciArrayList_t *al, size_t from, size_t to) {
    if (from < to) {
        size_t mid = from + (to - from) / 2;
        _sortRange(al, from, mid);
        _sortRange(al, mid + 1, to);
        _merge(al, from, mid, mid + 1, to);
    }
}

void Mergesort(cciArrayList_t *al) {
    _sortRange(al, 0, al->size - 1);
}