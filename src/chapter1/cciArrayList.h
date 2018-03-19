//
// Created by wein on 3/4/18.
//

#ifndef CCISOLUTIONSC_CCIARRAYLIST_H
#define CCISOLUTIONSC_CCIARRAYLIST_H

#include "cciValue.h"

#include <stddef.h>

typedef enum {
    CCI_ARRAYLIST_NOERROR,
    CCI_ARRAYLIST_INDEXERROR,
} CCI_ARRAYLIST_ERRORS;

typedef struct {
    cciValue_t *store;
    size_t capacity;
    size_t size;
    CCI_ARRAYLIST_ERRORS errCode;
} cciArrayList_t;

cciArrayList_t *AlNew();

void AlDelete(cciArrayList_t *al);

void AlSet(cciArrayList_t *al, size_t index, cciValue_t value);

cciValue_t AlGet(cciArrayList_t *al, size_t index);

void AlEmplaceBack(cciArrayList_t *al, cciValue_t value);

cciValue_t AlBack(cciArrayList_t *al);

void AlReserve(cciArrayList_t *al, size_t newCapacity);

cciValue_t AlPopBack(cciArrayList_t *al);

void AlInsert(cciArrayList_t *al, size_t index, cciValue_t value);

#endif //CCISOLUTIONSC_CCIARRAYLIST_H
