//
// Created by wein on 3/3/18.
//

#include "cciHashTable.h"
#include <stdlib.h>

cciHashTable_t *NewHashTable() {
    cciHashTable_t *tb = (cciHashTable_t *)malloc(sizeof(cciHashTable_t));
    return tb;
}

void ISetInt(cciHashTable_t *hashTable, int key, int value) {
    ;
}

int IGetInt(cciHashTable_t *hashTable, int key) {
    return 0;
}

void DeleteHashTable(cciHashTable_t *hashTable) {
    free(hashTable);
}
