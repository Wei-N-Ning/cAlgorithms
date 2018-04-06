//
// Created by wein on 4/6/18.
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

void test_minimalDFSExpectNodesVisited() {
    admSimpleGraph_t *G = CreateGraphFromString(s_dumbGraph, 8);
    admSimpleNode_t *start = GetLabelledNode(G, "A");
    admSimpleNode_t *sut = GetLabelledNode(G, "B");
    admDFSState_t *state = CreateDFSState(8);
    assert(0 == *AdmWeightHandle(sut));
    AdmGraphDFS(G, start, state, addWeightVisitor, NULL);
    assert(1 == *AdmWeightHandle(sut));
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
