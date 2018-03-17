//
// Created by wein on 3/18/18.
//
// A value encapsulates primitive types

#ifndef CCISOLUTIONSC_CCIVALUE_H
#define CCISOLUTIONSC_CCIVALUE_H

#include <stdint.h>

#ifndef VTYPE
#define VTYPE uint64_t
#endif

typedef enum {
    CCI_INT,
    CCI_FLOAT,
    CCI_CHAR,
    CCI_STR,
} cciValueType_t;

typedef struct CCIValue {
    union {
        float f;
        uint64_t i;
        char c;
    } store;
    cciValueType_t type;
} cciValue_t;

#define SETINT(v,x) v.store.i=0; v.store.i=x; v.type=CCI_INT;
#define SETFLOAT(v,x) v.store.i=0; v.store.f=x; v.type=CCI_FLOAT;
#define SETCHAR(v,x) v.store.i=0; v.store.c=x; v.type=CCI_CHAR;

#define GETINT(v) (int)v.store.i
#define GETFLOAT(v) v.store.f
#define GETCHAR(v) v.store.c

cciValue_t newInt(int x);
cciValue_t newFloat(float x);
cciValue_t newChar(char x);

#endif //CCISOLUTIONSC_CCIVALUE_H
