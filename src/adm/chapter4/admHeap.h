//
// Created by wein on 3/29/18.
//

#ifndef CCISOLUTIONSC_ADMHEAP_H
#define CCISOLUTIONSC_ADMHEAP_H

#include <stddef.h>

struct AdmHeap;
typedef struct AdmHeap admHeap_t;

admHeap_t *CreateAdmHeap(size_t capacity);

void DeleteAdmHeap(admHeap_t *hp);

#endif //CCISOLUTIONSC_ADMHEAP_H
