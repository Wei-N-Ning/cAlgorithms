//
// Created by wein on 3/20/18.
//

#include <cci/cciStack.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void doPush(cciStack_t *st, size_t num) {
    for (int i=0; i<num; ++i) {
        CCI_StackPush(st, CCIValue_newInt(i));
    }
}

void doPop(cciStack_t *st, size_t num) {
    for (size_t i=0; i<num; ++i) {
        CCI_StackPop(st);
    }
}

int main(int argc, char **argv) {
    size_t num = 8;
    size_t workloads[8] = {10, 100, 1000, 10000, 100000, 1000000, 5000000, 10000000};
    cciStack_t *st = NULL;
    clock_t start;
    clock_t end;
    double msecPush = 0.0;
    double msecPop = 0.0;

    for (size_t i=0; i<num; ++i) {

        st = CCI_CreateStack(0);
        start = clock();
        doPush(st, workloads[i]);
        end = clock();
        msecPush = end - start;

        start = clock();
        doPop(st, workloads[i]);
        end = clock();
        msecPop = end - start;
        CCI_DeleteStack(st);

        printf("%d %f %f\n", (int)workloads[i], msecPush, msecPop);
    }

    return 0;
}