//
// Created by wein on 4/2/18.
//

#ifndef CCISOLUTIONSC_ADMSIMPLEGRAPH_H
#define CCISOLUTIONSC_ADMSIMPLEGRAPH_H

#include <stddef.h>

#define MAX_LABEL_LENGTH 16

struct AdmSimpleNode;
typedef struct AdmSimpleNode admSimpleNode_t;

struct AdmSimpleGraph;
typedef struct AdmSimpleGraph admSimpleGraph_t;

admSimpleNode_t *CreateAdmSimpleNode();
void DeleteAdmSimpleNode(admSimpleNode_t *n);

size_t AdmSNDegree(admSimpleNode_t *n);

//////////////////////////////////////////////

admSimpleGraph_t *CreateAdmSimpleGraph();
void DeleteAdmSimpleGraph(admSimpleGraph_t *G);

//////////////// utilities ///////////////////

enum GraphIniterMode {
    GraphIniterMode_file,  // not implemented
    GraphIniterMode_string,  // test friendly
};

int InitGraph(enum GraphIniterMode mode, const char *str, admSimpleGraph_t *o_G);

#endif //CCISOLUTIONSC_ADMSIMPLEGRAPH_H
