//
// Created by wein on 3/18/18.
//

#include "cciValue.h"

#include <math.h>
#include <string.h>
#include <assert.h>

cciValue_t invalid() {
    cciValue_t v;
    v.type = CCI_INVALID;
    v.store.i = 0;
    return v;
}

cciValue_t newInt(int x) {
    cciValue_t v;
    SETINT(v, x);
    return v;
}

cciValue_t newFloat(float x) {
    cciValue_t v;
    SETFLOAT(v, x);
    return v;
}

cciValue_t newChar(char x) {
    cciValue_t v;
    SETCHAR(v, x);
    return v;
}

cciValue_t newStr(char *x) {
    cciValue_t v;
    SETSTR(v, x);
    return v;
}

int CompareI(cciValue_t lhs, cciValue_t rhs) {
    int delta = lhs.store.i - rhs.store.i;
    if (delta == 0) {
        return 0;
    }
    return delta > 0 ? 1 : -1;
}

int CompareF(cciValue_t lhs, cciValue_t rhs) {
    float delta = lhs.store.f - rhs.store.f;
    if (fabs(delta) < 1e-7) {
        return 0;
    }
    return delta > 0 ? 1 : -1;
}

int CompareS(cciValue_t lhs, cciValue_t rhs) {
    assert(lhs.type == CCI_STR && rhs.type == CCI_STR);
    char *slhs = GETSTR(lhs);
    char *srhs = GETSTR(rhs);
    return strcmp(slhs, srhs);
}
