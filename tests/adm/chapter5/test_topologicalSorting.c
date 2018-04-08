//
// Created by wein on 4/8/18.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <admSimpleGraph.h>

void RunTinyTests();

// see ADM P191
// expected topo order: G, A, B, C, F, E, D
static const char *s_dag =\
"G->A\n"
"G->F\n"
"A->B\n"
"A->C\n"
"F->E\n"
"C->F\n"
"C->E\n"
"B->C\n"
"B->D\n"
"E->D\n"
;

static char *buf = NULL;
static const size_t bufLen = 4096;
static char *bufCurr = NULL;

void setUp() {
    buf = malloc(bufLen);
    bufCurr = buf;
}

void tearDown() {
    free(buf);
    buf = NULL;
    bufCurr = NULL;
}

void printNodeVisitor(admSimpleNode_t *n) {
    bufCurr += sprintf(bufCurr, "%s, ", AdmNodeLabel(n));
}

void test_expectTopoOrder() {
    size_t sz = 16;
    admSimpleGraph_t *G = CreateGraphFromString(s_dag, sz);
    admSimpleNode_t *start = GetLabelledNode(G, "G");
    admDFSState_t *state = CreateDFSState(sz);
    AdmGraphDFS(G, start, state, printNodeVisitor, NULL);
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
    assert(0 == strcmp("G, A, B, C, F, E, D, ", buf));
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
