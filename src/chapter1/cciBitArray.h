//
// Created by wein on 3/4/18.
//
// A fix sized bit array

#ifndef CCISOLUTIONSC_CCIBITARRAY_H
#define CCISOLUTIONSC_CCIBITARRAY_H

#include <stdlib.h>
#include <memory.h>

typedef unsigned int BitSlot;

typedef struct {
    BitSlot *store;
    size_t size;
} cciBitArray_t;

cciBitArray_t *BaNew(unsigned int initialBit, size_t numBits);

void BaDelete(cciBitArray_t *ba);

void BaSet(cciBitArray_t *ba, size_t index, unsigned int bit);

unsigned int BaGet(cciBitArray_t *ba, size_t index);

#endif //CCISOLUTIONSC_CCIBITARRAY_H
