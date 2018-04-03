//
// Created by wein on 4/2/18.
//

#ifndef CCISOLUTIONSC_ADMSIMPLEGRAPH_H
#define CCISOLUTIONSC_ADMSIMPLEGRAPH_H

#include <stddef.h>

#define MAX_LABEL_LENGTH 16
#define MAX_GRAPH_SIZE 128

struct AdmSimpleNode;
typedef struct AdmSimpleNode admSimpleNode_t;

struct AdmSimpleGraph;
typedef struct AdmSimpleGraph admSimpleGraph_t;

admSimpleNode_t *CreateAdmSimpleNode();
void DeleteAdmSimpleNode(admSimpleNode_t *n);

size_t AdmSNDegree(admSimpleNode_t *n);

//////////////////////////////////////////////

admSimpleGraph_t *CreateAdmSimpleGraph();
admSimpleNode_t *GetOrCreateAdmNode(admSimpleGraph_t *G, const char *label);
void DeleteAdmSimpleGraph(admSimpleGraph_t *G);
size_t AdmGraphSize(admSimpleGraph_t *G);

//////////////// utilities ///////////////////

enum GraphIniterMode {
    GraphIniterMode_file,  // not implemented
    GraphIniterMode_string,  // test friendly
};

admSimpleGraph_t *CreateGraphFromString(const char *str);

#endif //CCISOLUTIONSC_ADMSIMPLEGRAPH_H
