//
// Created by wein on 4/1/18.
//

#include <cciArrayList.h>

#ifndef CCISOLUTIONSC_ADMQUICKSORT_H
#define CCISOLUTIONSC_ADMQUICKSORT_H

// Lomuto partition scheme
// https://en.wikipedia.org/wiki/Quicksort
// low can be -1
int AdmPartition(cciArrayList_t *al, int lo, int hi);

void AdmQuicksort(cciArrayList_t *al);

#endif //CCISOLUTIONSC_ADMQUICKSORT_H
