//
// Created by wein on 3/19/18.
//

#ifndef CCISOLUTIONSC_CCISTACK_H
#define CCISOLUTIONSC_CCISTACK_H

#include "cciValue.h"
#include "cciArrayList.h"

#include <stddef.h>

typedef struct CCIStack {
    cciArrayList_t *arr;
} cciStack_t;

cciStack_t *CCI_CreateStack(size_t capacity);

void CCI_DeleteStack(cciStack_t *st);

cciValue_t CCI_StackPop(cciStack_t *st);

void CCI_StackPush(cciStack_t *st, cciValue_t value);

cciValue_t CCI_StackPeek(cciStack_t *st);

int CCI_StackEmpty(cciStack_t *st);

#endif //CCISOLUTIONSC_CCISTACK_H
