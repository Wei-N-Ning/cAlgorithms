//
// Created by wein on 3/3/18.
//

#ifndef CCISOLUTIONSC_CCILIST_H
#define CCISOLUTIONSC_CCILIST_H

typedef struct cciList {
    struct cciListNode *head;
    struct cciListNode *tail;
    int size;
} cciList_t;

cciList_t *NewList();

void DeleteList(cciList_t *l);

void AppendInt(cciList_t *l, int v);

#endif //CCISOLUTIONSC_CCILIST_H
