//
// Created by wein on 4/2/18.
//

#include "admSimpleGraph.h"

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include <admToStr.h>
#include <admReadline.h>
#include <cci/cciValue.h>
#include <cci/cciList.h>
#include <cci/cciHashTable.h>
#include <cci/cciArrayList.h>
#include <cci/cciQueue.h>
#include <cci/cciStack.h>

struct AdmSimpleNode {
    char label[MAX_LABEL_LENGTH];
    cciArrayList_t *to;
    cciValue_t value;
    uint64_t weight;
    int componentId;
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
    n->to = CCI_AlNew();
    n->value = CCIValue_invalid();
    n->preserved = NULL;
    n->componentId = -1;
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
    v = CCI_AlGet(n->to, idx);
    return CCIValue_GETPOINTER(v, admSimpleEdge_t);
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
    CCI_AlEmplaceBack(this->to, CCIValue_newPointer(e));
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
            v = CCI_AlGet(n->to, i);
            e = CCIValue_GETPOINTER(v, admSimpleEdge_t);
            DeleteAdmSimpleEdge(e);
        }
        CCI_AlDelete(n->to);
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
    size_t capacity;
};

static void killerVisitor(size_t index, size_t slotPos, cciValue_t *k, cciValue_t *v) {
    admSimpleNode_t *n = CCIValue_GETPOINTER((*v), admSimpleNode_t);
    if (n) {
        DeleteAdmSimpleNode(n);
    }
}

admSimpleGraph_t *CreateAdmSimpleGraph(size_t capacity) {
    admSimpleGraph_t *G = malloc(sizeof(admSimpleGraph_t));
    G->size = 0;
    G->nodeByLabel = CCI_NewHashTable(capacity);
    return G;
}

admSimpleNode_t *GetOrCreateNode(admSimpleGraph_t *G, uint64_t k) {
    admSimpleNode_t *n = CCIValue_GETPOINTER(CCI_IGet(G->nodeByLabel, k), admSimpleNode_t);
    if (n) {
        return n;
    }
    n = CreateAdmSimpleNode();
    n->weight = k;
    CCI_SSet(G->nodeByLabel, n->label, CCIValue_newPointer(n));
    G->size += 1;
    return n;
}

admSimpleNode_t * GetOrCreateLabelledNode(admSimpleGraph_t *G, const char *label) {
    admSimpleNode_t *n = CCIValue_GETPOINTER(CCI_SGet(G->nodeByLabel, label), admSimpleNode_t);
    if (n) {
        return n;
    }
    n = CreateAdmSimpleNode();
    size_t sz = strlen(label);
    if (sz > MAX_LABEL_LENGTH - 1) {
        sz = MAX_LABEL_LENGTH - 1;
    }
    memcpy(n->label, label, sz);
    n->weight = 0;
    CCI_SSet(G->nodeByLabel, n->label, CCIValue_newPointer(n));
    G->size += 1;
    return n;
}

admSimpleNode_t *GetAdmNode(admSimpleGraph_t *G, uint64_t k) {
    return CCIValue_GETPOINTER(CCI_IGet(G->nodeByLabel, k), admSimpleNode_t);
}

admSimpleNode_t *GetLabelledNode(admSimpleGraph_t *G, const char *label) {
    return CCIValue_GETPOINTER(CCI_SGet(G->nodeByLabel, label), admSimpleNode_t);
}

size_t AdmGraphSize(admSimpleGraph_t *G) {
    return G->size;
}

void AdmGraphIter(admSimpleGraph_t *G, void *callback) {
    cci_ht_callback_t cb = (cci_ht_callback_t)callback;
    CCI_HTIterate(G->nodeByLabel, cb);
}

void AdmGetNodes(admSimpleGraph_t *G, cciArrayList_t *o_nodes) {
    CCI_HTGetValues(G->nodeByLabel, o_nodes);
}

void DeleteAdmSimpleGraph(admSimpleGraph_t *G) {
    if (G->nodeByLabel) {
        CCI_HTIterate(G->nodeByLabel, killerVisitor);
        CCI_DeleteHashTable(G->nodeByLabel);
    }
    free(G);
}

///////////////////////////////////////////////

