//
// Created by wein on 3/3/18.
//

#ifndef CCISOLUTIONSC_CCILIST_H
#define CCISOLUTIONSC_CCILIST_H

typedef enum CCILIST_ERROR {
    CCILIST_NO_ERROR,
    CCILIST_INDEX_ERROR,
} CCILIST_ERROR;

typedef struct cciList {
    struct cciListNode *head;
    struct cciListNode *tail;
    int size;
    CCILIST_ERROR errCode;
} cciList_t;

cciList_t *NewList();

void DeleteList(cciList_t *l);

void AppendInt(cciList_t *l, int v);

int GetInt(cciList_t *l, int index);

void InsertInt(cciList_t *l, int index, int value);

#endif //CCISOLUTIONSC_CCILIST_H
