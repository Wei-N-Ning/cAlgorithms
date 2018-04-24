//
// Created by wein on 4/24/18.
//

#include "minEditDistsNaive.h"

#include <stdio.h>
#include <stdlib.h>

static int *table;
static int table_w;
static int table_h;

static int match(char lhs, char rhs) {
    return (lhs == rhs) ? 0 : 1;
}

static int indel(char c) {
    return 1;
}

static void tableSetUp(int w, int h) {
    table_w = w;
    table_h = h;
    int sz = w * h;
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
    if (i < 0 || j < 0) {
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
    enum STRCMP k = STRCMP_MATCH;
    for (; k <= STRCMP_INSERT; ++k) {
        if (opt[k] < lowest_cost) {
            lowest_cost = opt[k];
        }
    }
    _set(s_idx, t_idx, lowest_cost);

    return lowest_cost;
}

// ADM doesn't explain this clearly: this function takes the array index
// rather than a "length" parameter, therefore in the case where i or j
// is 0, the answer should be 1 (take the first character from both strings)
int stringCompareSlow(const char *s, const char *t, int i, int j) {
    int result = _strCmp(s, t, i, j);
    return result;
}

int stringCompareCached(const char *s, const char *t, int i, int j) {
    tableSetUp(i + 1, j + 1);
    int result = _strCmp(s, t, i, j);
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