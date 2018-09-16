//
// Created by wein on 3/4/18.
//

#include "cciArrayList.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

cciArrayList_t *CCI_AlNew() {
    cciArrayList_t *al = malloc(sizeof(cciArrayList_t));
    al->store = malloc(sizeof(cciValue_t) * 8);
    al->capacity = 8;
    al->size = 0;
    al->errCode = CCI_ARRAYLIST_NOERROR;
    return al;
}

void CCI_AlDelete(cciArrayList_t *al) {
    free(al->store);
    free(al);
}

static int validateIndex(cciArrayList_t *al, size_t index) {
    if (index >= al->size || index < 0) {
        return 0;
    }
    return 1;
}

static size_t increaseCapacity(cciArrayList_t *al, size_t newCapacity) {
    if (!newCapacity) {
        newCapacity = 2 * al->capacity;
    }
    cciValue_t *store = malloc(sizeof(cciValue_t) * newCapacity);
    memcpy(store, al->store, sizeof(cciValue_t) * al->size);
    free(al->store);
    al->store = store;
    al->capacity = newCapacity;
    return newCapacity;
}

void CCI_AlSet(cciArrayList_t *al, size_t index, cciValue_t value) {
    if (validateIndex(al, index)) {
        al->store[index] = value;
    }
    al->errCode = CCI_ARRAYLIST_INDEXERROR;
}

cciValue_t CCI_AlGet(cciArrayList_t *al, size_t index) {
    if (validateIndex(al, index)) {
        return al->store[index];
    }
    al->errCode = CCI_ARRAYLIST_INDEXERROR;
    return CCIValue_invalid();
}

void CCI_AlEmplaceBack(cciArrayList_t *al, cciValue_t value) {
    al->store[al->size] = value;
    al->size++;
    if (al->size > al->capacity / 2) {
        increaseCapacity(al, 0);
    }
}

cciValue_t CCI_AlBack(cciArrayList_t *al) {
    if (validateIndex(al, al->size - 1)) {
        return al->store[al->size - 1];
    }
    al->errCode = CCI_ARRAYLIST_INDEXERROR;
    return CCIValue_invalid();
}

void CCI_AlReserve(cciArrayList_t *al, size_t newCapacity) {
    if (newCapacity > al->capacity) {
        increaseCapacity(al, newCapacity);
    }
}

cciValue_t CCI_AlPopBack(cciArrayList_t *al) {
    if (! al->size) {
        return CCIValue_invalid();
    }
    return al->store[(al->size--) - 1];
}
// 0       4       8
// 1 2 3 4 5 6 7 8 9
// x x x x x x x
//         y y y y y o o
static void copyN(cciArrayList_t *al, size_t from, size_t to, size_t num) {
    size_t delta;
    if ((delta = to + num - al->size) > 0) {
        num -= delta;
    }
    memcpy(al->store + to, al->store + from, sizeof(int) * num);
}

void CCI_AlInsert(cciArrayList_t *al, size_t pos, cciValue_t value) {
    if (pos == 0 && al->size == 0) {
        CCI_AlEmplaceBack(al, value);
        return;
    }
    if (!validateIndex(al, pos)) {
        al->errCode = CCI_ARRAYLIST_INDEXERROR;
        return;
    }
    CCI_AlEmplaceBack(al, CCIValue_invalid());
    copyN(al, pos + 1, pos + 2, al->size);
    CCI_AlSet(al, pos + 1, value);
}

void CCI_AlPrint(cciArrayList_t *al) {
    for (size_t i=0; i < al->size; printf("%d ", CCIValue_GETINT(CCI_AlGet(al, i))), i++) ;
    printf("\n");
}
