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

void test_expectTopoOrder() {
    size_t sz = 16;
    int ok = 0;
    admSimpleGraph_t *G = CreateGraphFromString(s_dag, sz);
    admSimpleNode_t *n = GetLabelledNode(G, "G");
    cciArrayList_t *arr = CCI_AlNew();
    ok = AdmTopoSort(G, n, arr);
    for (size_t i=0; i<arr->size; ++i) {
        n = CCIValue_GETPOINTER(CCI_AlGet(arr, i), admSimpleNode_t);
        bufCurr += sprintf(bufCurr, "%s, ", AdmNodeLabel(n));
    }
    assert(1 == ok);
    assert(0 == strcmp("G, A, B, C, F, E, D, ", buf));
    CCI_AlDelete(arr);
    DeleteAdmSimpleGraph(G);
}

void test_expectTopoSortFailed() {
    size_t sz = 16;
    admSimpleGraph_t *G = CreateGraphFromString(s_dag, sz);
    admSimpleNode_t *A = GetLabelledNode(G, "A");
    admSimpleNode_t *B = GetLabelledNode(G, "B");
    AdmConnectTo(B, A);
    assert(! AdmTopoSort(G, A, NULL));
    DeleteAdmSimpleGraph(G);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
