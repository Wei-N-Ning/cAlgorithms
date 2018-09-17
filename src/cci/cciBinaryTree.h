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
    struct CCIBinTreeNode *parent;
    cciValue_t value;
} cciBinTreeNode_t;

typedef void (*VisitorFunc)(cciBinTreeNode_t *n, void *state);

typedef struct CCIBinTreeNodeVisitor {
    void *state;
    VisitorFunc func;
} cciBinTreeNodeVisitor_t;

cciBinTreeNode_t *CreateBinTreeNode(cciBinTreeNode_t *parent);

cciBinTreeNodeVisitor_t CreateBinTreeVisitor(VisitorFunc func, void *state);

cciBinTreeNode_t *BinTreeSearch(
    cciBinTreeNode_t *aNode,
    cciValue_t v,
    CCIValue_CompareFunc func  // typedef in cciValue.h
);

cciBinTreeNode_t *BinTreeMin(cciBinTreeNode_t *aNode, CCIValue_CompareFunc func);
cciBinTreeNode_t *BinTreeMax(cciBinTreeNode_t *aNode, CCIValue_CompareFunc func);

int Traverse(cciBinTreeNode_t *aNode, cciBinTreeNodeVisitor_t *visitor);

// root node has depth of 1
int Depth(cciBinTreeNode_t *aNode);

int Height(cciBinTreeNode_t *aNode);

cciBinTreeNode_t *BinTreeInsert(
    cciBinTreeNode_t *aNode,
    cciValue_t v,
    CCIValue_CompareFunc func
);

int BinTreeInsertNode(
    cciBinTreeNode_t *aNode,
    cciBinTreeNode_t *newNode,
    CCIValue_CompareFunc func
);

// return a new tree with the given node removed to the caller
cciBinTreeNode_t *BinTreeRemove(
    cciBinTreeNode_t *top,
    cciValue_t v,
    CCIValue_CompareFunc func
);

////////////////// utilities //////////////////

// must call at the beginning of main()
void InitFactory();

// must call at the end of main()
void CloseFactory();

#endif //CCISOLUTIONSC_CCIBINARYTREE_H
