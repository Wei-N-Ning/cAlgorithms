//
// Created by wein on 3/3/18.
//

#ifndef CCISOLUTIONSC_CCIHASHTABLE_H
#define CCISOLUTIONSC_CCIHASHTABLE_H

void *NewHashTable();

ISetInt(void *hashTable, int key, int value);

int IGetInt(void *hashTable, int key);

DeleteHashTable(void *hashTable);

#endif //CCISOLUTIONSC_CCIHASHTABLE_H
