//You are given a binary tree in which each node contains a value. Design an algorithm
//    to print all paths which sum up to that value. Note that it can be any path in the tree
//- it does not have to start at the root.

// MY NOTE: is the binary tree constructed based on the values of the nodes? if not I need to reconstruct another
// binary tree (N LogN) to simplify the problem

// for each node N:
//

#include <math.h>
#include <stdio.h>
#include <string.h>

#include <cci/cciBinaryTree.h>
#include <cci/cciArrayList.h>
#include <cci/cciQueue.h>
#include <cci/cciValue.h>

#include <stdlib.h>


void RunTinyTests();

//////// if the binary tree is constructed based on the node values

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

void SetUpGlobal() {
    InitFactory();
}

void TearDownGlobal() {
    CloseFactory();
}

void printPathBySum(cciBinTreeNode_t *n, int value) {
    // N LogN (for each N < Sum, traverse from N to its descendants until their sum is larger than or equal to Sum)
    cciQueue_t *qu = CCI_CreateQueue();
    cciBinTreeNode_t *this = BinTreeSearch(n, CCIValue_newInt(value), NULL);
    int sum = value;
    if (this) {
        CCI_Enqueue(qu, CCIValue_newPointer(this->left));
    }
    while (!CCI_QueueEmpty(qu)) {
        this = CCIValue_GETPOINTER(CCI_Dequeue(qu), cciBinTreeNode_t);
        if (!this) {
            break;
        }
        sum -= CCIValue_GETINT(this->value);
        if (sum == 0) {
            printf("+ found\n");
        }
        CCI_Enqueue(qu, CCIValue_newPointer(this->left));
        CCI_Enqueue(qu, CCIValue_newPointer(this->parent));
    }
    CCI_DeleteQueue(qu);
}

void test_printBinaryTree() {
    size_t sz = 8;
    int arr[sz];
    for (size_t i=sz; i--; arr[i] = rand() % 100) ;
    cciBinTreeNode_t *n = createMockTreeFromArray(arr, sz);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}