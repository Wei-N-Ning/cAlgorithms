//
// Created by wein on 3/4/18.
//

#include "cciBitArray.h"

cciBitArray_t *BaNew(unsigned int initialBit, size_t numBits) {
    size_t numBitSlots = numBits / sizeof(BitSlot) + 1;
    cciBitArray_t *ba = malloc(sizeof(cciBitArray_t));
    ba->store = malloc(sizeof(BitSlot) * numBitSlots);
    ba->size = numBits;
    memset(ba->store, initialBit, numBitSlots);
    return ba;
}

void BaDelete(cciBitArray_t *ba) {
    free(ba->store);
    free(ba);
}

static BitSlot update(BitSlot slot, size_t nthBit, unsigned int bit) {
    BitSlot mask = 0xFFFFFFFF & (0b1 << (nthBit -1));
    if (bit) {
        return slot | mask;
    } else {
        return slot & (~mask);
    }
}

static unsigned int check(BitSlot slot, size_t nthBit) {
    BitSlot mask = 0xFFFFFFFF & (0b1 << (nthBit - 1));
    if (slot & mask) {
        return 1;
    }
    return 0;
}

void BaSet(cciBitArray_t *ba, size_t index, unsigned int bit) {
    size_t nthInt = index / sizeof(int);
    size_t nthBit = index % sizeof(int);
    ba->store[nthInt] = update(ba->store[nthInt], nthBit, bit);
}

unsigned int BaGet(cciBitArray_t *ba, size_t index) {
    size_t nthInt = index / sizeof(int);
    size_t nthBit = index % sizeof(int);
    return check(ba->store[nthInt], nthBit);
}