void AdmGraphBFS(admSimpleGraph_t *G,
                 admSimpleNode_t *n,
                 cciHashTable_t *BFSTree,
                 admNodeVisitor_t nodeVisitor,
                 admConnVisitor_t connVisitor) {
    cciQueue_t *Q =  CCI_CreateQueue();
    cciHashTable_t *discovered = CCI_NewHashTable(AdmGraphSize(G));
    cciValue_t v;
    admSimpleNode_t *this = NULL;
    admSimpleEdge_t *conn = NULL;
    admSimpleNode_t *connected = NULL;
    size_t nconns = 0;
    CCI_Enqueue(Q, CCIValue_newPointer(n));
    CCI_ISet(discovered, (uint64_t)n, CCIValue_newPointer(n));
    if (BFSTree) {
        CCI_ISet(BFSTree, (uint64_t)n, CCIValue_invalid());
    }
    while (! CCI_QueueEmpty(Q)) {
        v = CCI_Dequeue(Q);
        this = CCIValue_GETPOINTER(v, admSimpleNode_t);
        if (nodeVisitor) {
            nodeVisitor(this);
        }
        nconns = AdmNumToNodes(this);
        for (size_t i=0; i<nconns; ++i) {
            conn = AdmEdge(this, i);
            connected = AdmEdgeTo(conn);
            if (CCIValue_ISVALID(CCI_IGet(discovered, (uint64_t)connected))) {
                // circular dependency detected
                continue;
            } else {
                CCI_ISet(discovered, (uint64_t)connected, CCIValue_newInt(1));
            }
            if (connVisitor) {
                connVisitor(conn);
            }
            CCI_Enqueue(Q, CCIValue_newPointer(connected));
            if (BFSTree) {
                CCI_ISet(BFSTree, (uint64_t)connected, CCIValue_newPointer(this));
            }
        }
    }
    CCI_DeleteQueue(Q);
    CCI_DeleteHashTable(discovered);
}

admDFSState_t *CreateDFSState(size_t sz) {
    admDFSState_t *state = malloc(sizeof(admDFSState_t));
    state->DFSTree = CCI_NewHashTable(sz);
    state->Entries = CCI_NewHashTable(sz);
    state->Exits = CCI_NewHashTable(sz);
    state->TreeNodes = CCI_AlNew();
    state->TreeEdges = CCI_AlNew();
    state->BackEdges = CCI_AlNew();
    state->StrongComponents = CCI_AlNew();
    state->time = 0;
    return state;
}

void DeleteDFSState(admDFSState_t *state) {
    cciValue_t v;
    cciArrayList_t *arr = NULL;
    CCI_DeleteHashTable(state->DFSTree);
    CCI_DeleteHashTable(state->Entries);
    CCI_DeleteHashTable(state->Exits);
    CCI_AlDelete(state->TreeNodes);
    CCI_AlDelete(state->TreeEdges);
    CCI_AlDelete(state->BackEdges);
    for (size_t i=state->StrongComponents->size; i--; ) {
        v = CCI_AlGet(state->StrongComponents, i);
        arr = CCIValue_GETPOINTER(v, cciArrayList_t);
        CCI_AlDelete(arr);
    }
    CCI_AlDelete(state->StrongComponents);
    free(state);
}

static int isBackEdge(cciHashTable_t *Entries, admSimpleEdge_t *e) {
    cciValue_t tFrom = CCI_IGet(Entries, (uint64_t)(e->from));
    cciValue_t tTo = CCI_IGet(Entries, (uint64_t)(e->to));
    return (CCIValue_GETINT(tFrom) > (CCIValue_GETINT(tTo))) ? 1: 0;
}

void AdmGraphDFS(admSimpleGraph_t *G,
                 admSimpleNode_t *start,
                 admDFSState_t *state,
                 admNodeDFSVisitor_t nodeVisitor,
                 admConnDFSVisitor_t connVisitor) {
    admSimpleNode_t *this = NULL;
    admSimpleEdge_t *conn = NULL;
    admSimpleEdge_t tmp;
    cciValue_t u, v;
    cciValue_t *p;
    cciArrayList_t *earlyStack = CCI_AlNew();
    cciArrayList_t *lateStack = CCI_AlNew();
    cciArrayList_t *nonTreeEdges = CCI_AlNew();

    tmp.from = NULL;
    tmp.to = start;
    CCI_AlEmplaceBack(earlyStack, CCIValue_newPointer(&tmp));

    while (earlyStack->size) {
        conn = CCIValue_GETPOINTER(CCI_AlPopBack(earlyStack), admSimpleEdge_t);
        this = conn->to;

        // "has it been discovered" test
        p = CCI_IGetOrCreate(state->Entries, (uint64_t)this);
        if (CCIValue_ISVALID((*p))) {
            if (conn->from) {
                CCI_AlEmplaceBack(nonTreeEdges, CCIValue_newPointer(conn));
            }
            continue;
        }
        CCIValue_SETINT((*p), state->time++);

        // processing (for node, it's equivalent to process_vertex_early() in ADM)
        if (nodeVisitor) {
            nodeVisitor(this, state);
        }
        CCI_AlEmplaceBack(state->TreeNodes, CCIValue_newPointer(this));
        if (connVisitor && conn->from) {
            connVisitor(conn, state);
        }

        // tree edges discover new node
        if (conn->from) {
            CCI_AlEmplaceBack(state->TreeEdges, CCIValue_newPointer(conn));
        }

        // store nodes in another stack to be re-processed in a reverse order
        CCI_AlEmplaceBack(lateStack, CCIValue_newPointer(this));
        if (conn->from) {
            CCI_ISet(state->DFSTree, (uint64_t)conn->to, CCIValue_newPointer(conn->from));
        }

        // create new "stack frames"
        for (size_t i=AdmNumToNodes(this); i--; ) {
            conn = AdmEdge(this, i);
            CCI_AlEmplaceBack(earlyStack, CCIValue_newPointer(conn));
        }
    }

    // back edges
    for (size_t i=0; i<nonTreeEdges->size; ++i) {
        u = CCI_AlGet(nonTreeEdges, i);
        conn = CCIValue_GETPOINTER(u, admSimpleEdge_t);
        if (isBackEdge(state->Entries, conn)) {
            CCI_AlEmplaceBack(state->BackEdges, u);
        }
    }

    // it is equivalent to process_vertex_late() in ADM
    for (size_t i=lateStack->size; i-- ; ) {
        this = CCIValue_GETPOINTER(CCI_AlGet(lateStack, i), admSimpleNode_t);
        CCI_ISet(state->Exits, (uint64_t)this, CCIValue_newInt(state->time++));
    }
    CCI_AlDelete(nonTreeEdges);
    CCI_AlDelete(lateStack);
    CCI_AlDelete(earlyStack);
}

