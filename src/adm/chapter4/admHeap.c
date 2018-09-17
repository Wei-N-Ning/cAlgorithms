//
// Created by wein on 3/29/18.
//

#include "admHeap.h"

#include <cci/cciArrayList.h>

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct AdmHeap {
    cciArrayList_t *al;
    size_t size;
};

admHeap_t *CreateAdmHeap(size_t capacity) {
    admHeap_t *hp = malloc(sizeof(admHeap_t));
    hp->al = CCI_AlNew();
    hp->size = 0;
    CCI_AlReserve(hp->al, capacity);
    return hp;
}

void DeleteAdmHeap(admHeap_t *hp) {
    if (! hp) {
        return;
    }
    if (hp->al) {
        CCI_AlDelete(hp->al);
    }
    free(hp);
}

int AdmParentIndex(const admHeap_t *pq, int idx) {
    int num = idx + 1;
    if (num <= 1) {
        return ADM_HP_INVALID_INDEX;
    }
    return (int)(num / 2.0) - 1;
}

int AdmLeftChildIndex(const admHeap_t *pq, int idx) {
    int num = (idx + 1) * 2 - 1;
    if (num >= pq->size) {
        return ADM_HP_INVALID_INDEX;
    }
    return num;
}

cciValue_t AdmHeapGet(const admHeap_t *pq, int idx) {
    return CCI_AlGet(pq->al, idx);
}

static void _swap(admHeap_t *pq, int from, int to) {
    cciValue_t tmp = AdmHeapGet(pq, from);
    assert(CCIValue_ISVALID(tmp));
    CCI_AlSet(pq->al, from, CCI_AlGet(pq->al, to));
    CCI_AlSet(pq->al, to, tmp);
}

static void bubbleUp(admHeap_t *pq, int idx) {
    int parentIndex = AdmParentIndex(pq, idx);
    if (ADM_HP_INVALID_INDEX == parentIndex) {
        return;
    }
    if (CCIValue_GETINT(AdmHeapGet(pq, parentIndex)) >
        CCIValue_GETINT(AdmHeapGet(pq, idx))) {
        _swap(pq, parentIndex, idx);
        bubbleUp(pq, parentIndex);
    }
}

static void bubbleUp_max(admHeap_t *pq, int idx) {
    int parentIndex = AdmParentIndex(pq, idx);
    if (ADM_HP_INVALID_INDEX == parentIndex) {
        return;
    }
    if (CCIValue_GETINT(AdmHeapGet(pq, parentIndex)) <
        CCIValue_GETINT(AdmHeapGet(pq, idx))) {
        _swap(pq, parentIndex, idx);
        bubbleUp(pq, parentIndex);
    }
}

void AdmHeapInsert(admHeap_t *pq, cciValue_t v) {
    CCI_AlEmplaceBack(pq->al, v);
    pq->size += 1;
    bubbleUp(pq, pq->size - 1);
}

static int _min(admHeap_t *pq, int lhs, int rhs) {
    cciValue_t l = AdmHeapGet(pq, lhs);
    cciValue_t r = AdmHeapGet(pq, rhs);
    if (rhs > pq->size - 1) {
        return lhs;
    }
    if (CCIValue_GETINT(l) < CCIValue_GETINT(r)) {
        return lhs;
    }
    return rhs;
}

static int _max(admHeap_t *pq, int lhs, int rhs) {
    cciValue_t l = AdmHeapGet(pq, lhs);
    cciValue_t r = AdmHeapGet(pq, rhs);
    if (rhs > pq->size - 1) {
        return lhs;
    }
    if (CCIValue_GETINT(l) > CCIValue_GETINT(r)) {
        return lhs;
    }
    return rhs;
}

