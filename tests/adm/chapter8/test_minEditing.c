//
// Created by wein on 4/23/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void RunTinyTests();

///////////////////////////////////////////////////////////
// common functions used by all the implementations

enum STRCMP {
    STRCMP_MATCH,
    STRCMP_INSERT,
    STRCMP_DELETE,
    STRCMP_SUB,
    STRCMP_NOOP,
};

static int match(char lhs, char rhs) {
    return (lhs == rhs) ? 0 : 1;
}

static int indel(char c) {
    return 1;
}

///////////////////////////////////////////////////////////
// demonstrate recursive implementation (naive)

static int *table;
static int table_w;
static int table_h;

static void tableSetUp(int w, int h) {
    table_w = w;
    table_h = h;
    size_t sz = w * h;
    table = malloc(sizeof(int) * sz);
    for (; sz-- ; table[sz] = 0) ;
}

static void tableTearDown() {
    if (table) {
        free(table);
        table = NULL;
    }
}

static int _get(int i, int j) {
    if (! table) {
        return 0;
    }
    return table[i * table_w + j];
}

static void _set(int i, int j, int v) {
    if (table) {
        table[i * table_w + j] = v;
    }
}

static int _strCmp(const char *s, const char *t, int s_idx, int t_idx) {
    int v = _get(s_idx, t_idx);
    if (v) {
        return v;
    }

    int opt[3] = {0, 0, 0};
    if (s_idx == -1) {
        return (t_idx > 0 ? t_idx : 0) * indel(' ');
    }
    if (t_idx == -1) {
        return (s_idx > 0 ? s_idx : 0) * indel(' ');
    }
    opt[STRCMP_MATCH] = _strCmp(s, t, s_idx - 1, t_idx - 1) + match(s[s_idx], t[t_idx]);
    opt[STRCMP_INSERT] = _strCmp(s, t, s_idx, t_idx - 1) + indel(t[t_idx]);
    opt[STRCMP_DELETE] = _strCmp(s, t, s_idx - 1, t_idx) + indel(s[s_idx]);

    int lowest_cost = opt[STRCMP_MATCH];
    for (int k = STRCMP_MATCH; k <= STRCMP_INSERT; ++k) {
        if (opt[k] < lowest_cost) {
            lowest_cost = opt[k];
        }
    }

    _set(s_idx, t_idx, lowest_cost);

    return lowest_cost;
}

// ADM doesn't explain this clearly: this function takes the array index
// rather than a "length" parameter, therefore in the case where toIdx
// is 0, the answer should be 1 (take the first character from both strings)
int stringCompareSlow(const char *s, const char *t, int toIdx) {
    int result = _strCmp(s, t, toIdx, toIdx);
    return result;
}

int stringCompareCached(const char *s, const char *t, int toIdx) {
    tableSetUp(toIdx + 1, toIdx + 1);
    int result = _strCmp(s, t, toIdx, toIdx);
    printf("\n");
    for (int row = 0; row < table_h; ++row) {
        for (int column = 0; column < table_w; ++column) {
            printf("%2d ", _get(row, column));
        }
        printf("\n");
    }
    tableTearDown();
    return result;
}

void xtest_recursion() {
    printf("\n");
    int r1 = stringCompareSlow(
        //012345678
        //xx  xxxxx
         "tHerEis acow 1337",
         "There IS no spoon",
        8
    );
    printf("min edits: (slow) %d, \n", r1);
    int r2 = stringCompareCached(
        "tHerEis acow 1337",
        "There IS no spoon",
        8
    );
    printf("min edits: (cached) %d, \n", r2);
}

///////////////////////////////////////////////////////////
// demonstrate DP implementation (keep track of operations)

struct Cell {
    int cost;
    enum STRCMP op;
    struct Cell *parent;
};

typedef struct Cell Cell;

static Cell *cells;
static int cells_h;
static int cells_w;

void cellsSetUp(int w, int h) {
    size_t sz = w * h;
    cells_h = h;
    cells_w = w;
    cells = malloc(sizeof(Cell) * sz);
    for (; sz-- ; ) {
        cells[sz].cost = 0;
        cells[sz].op = STRCMP_NOOP;
        cells[sz].parent = NULL;
    }
    for (int row = 0, column = 0; row < cells_h; ++row) {
        cells[row * cells_w + column].cost = row;
    }
    for (int row = 0, column = 0; column < cells_w; ++column) {
        cells[row * cells_w + column].cost = column;
    }
}

void cellsTearDown() {
    if (cells) {
        free(cells);
        cells = NULL;
    }
}

static Cell *_getCell(int i, int j) {
    return cells + i * cells_w + j;
}

static void _setCell(int i, int j,
                     int cost, enum STRCMP op, Cell *parent) {
    Cell *c = cells + i * cells_w + j;
    c->cost = cost;
    c->op = op;
    c->parent = parent;
}

static int _strCmpDP(const char *s, const char *t, int s_idx, int t_idx) {
    Cell tmp;
    int i, j;
    int opt[3] = {0, 0, 0};
    for (i = 1 ; i <= s_idx; ++i) {
        for (j = 1 ; j <= t_idx; ++j) {
            opt[STRCMP_MATCH] = _getCell(i - 1, j - 1)->cost + match(s[i], t[j]);
            opt[STRCMP_INSERT] = _getCell(i, j - 1)->cost + indel(t[j]);
            opt[STRCMP_DELETE] = _getCell(i - 1, j)->cost + indel(s[i]);

            // select the lowest cost for the current cell (i, j)
            tmp.cost = opt[STRCMP_MATCH];
            tmp.op = STRCMP_MATCH;
            for (enum STRCMP k = STRCMP_INSERT; k <= STRCMP_DELETE; ++k) {
                if (opt[k] < tmp.cost) {
                    tmp.cost = opt[k];
                    tmp.op = k;
                }
            }
            _setCell(i, j, tmp.cost, tmp.op, NULL);
        }
    }
    return _getCell(s_idx, t_idx)->cost;
}

int stringCompareDP(const char *s, const char *t, int toIdx) {
    cellsSetUp(toIdx + 1, toIdx + 1);
    int result = _strCmpDP(s, t, toIdx, toIdx);
    printf("\n");
    for (int row = 0; row < cells_h; ++row) {
        for (int column = 0; column < cells_w; ++column) {
            printf("%2d ", _getCell(row, column)->cost);
        }
        printf("\n");
    }
    cellsTearDown();
    return result;
}

void test_dynamicProgramming() {
    int r1 = stringCompareDP(
        //0123456789
        // xx  xxxxx
         " tHerEis acow 1337",
         " There IS no spoon",
        9
    );
    printf("min edits: (dp) %d, ", r1);
}

///////////////////////////////////////////////////////////

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}