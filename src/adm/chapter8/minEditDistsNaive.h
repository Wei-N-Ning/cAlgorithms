//
// Created by wein on 4/24/18.
//

#ifndef CCISOLUTIONSC_MINEDITDISTS_H
#define CCISOLUTIONSC_MINEDITDISTS_H

enum STRCMP {
    STRCMP_NOOP = -1,
    STRCMP_MATCH = 0,
    STRCMP_INSERT = 1,
    STRCMP_DELETE = 2,
    STRCMP_SUB = 3,
};

int stringCompareSlow(const char *s, const char *t, int i, int j);
int stringCompareCached(const char *s, const char *t, int i, int j);

#endif //CCISOLUTIONSC_MINEDITDISTS_H
