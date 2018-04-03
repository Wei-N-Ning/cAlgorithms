
#include "admReadline.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 64

///////////////////////////////////////////////////////////

const char *AdmLineAsString(struct AdmLine *l) {
    return (const char *)(l->data);
}

int AdmReadString(const char *str, struct AdmLine *l) {
    // although the format string specifies 64 characters, 
    // it really expects to read in less than 60 chars.
    return sscanf(str, "%64s", (char *)(l->data));
}

int AdmCheckString(struct AdmLine *l) {
    size_t nchars = 0;
    if (! (nchars = strlen(AdmLineAsString(l)))) {
        return 0;
    }
    if (nchars > LINE_LENGTH - 4) {
        return 0;
    }
    // count in the newline character
    l->start += nchars + 1;
    return 1;
}

struct AdmLine *AdmCreateStringReader() {
    struct AdmLine *l = malloc(sizeof(struct AdmLine));
    l->dataSize = LINE_LENGTH;
    l->data = malloc(l->dataSize);
    l->reset = AdmResetLine;
    l->read = AdmReadString;
    l->check = AdmCheckString;
    l->start = 0;
    l->end = 0;
    return l;
}

///////////////////////////////////////////////////////////

void *AdmLineData(struct AdmLine *l) {
    return l->data;
}

void AdmResetLine(struct AdmLine *l) {
    memset(l->data, 0, l->dataSize);
}

void AdmDeleteLine(struct AdmLine *l) {
    if (l->data) {
        free(l->data);
        l->data = NULL;
    }
    free(l);
}

int AdmReadLine(const char *str, struct AdmLine *l) {
    l->reset(l);
    if (! (l->read(str + l->start, l) && l->check(l))) {
        return 0;
    }
    return 1;
}
