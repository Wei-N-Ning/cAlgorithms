//
// Created by wein on 3/19/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <cciArrayList.h>
#include <time.h>

void appendToCArray(size_t workload, int *arr) {
    for (int i=0; i<workload; ++i) {
        arr[i] = i;
    }
}

void appendToArrayList(size_t workload, cciArrayList_t *al) {
    for (int i=0; i<workload; ++i) {
        AlEmplaceBack(al, newInt(i));
    }
}

void eachRound(size_t workload) {
    int *arr = malloc(sizeof(int) * workload);
    cciArrayList_t *al = AlNew();
    clock_t start, end;
    double msecArr = 0.0;
    double msecAl = 0.0;

    start = clock();
    appendToCArray(workload, arr);
    end = clock();
    msecArr = end - start;

    start = clock();
    appendToArrayList(workload, al);
    end = clock();
    msecAl = end -start;

    AlDelete(al);
    free(arr);

    printf("%d %f %f\n", (int)workload, msecArr, msecAl);
}

int main(int argc, char **argv) {
    size_t workloads[8] = {100, 500, 1000, 10000, 50000, 100000, 500000, 1000000};
    for (int i=0; i<8; ++i) {
        eachRound(workloads[i]);
    }
    return 0;
}