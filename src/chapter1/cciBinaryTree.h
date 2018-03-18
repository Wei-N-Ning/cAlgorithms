//
// Created by wein on 3/11/18.
//

#ifndef CCISOLUTIONSC_CCIBINARYTREE_H
#define CCISOLUTIONSC_CCIBINARYTREE_H

#include "cciValue.h"

/////// Binary Tree API

typedef struct CCIBinTreeNode {
    struct CCIBinTreeNode *left;
    struct CCIBinTreeNode *right;
    cciValue_t value;
} cciBinTreeNode_t;

cciBinTreeNode_t *CreateBinTreeNode();

cciBinTreeNode_t *Search(
    cciBinTreeNode_t *aNode,
    cciValue_t v,
    CompareFunc func  // typedef in cciValue.h
);

/////// utilities

// must call at the beginning of main()
void InitFactory();

// must call at the end of main()
void CloseFactory();

#endif //CCISOLUTIONSC_CCIBINARYTREE_H
