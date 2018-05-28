//
// Created by wein on 5/21/18.
//
// this is the second revision of the solution, inspired by the Python version

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>

/*
 * @ @ t T h e r e   I s
 * @ 0 1 2 3 4 5 6 7 8 9
 * T 1 1 2
 * h 2 *
 * e 3
 * r 4
 * e 5
 * i 6
 * s 7
 * */

// at the cell marked *, there are the 3 PREVIOUS choices 
// that lead to this state:
// if the path came from the left adjacent cell, the choice 
// was to delete - meaning that 't' had been deleted from
// string s
// if the path came from the top adjacent cell, the choice 
// was to insert - meaning that 'h' had been inserted to 
// string s
// lastly if the path came from the top-left cell, the 
// choice was to edit - meaning that 't' had been replaced 
// by 'h'; if both characters were the same, there would be 
// no change at all

// notes on space complexity
// if the complete editing sequence is not required, one 
// can use two arrays to book keep the current choice and 
// the most recent choice:
// n   x x x x . . . . .
// n+1 *
// because the algorithm always populates one row at a time 
// (less optimal??) one can modify the GetCell() function 
// and table constructor to carefully construct, modify and 
// swap these two arrays, while still following the table-based 
// logic

// notes on retrieve the editing sequence
// the cell, table[size - 1] stores the minimum editing cost
// required to turn string s into t (why? because each cell
// is local optimal)
// one can implement a backtracking function to construct
// the complete editing sequence

enum ACTION {
    AC_NULL,
    AC_INSERT,
    AC_DELETE,
    AC_EDIT,
};

typedef struct __CELL {
    enum ACTION ac;
    int cost;
} Cell;

typedef struct __TABLE {
    int numRows;
    int numColumns;
    Cell *cells;
} Table;

Cell *GetCell(Table *tb, int row, int column) {
    assert(row >= 0 && row < tb->numRows && column >= 0 && column < tb->numColumns);
    return tb->cells + row * tb->numColumns + column;
}

Table *Create(int numRows, int numColumns) {
    Table *tb = malloc(sizeof(Table));
    tb->cells = malloc(sizeof(Cell) * numRows * numColumns);
    tb->numRows = numRows;
    tb->numColumns = numColumns;

    // initialize all cell to be 0-cost and have NULL action type
    memset(tb->cells, 0, sizeof(Cell) * numRows * numColumns);
    return tb;
}

typedef void(*IterCallback)(Cell *, int row, int column, void *state);

void IterRow(Table *table, int row, IterCallback cb, void *state) {
    for (int column = 0; column < table->numColumns; ++column) {
        cb(GetCell(table, row, column), row, column, state);
    }
}

void IterColumn(Table *table, int column, IterCallback cb, void *state) {
    for (int row = 0; row < table->numRows; ++row) {
        cb(GetCell(table, row, column), row, column, state);
    }
}

void Delete(Table *tb) {
    if (! tb) {
        return;
    }
    if (tb->cells) {
        free(tb->cells);
    }
    free(tb);
}

void InitFirstRow(Cell *cell, int row, int column, void *state) {
    cell->ac = AC_DELETE;
    cell->cost = column;
}

void InitFirstColumn(Cell *cell, int row, int column, void *state) {
    cell->ac = AC_INSERT;
    cell->cost = row;
}

void PrintCell(Cell *cell, int row, int column, void *state) {
    printf("%d ", cell->cost);
}

int CostInsert() {
    return 1;
}

int CostDelete() {
    return 1;
}

int CostEdit(const char lhs, const char rhs) {
    return (lhs != rhs) ? 1 : 0;
}

int solve(const char *s, const char *t, char *o_editSequence) {
    int s_length = (int)strlen(s);  // size of the row - 1
    int t_length = (int)strlen(t);  // size of the column - 1
    int numColumns = s_length + 1;
    int numRows = t_length + 1;
    Table *table = Create(numRows, numColumns);
    IterRow(table, 0, InitFirstRow, NULL);
    IterColumn(table, 0, InitFirstColumn, NULL);
    GetCell(table, 0, 0)->cost = 0; GetCell(table, 0, 0)->ac = AC_NULL;

    // book keep the costs that are the results of the previous choices: INSERT, DELETE or EDIT
    int costs[3] = {0, 0, 0};
    Cell *this = NULL;

    // walk through string s from the first character
    for (int s_idx = 1; s_idx < numColumns; ++s_idx) {  // s_idx is the column index
        for (int t_idx = 1; t_idx < numRows; ++t_idx) {  // t_idx is the row index
            this = GetCell(table, t_idx, s_idx);
            this->cost = INT_MAX;
            costs[AC_INSERT] = CostInsert() + GetCell(table, t_idx - 1, s_idx)->cost;
            costs[AC_DELETE] = CostDelete() + GetCell(table, t_idx, s_idx - 1)->cost;
            costs[AC_EDIT] = CostEdit(s[s_idx - 1], t[t_idx - 1]) + GetCell(table, t_idx - 1, s_idx - 1)->cost;

            for (enum ACTION ac = AC_INSERT; ac <= AC_EDIT; ++ac) {
                if (costs[ac] < this->cost) {
                    this->cost = costs[ac];
                    this->ac = ac;
                }
            }
        }
    }

    printf("\n");
    for (int row = 0; row < numRows; ++row) {
        IterRow(table, row, PrintCell, NULL);
        printf("\n");
    }

    int cost = GetCell(table, numRows - 1, numColumns - 1)->cost;
    Delete(table);
    return cost;
}

void RunTinyTests();

void test_givenStringsExpectEditingSequence() {
    const char *s = "tThere Is";
    const char *t = "Thereis";
    char editingSequence[16];
    for (int i = 16; i--; editingSequence[i] = '\0') ;

    int num = solve(s, t, editingSequence);
    assert(num == 3);
    printf("%s", editingSequence);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
