//
// Created by wein on 3/18/18.
//
// A value encapsulates primitive types

#ifndef CCISOLUTIONSC_CCIVALUE_H
#define CCISOLUTIONSC_CCIVALUE_H

#include <stdint.h>
#include <stddef.h>

#ifndef VTYPE
#define VTYPE uint64_t
#endif

typedef enum {
    CCI_INVALID,
    CCI_INT,
    CCI_FLOAT,
    CCI_CHAR,
    CCI_STR,
    CCI_POINTER,
} cciValueType_t;

typedef struct CCIValue {
    union {
        float f;
        uint64_t i;
        char c;
        char *s;
    } store;
    cciValueType_t type;
    size_t sz;
} cciValue_t;

#define RESET(v) v.store.i=0;
#define SETINT(v,x) v.store.i=0; v.store.i=x; v.type=CCI_INT;
#define SETFLOAT(v,x) v.store.i=0; v.store.f=x; v.type=CCI_FLOAT;
#define SETCHAR(v,x) v.store.i=0; v.store.c=x; v.type=CCI_CHAR;
#define SETSTR(v,x) v.store.i=0; v.store.s=x; v.type=CCI_STR;
#define SETPOINTER(v,x) v.store.i=0; v.store.i=(uint64_t)x; v.type=CCI_POINTER;

#define GETINT(v) (int)v.store.i
#define GETFLOAT(v) v.store.f
#define GETCHAR(v) v.store.c
#define GETSTR(v) v.store.s
#define GETPOINTER(v, t) (t *)(v.store.i)
#define ISVALID(v) (v.type != CCI_INVALID)

cciValue_t invalid();
cciValue_t newInt(int x);
cciValue_t newPointer(void *x);
cciValue_t newFloat(float x);
cciValue_t newChar(char x);
cciValue_t newStr(char *s);

typedef int (*CompareFunc)(cciValue_t lhs, cciValue_t rhs);
int CompareI(cciValue_t lhs, cciValue_t rhs);
int CompareF(cciValue_t lhs, cciValue_t rhs);
int CompareS(cciValue_t lhs, cciValue_t rhs);

#define ICOMPARE(lhs,rhs) CompareI((lhs),(rhs))

#endif //CCISOLUTIONSC_CCIVALUE_H
