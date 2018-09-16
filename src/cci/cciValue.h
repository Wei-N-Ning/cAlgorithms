//
// Created by wein on 3/18/18.
//
// A value encapsulates primitive types

#ifndef CCISOLUTIONSC_CCIVALUE_H
#define CCISOLUTIONSC_CCIVALUE_H

#include <stddef.h>
#include <stdint.h>

#ifndef CCI_VALUETYPE
#define CCI_VALUETYPE uint64_t
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

#define CCIValue_RESET(v) v.store.i = 0;
#define CCIValue_SETINT(v, x)                                                  \
  v.store.i = 0;                                                               \
  v.store.i = x;                                                               \
  v.type = CCI_INT;
#define CCIValue_SETFLOAT(v, x)                                                \
  v.store.i = 0;                                                               \
  v.store.f = x;                                                               \
  v.type = CCI_FLOAT;
#define CCIValue_SETCHAR(v, x)                                                 \
  v.store.i = 0;                                                               \
  v.store.c = x;                                                               \
  v.type = CCI_CHAR;
#define CCIValue_SETSTR(v, x)                                                  \
  v.store.i = 0;                                                               \
  v.store.s = x;                                                               \
  v.type = CCI_STR;
#define CCIValue_SETPOINTER(v, x)                                              \
  v.store.i = 0;                                                               \
  v.store.i = (uint64_t)x;                                                     \
  v.type = CCI_POINTER;

#define CCIValue_GETINT(v) (int)v.store.i
#define CCIValue_GETFLOAT(v) v.store.f
#define CCIValue_GETCHAR(v) v.store.c
#define CCIValue_GETSTR(v) v.store.s
#define CCIValue_GETPOINTER(v, t) (t *)(v.store.i)
#define CCIValue_ISVALID(v) (v.type != CCI_INVALID)

cciValue_t CCIValue_invalid();

cciValue_t CCIValue_newInt(int x);

cciValue_t CCIValue_newPointer(void *x);

cciValue_t CCIValue_newFloat(float x);

cciValue_t CCIValue_newChar(char x);

cciValue_t CCIValue_newStr(char *s);

typedef int (*CCIValue_CompareFunc)(cciValue_t lhs, cciValue_t rhs);

int CCIValue_CompareI(cciValue_t lhs, cciValue_t rhs);

int CCIValue_CompareF(cciValue_t lhs, cciValue_t rhs);

int CCIValue_CompareS(cciValue_t lhs, cciValue_t rhs);

#define CCIValue_ICOMPARE(lhs, rhs) CompareI((lhs), (rhs))

#endif // CCISOLUTIONSC_CCIVALUE_H
