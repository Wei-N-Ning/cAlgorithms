//
// Created by wein on 4/26/18.
//

#include <stdio.h>
#include <string.h>
#include <minEditDists.h>

void RunTinyTests();

int match(StrCmpState *state, int i, int j) {
    return (state->s[i] == state->t[j]) ? 0 : 3;
}

void test_nothing() {
    const char *haystack = "DoMdomm2om2omddomd2ooDdoommoomTomdd";
    const char *needle =   "2oo%doom";
    StrCmpState *state = createDefaultState(haystack, strlen(haystack), needle, strlen(needle));
    state->match = match;
    int r1 = stringCompare(state);
    editSequence(state);
    deleteState(state);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}