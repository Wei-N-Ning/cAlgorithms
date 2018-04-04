//
// Created by wein on 4/2/18.
//

#ifndef CCISOLUTIONSC_ADMSIMPLEGRAPH_H
#define CCISOLUTIONSC_ADMSIMPLEGRAPH_H

#include <stddef.h>
#include <stdint.h>

#define MAX_LABEL_LENGTH 16
#define MAX_GRAPH_SIZE 4096

struct AdmSimpleNode;
typedef struct AdmSimpleNode admSimpleNode_t;

struct AdmSimpleGraph;
typedef struct AdmSimpleGraph admSimpleGraph_t;

admSimpleNode_t *CreateAdmSimpleNode();
size_t AdmNumToNodes(admSimpleNode_t *n);
admSimpleNode_t *AdmToNode(admSimpleNode_t *n, size_t idx);
int AdmConnectTo(admSimpleNode_t *this, admSimpleNode_t *to_);
const char *AdmNodeLabel(admSimpleNode_t *n);
void DeleteAdmSimpleNode(admSimpleNode_t *n);

size_t AdmSNDegree(admSimpleNode_t *n);

//////////////////////////////////////////////

admSimpleGraph_t *CreateAdmSimpleGraph();
admSimpleNode_t *GetOrCreateNode(admSimpleGraph_t *G, uint64_t k);
admSimpleNode_t *GetOrCreateLabelledNode(admSimpleGraph_t *G, const char *label);
admSimpleNode_t *GetAdmNode(admSimpleGraph_t *G, uint64_t k);
admSimpleNode_t *GetLabelledNode(admSimpleGraph_t *G, const char *label);
void DeleteAdmSimpleGraph(admSimpleGraph_t *G);
size_t AdmGraphSize(admSimpleGraph_t *G);

void AdmGraphIter(admSimpleGraph_t *G, void *callback);

//////////////// traversal ///////////////////

typedef void (*admNodeVisitor_t)(admSimpleNode_t *n);
void AdmGraphBFS(admSimpleNode_t *n, admNodeVisitor_t visitor);

//////////////// utilities ///////////////////

admSimpleGraph_t *CreateGraphFromString(const char *str);

#endif //CCISOLUTIONSC_ADMSIMPLEGRAPH_H
