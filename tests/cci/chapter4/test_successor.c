//
// Created by wein on 3/28/18.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <cci/cciBinaryTree.h>
#include <cci/cciValue.h>
#include <time.h>

#define ARR_SIZE 255
static int *arr = NULL;
static cciBinTreeNode_t *root = NULL;

void RunTinyTests();

void SetUpGlobal() {
    InitFactory();
    root = CreateBinTreeNode(NULL);
    arr = malloc(sizeof(int) * ARR_SIZE);
    for (int i=0; i<ARR_SIZE; ++i) {
        arr[i] = CCIValue_GETINT(BinTreeInsert(root, CCIValue_newInt(rand()), NULL)->value);
    }
}

void TearDownGlobal() {
    free(arr);
    CloseFactory();
}

static cciBinTreeNode_t *createNode(int x, cciBinTreeNode_t *parent) {
    cciBinTreeNode_t *n = CreateBinTreeNode(parent);
    CCIValue_SETINT(n->value, x);
    return n;
}

static cciBinTreeNode_t *createMockTreeFromArray(const int *arr, size_t num) {
    cciBinTreeNode_t *top = createNode(arr[0], NULL);
    for (int i=1; i<num; ++i) {
        BinTreeInsert(top, CCIValue_newInt(arr[i]), NULL);
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
    assert(33 == CCIValue_GETINT(successor(r, CCIValue_newInt(26))->value));
    assert(11 == CCIValue_GETINT(successor(r, CCIValue_newInt(1))->value));
    assert(23 == CCIValue_GETINT(successor(r, CCIValue_newInt(11))->value));
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
    assert(! successor(r, CCIValue_newInt(234324)));
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
    assert(! successor(r, CCIValue_newInt(46)));
}

static void profEach(cciBinTreeNode_t *r, int *workload, size_t szWorkload) {
    for (size_t i=0; i < szWorkload; ++i) {
        successor(r, CCIValue_newInt(workload[i]));
    }
}

static void profAll() {
    InitFactory();
    size_t szWorkloads[6] = {
        0, 100, 1000,
        //5000,
        //10000, 20000
    };
    root = CreateBinTreeNode(NULL);
    int *arr = malloc(sizeof(int) * 20000);
    for (int i=0; i<20000; ++i) {
        arr[i] = CCIValue_GETINT(BinTreeInsert(root, CCIValue_newInt(rand()), NULL)->value);
    }
    time_t start, end;
    double msec;
    for (int i=0; i<6; ++i) {
        start = clock();
        profEach(root, arr, szWorkloads[i]);
        end = clock();
        msec =  end - start;
        printf("%d %f\n", (int)szWorkloads[i], msec);
    }
    free(arr);
    CloseFactory();
}

int main(int argc, char **argv) {
    RunTinyTests();
    profAll();
    return 0;
}