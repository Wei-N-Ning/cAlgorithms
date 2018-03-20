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

cciList_t *NewList();

void DeleteList(cciList_t *l);

void Append(cciList_t *l, cciValue_t value);

cciValue_t Get(cciList_t *l, size_t index);

void Set(cciList_t *l, size_t index, cciValue_t value);

void Insert(cciList_t *l, size_t index, cciValue_t value);

void Remove(cciList_t *l, size_t index);

#endif //CCISOLUTIONSC_CCILIST_H
