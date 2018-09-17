//
// Created by wein on 3/20/18.
//

#include <cci/cciQueue.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void _Enqueue(cciQueue_t *qu, size_t num) {
    for (int i=0; i<num; ++i) {
        CCI_Enqueue(qu, CCIValue_newInt(i));
    }
}

static void _Dequeue(cciQueue_t *qu, size_t num) {
    for (size_t i=0; i<num; ++i) {
        CCI_Dequeue(qu);
    }
}

int main(int argc, char **argv) {
    size_t num = 8;
    size_t workloads[8] = {10, 100, 1000, 10000, 100000, 1000000, 5000000, 10000000};
    cciQueue_t *qu = NULL;
    clock_t start;
    clock_t end;
    double msecPush = 0.0;
    double msecPop = 0.0;

    for (size_t i=0; i<num; ++i) {

        qu = CCI_CreateQueue();
        start = clock();
        _Enqueue(qu, workloads[i]);
        end = clock();
        msecPush = end - start;

        start = clock();
        _Dequeue(qu, workloads[i]);
        end = clock();
        msecPop = end - start;
        CCI_DeleteQueue(qu);

        printf("%d %f %f\n", (int)workloads[i], msecPush, msecPop);
    }

    return 0;
}