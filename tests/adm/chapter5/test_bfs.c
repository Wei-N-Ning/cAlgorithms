//
// Created by wein on 4/5/18.
//

#include <assert.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <admToStr.h>
#include <admSimpleGraph.h>

void RunTinyTests();

const char *s_dumbGraph = \
"A->B\n"
"C->D\n";

static void addWeightVisitor(admSimpleNode_t *n) {
    uint64_t *weightHandle = AdmWeightHandle(n);
    (*weightHandle)++;
}

static void printConnectionVisitor(admSimpleEdge_t *e) {
    printf("%s->%s\n", AdmNodeLabel(AdmEdgeFrom(e)), AdmNodeLabel(AdmEdgeTo(e)));
}

void test_minimalBFSExpectNodesVisited() {
    admSimpleGraph_t *G = CreateGraphFromString(s_dumbGraph, 8);
    admSimpleNode_t *start = GetLabelledNode(G, "C");
    assert(0 == *AdmWeightHandle(GetLabelledNode(G, "C")));
    assert(0 == *AdmWeightHandle(GetLabelledNode(G, "D")));
    AdmGraphBFS(G, start, NULL, addWeightVisitor, NULL);
    assert(1 == *AdmWeightHandle(GetLabelledNode(G, "C")));
    assert(1 == *AdmWeightHandle(GetLabelledNode(G, "D")));
    DeleteAdmSimpleGraph(G);
}

const char *s_dumbGraphCircularDependency = \
"A->B\n"
"B->C\n"
"A->C\n"
"C->A\n"
"C->D\n"
"A->D\n"
;

// C->A
// C->D
// A->B
void test_expectAllNodesVisitedOnlyOnce() {
    admSimpleGraph_t *G = CreateGraphFromString(s_dumbGraphCircularDependency, 8);
    admSimpleNode_t *start = GetLabelledNode(G, "C");
    AdmGraphBFS(G, start, NULL, addWeightVisitor, printConnectionVisitor);
    assert(1 == *AdmWeightHandle(GetLabelledNode(G, "A")));
    assert(1 == *AdmWeightHandle(GetLabelledNode(G, "C")));
    DeleteAdmSimpleGraph(G);
}

void test_expectShortestPathViaBFSTree() {
    // expecting A->D
    admSimpleGraph_t *G = CreateGraphFromString(s_dumbGraphCircularDependency, 8);
    cciHashTable_t *BFSTree = NewHashTable(8);
    admSimpleNode_t *start = GetLabelledNode(G, "A");
    admSimpleNode_t *expected = GetLabelledNode(G, "D");
    cciValue_t v;
    AdmGraphBFS(G, start, BFSTree, NULL, NULL);
    v = IGet(BFSTree, (uint64_t)expected);
    assert(ISVALID(v));
    assert(start == GETPOINTER(v, admSimpleNode_t));
    DeleteHashTable(BFSTree);
    DeleteAdmSimpleGraph(G);
}

static admSimpleGraph_t *createGraph(size_t workload, admSimpleNode_t **start) {
    size_t nbuf = 32;
    admSimpleGraph_t *G = CreateAdmSimpleGraph(workload);
    admSimpleNode_t *n = NULL;
    admSimpleNode_t **arr = malloc(workload * sizeof(admSimpleNode_t *));
    char buf[32];
    memset(buf, 0, nbuf);
    for (uint64_t i=0; i<workload; ++i) {
        BytesToUniqueString(i * 2 + 1, buf, nbuf);
        n = GetOrCreateLabelledNode(G, buf);
        arr[i] = n;
    }
    for (size_t i=0; i<workload; ++i) {
        n = arr[i];
        for (size_t idx = 0; idx<workload; idx = idx * 2 + 1) {
            AdmConnectTo(n, arr[(idx + 1 + i) % workload]);
        }
    }
    (*start) = arr[0];
    free(arr);
    return G;
}

// the procedurally generated graph is a non-trivial graph;
// every node is connected to log(N) other nodes
void test_getConnectedComponent() {
    admSimpleNode_t *start = NULL;
    admSimpleGraph_t *G = createGraph(0x34, &start);
    cciHashTable_t *BFSTree = NewHashTable(0x34);
    AdmGraphBFS(G, start, BFSTree, NULL, NULL);
    assert(0x34 == HashTableNumKeys(BFSTree));
    DeleteHashTable(BFSTree);
    DeleteAdmSimpleGraph(G);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
