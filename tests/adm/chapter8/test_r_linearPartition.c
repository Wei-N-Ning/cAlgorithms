
/*
 * giving sequence:
 * a b c d e f g
 */


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>

typedef struct __CELL {
    int diff;
    int seqStart;
} Cell;

typedef struct __TABLE {
    int numElements;
    Cell *cells;
} Table;

Cell *GetCell(Table *tb, int row, int column) {
    assert(row >= 0 && row < tb->numElements && column >= 0 && column < tb->numElements);
    return tb->cells + row * tb->numElements + column;
}

Table *Create(int numElements) {
    Table *tb = malloc(sizeof(Table));
    tb->cells = malloc(sizeof(Cell) * numElements * numElements);
    tb->numElements = numElements;

    // initialize all cells
    memset(tb->cells, 0, sizeof(Cell) * numElements * numElements);
    for (int i = 0; i < numElements; ++i) {
        GetCell(tb, i, i)->diff = INT_MAX;
        GetCell(tb, i, i)->seqStart = -1;
    }
    return tb;
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


int solve(int *arr, int sz, int numSeqs) {
    Table *table = Create(sz);
    for (int seqStart = 0; seqStart < sz; ++seqStart) {
        for (int seqEnd = seqStart + 1; seqEnd < sz; ++seqEnd) {

        }
    }
    Delete(table);
    return 0;
}

void RunTinyTests();

void test_givenSequenceExpectMinDiff() {
    int arr[5] = {1, 3, 5, 11, 3};
    int diff = solve(arr, 5, 2);
//    assert(diff == 5);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
