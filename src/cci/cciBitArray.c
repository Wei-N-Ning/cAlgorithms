//
// Created by wein on 3/4/18.
//

#include "cciBitArray.h"
#include <limits.h>

#define IndexToSlot(index) ((index) / (sizeof(CCI_BitSlot) * CHAR_BIT))
#define IndexToNthBit(index) ((index) % (sizeof(CCI_BitSlot) * CHAR_BIT))
#define BytesBySlots(num) ((num) * sizeof(CCI_BitSlot))
#define NthBitMask(nth) (0xFFFFFFFF & (0b1 << (nth)))
#define BitsPerSlot (sizeof(CCI_BitSlot) * CHAR_BIT)

cciBitArray_t *CCI_BaNew(unsigned int initialBit, size_t numBits) {
    size_t numSlots = IndexToSlot(numBits - 1);
    if (IndexToNthBit(numBits - 1)) {
        numSlots++;
    }
    cciBitArray_t *ba = malloc(sizeof(cciBitArray_t));
    ba->store = malloc(BytesBySlots(numSlots));
    memset(ba->store, initialBit, BytesBySlots(numSlots));
    ba->slots = numSlots;
    ba->size = numBits;
    return ba;
}

cciBitArray_t *CCI_CreateBaFromUInt(unsigned int value) {
    cciBitArray_t *ba = CCI_BaNew(0, BitsPerSlot);
    memcpy(ba->store, &value, sizeof(CCI_BitSlot));
    return ba;
}

void CCI_BaOutput(cciBitArray_t *ba, CCI_BitSlot *o, size_t numBits) {
    size_t numBytes;
    if (!numBits) {
        numBytes = BytesBySlots(ba->slots);
    } else {
        numBytes = numBits / BitsPerSlot;
        if (numBits % BitsPerSlot) {
            numBytes++;
        }
    }
    memcpy(o, ba->store, numBytes);
}

void CCI_BaDelete(cciBitArray_t *ba) {
    free(ba->store);
    free(ba);
}

static CCI_BitSlot update(CCI_BitSlot slot, size_t nthBit, unsigned int bit) {
    CCI_BitSlot mask = NthBitMask(nthBit);
    if (bit) {
        return slot | mask;
    } else {
        return slot & (~mask);
    }
}

static unsigned int check(CCI_BitSlot slot, size_t nthBit) {
    CCI_BitSlot mask = NthBitMask(nthBit);
    if (slot & mask) {
        return 1;
    }
    return 0;
}

void CCI_BaSet(cciBitArray_t *ba, size_t index, unsigned int bit) {
    size_t nthInt = IndexToSlot(index);
    size_t nthBit = IndexToNthBit(index);
    ba->store[nthInt] = update(ba->store[nthInt], nthBit, bit);
}

unsigned int CCI_BaGet(cciBitArray_t *ba, size_t index) {
    size_t nthInt = IndexToSlot(index);
    size_t nthBit = IndexToNthBit(index);
    return check(ba->store[nthInt], nthBit);
}
