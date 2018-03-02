//
// Created by wein on 3/3/18.
//

#include "cciList.h"
#include <stdlib.h>

typedef struct cciListNode {
    struct cciListNode *prev;
    struct cciListNode *next;
    int value;
} cciListNode_t;

cciList_t *NewList() {
    cciList_t *l = malloc(sizeof(cciList_t));
    l->head = 0;
    l->tail = 0;
    return l;
}

void DeleteList(cciList_t *l) {
    cciListNode_t *curr = l->head;
    while (curr) {
        l->head = l->head->next;
        free(curr);
        curr = l->head;
    }
    free(l);
}

cciListNode_t *createNode() {
    cciListNode_t *n = malloc(sizeof(cciListNode_t));
    n->value = 0;
    return n;
}

void deleteNode(cciListNode_t *n) {
    if (n->prev) {
        n->prev->next = n->next;
    }
    if (n->next) {
        n->next->prev = n->prev;
    }
    free(n);
}

void AppendInt(cciList_t *l, int v) {
    cciListNode_t *n = createNode();
    n->value = v;
    if (l->size == 0) {
        l->head = n;
    } else {
        n->prev = l->tail;
        l->tail->next = n;
    }
    l->tail = n;
    l->size++;
}
