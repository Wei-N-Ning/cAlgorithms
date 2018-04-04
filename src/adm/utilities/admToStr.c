//
// Created by wein on 4/4/18.
//

#include "admToStr.h"

size_t BytesToUniqueString(uint64_t v, char *buf, size_t sz) {
    size_t i = 0;
    for ( ; v && i < sz; ++i) {
        buf[i] = 0x41 + (char)(0x000000000000000F & v);
        v = v >> 4;
    }
    return i;
}
