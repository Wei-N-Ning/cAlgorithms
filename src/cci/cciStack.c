//
// Created by wein on 3/19/18.
//

#include "cciStack.h"
#include "cciArrayList.h"

#include <stdlib.h>

cciStack_t *CCI_CreateStack(size_t capacity) {
    cciStack_t *st = malloc(sizeof(cciStack_t));
    st->arr = CCI_AlNew();
    CCI_AlReserve(st->arr, capacity);
    return st;
}

void CCI_DeleteStack(cciStack_t *st) {
    CCI_AlDelete(st->arr);
    free(st);
}

void CCI_StackPush(cciStack_t *st, cciValue_t value) {
    CCI_AlEmplaceBack(st->arr, value);
}

cciValue_t CCI_StackPop(cciStack_t *st) {
    return CCI_AlPopBack(st->arr);
}

cciValue_t CCI_StackPeek(cciStack_t *st) {
    return CCI_AlBack(st->arr);
}

int CCI_StackEmpty(cciStack_t *st) {
    return st->arr->size == 0 ? 1 : 0;
}
