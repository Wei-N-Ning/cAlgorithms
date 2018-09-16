//
// Created by wein on 3/3/18.
//

#ifndef CCISOLUTIONSC_CCILIST_H
#define CCISOLUTIONSC_CCILIST_H

#include "cciValue.h"

typedef enum CCILIST_ERROR {
    CCILIST_NO_ERROR,
    CCILIST_INDEX_ERROR,
    CCILIST_VALUE_NOTFOUND,
} CCILIST_ERROR;

typedef struct cciList {
    struct cciListNode *head;
    struct cciListNode *tail;
    size_t size;
    CCILIST_ERROR errCode;
} cciList_t;

cciList_t *CCI_NewList();

void CCI_DeleteList(cciList_t *l);

void CCI_ListAppend(cciList_t *l, cciValue_t value);

// returns a pointer to the value in the list
cciValue_t *CCI_ListAppendR(cciList_t *l, cciValue_t value);

cciValue_t CCI_ListGet(cciList_t *l, size_t index);

// returns a pointer to the value in the list
cciValue_t *CCI_ListGetR(cciList_t *l, size_t index);

void CCI_ListSet(cciList_t *l, size_t index, cciValue_t value);

void CCI_ListInsert(cciList_t *l, size_t index, cciValue_t value);

void CCI_ListRemove(cciList_t *l, size_t index);

#endif //CCISOLUTIONSC_CCILIST_H
