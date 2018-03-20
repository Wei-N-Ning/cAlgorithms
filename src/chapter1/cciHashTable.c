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
};

cciHashTable_t *NewHashTable(size_t size) {
    cciHashTable_t *tb = malloc(sizeof(cciHashTable_t));
    tb->slots = malloc(sizeof(cciHashSlot_t) * size);
    for (size_t i=0; i<size; ++i) {
        tb->slots[i].l = NewList();
    }
    tb->size = size;
    return tb;
}

void DeleteHashTable(cciHashTable_t *tb) {
    for (size_t i=0; i<tb->size; ++i) {
        DeleteList(tb->slots[i].l);
    }
    free(tb->slots);
    free(tb);
}

static unsigned int hashString(const char *s) {
    unsigned int h = 5381;
    for (unsigned char c=*s; c != '\0'; c=*++s) {
        h = h * 33 + c;
    }
    return h;
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
                return v;
            }
        }
    }
    return invalid();
}