static void bubbleDown(admHeap_t *pq, int parentIdx) {
    int childIdx = AdmLeftChildIndex(pq, parentIdx);
    if (childIdx == ADM_HP_INVALID_INDEX) {
        return;
    }
    int minIdx = _min(pq, parentIdx, childIdx);
    minIdx = _min(pq, minIdx, childIdx + 1);
    if (minIdx != parentIdx) {
        _swap(pq, minIdx, parentIdx);
        bubbleDown(pq, minIdx);
    }
}

static void bubbleDown_max(admHeap_t *pq, int parentIdx) {
    int childIdx = AdmLeftChildIndex(pq, parentIdx);
    if (childIdx == ADM_HP_INVALID_INDEX) {
        return;
    }
    int maxIdx = _max(pq, parentIdx, childIdx);
    maxIdx = _max(pq, maxIdx, childIdx + 1);
    if (maxIdx != parentIdx) {
        _swap(pq, maxIdx, parentIdx);
        bubbleDown_max(pq, maxIdx);
    }
}

cciValue_t AdmHeapPop(admHeap_t *pq) {
    if (pq->size <= 0) {
        return CCIValue_invalid();
    }
    cciValue_t r = AdmHeapGet(pq, 0);
    _swap(pq, 0, pq->size - 1);

    // not calling AlPopBack() for two good reasons:
    // 1) bubbleUp(), bubbleDown() and _min() must be doing boundary checks only; in the previous implementations
    // they were validating the cci value objects - this was problematic
    // 2) the cci values that are swapped to the bottom form a natural sorted array - this can be directly returned to
    // the caller; the order will be reversed hence min-heapsort should use max-bubbleUp/Down() functions

    pq->size -= 1;
    bubbleDown(pq, 0);
    return r;
}

cciValue_t AdmHeapPop_max(admHeap_t *pq) {
    if (pq->size <= 0) {
        return CCIValue_invalid();
    }
    cciValue_t r = AdmHeapGet(pq, 0);
    _swap(pq, 0, pq->size - 1);
    pq->size -= 1;
    bubbleDown_max(pq, 0);
    return r;
}

void AdmHeapsortInts(int *ins, size_t sz) {
    admHeap_t *hp = CreateAdmHeap(sz);
    for (size_t i=sz; i--; AdmHeapInsert(hp, CCIValue_newInt(ins[i]))) ;
    for (size_t i=sz; i--; ins[sz - 1 - i] = CCIValue_GETINT(AdmHeapPop(hp))) ;
    DeleteAdmHeap(hp);
}

void Heapify(cciArrayList_t *al) {
    admHeap_t *hp = malloc(sizeof(admHeap_t));
    hp->size = al->size;
    hp->al = al;

    // reason for traversing from the tail:
    // (ADM P127)
    // consider the array in reverse order, starting from the last (nth) position.
    // It represents a leaf of the tree and so dominates its nonexistent children.
    // The same is the case for the last n/2 positions in the array, because all
    // are leaves.
    // If we continue to walk backwards through the array we will finally encounter
    // an internal node with children. This element may not dominate its children,
    // but its children represent well-formed (if small) heaps.
    for (size_t i=hp->size; i--; ) {
        bubbleDown(hp, i);
    }
    hp->al = NULL;
    hp->size = 0;
    DeleteAdmHeap(hp);
}

// NOTE: use max-heap for ascending order, min-heap for descending order
// see the implementation of AdmHeapPop()
void AdmHeapsortAl(cciArrayList_t *al, enum AdmHeapDirection dir) {
    admHeap_t *hp = malloc(sizeof(admHeap_t));
    hp->size = al->size;
    hp->al = al;
    if (dir == AdmHeapDirection_Descending) {

        // see heapify() for more details
        for (size_t i=hp->size; i--; bubbleDown(hp, i)) ;
        for (size_t i=hp->size; i--; AdmHeapPop(hp)) ;
    } else {
        for (size_t i=hp->size; i--; bubbleDown_max(hp, i)) ;
        for (size_t i=hp->size; i--; AdmHeapPop_max(hp)) ;
    }
    hp->al = NULL;
    hp->size = 0;
    DeleteAdmHeap(hp);
}

