//
// Created by wein on 4/2/18.
//

#include <assert.h>

#include <admSimpleGraph.h>

void RunTinyTests();

void test_createSimpleNodeExpectInitialState() {
    admSimpleNode_t *n = CreateAdmSimpleNode();
    assert(n);
    assert(! AdmSNDegree(n));
    DeleteAdmSimpleNode(n);
}

////////////////////////////////////////////////

void test_createSimpleGraphExpectInitialState() {
    admSimpleGraph_t *G = CreateAdmSimpleGraph();
    assert(G);
    DeleteAdmSimpleGraph(G);
}

////////////////////////////////////////////////

static const char *s_dumbGraph = \
"A->B\n"
"A->C\n"
"B->D\n"
"C->E\n";

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}