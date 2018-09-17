//
// Created by wein on 3/3/18.
//

#ifndef CCISOLUTIONSC_CCIHASHTABLE_H
#define CCISOLUTIONSC_CCIHASHTABLE_H

#include "cciValue.h"
#include "cciArrayList.h"

typedef struct cciHashTable cciHashTable_t;

cciHashTable_t *CCI_NewHashTable(size_t size);

void CCI_DeleteHashTable(cciHashTable_t *tb);

void CCI_SSet(cciHashTable_t *tb, char *key, cciValue_t value);
cciValue_t CCI_SGet(cciHashTable_t *tb, const char *key);
cciValue_t CCI_SPop(cciHashTable_t *tb, const char *key);

void CCI_ISet(cciHashTable_t *tb, uint64_t key, cciValue_t value);
cciValue_t CCI_IGet(cciHashTable_t *tb, uint64_t key);
cciValue_t *CCI_IGetOrCreate(cciHashTable_t *tb, uint64_t key);
cciValue_t CCI_IPop(cciHashTable_t *tb, uint64_t key);

size_t CCI_HashTableNumKeys(cciHashTable_t *tb);
size_t CCI_HashTableSize(cciHashTable_t *tb);

typedef void (*cci_ht_callback_t)(size_t index, size_t slotPos, cciValue_t *k, cciValue_t *v);

void CCI_HTIterate(cciHashTable_t *tb, cci_ht_callback_t cb);

void CCI_HTGetValues(cciHashTable_t *tb, cciArrayList_t *o_values);

//////// utility

void CCI_HTMetrics(
    cciHashTable_t *tb,
    double *o_utilization,  // slots used
    double *o_chainFactor,  // average length of the chain
    double *o_collisionRate  // num collision / num slots used
);

#endif //CCISOLUTIONSC_CCIHASHTABLE_H
