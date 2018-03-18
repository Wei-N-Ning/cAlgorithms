//
// Created by wein on 3/19/18.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <cciValue.h>
#include <cciBinaryTree.h>

// generate num random integers in o_arr
void generateWorkload(size_t num, cciValue_t *o_arr) {
    for (int i=0; i<num; ++i) {
        o_arr[i] = newInt(rand());
    }
}

// populate the binary tree o_t by inserting the integers in
// arr one by one
void doInsert(cciValue_t *arr, size_t num, cciBinTreeNode_t *o_t) {
    for (int i=0; i<num; ++i) {
        BinTreeInsert(o_t, arr[i], NULL);
    }
}

void doTraverse(cciBinTreeNode_t *t) {
    Traverse(t, NULL);
}

int main(int argc, char **argv) {
    size_t rounds = 8;
    size_t workload[] = {10, 100, 200, 500, 1000, 5000, 10000, 20000};
    cciValue_t *arr = malloc(sizeof(cciValue_t) * 20000);
    clock_t before;
    clock_t after;
    double timeInsert = 0.0;
    double timeTraverse = 0.0;
    cciBinTreeNode_t *t = NULL;
    generateWorkload(20000, arr);
    for (int i=0; i<rounds; ++i) {
        InitFactory();
        t = CreateBinTreeNode(NULL);
        t->value = arr[0];

        before = clock();
        doInsert(arr, workload[i], t);
        after = clock();
        timeInsert = after - before;

        before = clock();
        doTraverse(t);
        after = clock();
        timeTraverse = after - before;

        printf("%d %f %f\n", (int)workload[i], timeInsert, timeTraverse);
        CloseFactory();
    }

    free(arr);
    return 0;
}
