#ifndef TINYCUNIT_H
#define TINYCUNIT_H

#include <assert.h>
#include <stdio.h>
#include <time.h>

#ifndef MAXNUMTESTFUNCS
#define MAXNUMTESTFUNCS 1024
#endif

#define __TestFunc(function_body) \
({ \
    void __fn__ function_body \
      __fn__; \
})

#define NewTinyTest(function_name) __TestFuncIdx++; __TestNames[__TestFuncIdx]=function_name; __TestFuncs[__TestFuncIdx] = __TestFunc
#define AssertTrue(actual) (assert(actual))
#define AssertEqual(expected, actual) (assert(expected == actual))

typedef void (*__TestFunc_t)(void);
__TestFunc_t __TestFuncs[MAXNUMTESTFUNCS] = {};
char *__TestNames[MAXNUMTESTFUNCS] = {};
int __TestFuncIdx = -1;

void InitializeTinyTests() {
    for (int i=0; i < MAXNUMTESTFUNCS; ++i) {
        __TestFuncs[i] = NULL;
        __TestNames[i] = "\0";
    }
}

void RunTinyTests() {
    clock_t before = clock(), after;
    double msec = 0.0;
    for (int i=0; i <= __TestFuncIdx; ++i) {
        printf("TinyTest: %s......", __TestNames[i]);
        __TestFuncs[i]();
        printf("PASSED\n");
    }
    after = clock();
    msec = after - before;
    printf("\nSummary: %d tests, %fs (%fms)\n", __TestFuncIdx + 1, msec/CLOCKS_PER_SEC, msec);
}

#endif //TINYCUNIT_H