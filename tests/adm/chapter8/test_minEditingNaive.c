//
// Created by wein on 4/24/18.
//
// to verify that the naive implementation (recursive function) works

#include <stdio.h>
#include <minEditDistsNaive.h>

void RunTinyTests();

void test_recursion() {
    printf("\n");
    int r1 = stringCompareSlow(
        "atherEis acow 1337",
        "there IS no spoon",
        8, 9
    );
    printf("min edits: (slow) %d, \n", r1);

}

void test_recursionCached() {
    printf("\n");
    int r2 = stringCompareCached(
        "atherEis acow 1337",
        "there IS no spoon",
        8, 9
    );
    printf("min edits: (cached) %d, \n", r2);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}