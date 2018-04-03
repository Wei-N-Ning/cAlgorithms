//
// Created by wein on 4/2/18.
//

#include "admSimpleGraph.h"

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include <cciValue.h>
#include <cciList.h>
#include <cciArrayList.h>

struct AdmSimpleNode {
    char label[MAX_LABEL_LENGTH];
    cciList_t *to;
    cciValue_t value;
    int weight;
};

admSimpleNode_t *CreateAdmSimpleNode() {
    admSimpleNode_t *n = malloc(sizeof(admSimpleNode_t));
    n->to = NewList();
    n->value = invalid();
    return n;
}

void DeleteAdmSimpleNode(admSimpleNode_t *n) {
    if (n->to) {
        DeleteList(n->to);
    }
    free(n);
}

size_t AdmSNDegree(admSimpleNode_t *n) {
    return n->to->size;
}

///////////////////////////////////////////////

struct AdmSimpleGraph {
    cciArrayList_t *nodes;
};

admSimpleGraph_t *CreateAdmSimpleGraph() {
    admSimpleGraph_t *G = malloc(sizeof(admSimpleGraph_t));
    G->nodes = AlNew();
    return G;
}

void DeleteAdmSimpleGraph(admSimpleGraph_t *G) {
    if (G->nodes) {
        AlDelete(G->nodes);
    }
    free(G);
}

///////////////////////////////////////////////
