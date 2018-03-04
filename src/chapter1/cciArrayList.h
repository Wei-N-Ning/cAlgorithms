//
// Created by wein on 3/4/18.
//

#ifndef CCISOLUTIONSC_CCIARRAYLIST_H
#define CCISOLUTIONSC_CCIARRAYLIST_H

typedef enum {
    CCI_ARRAYLIST_NOERROR,
    CCI_ARRAYLIST_INDEXERROR,
} CCI_ARRAYLIST_ERRORS;

typedef struct {
    int *store;
    unsigned int capacity;
    unsigned int size;
    CCI_ARRAYLIST_ERRORS errCode;
} cciArrayList_t;

cciArrayList_t *AlNew();

void AlDelete(cciArrayList_t *al);

void AlSetInt(cciArrayList_t *al, int key, int value);

int AlGetInt(cciArrayList_t *al, int key);

void AlEmplaceBack(cciArrayList_t *al, int value);

int AlBack(cciArrayList_t *al);

void AlReserve(cciArrayList_t *al, unsigned int newCapacity);

int AlPopBack(cciArrayList_t *al);

void AlInsertInt(cciArrayList_t *al, int key, int value);

#endif //CCISOLUTIONSC_CCIARRAYLIST_H
