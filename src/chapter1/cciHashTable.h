//
// Created by wein on 3/3/18.
//

#ifndef CCISOLUTIONSC_CCIHASHTABLE_H
#define CCISOLUTIONSC_CCIHASHTABLE_H

#include "cciList.h"
#include "cciValue.h"

typedef enum CCIHASHTABLE_ERROR_CODE {
    CCIHASHTABLE_NOERROR,
    CCIHASHTABLE_KEY_NOTFOUND,
} CCIHASHTABLE_ERROR_CODE;

typedef struct cciHashTable {
    cciList_t **store;
    size_t size;
    CCIHASHTABLE_ERROR_CODE errCode;
} cciHashTable_t;

cciHashTable_t *NewHashTable();

void DeleteHashTable(cciHashTable_t *hashTable);

void SSet(cciHashTable_t *hashTable, const char *key, cciValue_t value);

cciValue_t SGet(cciHashTable_t *hashTable, const char *key);

#endif //CCISOLUTIONSC_CCIHASHTABLE_H
