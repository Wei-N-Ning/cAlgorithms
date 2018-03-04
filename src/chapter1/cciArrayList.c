//
// Created by wein on 3/4/18.
//

#include "cciArrayList.h"
#include <stdlib.h>
#include <memory.h>

cciArrayList_t *AlNew() {
    cciArrayList_t *al = malloc(sizeof(cciArrayList_t));
    al->store = malloc(sizeof(int *) * 8);
    al->capacity = 8;
    al->size = 0;
    al->errCode = CCI_ARRAYLIST_NOERROR;
    return al;
}

void AlDelete(cciArrayList_t *al) {
    free(al->store);
    free(al);
}

static int validateIndex(cciArrayList_t *al, int key) {
    if (key >= al->size || key < 0) {
        return 0;
    }
    return 1;
}

static int increaseCapacity(cciArrayList_t *al, unsigned int newCapacity) {
    if (!newCapacity) {
        newCapacity = 2 * al->capacity;
    }
    int *store = malloc(sizeof(int *) * newCapacity);
    memcpy(store, al->store, sizeof(int) * al->size);
    free(al->store);
    al->store = store;
    al->capacity = newCapacity;
    return newCapacity;
}

void AlSetInt(cciArrayList_t *al, int key, int value) {
    if (validateIndex(al, key)) {
        al->store[key] = value;
    }
    al->errCode = CCI_ARRAYLIST_INDEXERROR;
}

int AlGetInt(cciArrayList_t *al, int key) {
    if (validateIndex(al, key)) {
        return al->store[key];
    }
    al->errCode = CCI_ARRAYLIST_INDEXERROR;
    return 0;
}

void AlEmplaceBack(cciArrayList_t *al, int value) {
    al->store[al->size] = value;
    al->size++;
    if (al->size > al->capacity / 2) {
        increaseCapacity(al, 0);
    }
}

int AlBack(cciArrayList_t *al) {
    if (validateIndex(al, al->size - 1)) {
        return al->store[al->size - 1];
    }
    al->errCode = CCI_ARRAYLIST_INDEXERROR;
    return 0;
}

void AlReserve(cciArrayList_t *al, unsigned int newCapacity) {
    if (newCapacity > al->capacity) {
        increaseCapacity(al, newCapacity);
    }
}

int AlPopBack(cciArrayList_t *al) {
    return al->store[(al->size--) - 1];
}
// 0       4       8
// 1 2 3 4 5 6 7 8 9
// x x x x x x x
//         y y y y y o o
static void copyN(cciArrayList_t *al, int from, int to, int num) {
    int delta;
    if ((delta = to + num - al->size) > 0) {
        num -= delta;
    }
    memcpy(al->store + to, al->store + from, sizeof(int) * num);
}

void AlInsertInt(cciArrayList_t *al, int pos, int value) {
    if (pos == 0 && al->size == 0) {
        AlEmplaceBack(al, value);
        return;
    }
    if (!validateIndex(al, pos)) {
        al->errCode = CCI_ARRAYLIST_INDEXERROR;
        return;
    }
    AlEmplaceBack(al, 0);
    copyN(al, pos + 1, pos + 2, al->size);
    AlSetInt(al, pos + 1, value);
}

