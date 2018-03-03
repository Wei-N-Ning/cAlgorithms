#ifndef TINYCUNIT_H
#define TINYCUNIT_H

#include <assert.h>
#include <stdio.h>
#include <time.h>

#ifndef MAXNUMTESTFUNCS
#define MAXNUMTESTFUNCS 1024
#endif

#define impl_TestFunc(function_body) \
({ \
    void __fn__ function_body \
      __fn__; \
})

#define NewTinyTest(function_name) impl_TestFuncIdx++; impl_TestNames[impl_TestFuncIdx]=function_name; impl_TestFuncs[impl_TestFuncIdx] = impl_TestFunc
#define AssertTrue(actual) (assert(actual))
#define AssertEqual(expected, actual) (assert(expected == actual))

typedef void (*impl_TestFunc_t)(void);
impl_TestFunc_t impl_TestFuncs[MAXNUMTESTFUNCS] = {};
char *impl_TestNames[MAXNUMTESTFUNCS] = {};
int impl_TestFuncIdx = -1;

void InitializeTinyTests() {
    for (int i=0; i < MAXNUMTESTFUNCS; ++i) {
        impl_TestFuncs[i] = NULL;
        impl_TestNames[i] = NULL;
    }
}

void RunTinyTests() {
    clock_t before = clock(), after;
    double msec = 0.0;
    for (int i=0; i <= impl_TestFuncIdx; ++i) {
        printf("TinyTest: %s......", impl_TestNames[i]);
        impl_TestFuncs[i]();
        printf("PASSED\n");
    }
    after = clock();
    msec = after - before;
    printf("\nSummary: %d tests, %fs (%fms)\n", impl_TestFuncIdx + 1, msec/CLOCKS_PER_SEC, msec);
}

#endif //TINYCUNIT_H