//
// Created by wein on 3/20/18.
//

#ifndef CCISOLUTIONSC_CCIQUEUE_H
#define CCISOLUTIONSC_CCIQUEUE_H

#include "cciValue.h"
#include "cciList.h"

typedef struct CCIQueue {
    cciList_t *l;
} cciQueue_t;

cciQueue_t *CCI_CreateQueue();

void CCI_DeleteQueue(cciQueue_t *qu);

void CCI_Enqueue(cciQueue_t *qu, cciValue_t value);

cciValue_t CCI_Dequeue(cciQueue_t *qu);

cciValue_t CCI_QueueFront(cciQueue_t *qu);

int CCI_QueueEmpty(cciQueue_t *qu);

#endif //CCISOLUTIONSC_CCIQUEUE_H
