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
#include <cciArrayList.h>

struct AdmSimpleNode {
    char label[MAX_LABEL_LENGTH];
    cciArrayList_t *to;
    cciValue_t value;
    uint64_t weight;
};

admSimpleNode_t *CreateAdmSimpleNode() {
    admSimpleNode_t *n = malloc(sizeof(admSimpleNode_t));
    n->to = AlNew();
    n->value = invalid();
    memset(n->label, 0, MAX_LABEL_LENGTH);
    return n;
}

size_t AdmNumToNodes(admSimpleNode_t *n) {
    return n->to->size;
}

admSimpleNode_t *AdmToNode(admSimpleNode_t *n, size_t idx) {
    if (idx > n->to->size - 1) {
        return NULL;
    }
    return GETPOINTER(AlGet(n->to, idx), admSimpleNode_t);
}

int AdmConnectTo(admSimpleNode_t *this, admSimpleNode_t *to_) {
    AlEmplaceBack(this->to, newPointer(to_));
    return 1;
}

const char *AdmNodeLabel(admSimpleNode_t *n) {
    return n->label;
}

void DeleteAdmSimpleNode(admSimpleNode_t *n) {
    if (n->to) {
        AlDelete(n->to);
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

admSimpleNode_t *GetOrCreateNode(admSimpleGraph_t *G, uint64_t k) {
    admSimpleNode_t *n = GETPOINTER(IGet(G->nodeByLabel, k), admSimpleNode_t);
    if (n) {
        return n;
    }
    if (G->size >= MAX_GRAPH_SIZE) {
        return NULL;
    }
    n = CreateAdmSimpleNode();
    n->weight = k;
    SSet(G->nodeByLabel, n->label, newPointer(n));
    G->size += 1;
    return n;
}

admSimpleNode_t * GetOrCreateLabelledNode(admSimpleGraph_t *G, const char *label) {
    admSimpleNode_t *n = GETPOINTER(SGet(G->nodeByLabel, label), admSimpleNode_t);
    if (n) {
        return n;
    }
    if (G->size >= MAX_GRAPH_SIZE) {
        return NULL;
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

admSimpleNode_t *GetAdmNode(admSimpleGraph_t *G, uint64_t k) {
    return GETPOINTER(IGet(G->nodeByLabel, k), admSimpleNode_t);
}

admSimpleNode_t *GetLabelledNode(admSimpleGraph_t *G, const char *label) {
    return GETPOINTER(SGet(G->nodeByLabel, label), admSimpleNode_t);
}

size_t AdmGraphSize(admSimpleGraph_t *G) {
    return G->size;
}

void AdmGraphIter(admSimpleGraph_t *G, void *callback) {
    callback_t cb = (callback_t)callback;
    Iterate(G->nodeByLabel, cb);
}

void DeleteAdmSimpleGraph(admSimpleGraph_t *G) {
    if (G->nodeByLabel) {
        Iterate(G->nodeByLabel, killerVisitor);
        DeleteHashTable(G->nodeByLabel);
    }
    free(G);
}

///////////////////////////////////////////////

static int extractLabels(const char *str, const char *token, char *o_first, char *o_second, int size) {
    const char *splitter = strstr(str, token);
    size_t firstLen = 0, secondLen = 0, sutLen = strlen(str), tokenLen = strlen(token);
    if (! (splitter && (firstLen = splitter - str) > 0)) {
        return 0;
    }
    secondLen = (sutLen - tokenLen > firstLen) ? sutLen - tokenLen - firstLen : 0;
    if (! secondLen) {
        return 0;
    }
    memcpy(o_first, str, (firstLen > size) ? size : firstLen);
    memcpy(o_second, splitter + tokenLen, (secondLen > size) ? size : secondLen);
    return 1;
}

admSimpleGraph_t *CreateGraphFromString(const char *buf) {
    admSimpleGraph_t *G = CreateAdmSimpleGraph();
    struct AdmLine *l = AdmCreateStringReader();
    char label[MAX_LABEL_LENGTH * 2];
    admSimpleNode_t *this = NULL;
    admSimpleNode_t *to_ = NULL;
    for (int i=0; AdmReadLine(buf, l); ++i) {
        memset(label, 0, MAX_LABEL_LENGTH * 2);
        // directed
        if (extractLabels(AdmLineAsString(l), "->", label, label + MAX_LABEL_LENGTH, MAX_LABEL_LENGTH - 1)) {
            this = GetOrCreateLabelledNode(G, label);
            to_ = GetOrCreateLabelledNode(G, label + MAX_LABEL_LENGTH);
            AlEmplaceBack(this->to, newPointer(to_));
        }
        // undirected
        else if (extractLabels(AdmLineAsString(l), "--", label, label + MAX_LABEL_LENGTH, MAX_LABEL_LENGTH - 1)) {
            this = GetOrCreateLabelledNode(G, label);
            to_ = GetOrCreateLabelledNode(G, label + MAX_LABEL_LENGTH);
            AlEmplaceBack(this->to, newPointer(to_));
            AlEmplaceBack(to_->to, newPointer(this));
        }
    }
    AdmDeleteLine(l);
    return G;
}


