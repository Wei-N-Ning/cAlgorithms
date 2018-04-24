//
// Created by wein on 4/23/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minEditDists.h>

void RunTinyTests();

void test_expectNumOfEditing() {
    const char *from = "thou shalt not";
    const char *to = "you should not";
    StrCmpState *state = createDefaultState(from, (int)strlen(from), to, (int)strlen(to));
    int r1 = stringCompare(state);
    deleteState(state);
    printf("min edits: (dp) %d, ", r1);
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

void test_expectCostMatrix() {
    const char *from = "thou shalt not";
    const char *to = "you should not";
    StrCmpState *state = createDefaultState(from, (int)strlen(from), to, (int)strlen(to));
    stringCompare(state);
    printf("\n");
    visitCells(state, printCost, printNewline);
    deleteState(state);
}

void test_expectOperationMatrix() {
    const char *from = "thou shalt not";
    const char *to = "you should not";
    StrCmpState *state = createDefaultState(from, (int)strlen(from), to, (int)strlen(to));
    stringCompare(state);
    printf("\n");
    visitCells(state, printOp, printNewline);
    deleteState(state);
}

void test_expectEditSequence() {
    const char *from = "thou shalt not";
    const char *to =   "you should not";
    StrCmpState *state = createDefaultState(from, (int)strlen(from), to, (int)strlen(to));
    stringCompare(state);
    editSequence(state);
    printf("\n");
    deleteState(state);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}