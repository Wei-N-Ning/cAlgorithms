//
// Created by wein on 4/2/18.
//

#include "admSimpleGraph.h"

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include <admReadline.h>
#include <cciValue.h>
#include <cciList.h>
#include <cciHashTable.h>
#include <cciArrayList.h>
#include <cciQueue.h>

struct AdmSimpleNode {
    char label[MAX_LABEL_LENGTH];
    cciArrayList_t *to;
    cciValue_t value;
    uint64_t weight;
    void *preserved;
};

struct AdmSimpleEdge {
    uint64_t weight;
    admSimpleNode_t *from;
    admSimpleNode_t *to;
    void *preserved;
};

admSimpleNode_t *CreateAdmSimpleNode() {
    admSimpleNode_t *n = malloc(sizeof(admSimpleNode_t));
    n->to = AlNew();
    n->value = invalid();
    n->preserved = NULL;
    memset(n->label, 0, MAX_LABEL_LENGTH);
    return n;
}

admSimpleEdge_t *CreateAdmSimpleEdge(admSimpleNode_t *from_, admSimpleNode_t *to_, size_t weight) {
    admSimpleEdge_t *e = malloc(sizeof(admSimpleEdge_t));
    e->weight = weight;
    e->from = from_;
    e->to = to_;
    e->preserved = NULL;
    return e;
}

admSimpleNode_t *AdmEdgeTo(admSimpleEdge_t *e) {
    return e->to;
}

admSimpleNode_t *AdmEdgeFrom(admSimpleEdge_t *e) {
    return e->from;
}

void DeleteAdmSimpleEdge(admSimpleEdge_t *e) {
    free(e);
}

size_t AdmNumToNodes(admSimpleNode_t *n) {
    return n->to->size;
}

admSimpleEdge_t *AdmEdge(admSimpleNode_t *n, size_t idx) {
    cciValue_t v;
    if (idx > n->to->size - 1) {
        return NULL;
    }
    v = AlGet(n->to, idx);
    return GETPOINTER(v, admSimpleEdge_t);
}

admSimpleNode_t *AdmToNode(admSimpleNode_t *n, size_t idx) {
    admSimpleEdge_t *e = AdmEdge(n, idx);
    if (e) {
        return e->to;
    }
    return NULL;
}

int AdmConnectTo(admSimpleNode_t *this, admSimpleNode_t *to_) {
    admSimpleEdge_t *e = CreateAdmSimpleEdge(this, to_, 0);
    AlEmplaceBack(this->to, newPointer(e));
    return 1;
}

const char *AdmNodeLabel(admSimpleNode_t *n) {
    return n->label;
}

void DeleteAdmSimpleNode(admSimpleNode_t *n) {
    size_t sz = n->to->size;
    cciValue_t v;
    admSimpleEdge_t *e = NULL;
    if (n->to) {
        for (size_t i=0; i<sz; ++i) {
            v = AlGet(n->to, i);
            e = GETPOINTER(v, admSimpleEdge_t);
            DeleteAdmSimpleEdge(e);
        }
        AlDelete(n->to);
    }
    free(n);
}

uint64_t *AdmWeightHandle(admSimpleNode_t *n) {
    return &n->weight;
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

admSimpleGraph_t *CreateAdmSimpleGraph(size_t sz) {
    admSimpleGraph_t *G = malloc(sizeof(admSimpleGraph_t));
    G->size = 0;
    G->nodeByLabel = NewHashTable(sz);
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
    n->weight = 0;
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

void AdmGraphBFS(admSimpleGraph_t *G,
                 admSimpleNode_t *n,
                 admNodeVisitor_t nodeVisitor,
                 admConnVisitor_t connVisitor) {
    cciQueue_t *Q =  CreateCCIQueue();
    cciHashTable_t *discovered = NewHashTable(AdmGraphSize(G));
    cciValue_t v;
    admSimpleNode_t *this = NULL;
    admSimpleEdge_t *conn = NULL;
    admSimpleNode_t *connected = NULL;
    size_t nconns = 0;
    Enqueue(Q, newPointer(n));
    while (! CCIQueueEmpty(Q)) {
        v = Dequeue(Q);
        this = GETPOINTER(v, admSimpleNode_t);
        if (nodeVisitor) {
            nodeVisitor(this);
        }
        ISet(discovered, (uint64_t)this, newPointer(this));
        nconns = AdmNumToNodes(this);
        for (size_t i=0; i<nconns; ++i) {
            conn = AdmEdge(this, i);
            connected = AdmEdgeTo(conn);
            if (connVisitor) {
                connVisitor(conn);
            }
            if (ISVALID(IGet(discovered, (uint64_t)connected))) {
                // circular dependency detected
                continue;
            }
            Enqueue(Q, newPointer(connected));
        }
    }
    DeleteCCIQueue(Q);
    DeleteHashTable(discovered);
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

admSimpleGraph_t *CreateGraphFromString(const char *buf, size_t sz) {
    admSimpleGraph_t *G = CreateAdmSimpleGraph((sz ? sz : MAX_GRAPH_SIZE));
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
            AdmConnectTo(this, to_);
        }
        // undirected
        else if (extractLabels(AdmLineAsString(l), "--", label, label + MAX_LABEL_LENGTH, MAX_LABEL_LENGTH - 1)) {
            this = GetOrCreateLabelledNode(G, label);
            to_ = GetOrCreateLabelledNode(G, label + MAX_LABEL_LENGTH);
            AdmConnectTo(this, to_);
            AdmConnectTo(to_, this);
        }
    }
    AdmDeleteLine(l);
    return G;
}

