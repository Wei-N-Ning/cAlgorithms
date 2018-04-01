//
// Created by wein on 4/1/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cciArrayList.h>
#include <admHeap.h>
#include <admMergesort.h>
#include <admQuicksort.h>

void populateAl(cciArrayList_t *al, size_t sz) {
    for (size_t i=sz; i--; AlEmplaceBack(al, newInt(random()))) ;
}

void resetAl(cciArrayList_t *al, size_t sz) {
    for (size_t i=sz; i--; AlSet(al, i, newInt(random()))) ;
}

double doMergesort(cciArrayList_t *al) {
    clock_t start, end;
    start = clock();
    Mergesort(al);
    end = clock();
    return end - start;
}

double doHeapsort(cciArrayList_t *al) {
    clock_t start, end;
    start = clock();
    AdmHeapsortAl(al, AdmHeapDirection_Ascending);
    end = clock();
    return end - start;
}

double doQuicksortHoarse(cciArrayList_t *al) {
    clock_t start, end;
    start = clock();
    AdmQuicksort(al, PartitionScheme_Hoare);
    end = clock();
    return end - start;
}

void oneRound(size_t workload) {
    cciArrayList_t *al = AlNew();
    double mHeap;
    double mMerge;
    double mQuick;
    AlReserve(al, workload);
    populateAl(al, workload);
    mMerge = doMergesort(al);

    resetAl(al, workload);
    mHeap = doHeapsort(al);

    resetAl(al, workload);
    mQuick = doQuicksortHoarse(al);

    printf("%d %f %f %f\n", (int)workload, mMerge, mHeap, mQuick);
}

void allRounds() {
    printf("workload mergesort heapsort quicksort(Hr)\n");
    for (size_t workload=34; workload < 5394134; workload *= 6) {
        oneRound(workload);
    }
}

int main(int argc, char **argv) {
    allRounds();
    return 0;
}
