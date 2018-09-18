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

static void addWeightVisitor(admSimpleNode_t *n, admDFSState_t *state) {
    uint64_t *weightHandle = AdmWeightHandle(n);
    (*weightHandle)++;
}

static void printNodeVisitor(admSimpleNode_t *n, admDFSState_t *state) {
    printf("%s ", AdmNodeLabel(n));
}

static void printConnectionVisitor(admSimpleEdge_t *e, admDFSState_t *state) {
    printf("%s->%s; ", AdmNodeLabel(AdmEdgeFrom(e)), AdmNodeLabel(AdmEdgeTo(e)));
}

void test_oneNode() {
    admSimpleGraph_t *G = CreateAdmSimpleGraph(8);
    admSimpleNode_t *A = GetOrCreateLabelledNode(G, "A");
    admDFSState_t *state = CreateDFSState(8);
    assert(0 == *AdmWeightHandle(A));
    AdmGraphDFS(G, A, state, addWeightVisitor, NULL);
    // node is visited
    assert(1 == *AdmWeightHandle(A));
    // entry-exit stats
    assert(0 == CCIValue_GETINT(CCI_IGet(state->Entries, (uint64_t)A)));
    assert(1 == CCIValue_GETINT(CCI_IGet(state->Exits, (uint64_t)A)));
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

void test_twoNodes() {
    admSimpleGraph_t *G = CreateGraphFromString("A->B\n", 8);
    admSimpleNode_t *A = GetOrCreateLabelledNode(G, "A");
    admSimpleNode_t *B = GetOrCreateLabelledNode(G, "B");
    admDFSState_t *state = CreateDFSState(8);
    assert(0 == *AdmWeightHandle(A));
    assert(0 == *AdmWeightHandle(B));
    AdmGraphDFS(G, A, state, addWeightVisitor, printConnectionVisitor);
    // node is visited
    assert(1 == *AdmWeightHandle(A));
    assert(1 == *AdmWeightHandle(B));
    // entry-exit stats
    assert(0 == CCIValue_GETINT(CCI_IGet(state->Entries, (uint64_t)A)));
    assert(1 == CCIValue_GETINT(CCI_IGet(state->Entries, (uint64_t)B)));
    assert(2 == CCIValue_GETINT(CCI_IGet(state->Exits, (uint64_t)B)));
    assert(3 == CCIValue_GETINT(CCI_IGet(state->Exits, (uint64_t)A)));
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

void test_minimalDFSExpectNodesVisited() {
    admSimpleGraph_t *G = CreateGraphFromString(s_dumbGraph, 8);
    admSimpleNode_t *start = GetLabelledNode(G, "A");
    admSimpleNode_t *sut = GetLabelledNode(G, "B");
    admDFSState_t *state = CreateDFSState(8);
    assert(0 == *AdmWeightHandle(sut));
    AdmGraphDFS(G, start, state, addWeightVisitor, printConnectionVisitor);
    assert(1 == *AdmWeightHandle(sut));
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

const char *s_minimal = \
"A->B\n"
"B->C\n"
"A->C\n"
"C->A\n"
"C->D\n"
"A->D\n"
"D->B\n";


void test_expectNodeVistingOrder() {
    admSimpleGraph_t *G = CreateGraphFromString(s_minimal, 8);
    admSimpleNode_t *start = GetLabelledNode(G, "A");
    admDFSState_t *state = CreateDFSState(8);
    AdmGraphDFS(G, start, state, printNodeVisitor, NULL);
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

void test_expectEdgeVisitingOrder() {
    admSimpleGraph_t *G = CreateGraphFromString(s_minimal, 8);
    admSimpleNode_t *start = GetLabelledNode(G, "A");
    admDFSState_t *state = CreateDFSState(8);
    AdmGraphDFS(G, start, state, NULL, printConnectionVisitor);
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

void test_expectDFSTreePopulated() {
    admSimpleGraph_t *G = CreateGraphFromString(s_minimal, 8);
    admSimpleNode_t *A = GetLabelledNode(G, "A");
    admSimpleNode_t *B = GetLabelledNode(G, "B");
    admSimpleNode_t *C = GetLabelledNode(G, "C");
    admSimpleNode_t *D = GetLabelledNode(G, "D");
    admDFSState_t *state = CreateDFSState(8);
    cciValue_t v;
    AdmGraphDFS(G, A, state, NULL, NULL);

    v = CCI_IGet(state->DFSTree, (uint64_t)A);
    assert(! CCIValue_ISVALID(v));

    v = CCI_IGet(state->DFSTree, (uint64_t )B);
    assert(A == CCIValue_GETPOINTER(v, admSimpleNode_t));

    v = CCI_IGet(state->DFSTree, (uint64_t )C);
    assert(B == CCIValue_GETPOINTER(v, admSimpleNode_t));

    v = CCI_IGet(state->DFSTree, (uint64_t )D);
    assert(C == CCIValue_GETPOINTER(v, admSimpleNode_t));

    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

void test_expectEntriesMapPopulated() {
    admSimpleGraph_t *G = CreateGraphFromString(s_minimal, 8);
    admSimpleNode_t *A = GetLabelledNode(G, "A");
    admSimpleNode_t *B = GetLabelledNode(G, "B");
    admSimpleNode_t *C = GetLabelledNode(G, "C");
    admSimpleNode_t *D = GetLabelledNode(G, "D");
    admDFSState_t *state = CreateDFSState(8);
    cciValue_t v;
    AdmGraphDFS(G, A, state, NULL, NULL);

    v = CCI_IGet(state->Entries, (uint64_t)A);
    assert(CCIValue_GETINT(v) == 0);

    v = CCI_IGet(state->Entries, (uint64_t)B);
    assert(CCIValue_GETINT(v) == 1);

    v = CCI_IGet(state->Entries, (uint64_t)D);
    assert(CCIValue_GETINT(v) == 3);

    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

static int numDescendants(admDFSState_t *state, admSimpleNode_t *n) {
    cciValue_t u = CCI_IGet(state->Entries, (uint64_t)n);
    cciValue_t v = CCI_IGet(state->Exits, (uint64_t)n);
    return (CCIValue_GETINT(v) - CCIValue_GETINT(u)) / 2;
}

void test_expectExitsMapPopulated() {
    admSimpleGraph_t *G = CreateGraphFromString(s_minimal, 8);
    admSimpleNode_t *A = GetLabelledNode(G, "A");
    admSimpleNode_t *B = GetLabelledNode(G, "B");
    admSimpleNode_t *C = GetLabelledNode(G, "C");
    admSimpleNode_t *D = GetLabelledNode(G, "D");
    admDFSState_t *state = CreateDFSState(8);
    AdmGraphDFS(G, A, state, NULL, NULL);
    assert(0 == numDescendants(state, D));
    assert(1 == numDescendants(state, C));
    assert(3 == numDescendants(state, A));
    assert(2 == numDescendants(state, B));
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
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

void test_expectTreeEdgesCollected() {
    size_t sz = 16;
    admSimpleGraph_t *G = CreateGraphFromString(s_undirected, 16);
    admSimpleNode_t *A = GetLabelledNode(G, "1");
    admDFSState_t *state = CreateDFSState(16);
    admSimpleEdge_t *e = NULL;
    cciValue_t v;
    AdmGraphDFS(G, A, state, NULL, NULL);
    for (size_t i=0; i<state->TreeEdges->size; i++) {
        v = CCI_AlGet(state->TreeEdges, i);
        e = CCIValue_GETPOINTER(v, admSimpleEdge_t);
        printf("%s->%s; ", AdmNodeLabel(AdmEdgeFrom(e)), AdmNodeLabel(AdmEdgeTo(e)));
    }
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

void test_expectTreeEdgesCollectedRecursiveModel() {
    size_t sz = 16;
    admSimpleGraph_t *G = CreateGraphFromString(s_undirected, 16);
    admSimpleNode_t *A = GetLabelledNode(G, "1");
    admDFSState_t *state = CreateDFSState(16);
    admSimpleEdge_t *e = NULL;
    cciValue_t v;
    AdmGraphRecurDFS(G, A, state, NULL, NULL);
    for (size_t i=0; i<state->TreeEdges->size; i++) {
        v = CCI_AlGet(state->TreeEdges, i);
        e = CCIValue_GETPOINTER(v, admSimpleEdge_t);
        printf("%s->%s; ", AdmNodeLabel(AdmEdgeFrom(e)), AdmNodeLabel(AdmEdgeTo(e)));
    }
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

void test_expectBackEdgesCollected() {
    size_t sz = 16;
    admSimpleGraph_t *G = CreateGraphFromString(s_undirected, sz);
    admSimpleNode_t *A = GetLabelledNode(G, "1");
    admDFSState_t *state = CreateDFSState(sz);
    admSimpleEdge_t *e = NULL;
    cciValue_t v;
    AdmGraphDFS(G, A, state, NULL, NULL);
    for (size_t i=0; i<state->BackEdges->size; i++) {
        v = CCI_AlGet(state->BackEdges, i);
        e = CCIValue_GETPOINTER(v, admSimpleEdge_t);
        printf("%s->%s; ", AdmNodeLabel(AdmEdgeFrom(e)), AdmNodeLabel(AdmEdgeTo(e)));
    }
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
