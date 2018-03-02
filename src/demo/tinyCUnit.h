//
// Created by wein on 3/2/18.
//

#ifndef TINYCUNIT_H
#define TINYCUNIT_H

#include <assert.h>
#include <stdio.h>

#ifndef MAXNUMTESTFUNCS
#define MAXNUMTESTFUNCS 1024
#endif

#define __TestFunc(return_type, function_body) \
({ \
    return_type __fn__ function_body \
      __fn__; \
})

#define NewTinyTest TestFuncs[__TestFuncIdx++] = __TestFunc
#define AssertTrue(actual) (assert(actual))
#define AssertEqual(expected, actual) (assert(expected == actual))

typedef int (*__TestFunc_t)(void);
__TestFunc_t TestFuncs[MAXNUMTESTFUNCS] = {};
char **TestNames[MAXNUMTESTFUNCS] = {};
int __TestFuncIdx = 0;

#endif //TINYCUNIT_H

void InitializeTinyTests() {
    for (int i=0; i < MAXNUMTESTFUNCS; ++i) {
        TestFuncs[i] = NULL;
        TestNames[i] = "\0";
    }
}

void RunTinyTests() {
    for (int i=0; i < __TestFuncIdx; ++i) {
        TestFuncs[i]();
    }
}
