//
// Created by wein on 3/4/18.
//
// A fix sized bit array

#ifndef CCISOLUTIONSC_CCIBITARRAY_H
#define CCISOLUTIONSC_CCIBITARRAY_H

#include <stdlib.h>
#include <memory.h>

typedef unsigned int CCI_BitSlot;

typedef struct {
    CCI_BitSlot *store;
    size_t size;
    size_t slots;
} cciBitArray_t;

cciBitArray_t *CCI_BaNew(unsigned int initialBit, size_t numBits);

cciBitArray_t *CCI_CreateBaFromUInt(unsigned int value);

void CCI_BaOutput(cciBitArray_t *ba, CCI_BitSlot *o, size_t numBits);

void CCI_BaDelete(cciBitArray_t *ba);

void CCI_BaSet(cciBitArray_t *ba, size_t index, unsigned int bit);

unsigned int CCI_BaGet(cciBitArray_t *ba, size_t index);

#endif //CCISOLUTIONSC_CCIBITARRAY_H
