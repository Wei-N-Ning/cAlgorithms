//
// Created by wein on 4/5/18.
//

#include <assert.h>

#include <admSimpleGraph.h>

void RunTinyTests();

const char *s_dumbGraph = \
"A->B\n"
"C->D\n";

static void addWeightVisitor(admSimpleNode_t *n) {
    uint64_t *weightHandle = AdmWeightHandle(n);
    (*weightHandle)++;
}

void test_minimalBFS() {
    admSimpleGraph_t *G = CreateGraphFromString(s_dumbGraph, 8);
    admSimpleNode_t *start = GetLabelledNode(G, "C");
    assert(0 == *AdmWeightHandle(GetLabelledNode(G, "C")));
    assert(0 == *AdmWeightHandle(GetLabelledNode(G, "D")));
    AdmGraphBFS(G, start, addWeightVisitor);
    assert(1 == *AdmWeightHandle(GetLabelledNode(G, "C")));
    assert(1 == *AdmWeightHandle(GetLabelledNode(G, "D")));
    DeleteAdmSimpleGraph(G);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
