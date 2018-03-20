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

cciQueue_t *CreateCCIQueue();

void DeleteCCIQueue(cciQueue_t *qu);

void Enqueue(cciQueue_t *qu, cciValue_t value);

cciValue_t Dequeue(cciQueue_t *qu);

cciValue_t Front(cciQueue_t *qu);

int CCIQueueEmpty(cciQueue_t *qu);

#endif //CCISOLUTIONSC_CCIQUEUE_H
