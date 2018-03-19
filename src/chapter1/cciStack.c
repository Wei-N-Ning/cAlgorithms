//
// Created by wein on 3/19/18.
//

#include "cciStack.h"
#include "cciArrayList.h"

#include <stdlib.h>

cciStack_t *CreateCCIStack(size_t capacity) {
    cciStack_t *st = malloc(sizeof(cciStack_t));
    st->arr = AlNew();
    AlReserve(st->arr, capacity);
    return st;
}

void DeleteCCIStack(cciStack_t *st) {
    AlDelete(st->arr);
    free(st);
}

void CCIStackPush(cciStack_t *st, cciValue_t value) {
    AlEmplaceBack(st->arr, value);
}

cciValue_t CCIStackPop(cciStack_t *st) {
    return AlPopBack(st->arr);
}

cciValue_t CCIStackPeek(cciStack_t *st) {
    return AlBack(st->arr);
}

int CCIStackEmpty(cciStack_t *st) {
    return st->arr->size == 0 ? 1 : 0;
}
