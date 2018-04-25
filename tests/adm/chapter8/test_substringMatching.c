//
// Created by wein on 4/25/18.
//

#include <stdio.h>
#include <string.h>

#include <minEditDists.h>

void RunTinyTests();

void test_nothing() {
    const char *needle = "doom";
    const char *haystack = "DoMdommdom2omddomddooDmoomdomdd";
    StrCmpState *state = createDefaultState(needle, 4, haystack, 12);
    stringCompare(state);
    editSequence(state);
    printf("\n");
    deleteState(state);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}