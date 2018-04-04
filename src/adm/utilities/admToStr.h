//
// Created by wein on 4/4/18.
//

#ifndef CCISOLUTIONSC_ADMTOSTR_H
#define CCISOLUTIONSC_ADMTOSTR_H

#include <stddef.h>
#include <stdint.h>

// for each nibble n in v, calculate 0x41 + n
// 64 bit (8 bytes) have 16 nibbles
// return the number of nibbles converted
size_t BytesToUniqueString(uint64_t v, char *buf, size_t sz);

#endif //CCISOLUTIONSC_ADMTOSTR_H
