
/*
 * giving sequence:
 * a b c d e f g
 *         ^
 *     ^
 * partition it to 3 sub sequences as fairly as possible
 *
 * strategy:
 * iteratively compute the optimal solutions
 *
 * say the iteration reaches element e, compare:
 * [a, b] [c, d, e]
 * [a, b, c] [d, e]
 * [a, b, c, d] [e]
 *
 * if the partition of [a, b, c] is not optimal, introducing [d, e]
 * has the following consequences:
 * > if sum([d, e]) is larger than the largest sub seq in [a, b, c]
 * this will make it even more unfair
 * > if sum([d, e]) is smaller than the smallest sub seq in [a, b, c]
 * same result
 * > if sum([d, e]) falls between the min and max sums, it does not
 * make the game fairer
 *
 * therefore all the non-optimal solutions should be skipped
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>

typedef struct __CELL {
} Cell;

typedef struct __TABLE {
    Cell *cells;
} Table;

Cell *GetCell(Table *tb, int row, int column) {
    return NULL;
}

Table *Create(int numElements) {
    Table *tb = malloc(sizeof(Table));
    tb->cells = malloc(sizeof(Cell) * numElements * numElements);
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
