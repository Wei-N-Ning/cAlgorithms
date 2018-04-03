//
// Created by wein on 4/3/18.
//

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <admReadline.h>

void RunTinyTests();

// no space is allowed
// try write out a line that is longer than 60 chars (including \n),
// the assert statement will fail
const char *SUT =\
"A->B\n"
"A->Z\n"
"B->D,D->F\n"
"C->E,E->M\n";

void test_readStringExpectLineData() {
    struct AdmLine *l = AdmCreateStringReader();
    for (int i=0; AdmReadLine(SUT, l); ++i) {
        if (i == 0) {
            assert(0 == strcmp(AdmLineAsString(l), "A->B"));
        } else if (i == 2) {
            assert(0 == strcmp(AdmLineAsString(l), "B->D,D->F"));
        }
    }
    AdmDeleteLine(l);
}

struct MockLabel {
    char first;
    char second;
};

void test_interpretLineAsLabel() {
    const char *str = NULL;
    struct MockLabel lb;
    struct AdmLine *l = AdmCreateStringReader();
    for (int i=0; AdmReadLine(SUT, l); ++i) {
        str = AdmLineAsString(l);
        assert(sscanf(str, "%c->%c", &lb.first, &lb.second));
        if (i == 0) {
            assert('A' == lb.first && 'B' == lb.second);
        } else if (i == 2) {
            assert('B' == lb.first && 'D' == lb.second);
        }
    }
    AdmDeleteLine(l);
}

struct MockNode {
    char label;
    struct MockNode *to_;
    struct MockNode *from_;
};

typedef struct MockNode mockNode_t;

mockNode_t *CreateMockNode(const char lb, mockNode_t *to_, mockNode_t *from_) {
    mockNode_t *n = malloc(sizeof(mockNode_t));
    n->label = lb;
    n->from_ = from_;
    n->to_ = to_;
    return n;
}

void DeleteMockNode(mockNode_t *n) {
    free(n);
}

void test_interpretLineAsNodes() {
    char fromLabel = 0;
    char toLabel = 0;
    const char *str = NULL;
    mockNode_t *fromNode = NULL;
    mockNode_t *toNode = NULL;
    mockNode_t *tmp = NULL;
    mockNode_t *nodeByLabel[0x7F];
    memset(nodeByLabel, 0, sizeof(mockNode_t *) * 0x7F);
    struct AdmLine *l = AdmCreateStringReader();
    for (int i=0; AdmReadLine(SUT, l); ++i) {
        str = AdmLineAsString(l);
        if (sscanf(str, "%c->%c", &fromLabel, &toLabel) == 2) {
            fromNode = nodeByLabel[fromLabel % 0x7F];
            if (! fromNode) {
                fromNode = CreateMockNode(fromLabel, NULL, NULL);
                nodeByLabel[fromLabel % 0x7F] = fromNode;
            }
            toNode = nodeByLabel[toLabel % 0x7F];
            if (! toNode) {
                toNode = CreateMockNode(toLabel, NULL, fromNode);
                nodeByLabel[toLabel % 0x7F] = toNode;
            }
            fromNode->to_ = toNode;
        }
    }
    tmp = nodeByLabel['Z' % 0x7F];
    assert('Z' == tmp->label);
    assert('A' == tmp->from_->label);
    tmp = nodeByLabel['C' % 0x7F];
    assert('C' == tmp->label);
    assert('E' == tmp->to_->label);
    for (int i=0; i<0x7F; ++i) {
        if (nodeByLabel[i]) {
            DeleteMockNode(nodeByLabel[i]);
        }
    }
    AdmDeleteLine(l);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}

