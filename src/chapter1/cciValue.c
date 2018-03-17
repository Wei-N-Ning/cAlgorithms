//
// Created by wein on 3/18/18.
//

#include "cciValue.h"

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
