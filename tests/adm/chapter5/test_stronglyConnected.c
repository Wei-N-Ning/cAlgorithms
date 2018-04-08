//
// Created by wein on 4/8/18.
//

#include <admSimpleGraph.h>

void RunTinyTests();

static const char *s_components =\
"1->2\n"
"2->3\n"
"2->4\n"
"2->5\n"
"3->1\n"
"4->1\n"
"4->8\n"
"4->6\n"
"5->6\n"
"6->7\n"
"7->5\n"
"8->6\n"
;

void test_getComponents() {
    size_t sz = 16;
    admSimpleGraph_t *G = CreateGraphFromString(s_components, sz);

    DeleteAdmSimpleGraph(G);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
