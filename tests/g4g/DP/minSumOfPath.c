//
// Created by wein on 4/15/18.
//
// post:
// https://www.geeksforgeeks.org/minimum-sum-path-triangle/
//
// NOTE: path starts from the top, finishes at the bottom
// HINT: bottom-up traversal, use memo, try to book keep the path as well

// value of the node itself: A[k][i]
// value of the children: A[k + 1][i], A[k + 1][i + 1]
// r0c0 r1c0 r1c1 r2c0 r2c1 r2c2 r3c0 r3c1 r3c2 r3c3
//  i   i+1  i+2  i+3  i+4  i+5  i+6  i+7  i+8  i+9

const char *doc = \
"   o"
"  o o"
" o o o k"
"o o o o k + 1"
"";

void RunTinyTests();

void test_nothing() {
    ;
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
