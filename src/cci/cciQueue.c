//
// Created by wein on 3/20/18.
//

#include "cciQueue.h"

#include <stdlib.h>

cciQueue_t *CCI_CreateQueue() {
    cciQueue_t *qu = malloc(sizeof(cciQueue_t));
    qu->l = CCI_NewList();
    return qu;
}

void CCI_DeleteQueue(cciQueue_t *qu) {
    CCI_DeleteList(qu->l);
    free(qu);
}

void CCI_Enqueue(cciQueue_t *qu, cciValue_t value) {
    CCI_ListAppend(qu->l, value);
}

cciValue_t CCI_Dequeue(cciQueue_t *qu) {
    cciValue_t value = CCI_QueueFront(qu);
    CCI_ListRemove(qu->l, 0);
    return value;
}

cciValue_t CCI_QueueFront(cciQueue_t *qu) {
    if (! qu->l->size) {
        return CCIValue_invalid();
    }
    return CCI_ListGet(qu->l, 0);
}

int CCI_QueueEmpty(cciQueue_t *qu) {
    return qu->l->size ? 0 : 1;
}