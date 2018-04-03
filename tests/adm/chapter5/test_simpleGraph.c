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

void test_deleteGraph() {
    admSimpleGraph_t *G = CreateAdmSimpleGraph();
    GetOrCreateAdmNode(G, "test");
    assert(1 == AdmGraphSize(G));
    DeleteAdmSimpleGraph(G);
}

////////////////////////////////////////////////

static const char *s_dumbGraph = \
"WOLF3D->DOOM\n"
"DOOM->DOOM2\n"
"DOOM2->DOOM1.7\n"
"DOOM2->QUAKE\n"
"DOOM->BLAKESTONE\n";

void test_createGraphFromString() {
    admSimpleGraph_t *G = CreateGraphFromString(s_dumbGraph);
//    assert(6 == AdmGraphSize(G));
    DeleteAdmSimpleGraph(G);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}