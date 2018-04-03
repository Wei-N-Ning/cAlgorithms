//
// Created by wein on 4/3/18.
//

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <admReadline.h>

void RunTinyTests();

// no space is allowed
// try write out a line that is longer than 60 chars (including \n),
// the assert statement will fail
const char *SUT =\
"A->B\n"
"A->C\n"
"B->D,D->F\n"
"C->E,E->M\n";

void test_readStringExpectLineData() {
    struct AdmLine *l = AdmCreateStringReader();
    for (int i=0; AdmReadLine(SUT, l); ++i) {
        if (i == 0) {
            assert(0 == strcmp(AdmLineAsString(l), "A->B"));
        } else if (i == 2) {
            assert(0 == strcmp(AdmLineAsString(l), "B->D,D->F"));
        }
    }
    AdmDeleteLine(l);
}

struct MockLabel {
    char first;
    char second;
};

void test_interpretLineAsLabel() {
    const char *str;
    struct MockLabel lb;
    struct AdmLine *l = AdmCreateStringReader();
    for (int i=0; AdmReadLine(SUT, l); ++i) {
        str = AdmLineAsString(l);
        assert(sscanf(str, "%c->%c", &lb.first, &lb.second));
        if (i == 0) {
            assert('A' == lb.first && 'B' == lb.second);
        } else if (i == 2) {
            assert('B' == lb.first && 'D' == lb.second);
        }
    }
    AdmDeleteLine(l);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}

