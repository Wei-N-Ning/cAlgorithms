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

cciArrayList_t *CCI_AlNew();

void CCI_AlDelete(cciArrayList_t *al);

void CCI_AlSet(cciArrayList_t *al, size_t index, cciValue_t value);

cciValue_t CCI_AlGet(cciArrayList_t *al, size_t index);

void CCI_AlEmplaceBack(cciArrayList_t *al, cciValue_t value);

cciValue_t CCI_AlBack(cciArrayList_t *al);

void CCI_AlReserve(cciArrayList_t *al, size_t newCapacity);

cciValue_t CCI_AlPopBack(cciArrayList_t *al);

void CCI_AlInsert(cciArrayList_t *al, size_t index, cciValue_t value);

void CCI_AlPrint(cciArrayList_t *al);

#endif //CCISOLUTIONSC_CCIARRAYLIST_H
