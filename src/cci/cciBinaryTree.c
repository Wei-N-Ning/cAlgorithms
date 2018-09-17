//
// Created by wein on 3/11/18.
//

#include "cciBinaryTree.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#define MAX_NUM_NODES 20000

static cciBinTreeNode_t *nodePool = NULL;
static int nodeIndex = 0;

cciBinTreeNode_t *CreateBinTreeNode(cciBinTreeNode_t *parent) {
    assert(nodePool && (nodeIndex != -1) && (nodeIndex <= MAX_NUM_NODES));
    cciBinTreeNode_t *n = nodePool + nodeIndex++;
    n->left = NULL;
    n->right = NULL;
    n->parent = parent;
    CCIValue_RESET(n->value);
    return n;
}

cciBinTreeNodeVisitor_t CreateBinTreeVisitor(VisitorFunc func, void *state) {
    cciBinTreeNodeVisitor_t v;
    v.state = state;
    v.func = func;
    return v;
}

cciBinTreeNode_t *BinTreeSearch(cciBinTreeNode_t *aNode, cciValue_t v,
                                CCIValue_CompareFunc func) {
    int cmp;
    if (!func) {
        func = CCIValue_CompareI; // default comparison function
    }
    if (!aNode) {
        return NULL;
    }
    cmp = func(v, aNode->value);
    if (cmp == 0) {
        return aNode;
    }
    if (cmp < 0) {
        return BinTreeSearch(aNode->left, v, func);
    } else {
        return BinTreeSearch(aNode->right, v, func);
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

cciBinTreeNode_t *BinTreeMin(cciBinTreeNode_t *aNode,
                             CCIValue_CompareFunc func) {
    if (!func) {
        func = CCIValue_CompareI;
    }
    if (!aNode->left) {
        return aNode;
    }
    return BinTreeMin(aNode->left, func);
}

cciBinTreeNode_t *BinTreeMax(cciBinTreeNode_t *aNode,
                             CCIValue_CompareFunc func) {
    if (!func) {
        func = CCIValue_CompareI;
    }
    if (!aNode->right) {
        return aNode;
    }
    return BinTreeMax(aNode->right, func);
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

static cciBinTreeNode_t *_insert(cciBinTreeNode_t **slot,
                                 cciBinTreeNode_t *parent, cciValue_t v,
                                 CCIValue_CompareFunc func) {
    cciBinTreeNode_t *this = NULL;
    int cmp;
    // parent is a leaf; this is a new left OR right branch to be created
    if ((*slot) == NULL) {
        this = CreateBinTreeNode(parent);
        this->value = v;
        this->parent = parent;
        (*slot) = this;
        return this;
    }
    cmp = func(v, (*slot)->value);
    if (cmp == 0) {
        return (*slot);
    }
    if (cmp < 0) {
        return _insert(&((*slot)->left), (*slot), v, func);
    }
    return _insert(&((*slot)->right), (*slot), v, func);
}

cciBinTreeNode_t *BinTreeInsert(cciBinTreeNode_t *aNode, cciValue_t v,
                                CCIValue_CompareFunc func) {
    if (!aNode) {
        return NULL;
    }
    if (!func) {
        func = CCIValue_CompareI;
    }
    return _insert(&aNode, aNode->parent, v, func);
}

static int _insertNode(cciBinTreeNode_t **slot, cciBinTreeNode_t *parent,
                       cciBinTreeNode_t *newNode, CCIValue_CompareFunc func) {
    int cmp;
    if ((*slot) == NULL) {
        (*slot) = newNode;
        newNode->parent = parent;
        return 1;
    }
    cmp = func(newNode->value, (*slot)->value);
    if (cmp == 0) {
        return 0;
    }
    if (cmp < 0) {
        return _insertNode((&(*slot)->left), (*slot), newNode, func);
    }
    return _insertNode((&(*slot)->right), (*slot), newNode, func);
}

int BinTreeInsertNode(cciBinTreeNode_t *aNode, cciBinTreeNode_t *newNode,
                      CCIValue_CompareFunc func) {
    if (!func) {
        func = CCIValue_CompareI;
    }
    return _insertNode(&aNode, aNode->parent, newNode, func);
}

static void _remove(cciBinTreeNode_t **slot, cciBinTreeNode_t *parent,
                    CCIValue_CompareFunc func) {
    cciBinTreeNode_t *right = (*slot)->right;
    cciBinTreeNode_t *left = (*slot)->left;
    (*slot) = NULL;
    if (right) {
        BinTreeInsertNode(parent, right, func);
    }
    if (left) {
        BinTreeInsertNode(parent, left, func);
    }
}

cciBinTreeNode_t *BinTreeRemove(cciBinTreeNode_t *top, cciValue_t v,
                                CCIValue_CompareFunc func) {
    int cmp;
    cciBinTreeNode_t *found = NULL;
    if (!func) {
        func = CCIValue_CompareI;
    }
    cmp = func(v, top->value);
    if (cmp == 0) {
        return NULL;
    }
    found = BinTreeSearch(top, v, func);
    if (found) {
        if (found == found->parent->left) {
            _remove(&(found->parent->left), found->parent, func);
        } else {
            _remove(&(found->parent->right), found->parent, func);
        }
    }
    return top;
}

int Depth(cciBinTreeNode_t *aNode) {
    int height = 0;
    while (aNode) {
        aNode = aNode->parent;
        height++;
    }
    return height;
}

// using macro is also fine BUT,
// if the macro is defined as MAXOF(x,y) ((x)>(y)?(x):(y)) THEN,
// MAXOF(Height(aNode->left), Height(aNode->right)) is expanded to:
// Height(aNode->left)>Height(aNode->right)?Height(aNode->left):Height(aNode->right)
static int _maxof(int x, int y) { return x > y ? x : y; }

int Height(cciBinTreeNode_t *aNode) {
    if (aNode) {
        return 1 + _maxof(Height(aNode->left), Height(aNode->right));
    }
    return 0;
}