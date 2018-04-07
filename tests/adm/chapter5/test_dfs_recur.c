//
// Created by wein on 4/8/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <admSimpleGraph.h>

void RunTinyTests();

const char *s_management = \
"E--F\n"
"E--C\n"
"F--C\n"
"A--B\n"
"A--D\n"
"B--D\n"
"F--G\n"
"D--H\n"
"G--H\n"
;

static const size_t bufLen = 4096;
static char *bufA = NULL;
static char *bufACurr = NULL;
static char *bufB = NULL;
static char *bufBCurr = NULL;

void setUp() {
    bufA = malloc(bufLen);
    memset(bufA, 0, bufLen);
    bufACurr = bufA;
    bufB = malloc(bufLen);
    memset(bufB, 0, bufLen);
    bufBCurr = bufB;
}

void tearDown() {
    free(bufA);
    bufA = NULL;
    bufACurr = NULL;
    free(bufB);
    bufB = NULL;
    bufBCurr = NULL;
}

void printNodeToBufA(admSimpleNode_t *n) {
    bufACurr += sprintf(bufACurr, "%s, ", AdmNodeLabel(n));
}

void printNodeToBufB(admSimpleNode_t *n) {
    bufBCurr += sprintf(bufBCurr, "%s, ", AdmNodeLabel(n));
}

void test_nothing() {
    admSimpleGraph_t *G = CreateGraphFromString(s_management, 10);
    admSimpleNode_t *A = GetLabelledNode(G, "A");
    admDFSState_t *state = NULL;

    // iterative dfs
    state = CreateDFSState(10);
    AdmGraphDFS(G, A, state, printNodeToBufA, NULL);
    DeleteDFSState(state);

    // recursive dfs
    state = CreateDFSState(10);
    AdmGraphRecurDFS(G, A, state, printNodeToBufB, NULL);
    DeleteDFSState(state);

    DeleteAdmSimpleGraph(G);
    printf("(%s)(%s)", bufA, bufB);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
