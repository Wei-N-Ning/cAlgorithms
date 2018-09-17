//
// Created by wein on 3/31/18.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <admHeap.h>

void heapsortTime() {
    printf("heapsort time\n");
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

void heapCreationTime() {
    printf("heap creation time\n");
    printf("workload create-by-insert() create-by-heapify()\n");
    admHeap_t *hp = NULL;
    cciArrayList_t *al = NULL;
    clock_t start, end;
    double timeInsert;
    double timeHeapify;
    for (size_t workload=9; workload < 3000000; workload *= 6) {

        hp = CreateAdmHeap(16);
        start = clock();
        for (size_t i=workload; i--; AdmHeapInsert(hp, CCIValue_newInt(random()))) ;
        end = clock();
        timeInsert = end - start;
        DeleteAdmHeap(hp);

        al = CCI_AlNew();
        for (size_t i=workload; i--; CCI_AlEmplaceBack(al, CCIValue_newInt(random()))) ;
        start = clock();
        Heapify(al);
        end = clock();
        timeHeapify = end - start;
        CCI_AlDelete(al);

        printf("%d %f %f\n", (int)workload, timeInsert, timeHeapify);
    }
}

int main(int argc, char **argv) {
    heapsortTime();
    heapCreationTime();
    return 0;
}
