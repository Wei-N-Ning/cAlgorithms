//
// Created by wein on 3/11/18.
//

#ifndef CCISOLUTIONSC_CCIBINARYTREE_H
#define CCISOLUTIONSC_CCIBINARYTREE_H

#include "cciValue.h"

////////////////// Binary Tree API //////////////////

typedef struct CCIBinTreeNode {
    struct CCIBinTreeNode *left;
    struct CCIBinTreeNode *right;
    cciValue_t value;
} cciBinTreeNode_t;

typedef void (*VisitorFunc)(cciBinTreeNode_t *n, void *state);

typedef struct CCIBinTreeNodeVisitor {
    void *state;
    VisitorFunc func;
} cciBinTreeNodeVisitor_t;

cciBinTreeNode_t *CreateBinTreeNode();

cciBinTreeNodeVisitor_t CreateVisitor(VisitorFunc func, void *state);

cciBinTreeNode_t *Search(
    cciBinTreeNode_t *aNode,
    cciValue_t v,
    CompareFunc func  // typedef in cciValue.h
);

cciBinTreeNode_t *FindMin(cciBinTreeNode_t *aNode, CompareFunc func);
cciBinTreeNode_t *FindMax(cciBinTreeNode_t *aNode, CompareFunc func);

int Traverse(cciBinTreeNode_t *aNode, cciBinTreeNodeVisitor_t *visitor);

////////////////// utilities //////////////////

// must call at the beginning of main()
void InitFactory();

// must call at the end of main()
void CloseFactory();

#endif //CCISOLUTIONSC_CCIBINARYTREE_H
