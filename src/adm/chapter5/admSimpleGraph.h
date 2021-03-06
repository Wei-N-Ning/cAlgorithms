//
// Created by wein on 4/2/18.
//

#ifndef CCISOLUTIONSC_ADMSIMPLEGRAPH_H
#define CCISOLUTIONSC_ADMSIMPLEGRAPH_H

#include <stddef.h>
#include <stdint.h>

#include <cci/cciHashTable.h>
#include <cci/cciArrayList.h>

#define MAX_LABEL_LENGTH 16

struct AdmSimpleNode;
typedef struct AdmSimpleNode admSimpleNode_t;

struct AdmSimpleEdge;
typedef struct AdmSimpleEdge admSimpleEdge_t ;

admSimpleNode_t *AdmEdgeTo(admSimpleEdge_t *e);
admSimpleNode_t *AdmEdgeFrom(admSimpleEdge_t *e);

struct AdmSimpleGraph;
typedef struct AdmSimpleGraph admSimpleGraph_t;

admSimpleNode_t *CreateAdmSimpleNode();
size_t AdmNumToNodes(admSimpleNode_t *n);
admSimpleNode_t *AdmToNode(admSimpleNode_t *n, size_t idx);
admSimpleEdge_t *AdmEdge(admSimpleNode_t *n, size_t idx);
int AdmConnectTo(admSimpleNode_t *this, admSimpleNode_t *to_);
const char *AdmNodeLabel(admSimpleNode_t *n);
void DeleteAdmSimpleNode(admSimpleNode_t *n);
uint64_t *AdmWeightHandle(admSimpleNode_t *n);

size_t AdmSNDegree(admSimpleNode_t *n);

//////////////////////////////////////////////

admSimpleGraph_t *CreateAdmSimpleGraph(size_t capacity);
admSimpleNode_t *GetOrCreateNode(admSimpleGraph_t *G, uint64_t k);
admSimpleNode_t *GetOrCreateLabelledNode(admSimpleGraph_t *G, const char *label);
admSimpleNode_t *GetAdmNode(admSimpleGraph_t *G, uint64_t k);
admSimpleNode_t *GetLabelledNode(admSimpleGraph_t *G, const char *label);
void DeleteAdmSimpleGraph(admSimpleGraph_t *G);
size_t AdmGraphSize(admSimpleGraph_t *G);

void AdmGraphIter(admSimpleGraph_t *G, void *callback);

void AdmGetNodes(admSimpleGraph_t *G, cciArrayList_t *o_nodes);

//////////////// traversal ///////////////////

typedef void (*admNodeVisitor_t)(admSimpleNode_t *n);
typedef void (*admConnVisitor_t)(admSimpleEdge_t *e);
// BFSTree:
// optional;
// to record the shortest path from n to every other node
// in the tree
//
// nodeVisitor:
// optional;
// a visitor function that is called for every node visited;
// use NULL if not interested
//
// connVisitor:
// optional;
// a visitor function that is called for every edge visited;
// use NULL if not interested
void AdmGraphBFS(admSimpleGraph_t *G,
                 admSimpleNode_t *n,
                 cciHashTable_t *BFSTree,
                 admNodeVisitor_t nodeVisitor,
                 admConnVisitor_t connVisitor);

struct AdmDFSState {
    cciHashTable_t *DFSTree;
    cciHashTable_t *Entries;
    cciHashTable_t *Exits;
    cciArrayList_t *TreeNodes;
    cciArrayList_t *TreeEdges;
    cciArrayList_t *BackEdges;
    cciArrayList_t *StrongComponents;  // array of arrays
    size_t time;
};

typedef struct AdmDFSState admDFSState_t;

typedef void (*admNodeDFSVisitor_t)(admSimpleNode_t *n, admDFSState_t *state);

typedef void (*admConnDFSVisitor_t)(admSimpleEdge_t *e, admDFSState_t *state);

admDFSState_t *CreateDFSState(size_t sz);

void DeleteDFSState(admDFSState_t *state);

void AdmGraphDFS(admSimpleGraph_t *G,
                 admSimpleNode_t *start,
                 admDFSState_t *state,
                 admNodeDFSVisitor_t nodeVisitor,
                 admConnDFSVisitor_t connVisitor);

void AdmGraphRecurDFS(admSimpleGraph_t *G,
                      admSimpleNode_t *start,
                      admDFSState_t *state,
                      admNodeDFSVisitor_t nodeVisitor,
                      admConnDFSVisitor_t connVisitor);

int AdmTopoSort(admSimpleGraph_t *G, admSimpleNode_t *start, cciArrayList_t *o_nodes);

//////////////// utilities ///////////////////

admSimpleGraph_t *CreateGraphFromString(const char *str, size_t sz);

admSimpleGraph_t *CreateProceduralGraph(size_t size, admSimpleNode_t **start);

#endif //CCISOLUTIONSC_ADMSIMPLEGRAPH_H
