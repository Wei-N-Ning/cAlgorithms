//
// Created by wein on 4/24/18.
//

#ifndef CCISOLUTIONSC_MINEDITDISTS_H
#define CCISOLUTIONSC_MINEDITDISTS_H

#include <stddef.h>

enum STRCMP {
    STRCMP_NOOP = -1,
    STRCMP_MATCH = 0,
    STRCMP_INSERT = 1,
    STRCMP_DELETE = 2,
    STRCMP_SUB = 3,
};

struct Cell {
    int cost;
    enum STRCMP op;
};

typedef struct Cell Cell;

struct StrCmpState;

typedef struct StrCmpState StrCmpState;

typedef int (*MatchFunc)(StrCmpState *state, int i, int j);
typedef int (*InsertDeleteFunc)( StrCmpState *state, int idx);
typedef void (*RowInitFunc)( StrCmpState *state);
typedef void (*ColumnInitFunc)( StrCmpState *state);
typedef void (*MatchHandler)( StrCmpState *state, int i, int j);
typedef void (*InsertHandler)( StrCmpState *state, int j);
typedef void (*DeleteHandler)( StrCmpState *state, int i);
typedef void (*GoalCellFunc)( StrCmpState *state, int *o_i, int *o_j);

struct StrCmpState {
    RowInitFunc rowInit;
    ColumnInitFunc columnInit;
    MatchFunc match;
    InsertDeleteFunc indel;
    GoalCellFunc goalCell;
    MatchHandler handleMatch;
    InsertHandler handleInsert;
    DeleteHandler handleDelete;

    char *s;
    size_t sLen;
    char *t;
    size_t tLen;

    Cell *table;
    size_t tableWidth;
    size_t tableHeight;
};

StrCmpState *createDefaultState(const char *s, size_t sLen, const char *t, size_t tLen);

void deleteState(StrCmpState *state);

int stringCompare(StrCmpState *state);

void editSequence(StrCmpState *state);

#endif //CCISOLUTIONSC_MINEDITDISTS_H
