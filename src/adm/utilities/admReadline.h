//
// Created by wein on 4/3/18.
//

#ifndef CCISOLUTIONSC_ADMREADLINE_H
#define CCISOLUTIONSC_ADMREADLINE_H

#include <stddef.h>

struct AdmLine;

typedef void (*LineReseter)(struct AdmLine *l);
typedef int (*LineReader)(const char *str, struct AdmLine *l);
typedef int (*LineValidator)(struct AdmLine *l);

struct AdmLine {
    size_t start;
    size_t end;

    void *data;
    size_t dataSize;

    LineReseter reset;
    LineReader read;
    LineValidator check;
};

//////////////////////////////////////////////////////////////

int AdmReadString(const char *str, struct AdmLine *l);
int AdmCheckString(struct AdmLine *l);
struct AdmLine *AdmCreateStringReader();
const char *AdmLineAsString(struct AdmLine *l);

//////////////////////////////////////////////////////////////

void *AdmLineData(struct AdmLine *l);
void AdmResetLine(struct AdmLine *l);
void AdmDeleteLine(struct AdmLine *l);
int AdmReadLine(const char *str, struct AdmLine *l);

#endif //CCISOLUTIONSC_ADMREADLINE_H
