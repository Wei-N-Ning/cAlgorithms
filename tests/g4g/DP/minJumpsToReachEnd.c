//
// Created by wein on 4/15/18.
// post
// https://www.geeksforgeeks.org/minimum-number-of-jumps-to-reach-end-of-a-given-array/

// NOTE: this is the naive method
// given arr A that has n ints
// one can forward from A[i] to any element up to (including) A[i + A[i]],
// if A[i] is 0 and i != n - 1, game is over
// because finding the path from A[0] to A[n - 1] uses the same
// logic as finding the path from A[i] to A[n - 1], where there
// exists a one jump solution from A[0] to A[i]
// the solution can be written as:
// solve(A, 0, n-1):
//    npaths = min(
//       solve(A, 1, n-1),
//       solve(A, 2, n-1),
//       ...
//       solve(A, i, n-1),
//    )
//    return 1 + npaths
//
// Use relaxation method
// for any i;
// relax the minimal jumps from 0 to i


#include <assert.h>
#include <stdio.h>

void RunTinyTests();


void test_solution() {
    int arr[8] = {3, 14, 159, 2, 6, 535, 8, 97};
    int njumps = 0;
    int distance = 0;
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}

