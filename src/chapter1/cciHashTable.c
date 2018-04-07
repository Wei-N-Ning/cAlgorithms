//
// Created by wein on 3/20/18.
//

#include "cciHashTable.h"

#include <stdlib.h>
#include <string.h>

#include "cciArrayList.h"
#include "cciList.h"

// each element in the array holds a cciHashSlot, which
// encapsulates a cciList (doubly linked list)
// [ ] [ ] [ ] ...... [ ] [ ] [ ]
//  |   |   |
//  o   o   o
//  o

// key1->value1->key2->value2....
typedef struct cciHashSlot {
    cciList_t *l;
} cciHashSlot_t;

struct cciHashTable {
    cciHashSlot_t *slots;
    size_t size;
    size_t nkeys;
};

cciHashTable_t *NewHashTable(size_t size) {
    cciHashTable_t *tb = malloc(sizeof(cciHashTable_t));
    tb->slots = malloc(sizeof(cciHashSlot_t) * size);
    for (size_t i=0; i<size; ++i) {
        tb->slots[i].l = NewList();
    }
    tb->size = size;
    tb->nkeys = 0;
    return tb;
}

void DeleteHashTable(cciHashTable_t *tb) {
    for (size_t i=0; i<tb->size; ++i) {
        DeleteList(tb->slots[i].l);
    }
    free(tb->slots);
    free(tb);
}

static uint64_t hashInt(uint64_t x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

static unsigned int hashString(const char *s) {
    unsigned int h = 5381;
    for (unsigned char c=*s; c != '\0'; c=*++s) {
        h = h * 33 + c;
    }
    return h;
}

size_t HashTableSize(cciHashTable_t *tb) {
    return tb->size;
}

size_t HashTableNumKeys(cciHashTable_t *tb) {
    return tb->nkeys;
}

void SSet(cciHashTable_t *tb, const char *key, cciValue_t value) {
    size_t index = hashString(key) % tb->size;
    cciList_t *l = tb->slots[index].l;
    cciValue_t svalue;
    if (l->size) {
        for (size_t slotPos = 0; slotPos < l->size; slotPos += 2) {
            svalue = Get(l, slotPos);
            if (strcmp(GETSTR(svalue), key) == 0) {
                Set(l, slotPos + 1, value);
                return;
            }
        }
    }
    Append(l, newStr(key));
    Append(l, value);
    tb->nkeys++;
}

cciValue_t SGet(cciHashTable_t *tb, const char *key) {
    size_t index = hashString(key) % tb->size;
    cciList_t *l = tb->slots[index].l;
    cciValue_t svalue;
    if (l->size) {
        for (size_t slotPos = 0; slotPos < l->size; slotPos += 2) {
            svalue = Get(l, slotPos);
            if (strcmp(GETSTR(svalue), key) == 0) {
                return Get(l, slotPos+1);
            }
        }
    }
    return invalid();
}

// similar to Python's dict.pop() method
cciValue_t SPop(cciHashTable_t *tb, const char *key) {
    size_t index = hashString(key) % tb->size;
    cciList_t *l = tb->slots[index].l;
    cciValue_t k;
    cciValue_t v;
    if (l->size) {
        for (size_t slotPos = 0; slotPos < l->size; slotPos += 2) {
            k = Get(l, slotPos);
            if (strcmp(GETSTR(k), key) == 0) {
                v = Get(l, slotPos+1);
                Remove(l, slotPos);
                Remove(l, slotPos); // slotPos now holds the value
                tb->nkeys--;
                return v;
            }
        }
    }
    return invalid();
}

void ISet(cciHashTable_t *tb, uint64_t key, cciValue_t value) {
    size_t index = hashInt(key) % tb->size;
    cciList_t *l = tb->slots[index].l;
    cciValue_t svalue;
    if (l->size) {
        for (size_t slotPos = 0; slotPos < l->size; slotPos += 2) {
            svalue = Get(l, slotPos);
            if (key == GETINT(svalue)) {
                Set(l, slotPos + 1, value);
                return;
            }
        }
    }
    Append(l, newInt(key));
    Append(l, value);
    tb->nkeys += 1;
}

cciValue_t IGet(cciHashTable_t *tb, uint64_t key) {
    size_t index = hashInt(key) % tb->size;
    cciList_t *l = tb->slots[index].l;
    cciValue_t svalue;
    if (l->size) {
        for (size_t slotPos = 0; slotPos < l->size; slotPos += 2) {
            svalue = Get(l, slotPos);
            if (key == GETINT(svalue)) {
                return Get(l, slotPos+1);
            }
        }
    }
    return invalid();
}

cciValue_t *IGetOrCreate(cciHashTable_t *tb, uint64_t key) {
    size_t index = hashInt(key) % tb->size;
    cciList_t *l = tb->slots[index].l;
    cciValue_t svalue;
    if (l->size) {
        for (size_t slotPos = 0; slotPos < l->size; slotPos += 2) {
            svalue = Get(l, slotPos);
            if (key == GETINT(svalue)) {
                return GetR(l, slotPos+1);
            }
        }
    }
    tb->nkeys += 1;
    Append(l, newInt(key));
    return AppendR(l, invalid());
}

cciValue_t IPop(cciHashTable_t *tb, uint64_t key) {
    size_t index = hashInt(key) % tb->size;
    cciList_t *l = tb->slots[index].l;
    cciValue_t k;
    cciValue_t v;
    if (l->size) {
        for (size_t slotPos = 0; slotPos < l->size; slotPos += 2) {
            k = Get(l, slotPos);
            if (key == GETINT(k)) {
                v = Get(l, slotPos+1);
                Remove(l, slotPos);
                Remove(l, slotPos); // slotPos now holds the value
                tb->nkeys--;
                return v;
            }
        }
    }
    return invalid();
}

void Iterate(cciHashTable_t *tb, callback_t cb)  {
    cciHashSlot_t *slot;
    cciValue_t k;
    cciValue_t v;
    if (! cb) {
        return;
    }
    for (size_t i=0; i<tb->size; ++i) {
        slot = tb->slots + i;
        for (size_t pos=0; pos<slot->l->size; pos+=2) {
            k = Get(slot->l, pos);
            v = Get(slot->l, pos+1);
            cb(i, pos, &k, &v);
        }
    }
}

void Metrics(
    cciHashTable_t *tb,
    double *o_utilization,
    double *o_chainFactor,
    double *o_collisionRate
) {
    size_t sizeTotal = HashTableSize(tb);
    size_t sizeUtilized = 0;
    size_t sizeCollision = 0;
    size_t longestChain = 0;
    size_t chainLength = 0;
    long totalChainLength = 0;
    for (size_t i=0; i<tb->size; ++i) {
        chainLength = tb->slots[i].l->size / 2;
        if (chainLength) {
            sizeUtilized +=1;
        }
        if (chainLength > longestChain) {
            longestChain = chainLength;
        }
        if (chainLength > 1) {
            sizeCollision += 1;
        }
        totalChainLength += chainLength;
    }
    *o_utilization = (double)sizeUtilized / (double)sizeTotal;
    *o_chainFactor = (double)longestChain / (double)sizeTotal;
    *o_collisionRate = (double)sizeCollision / (double)sizeTotal;
}
