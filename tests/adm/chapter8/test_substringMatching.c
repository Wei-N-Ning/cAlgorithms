//
// Created by wein on 4/25/18.
//

#include <stdio.h>
#include <string.h>

#include <minEditDists.h>

void RunTinyTests();

static void columnInit(StrCmpState *state) {
    for (size_t column = state->tableWidth;
         column--;
         state->table[column].cost = 0, state->table[column].op = STRCMP_NOOP ) ;
}

static void goalCell(StrCmpState *state, int *o_i, int *o_j) {
    *o_i = (int)state->sLen;
    *o_j = 0;
    for (int k = 1; k <= state->tLen; ++k) {
        if (state->table[(*o_i) * state->tableWidth + k].cost <\
            state->table[(*o_i) * state->tableWidth + (*o_j)].cost) {
            *o_j = k;
        }
    }
    state->goal_i = *o_i;
    state->goal_j = *o_j;
}

typedef void (*CellVisitor)(Cell *c);
typedef void (*EndOfRow)();

void printCost(Cell *c) {
    printf("%2d ", c->cost);
}

void printOp(Cell *c) {
    printf("%2d ", c->op);
}

void printNewline() {
    printf("\n");
}

void visitCells(StrCmpState *state, CellVisitor cvi, EndOfRow eor) {
    Cell *c = NULL;
    for (int row = 0; row < state->tableHeight; ++row) {
        for (int column = 0; column < state->tableWidth; ++column) {
            c = state->table + row * state->tableWidth + column;
            cvi(c);
        }
        if (eor) {
            eor();
        }
    }
}

void test_all() {
    const char *haystack = "DoMdomm2om2omddomd2ooDdoommoomTomdd";
    const char *needle =   "doom";
    StrCmpState *state = createDefaultState(haystack, strlen(haystack), needle, strlen(needle));
    state->columnInit = columnInit;
    state->goalCell = goalCell;
    stringCompare(state);
    printf("goal: %d (%c) ", state->goal_j - 1, haystack[state->goal_j - 1]);
    deleteState(state);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}