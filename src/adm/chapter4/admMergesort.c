//
// Created by wein on 4/1/18.
//

#include "admMergesort.h"

#include <cciQueue.h>

static void _merge(cciArrayList_t *al, size_t from1, size_t to1, size_t from2, size_t to2) {
    cciQueue_t *qu1 = CreateCCIQueue();
    cciQueue_t *qu2 = CreateCCIQueue();
    size_t i = from1;
    for (size_t idx=from1; idx<=to1; Enqueue(qu1, AlGet(al, idx)), idx++) ;
    for (size_t idx=from2; idx<=to2; Enqueue(qu2, AlGet(al, idx)), idx++) ;
    while (! (CCIQueueEmpty(qu1) || CCIQueueEmpty(qu2))) {
        if (GETINT(CCIQueueFront(qu1)) < GETINT(CCIQueueFront(qu2))) {
            AlSet(al, i++, Dequeue(qu1));
        } else {
            AlSet(al, i++, Dequeue(qu2));
        }
    }
    while (! CCIQueueEmpty(qu1)) {
        AlSet(al, i++, Dequeue(qu1));
    }
    while (! CCIQueueEmpty(qu2)) {
        AlSet(al, i++, Dequeue(qu2));
    }
    DeleteCCIQueue(qu1);
    DeleteCCIQueue(qu2);
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