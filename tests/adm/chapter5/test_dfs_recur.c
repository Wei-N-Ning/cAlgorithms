//
// Created by wein on 4/8/18.
//

#include <assert.h>
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

static void printConnectionVisitor(admSimpleEdge_t *e, admDFSState_t *state) {
    printf("%s->%s; ", AdmNodeLabel(AdmEdgeFrom(e)), AdmNodeLabel(AdmEdgeTo(e)));
}

void printNodeToBufA(admSimpleNode_t *n, admDFSState_t *state) {
    bufACurr += sprintf(bufACurr, "%s, ", AdmNodeLabel(n));
}

void printEdgeToBufA(admSimpleEdge_t *e, admDFSState_t *state) {
    bufACurr += sprintf(bufACurr, "%s->%s, ", AdmNodeLabel(AdmEdgeFrom(e)), AdmNodeLabel(AdmEdgeTo(e)));
}

void printNodeToBufB(admSimpleNode_t *n, admDFSState_t *state) {
    bufBCurr += sprintf(bufBCurr, "%s, ", AdmNodeLabel(n));
}

void printEdgeToBufB(admSimpleEdge_t *e, admDFSState_t *state) {
    bufBCurr += sprintf(bufBCurr, "%s->%s, ", AdmNodeLabel(AdmEdgeFrom(e)), AdmNodeLabel(AdmEdgeTo(e)));
}

void test_simpleUndirectGraphExpectNodeOrder() {
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

    assert(0 == strcmp(bufA, bufB));
}

void test_simpleUndirectGraphExpectEdgeOrder() {
    admSimpleGraph_t *G = CreateGraphFromString(s_management, 10);
    admSimpleNode_t *A = GetLabelledNode(G, "A");
    admDFSState_t *state = NULL;

    // iterative dfs
    state = CreateDFSState(10);
    AdmGraphDFS(G, A, state, NULL, printEdgeToBufA);
    DeleteDFSState(state);

    // recursive dfs
    state = CreateDFSState(10);
    AdmGraphRecurDFS(G, A, state, NULL, printEdgeToBufB);
    DeleteDFSState(state);

    DeleteAdmSimpleGraph(G);
    printf("(%s)(%s)", bufA, bufB);

    assert(0 == strcmp(bufA, bufB));
}

void test_proceduralGraphExpectNodeOrder() {
    admSimpleNode_t *start = NULL;
    size_t size = 184;
    admSimpleGraph_t *G = CreateProceduralGraph(size, &start);
    admDFSState_t *state = NULL;

    // iterative dfs
    state = CreateDFSState(size);
    AdmGraphDFS(G, start, state, printNodeToBufA, NULL);
    DeleteDFSState(state);

    // recursive dfs
    state = CreateDFSState(size);
    AdmGraphRecurDFS(G, start, state, printNodeToBufB, NULL);
    DeleteDFSState(state);

    DeleteAdmSimpleGraph(G);

    assert(0 == strcmp(bufA, bufB));
}

// see ADM P183 example
const char *s_undirected = \
"1--6\n"
"1--2\n"
"1--5\n"
"2--3\n"
"2--5\n"
"3--4\n"
"5--4\n"
;

void test_expectBackEdges() {
    size_t sz = 10;
    admSimpleGraph_t *G = CreateGraphFromString(s_undirected, sz);
    admSimpleNode_t *A = GetLabelledNode(G, "1");
    admSimpleEdge_t *e = NULL;
    admDFSState_t *state = NULL;
    cciValue_t v;

    // iterative dfs
    state = CreateDFSState(sz);
    AdmGraphDFS(G, A, state, NULL, NULL);
    for (size_t i=0; i<state->BackEdges->size; i++) {
        v = AlGet(state->BackEdges, i);
        e = GETPOINTER(v, admSimpleEdge_t);
        bufACurr += sprintf(bufACurr, "%s->%s, ", AdmNodeLabel(AdmEdgeFrom(e)), AdmNodeLabel(AdmEdgeTo(e)));
    }
    DeleteDFSState(state);

    // recursive dfs
    state = CreateDFSState(sz);
    AdmGraphRecurDFS(G, A, state, NULL, NULL);
    for (size_t i=0; i<state->BackEdges->size; i++) {
        v = AlGet(state->BackEdges, i);
        e = GETPOINTER(v, admSimpleEdge_t);
        bufBCurr += sprintf(bufBCurr, "%s->%s, ", AdmNodeLabel(AdmEdgeFrom(e)), AdmNodeLabel(AdmEdgeTo(e)));
    }
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);

    printf("(%s)(%s)", bufA, bufB);
    assert(0 == strcmp(bufA, bufB));
}

void test_proceduralGraphExpectBackEdges() {
    admSimpleNode_t *start = NULL;
    size_t sz = 256;
    admSimpleGraph_t *G = CreateProceduralGraph(sz, &start);
    admSimpleEdge_t *e = NULL;
    admDFSState_t *state = NULL;
    cciValue_t v;

    // iterative dfs
    state = CreateDFSState(sz);
    AdmGraphDFS(G, start, state, NULL, NULL);
    for (size_t i=0; i<state->BackEdges->size; i++) {
        v = AlGet(state->BackEdges, i);
        e = GETPOINTER(v, admSimpleEdge_t);
        bufACurr += sprintf(bufACurr, "%s->%s, ", AdmNodeLabel(AdmEdgeFrom(e)), AdmNodeLabel(AdmEdgeTo(e)));
    }
    DeleteDFSState(state);

    // recursive dfs
    state = CreateDFSState(sz);
    AdmGraphRecurDFS(G, start, state, NULL, NULL);
    for (size_t i=0; i<state->BackEdges->size; i++) {
        v = AlGet(state->BackEdges, i);
        e = GETPOINTER(v, admSimpleEdge_t);
        bufBCurr += sprintf(bufBCurr, "%s->%s, ", AdmNodeLabel(AdmEdgeFrom(e)), AdmNodeLabel(AdmEdgeTo(e)));
    }
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);

    assert(0 == strcmp(bufA, bufB));
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
