//
// Created by wein on 4/24/18.
//

#include "minEditDists.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Cell *_getCell(StrCmpState *state, int i, int j) {
    return state->table + i * state->tableWidth + j;
}

static void _setCell(StrCmpState *state, int i, int j, int cost, enum STRCMP op) {
    Cell *c = state->table + i * state->tableWidth + j;
    c->cost = cost;
    c->op = op;
}

static int default_match(StrCmpState *state, int i, int j) {
    return (state->s[i] == state->t[j]) ? 0 : 1;
}

static int default_indel(StrCmpState *state, int idx) {
    return 1;
}

static void default_rowInit( StrCmpState *state) {
    for (size_t row = state->tableHeight;
         row--;
         state->table[row * state->tableWidth].cost = (int)row, state->table[row * state->tableWidth].op = STRCMP_DELETE) ;
    state->table->op = STRCMP_NOOP;
}

static void default_columnInit( StrCmpState *state) {
    for (size_t column = state->tableWidth;
         column--;
         state->table[column].cost = (int)column, state->table[column].op = STRCMP_INSERT ) ;
    state->table->op = STRCMP_NOOP;
}

static void default_handleMatch( StrCmpState *state, int i, int j) {
    if (state->s[i] == state->t[j]) {
        printf("M");
    } else {
        printf("S");
    }
}

static void default_handleInsert( StrCmpState *state, int j) {
    printf("I");
}

static void default_handleDelete( StrCmpState *state, int i) {
    printf("D");
}

static void default_goalCell( StrCmpState *state, int *o_i, int *o_j) {
    *o_i = (int)state->sLen;
    *o_j = (int)state->tLen;
}

int stringCompare(struct StrCmpState *state) {
    int i, j;
    int i_sel, j_sel;
    int opt[3] = {0, 0, 0};

    state->rowInit(state);
    state->columnInit(state);

    for (i = 1; i <= state->sLen; ++i) {
        for (j = 1; j <= state->tLen; ++j) {
            opt[STRCMP_MATCH] = _getCell(state, i - 1, j - 1)->cost + state->match(state, i, j);
            opt[STRCMP_INSERT] = _getCell(state, i, j - 1)->cost + state->indel(state, j);
            opt[STRCMP_DELETE] = _getCell(state, i - 1, j)->cost + state->indel(state, i);

            // select the lowest cost for the current cell (i, j)
            Cell tmp;
            tmp.cost = opt[STRCMP_MATCH];
            tmp.op = STRCMP_MATCH;
            for (enum STRCMP k = STRCMP_INSERT; k <= STRCMP_DELETE; ++k) {
                if (opt[k] < tmp.cost) {
                    tmp.cost = opt[k];
                    tmp.op = k;
                }
            }
            _setCell(state, i, j, tmp.cost, tmp.op);
        }
    }
    state->goalCell(state, &i_sel, &j_sel);
    return _getCell(state, i_sel, j_sel)->cost;
}

StrCmpState *createDefaultState(const char *s, size_t sLen, const char *t, size_t tLen) {
    StrCmpState *state = malloc(sizeof(StrCmpState));
    state->s = malloc(sizeof(char) * (sLen + 1));
    state->s[0] = ' ';
    strncpy(state->s + 1, s, sLen);
    state->sLen = sLen;
    state->t = malloc(sizeof(char) * (tLen + 1));
    state->t[0] = ' ';
    strncpy(state->t + 1, t, tLen);
    state->tLen = tLen;
    size_t sz = (sLen + 1) * (tLen + 1);
    state->table = malloc(sizeof(Cell) * sz);
    for (; sz--; state->table[sz].op = STRCMP_NOOP, state->table[sz].cost = 0) ;
    state->tableWidth = sLen + 1;
    state->tableHeight = tLen + 1;

    state->columnInit = default_columnInit;
    state->rowInit = default_rowInit;
    state->goalCell = default_goalCell;
    state->handleDelete = default_handleDelete;
    state->handleInsert = default_handleInsert;
    state->handleMatch = default_handleMatch;
    state->match = default_match;
    state->indel = default_indel;

    return state;
}

void deleteState(StrCmpState *state) {
    free(state->s);
    free(state->t);
    free(state->table);
    free(state);
}

static void _editSequence(StrCmpState *state, int i, int j) {
    Cell *cell = _getCell(state, i, j);
    if (cell->op == STRCMP_NOOP) {
        return;
    }
    if (cell->op == STRCMP_MATCH) {
        _editSequence(state, i - 1, j - 1);
        state->handleMatch(state, i, j);
    } else if (cell->op == STRCMP_INSERT) {
        _editSequence(state, i, j - 1);
        state->handleInsert(state, j);
    } else if (cell->op == STRCMP_DELETE) {
        _editSequence(state, i - 1, j);
        state->handleDelete(state, i);
    }
}

void editSequence(StrCmpState *state) {
    _editSequence(state, (int)state->sLen, (int)state->tLen);
}
