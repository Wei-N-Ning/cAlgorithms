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

const char *s_dumbGraphCircularDependency = \
"A->B\n"
"B->C\n"
"A->C\n"
"C->A\n"
"C->D\n"
"A->D\n";

void test_expectEdgesVisited() {
    admSimpleGraph_t *G = CreateGraphFromString(s_dumbGraphCircularDependency, 8);
    admSimpleNode_t *start = GetLabelledNode(G, "A");
    admSimpleNode_t *sut = GetLabelledNode(G, "B");
    admDFSState_t *state = CreateDFSState(8);
    AdmGraphDFS(G, start, state, NULL, printConnectionVisitor);
    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

void test_expectDFSTreePopulated() {
    admSimpleGraph_t *G = CreateGraphFromString(s_dumbGraphCircularDependency, 8);
    admSimpleNode_t *start = GetLabelledNode(G, "A");
    admSimpleNode_t *sut = GetLabelledNode(G, "B");
    admDFSState_t *state = CreateDFSState(8);
    cciValue_t v;
    AdmGraphDFS(G, start, state, NULL, NULL);

    v = IGet(state->DFSTree, (uint64_t)start);
    assert(! ISVALID(v));

    v = IGet(state->DFSTree, (uint64_t )GetLabelledNode(G, "B"));
    assert(start == GETPOINTER(v, admSimpleNode_t));

    v = IGet(state->DFSTree, (uint64_t)GetLabelledNode(G, "D"));  // C
    v = IGet(state->DFSTree, GETINT(v));  // B
    assert(sut == GETPOINTER(v, admSimpleNode_t));

    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

void test_expectEntriesMapPopulated() {
    admSimpleGraph_t *G = CreateGraphFromString(s_dumbGraphCircularDependency, 8);
    admSimpleNode_t *start = GetLabelledNode(G, "A");
    admSimpleNode_t *sut = GetLabelledNode(G, "B");
    admDFSState_t *state = CreateDFSState(8);
    cciValue_t v;
    AdmGraphDFS(G, start, state, NULL, NULL);

    v = IGet(state->Entries, (uint64_t)sut);
    assert(1 == GETINT(v));

    v = IGet(state->Entries, (uint64_t)GetLabelledNode(G, "D"));
    assert(3 == GETINT(v));

    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

void test_expectExitsMapPopulated() {
    admSimpleGraph_t *G = CreateGraphFromString(s_dumbGraphCircularDependency, 8);
    admSimpleNode_t *start = GetLabelledNode(G, "A");
    admSimpleNode_t *sut = GetLabelledNode(G, "B");
    admDFSState_t *state = CreateDFSState(8);
    cciValue_t v;
    AdmGraphDFS(G, start, state, NULL, NULL);

    v = IGet(state->Exits, (uint64_t)sut);
    assert(6 == GETINT(v));

    v = IGet(state->Exits, (uint64_t)GetLabelledNode(G, "D"));
    assert(4 == GETINT(v));

    DeleteDFSState(state);
    DeleteAdmSimpleGraph(G);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}