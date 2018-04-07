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
    assert(0 == GETINT(IGet(state->Entries, (uint64_t)A)));
//    assert(1 == GETINT(IGet(state->Exits, (uint64_t)A)));
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
//    assert(0 == GETINT(IGet(state->Entries, (uint64_t)A)));
//    assert(1 == GETINT(IGet(state->Entries, (uint64_t)B)));
//    assert(2 == GETINT(IGet(state->Exits, (uint64_t)B)));
//    assert(3 == GETINT(IGet(state->Exits, (uint64_t)A)));
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

void xtest_minimalDFSExpectNodesVisited() {
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


void xtest_expectEdgesVisited() {
    admSimpleGraph_t *G = CreateGraphFromString(s_minimal, 8);
    admSimpleNode_t *start = GetLabelledNode(G, "A");
    admDFSState_t *state = CreateDFSState(8);
    AdmGraphDFS(G, start, state, NULL, printConnectionVisitor);
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

void xtest_expectDFSTreePopulated() {
    admSimpleGraph_t *G = CreateGraphFromString(s_minimal, 8);
    admSimpleNode_t *A = GetLabelledNode(G, "A");
    admSimpleNode_t *B = GetLabelledNode(G, "B");
    admSimpleNode_t *C = GetLabelledNode(G, "C");
    admSimpleNode_t *D = GetLabelledNode(G, "D");
    admDFSState_t *state = CreateDFSState(8);
    cciValue_t v;
    AdmGraphDFS(G, A, state, NULL, NULL);

    v = IGet(state->DFSTree, (uint64_t)A);
    assert(! ISVALID(v));

    v = IGet(state->DFSTree, (uint64_t )B);
    assert(A == GETPOINTER(v, admSimpleNode_t));

    v = IGet(state->DFSTree, (uint64_t )C);
    assert(B == GETPOINTER(v, admSimpleNode_t));

    v = IGet(state->DFSTree, (uint64_t )D);
    assert(C == GETPOINTER(v, admSimpleNode_t));

    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

void xtest_expectEntriesMapPopulated() {
    admSimpleGraph_t *G = CreateGraphFromString(s_minimal, 8);
    admSimpleNode_t *A = GetLabelledNode(G, "A");
    admSimpleNode_t *B = GetLabelledNode(G, "B");
    admSimpleNode_t *C = GetLabelledNode(G, "C");
    admSimpleNode_t *D = GetLabelledNode(G, "D");
    admDFSState_t *state = CreateDFSState(8);
    cciValue_t v;
    AdmGraphDFS(G, A, state, NULL, NULL);

    v = IGet(state->Entries, (uint64_t)A);
    assert(GETINT(v) == 0);

    v = IGet(state->Entries, (uint64_t)B);
    assert(GETINT(v) == 3);

    v = IGet(state->Entries, (uint64_t)D);
    assert(GETINT(v) == 6);

    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

static int numDescendants(admDFSState_t *state, admSimpleNode_t *n) {
    cciValue_t u = IGet(state->Entries, (uint64_t)n);
    cciValue_t v = IGet(state->Exits, (uint64_t)n);
    return (GETINT(v) - GETINT(u)) / 2;
}

void xtest_expectExitsMapPopulated() {
    admSimpleGraph_t *G = CreateGraphFromString(s_minimal, 8);
    admSimpleNode_t *A = GetLabelledNode(G, "A");
    admSimpleNode_t *B = GetLabelledNode(G, "B");
    admSimpleNode_t *C = GetLabelledNode(G, "C");
    admSimpleNode_t *D = GetLabelledNode(G, "D");
    admDFSState_t *state = CreateDFSState(8);
    AdmGraphDFS(G, A, state, NULL, NULL);
    assert(1 == numDescendants(state, D));
    assert(2 == numDescendants(state, C));
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
