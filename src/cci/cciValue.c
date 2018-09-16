//
// Created by wein on 3/18/18.
//

#include "cciValue.h"

#include <math.h>
#include <string.h>
#include <assert.h>

cciValue_t CCIValue_invalid() {
    cciValue_t v;
    v.type = CCI_INVALID;
    v.store.i = 0;
    return v;
}

cciValue_t CCIValue_newInt(int x) {
    cciValue_t v;
    CCIValue_SETINT(v, x);
    return v;
}

cciValue_t CCIValue_newFloat(float x) {
    cciValue_t v;
    CCIValue_SETFLOAT(v, x);
    return v;
}

cciValue_t CCIValue_newChar(char x) {
    cciValue_t v;
    CCIValue_SETCHAR(v, x);
    return v;
}

cciValue_t CCIValue_newStr(char *x) {
    cciValue_t v;
    CCIValue_SETSTR(v, x);
    return v;
}

cciValue_t CCIValue_newPointer(void *p) {
    cciValue_t v;
    CCIValue_SETPOINTER(v, p);
    return v;
}

int CCIValue_CompareI(cciValue_t lhs, cciValue_t rhs) {
    int delta = lhs.store.i - rhs.store.i;
    if (delta == 0) {
        return 0;
    }
    return delta > 0 ? 1 : -1;
}

int CCIValue_CompareF(cciValue_t lhs, cciValue_t rhs) {
    float delta = lhs.store.f - rhs.store.f;
    if (fabs(delta) < 1e-7) {
        return 0;
    }
    return delta > 0 ? 1 : -1;
}

int CCIValue_CompareS(cciValue_t lhs, cciValue_t rhs) {
    assert(lhs.type == CCI_STR && rhs.type == CCI_STR);
    char *slhs = CCIValue_GETSTR(lhs);
    char *srhs = CCIValue_GETSTR(rhs);
    return strcmp(slhs, srhs);
}
