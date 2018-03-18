//
// Created by wein on 3/11/18.
//

#include "cciBinaryTree.h"

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_NUM_NODES 1024

static cciBinTreeNode_t *nodePool = NULL;
static ssize_t nodeIndex = 0;

cciBinTreeNode_t *CreateBinTreeNode() {
    assert(
        nodePool &&
        (nodeIndex != -1) &&
        (nodeIndex <= MAX_NUM_NODES));
    cciBinTreeNode_t *n = nodePool + nodeIndex++;
    n->left = NULL;
    n->right = NULL;
    RESET(n->value);
    return n;
}

cciBinTreeNodeVisitor_t CreateVisitor(VisitorFunc func, void *state) {
    cciBinTreeNodeVisitor_t v;
    v.state = state;
    v.func = func;
    return v;
}

cciBinTreeNode_t *Search(cciBinTreeNode_t *aNode, cciValue_t v, CompareFunc func) {
    int cmp;
    if (! func) {
        func = CompareI;  // default comparison function
    }
    if (! aNode) {
        return NULL;
    }
    cmp = func(v, aNode->value);
    if (cmp == 0) {
        return aNode;
    }
    if (cmp < 0) {
        return Search(aNode->left, v, func);
    } else {
        return Search(aNode->right, v, func);
    }
    return NULL;
}

void InitFactory() {
    nodePool = malloc(sizeof(cciBinTreeNode_t) * MAX_NUM_NODES);
    nodeIndex = 0;
}

void CloseFactory() {
    free(nodePool);
    nodePool = NULL;
    nodeIndex = -1;
}

cciBinTreeNode_t *FindMin(cciBinTreeNode_t *aNode, CompareFunc func) {
    if (! func) {
        func = CompareI;
    }
    if (! aNode->left) {
        return aNode;
    }
    return FindMin(aNode->left, func);
}

cciBinTreeNode_t *FindMax(cciBinTreeNode_t *aNode, CompareFunc func) {
    if (! func) {
        func = CompareI;
    }
    if (! aNode->right) {
        return aNode;
    }
    return FindMax(aNode->right, func);
}

int Traverse(cciBinTreeNode_t *aNode, cciBinTreeNodeVisitor_t *visitor) {
    int total = 0;
    if (aNode) {
        total += 1;
        total += Traverse(aNode->left, visitor);
        if (visitor && visitor->func) {
            visitor->func(aNode, visitor->state);
        }
        total += Traverse(aNode->right, visitor);
    }
    return total;
}

