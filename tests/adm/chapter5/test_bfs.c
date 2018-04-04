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
    ;
}
void test_minimalBFS() {
    admSimpleGraph_t *G = CreateGraphFromString(s_dumbGraph);
    admSimpleNode_t *start = GetLabelledNode(G, "C");
    AdmGraphBFS(start, addWeightVisitor);
    DeleteAdmSimpleGraph(G);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
