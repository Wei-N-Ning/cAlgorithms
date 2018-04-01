//
// Created by wein on 4/1/18.
//

#include <cciArrayList.h>

#ifndef CCISOLUTIONSC_ADMQUICKSORT_H
#define CCISOLUTIONSC_ADMQUICKSORT_H

enum PartitionScheme {
    PartitionScheme_Lomuto,
    PartitionScheme_Hoare,
};

// Two partition schemes
// https://en.wikipedia.org/wiki/Quicksort
int LomutoPartition(cciArrayList_t *al, int lo, int hi);
int HoarePartition(cciArrayList_t *al, int lo, int hi);

void AdmQuicksort(cciArrayList_t *al, enum PartitionScheme ps);

#endif //CCISOLUTIONSC_ADMQUICKSORT_H
