//
// Created by wein on 3/29/18.
//

#ifndef CCISOLUTIONSC_ADMHEAP_H
#define CCISOLUTIONSC_ADMHEAP_H

#include <stddef.h>
#include <cciValue.h>
#include <cciArrayList.h>

#define ADM_HP_INVALID_INDEX (-1)

struct AdmHeap;
typedef struct AdmHeap admHeap_t;

admHeap_t *CreateAdmHeap(size_t capacity);

void DeleteAdmHeap(admHeap_t *hp);

int AdmParentIndex(const admHeap_t *pq, int idx);

int AdmLeftChildIndex(const admHeap_t *pq, int idx);

cciValue_t AdmHeapGet(const admHeap_t *pq, int idx);

void AdmHeapInsert(admHeap_t *pq, cciValue_t v);

cciValue_t AdmHeapPop(admHeap_t *pq);

void AdmHeapsortInts(int *ins, size_t sz);

void Heapify(cciArrayList_t *al);

void AdmHeapsortAl(cciArrayList_t *al);

#endif //CCISOLUTIONSC_ADMHEAP_H
