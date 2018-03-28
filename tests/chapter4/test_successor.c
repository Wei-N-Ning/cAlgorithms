//
// Created by wein on 3/28/18.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <cciBinaryTree.h>
#include <cciValue.h>

#define ARR_SIZE 255
static int *arr = NULL;
static cciBinTreeNode_t *root = NULL;

void RunTinyTests();

void SetUpGlobal() {
    InitFactory();
    root = CreateBinTreeNode(NULL);
    arr = malloc(sizeof(int) * ARR_SIZE);
    for (int i=0; i<ARR_SIZE; ++i) {
        arr[i] = GETINT(BinTreeInsert(root, newInt(rand()), NULL)->value);
    }
}

void TearDownGlobal() {
    free(arr);
    CloseFactory();
}

static cciBinTreeNode_t *createNode(int x, cciBinTreeNode_t *parent) {
    cciBinTreeNode_t *n = CreateBinTreeNode(parent);
    SETINT(n->value, x);
    return n;
}

static cciBinTreeNode_t *createMockTreeFromArray(const int *arr, size_t num) {
    cciBinTreeNode_t *top = createNode(arr[0], NULL);
    for (int i=1; i<num; ++i) {
        BinTreeInsert(top, newInt(arr[i]), NULL);
    }
    return top;
}

//////////// solution

struct NodePair {
    cciBinTreeNode_t *this;
    cciBinTreeNode_t *successor;
};

void visit(cciBinTreeNode_t *n, void *state) {
    struct NodePair *np = (struct NodePair *)(state);
    if (np->successor == np->this) {
        np->successor = n;
        return;
    }
    if (np->this == n) {
        np->successor = np->this;
        return;
    }
}

cciBinTreeNode_t *successor(cciBinTreeNode_t *root, const cciValue_t v) {
    cciBinTreeNode_t *this = BinTreeSearch(root, v, NULL);
    if (! this) {
        return NULL;
    }
    struct NodePair np;
    np.successor = NULL;
    np.this = this;
    cciBinTreeNodeVisitor_t visitor;
    visitor.state = (void *)&np;
    visitor.func = visit;
    Traverse(root, &visitor);
    if (np.successor == np.this) {
        np.successor = NULL;
    }
    return np.successor;
}

void test_expectSuccessorFound() {
    int arr[8] = {46, 23, 24, 11, 26, 37, 1, 33};
    //            46
    //    23
    //  11  24
    //1       26
    //          37
    //        33
    cciBinTreeNode_t *r = createMockTreeFromArray(arr, 8);
    assert(33 == GETINT(successor(r, newInt(26))->value));
    assert(11 == GETINT(successor(r, newInt(1))->value));
    assert(23 == GETINT(successor(r, newInt(11))->value));
}

void test_givenInvalidNodeExpectSuccessorNotFound() {
    int arr[8] = {46, 23, 24, 11, 26, 37, 1, 33};
    //            46
    //    23
    //  11  24
    //1       26
    //          37
    //        33
    cciBinTreeNode_t *r = createMockTreeFromArray(arr, 8);
    assert(! successor(r, newInt(234324)));
}

void test_givenLastNodeExpectSuccessorNotFound() {
    int arr[8] = {46, 23, 24, 11, 26, 37, 1, 33};
    //            46
    //    23
    //  11  24
    //1       26
    //          37
    //        33
    cciBinTreeNode_t *r = createMockTreeFromArray(arr, 8);
    assert(! successor(r, newInt(46)));
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}