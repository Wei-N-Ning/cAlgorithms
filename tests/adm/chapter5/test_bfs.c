//
// Created by wein on 4/5/18.
//

#include <assert.h>
#include <stdio.h>

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
    AdmGraphBFS(G, start, addWeightVisitor, NULL);
    assert(1 == *AdmWeightHandle(GetLabelledNode(G, "C")));
    assert(1 == *AdmWeightHandle(GetLabelledNode(G, "D")));
    DeleteAdmSimpleGraph(G);
}

const char *s_dumbGraphCircularDependency = \
"A->B\n"
"B->C\n"
"A->C\n"
"C->A\n"
;

void test_expectAllNodesVisitedOnlyOnce() {
    admSimpleGraph_t *G = CreateGraphFromString(s_dumbGraphCircularDependency, 8);
    admSimpleNode_t *start = GetLabelledNode(G, "C");
    AdmGraphBFS(G, start, addWeightVisitor, printConnectionVisitor);
    assert(1 == *AdmWeightHandle(GetLabelledNode(G, "A")));
    assert(1 == *AdmWeightHandle(GetLabelledNode(G, "C")));
    DeleteAdmSimpleGraph(G);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