void AdmGraphRecurDFS(admSimpleGraph_t *G,
                      admSimpleNode_t *start,
                      admDFSState_t *state,
                      admNodeDFSVisitor_t nodeVisitor,
                      admConnDFSVisitor_t connVisitor) {
    size_t nconns = AdmNumToNodes(start);
    admSimpleNode_t *connected = NULL;
    admSimpleEdge_t *conn = NULL;
    CCI_ISet(state->Entries, (uint64_t)start, CCIValue_newInt(state->time++));
    if (nodeVisitor) {
        nodeVisitor(start, state);
    }
    CCI_AlEmplaceBack(state->TreeNodes, CCIValue_newPointer(start));
    for (size_t i=0; i<nconns; ++i) {
        conn = AdmEdge(start, i);
        connected = AdmEdgeTo(conn);
        if (CCIValue_ISVALID(CCI_IGet(state->Entries, (uint64_t)connected))) {
            // circular dependency detected

            if (CCIValue_GETINT(CCI_IGet(state->Entries, (uint64_t)(conn->from))) > \
                CCIValue_GETINT(CCI_IGet(state->Entries, (uint64_t)(conn->to)))) {
                CCI_AlEmplaceBack(state->BackEdges, CCIValue_newPointer(conn));
            }
            continue;
        }
        if (connVisitor) {
            connVisitor(conn, state);
        }
        CCI_AlEmplaceBack(state->TreeEdges, CCIValue_newPointer(conn));
        CCI_ISet(state->DFSTree, (uint64_t)connected, CCIValue_newPointer(start));
        AdmGraphRecurDFS(G, connected, state, nodeVisitor, connVisitor);
    }
    CCI_ISet(state->Exits, (uint64_t)start, CCIValue_newInt(state->time++));
}


int AdmTopoSort(admSimpleGraph_t *G, admSimpleNode_t *start, cciArrayList_t *o_nodes) {
    admDFSState_t *state = CreateDFSState(AdmGraphSize(G));
    int ok = 0;
    AdmGraphDFS(G, start, state, NULL, NULL);
    if (0 == state->BackEdges->size) {
        ok = 1;
        if (o_nodes) {
            for (size_t i=0; i<state->TreeNodes->size; ++i) {
                CCI_AlEmplaceBack(o_nodes, CCI_AlGet(state->TreeNodes, i));
            }
        }
    }
    DeleteDFSState(state);
    return ok;
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
    admSimpleGraph_t *G = CreateAdmSimpleGraph(sz);
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

admSimpleGraph_t *CreateProceduralGraph(size_t size, admSimpleNode_t **start) {
    size_t nbuf = 32;
    admSimpleGraph_t *G = CreateAdmSimpleGraph(size);
    admSimpleNode_t *n = NULL;
    admSimpleNode_t **arr = malloc(size * sizeof(admSimpleNode_t *));
    char buf[32];
    memset(buf, 0, nbuf);
    for (uint64_t i=0; i<size; ++i) {
        BytesToUniqueString(i * 2 + 1, buf, nbuf);
        n = GetOrCreateLabelledNode(G, buf);
        arr[i] = n;
    }
    for (size_t i=0; i<size; ++i) {
        n = arr[i];
        for (size_t idx = 0; idx<size; idx = idx * 2 + 1) {
            AdmConnectTo(n, arr[(idx + 1 + i) % size]);
        }
    }
    (*start) = arr[0];
    free(arr);
    return G;
}
