//
// Created by wein on 3/3/18.
//

#ifndef CCISOLUTIONSC_CCIHASHTABLE_H
#define CCISOLUTIONSC_CCIHASHTABLE_H

typedef struct cciHashTable {
    int __;
} cciHashTable_t;

cciHashTable_t *NewHashTable();

void ISetInt(cciHashTable_t *hashTable, int key, int value);

int IGetInt(cciHashTable_t *hashTable, int key);

void DeleteHashTable(cciHashTable_t *hashTable);

#endif //CCISOLUTIONSC_CCIHASHTABLE_H
