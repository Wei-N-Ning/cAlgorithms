//
// Created by wein on 3/3/18.
//

#include "cciHashTable.h"
#include "cciList.h"
#include <stdlib.h>

#ifndef DEFAULTHASHTABLESIZE
#define DEFAULTHASHTABLESIZE 1024
#endif

unsigned int hashInt(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

unsigned int hashString(const char *s) {
    unsigned int h = 5381;
    for (unsigned char c=*s; c != '\0'; c=*++s) {
        h = h * 33 + c;
    }
    return h;
}

void initSlots(cciHashTable_t *tb) {
    int size = DEFAULTHASHTABLESIZE;
    tb->store = (cciList_t **)malloc(sizeof(cciList_t *) * size);
    for (int i=0; i < size; ++i) {
        tb->store[i] = NewList();
    }
    tb->size = size;
}

cciHashTable_t *NewHashTable() {
    cciHashTable_t *tb = (cciHashTable_t *)malloc(sizeof(cciHashTable_t));
    initSlots(tb);
    return tb;
}

void DeleteHashTable(cciHashTable_t *hashTable) {
    cciList_t *l = NULL;
    for (int i=0; i < hashTable->size; ++i) {
        l = hashTable->store[i];
        DeleteList(l);
        hashTable->store[i] = NULL;
    }
    free(hashTable->store);
    free(hashTable);
}

cciList_t *slot(cciHashTable_t *tb, const char *key) {
    unsigned int h = hashString(key);
    return tb->store[h % tb->size];
}

void SSetInt(cciHashTable_t *tb, const char *key, int value) {
    cciList_t *l = slot(tb, key);
    AppendInt(l, value);
}

int SGetInt(cciHashTable_t *tb, const char *key) {
    cciList_t *l = slot(tb, key);
    if (l->size == 0) {
        tb->errCode = CCIHASHTABLE_KEY_NOTFOUND;
        return 0;
    }
    return GetInt(l, 0);
}
