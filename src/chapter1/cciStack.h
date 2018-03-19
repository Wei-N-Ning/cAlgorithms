//
// Created by wein on 3/19/18.
//

#ifndef CCISOLUTIONSC_CCISTACK_H
#define CCISOLUTIONSC_CCISTACK_H

#include <stddef.h>

#include "cciValue.h"
#include "cciArrayList.h"

typedef struct CCIStack {
    cciArrayList_t *arr;
} cciStack_t;

cciStack_t *CreateCCIStack(size_t capacity);

void DeleteCCIStack(cciStack_t *st);

cciValue_t CCIStackPop(cciStack_t *st);

void CCIStackPush(cciStack_t *st, cciValue_t value);

cciValue_t CCIStackPeek(cciStack_t *st);

int CCIStackEmpty(cciStack_t *st);

#endif //CCISOLUTIONSC_CCISTACK_H
