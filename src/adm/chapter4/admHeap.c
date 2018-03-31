//
// Created by wein on 3/29/18.
//

#include "admHeap.h"

#include <stdlib.h>
#include <stdio.h>

#include <cciArrayList.h>
#include <assert.h>

struct AdmHeap {
    cciArrayList_t *al;
    size_t size;
};

admHeap_t *CreateAdmHeap(size_t capacity) {
    admHeap_t *hp = malloc(sizeof(admHeap_t));
    hp->al = AlNew();
    hp->size = 0;
    AlReserve(hp->al, capacity);
    return hp;
}

void DeleteAdmHeap(admHeap_t *hp) {
    if (! hp) {
        return;
    }
    if (hp->al) {
        AlDelete(hp->al);
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
    return AlGet(pq->al, idx);
}

static void _swap(admHeap_t *pq, int from, int to) {
    cciValue_t tmp = AdmHeapGet(pq, from);
    assert(ISVALID(tmp));
    AlSet(pq->al, from, AlGet(pq->al, to));
    AlSet(pq->al, to, tmp);
}

static void bubbleUp(admHeap_t *pq, int idx) {
    int parentIndex = AdmParentIndex(pq, idx);
    if (ADM_HP_INVALID_INDEX == parentIndex) {
        return;
    }
    if (GETINT(AdmHeapGet(pq, parentIndex)) > GETINT(AdmHeapGet(pq, idx))) {
        _swap(pq, parentIndex, idx);
        bubbleUp(pq, parentIndex);
    }
}

void AdmHeapInsert(admHeap_t *pq, cciValue_t v) {
    AlEmplaceBack(pq->al, v);
    pq->size += 1;
    bubbleUp(pq, pq->size - 1);
}

static int _min(admHeap_t *pq, int lhs, int rhs) {
    cciValue_t l = AdmHeapGet(pq, lhs);
    cciValue_t r = AdmHeapGet(pq, rhs);
    if (rhs > pq->size - 1) {
        return lhs;
    }
    if (GETINT(l) < GETINT(r)) {
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

cciValue_t AdmHeapPop(admHeap_t *pq) {
    if (pq->size <= 0) {
        return invalid();
    }
    cciValue_t r = AdmHeapGet(pq, 0);
    _swap(pq, 0, pq->size - 1);
    AlPopBack(pq->al);
    pq->size -= 1;
    bubbleDown(pq, 0);
    return r;
}

void AdmHeapsortInts(int *ins, size_t sz) {
    admHeap_t *hp = CreateAdmHeap(sz);
    for (size_t i=sz; i--; AdmHeapInsert(hp, newInt(ins[i]))) ;
    for (size_t i=sz; i--; ins[sz - 1 - i] = GETINT(AdmHeapPop(hp))) ;
    DeleteAdmHeap(hp);
}

void Heapify(cciArrayList_t *al) {
    admHeap_t *hp = malloc(sizeof(admHeap_t));
    hp->size = al->size;
    hp->al = al;
    for (size_t i=hp->size; i--; ) {
        bubbleDown(hp, i);
    }
    hp->al = NULL;
    hp->size = 0;
    DeleteAdmHeap(hp);
}

void AdmHeapsortAl(cciArrayList_t *al) {
    admHeap_t *hp = malloc(sizeof(admHeap_t));
    cciValue_t tmp;
    hp->size = al->size;
    hp->al = al;
    for (size_t i=hp->size; i--; bubbleDown(hp, i)) ;
    for (size_t i=hp->size; i--; ) {
        tmp = AdmHeapPop(hp);
        AlEmplaceBack(al, tmp);
    }
    hp->al = NULL;
    hp->size = 0;
    DeleteAdmHeap(hp);
}