//
// Created by wein on 4/2/18.
//

#include <assert.h>
#include <string.h>

#include <admSimpleGraph.h>

void RunTinyTests();

void test_createSimpleNodeExpectInitialState() {
    admSimpleNode_t *n = CreateAdmSimpleNode();
    assert(n);
    assert(! AdmSNDegree(n));
    DeleteAdmSimpleNode(n);
}

void test_connectionBetweenNodes() {
    admSimpleNode_t *n1 = CreateAdmSimpleNode();
    admSimpleNode_t *n2 = CreateAdmSimpleNode();
    assert(0 == AdmNumToNodes(n1));
    AdmConnectTo(n1, n2);
    assert(1 == AdmNumToNodes(n1));
    assert(n2 == AdmToNode(n1, 0));
    assert(! AdmToNode(n1, 1));
    DeleteAdmSimpleNode(n1);
    DeleteAdmSimpleNode(n2);
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

static const char *directedGraph = \
"WOLF3D->DOOM\n"
"DOOM->DOOM2\n"
"DOOM2->DOOM1.7\n"
"DOOM2->QUAKE\n"
"DOOM->BLAKESTONE\n";

void test_createDirectedGraphFromString() {
    admSimpleGraph_t *G = CreateGraphFromString(directedGraph);
    admSimpleNode_t *n = NULL;
    assert(6 == AdmGraphSize(G));

    n = GetAdmNode(G, "WOLF3D");
    assert(n);
    assert(1 == AdmNumToNodes(n));
    assert(! AdmToNode(n, 2));
    assert(0 == strcmp("DOOM", AdmNodeLabel(AdmToNode(n, 0))));

    n = GetAdmNode(G, "DOOM2");
    assert(n);
    assert(2 == AdmNumToNodes(n));
    assert(0 == strcmp("DOOM1.7", AdmNodeLabel(AdmToNode(n, 0))));
    assert(0 == strcmp("QUAKE", AdmNodeLabel(AdmToNode(n, 1))));

    DeleteAdmSimpleGraph(G);
}

static const char *undirectedGraph = \
"HK416--m4a1\n"
"AK103--AKM\n"
"m4a1--DDM4\n"
"AKM--NorincoType56\n"
"HK416--m27IAR\n";

void test_createUndirectedGraphFromString() {
    admSimpleGraph_t *G = CreateGraphFromString(undirectedGraph);
    admSimpleNode_t *n = NULL;
    assert(7 == AdmGraphSize(G));

    n = GetAdmNode(G, "m4a1");
    assert(n);
    assert(2 == AdmNumToNodes(n));
    assert(0 == strcmp("DDM4", AdmNodeLabel(AdmToNode(n, 1))));

    DeleteAdmSimpleGraph(G);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}