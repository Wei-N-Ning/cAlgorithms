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
#include <cciHashTable.h>
#include <admReadline.h>

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
    memset(n->label, 0, MAX_LABEL_LENGTH);
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
    cciHashTable_t *nodeByLabel;
    size_t size;
};

static void killerVisitor(size_t index, size_t slotPos, cciValue_t *k, cciValue_t *v) {
    admSimpleNode_t *n = GETPOINTER((*v), admSimpleNode_t);
    if (n) {
        DeleteAdmSimpleNode(n);
    }
}

admSimpleGraph_t *CreateAdmSimpleGraph() {
    admSimpleGraph_t *G = malloc(sizeof(admSimpleGraph_t));
    G->size = 0;
    G->nodeByLabel = NewHashTable(MAX_GRAPH_SIZE);
    return G;
}

admSimpleNode_t * GetOrCreateAdmNode(admSimpleGraph_t *G, const char *label) {
    admSimpleNode_t *n = NULL;
    n = GETPOINTER(SGet(G->nodeByLabel, label), admSimpleNode_t);
    if (n) {
        return n;
    }
    n = CreateAdmSimpleNode();
    size_t sz = strlen(label);
    if (sz > MAX_LABEL_LENGTH - 1) {
        sz = MAX_LABEL_LENGTH - 1;
    }
    memcpy(n->label, label, sz);
    SSet(G->nodeByLabel, n->label, newPointer(n));
    G->size += 1;
    return n;
}

size_t AdmGraphSize(admSimpleGraph_t *G) {
    return G->size;
}

void DeleteAdmSimpleGraph(admSimpleGraph_t *G) {
    if (G->nodeByLabel) {
        Iterate(G->nodeByLabel, killerVisitor);
        DeleteHashTable(G->nodeByLabel);
    }
    free(G);
}

///////////////////////////////////////////////

admSimpleGraph_t *CreateGraphFromString(const char *buf) {
    admSimpleGraph_t *G = CreateAdmSimpleGraph();
    struct AdmLine *l = AdmCreateStringReader();
    const char *line = NULL;
    admSimpleNode_t *this = NULL;
    admSimpleNode_t *to_ = NULL;
    char *labels[2] = {NULL, NULL};
    for (int i=0; AdmReadLine(buf, l); ++i) {
        line = AdmLineAsString(l);
    }
    AdmDeleteLine(l);
    return G;
}
