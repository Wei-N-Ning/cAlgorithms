//
// Created by wein on 4/2/18.
//

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <admSimpleGraph.h>
#include <admToStr.h>
#include <cciValue.h>
#include <cciHashTable.h>

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
    GetOrCreateLabelledNode(G, "test");
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

    n = GetLabelledNode(G, "WOLF3D");
    assert(n);
    assert(1 == AdmNumToNodes(n));
    assert(! AdmToNode(n, 2));
    assert(0 == strcmp("DOOM", AdmNodeLabel(AdmToNode(n, 0))));

    n = GetLabelledNode(G, "DOOM2");
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

    n = GetLabelledNode(G, "m4a1");
    assert(n);
    assert(2 == AdmNumToNodes(n));
    assert(0 == strcmp("DDM4", AdmNodeLabel(AdmToNode(n, 1))));

    DeleteAdmSimpleGraph(G);
}

static const char *buildGraph = \
"animSuite->widgets\n"
"animSuite->services\n"
"widgets->qt\n"
"widgets->common\n"
"services->common\n"
"services->libjson\n"
"services->request\n"
"common->libalgor\n"
"common->fsUtils\n"
"fsUtils->vendor\n"
"libalgor->libstring\n";

static void printKV(size_t index, size_t slotPos, cciValue_t *k, cciValue_t *v) {
    admSimpleNode_t *n = GETPOINTER((*v), admSimpleNode_t);
    printf("%s: ", AdmNodeLabel(n));
    for (size_t conn=0; conn<AdmNumToNodes(n); ++conn) {
        printf("%s, ", AdmNodeLabel(AdmToNode(n, conn)));
    }
    printf("\n");
}

static void assertKV(size_t index, size_t slotPos, cciValue_t *k, cciValue_t *v) {
    admSimpleNode_t *n = GETPOINTER((*v), admSimpleNode_t);
    assert(n);
}

void test_createGraphWithRandomNodes() {
    size_t workload = 0x123;
    size_t nbuf = 32;
    admSimpleGraph_t *G = CreateAdmSimpleGraph();
    admSimpleNode_t *n = NULL;
    admSimpleNode_t *arr[0x123];
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
    AdmGraphIter(G, assertKV);
    assert(workload == AdmGraphSize(G));
    DeleteAdmSimpleGraph(G);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}