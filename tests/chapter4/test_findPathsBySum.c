//You are given a binary tree in which each node contains a value. Design an algorithm
//    to print all paths which sum up to that value. Note that it can be any path in the tree
//- it does not have to start at the root.

// MY NOTE: is the binary tree constructed based on the values of the nodes? if not I need to reconstruct another
// binary tree (N LogN) to simplify the problem

#include <stdio.h>

#include <cciBinaryTree.h>
#include <cciQueue.h>
#include <cciValue.h>
#include <stdlib.h>

void RunTinyTests();

//////// if the binary tree is constructed based on the node values

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

void SetUpGlobal() {
    InitFactory();
}

void TearDownGlobal() {
    CloseFactory();
}

void printPathBySum(cciBinTreeNode_t *n, int value) {
    // N LogN (for each N < Sum, traverse from N to its descendants until their sum is larger than or equal to Sum)
    cciQueue_t *qu = CreateCCIQueue();
    cciBinTreeNode_t *this = BinTreeSearch(n, newInt(value), NULL);
    int sum = value;
    if (this) {
        Enqueue(qu, newPointer(this->left));
    }
    while (!CCIQueueEmpty(qu)) {
        this = GETPOINTER(Dequeue(qu), cciBinTreeNode_t);
        if (!this) {
            break;
        }
        sum -= GETINT(this->value);
        if (sum == 0) {
            printf("+ found\n");
        }
        Enqueue(qu, newPointer(this->left));
        Enqueue(qu, newPointer(this->parent));
    }
    DeleteCCIQueue(qu);
}

static void _binTreePrint(cciBinTreeNode_t *n) {
    cciQueue_t *qu = CreateCCIQueue();
    cciBinTreeNode_t *this = NULL;
    int thisLevel = 1;
    int lastLevel = 0;
    char token;
    Enqueue(qu, newPointer(n));
    Enqueue(qu, newInt(thisLevel));
    Enqueue(qu, newChar('O'));
    while (! CCIQueueEmpty(qu)) {
        this = GETPOINTER(Dequeue(qu), cciBinTreeNode_t);
        thisLevel = GETINT(Dequeue(qu));
        token = GETCHAR(Dequeue(qu));

        if (thisLevel > lastLevel) {
            printf("\n");
            lastLevel = thisLevel;
        }
        if (this->parent) {
            printf("%d/", GETINT(this->parent->value));
        } else {
            printf("/");
        }
        printf("%d ", GETINT(this->value));
        if (this->left) {
            Enqueue(qu, newPointer(this->left));
            Enqueue(qu, newInt(Depth(this->left)));
            Enqueue(qu, newChar('L'));
        }
        if (this->right) {
            Enqueue(qu, newPointer(this->right));
            Enqueue(qu, newInt(Depth(this->right)));
            Enqueue(qu, newChar('R'));
        }
    }
    DeleteCCIQueue(qu);
}

void test_printBinaryTree() {
    int groups1[8] = {46, 24, 22, 12, 16, 18, 1, 45};
    //               46
    //             24
    //          22    45
    //   12
    //1      16
    //     18
    int arr[255];
    for (int i=255; i--; arr[i] = rand() % 1000) ;
    cciBinTreeNode_t *n = createMockTreeFromArray(arr, 255);
    printf("\n");
    _binTreePrint(n);
    printf("\n");
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}