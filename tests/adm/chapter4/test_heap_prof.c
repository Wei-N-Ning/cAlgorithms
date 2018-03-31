//
// Created by wein on 3/31/18.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <admHeap.h>

void doAllWorks() {
    int *arr = NULL;
    clock_t start, end;
    double msec;
    for (size_t workload=9; workload < 3000000; workload *= 6) {
        arr = malloc(sizeof(int) * workload);
        for (size_t i=workload; i--; arr[i] = (int)random()) ;
        start = clock();
        AdmHeapsortInts(arr, workload);
        end = clock();
        msec = end - start;
        free(arr);
        printf("%d %f\n", (int)workload, msec);
    }
}

int main(int argc, char **argv) {
    doAllWorks();
    return 0;
}
