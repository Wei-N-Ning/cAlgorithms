//
// Created by wein on 3/3/18.
//

#ifndef CCISOLUTIONSC_CCIHASHTABLE_H
#define CCISOLUTIONSC_CCIHASHTABLE_H

#include "cciValue.h"

typedef struct cciHashTable cciHashTable_t;

cciHashTable_t *NewHashTable(size_t size);

void DeleteHashTable(cciHashTable_t *tb);

void SSet(cciHashTable_t *tb, const char *key, cciValue_t value);
cciValue_t SGet(cciHashTable_t *tb, const char *key);
cciValue_t SPop(cciHashTable_t *tb, const char *key);

void ISet(cciHashTable_t *tb, uint64_t key, cciValue_t value);
cciValue_t IGet(cciHashTable_t *tb, uint64_t key);
cciValue_t *IGetOrCreate(cciHashTable_t *tb, uint64_t key);
cciValue_t IPop(cciHashTable_t *tb, uint64_t key);

size_t HashTableNumKeys(cciHashTable_t *tb);
size_t HashTableSize(cciHashTable_t *tb);

typedef void (*callback_t)(size_t index, size_t slotPos, cciValue_t *k, cciValue_t *v);

void Iterate(cciHashTable_t *tb, callback_t cb);

//////// utility

void Metrics(
    cciHashTable_t *tb,
    double *o_utilization,  // slots used
    double *o_chainFactor,  // average length of the chain
    double *o_collisionRate  // num collision / num slots used
);

#endif //CCISOLUTIONSC_CCIHASHTABLE_H
