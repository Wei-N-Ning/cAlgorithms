//
// Created by wein on 4/9/18.
//

#include <math.h>
#include <stdio.h>

#include <cciArrayList.h>

void RunTinyTests();

// note: can be invalidate by computing solve(4) manually
// see how . . - - invalidates the previous combinations
static size_t solve(size_t steps) {
    if (steps == 3) {
        return 4;
    } else if (steps == 2) {
        return 2;
    } else if (steps == 1) {
        return 1;
    } else if (steps == 0) {
        return 0;
    }
    return solve((size_t)(round(steps / 2.0))) * \
           solve(steps / 2);
}

static size_t Solve(int steps) {
    if (steps < 0) {
        return 0;
    } else if (steps == 0) {
        return 1;
    } else {
        return Solve(steps-1) + Solve(steps-2) + Solve(steps-3);
    }
}

void test_nothing() {
    printf("mine: %lu , answer: %lu ", solve(4), Solve(4));
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}

