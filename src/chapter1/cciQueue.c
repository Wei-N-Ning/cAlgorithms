//
// Created by wein on 3/20/18.
//

#include "cciQueue.h"

#include <stdlib.h>

cciQueue_t *CreateCCIQueue() {
    cciQueue_t *qu = malloc(sizeof(cciQueue_t));
    qu->l = NewList();
    return qu;
}

void DeleteCCIQueue(cciQueue_t *qu) {
    DeleteList(qu->l);
    free(qu);
}

void Enqueue(cciQueue_t *qu, cciValue_t value) {
    Append(qu->l, value);
}

cciValue_t Dequeue(cciQueue_t *qu) {
    cciValue_t value = CCIQueueFront(qu);
    Remove(qu->l, 0);
    return value;
}

cciValue_t CCIQueueFront(cciQueue_t *qu) {
    if (! qu->l->size) {
        return invalid();
    }
    return Get(qu->l, 0);
}

int CCIQueueEmpty(cciQueue_t *qu) {
    return qu->l->size ? 0 : 1;
}