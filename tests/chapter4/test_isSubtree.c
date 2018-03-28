//You have two very large binary trees: T1, with millions of nodes, and T2, with hun-
//dreds of nodes. Create an algorithm to decide if T2 is a subtree of T1.

#include <cciBinaryTree.h>
#include <cciQueue.h>
#include <cciValue.h>
#include <assert.h>

void RunTinyTests();

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

int isSubtree(cciBinTreeNode_t *host, cciBinTreeNode_t *sub) {
    cciBinTreeNode_t *this;
    int sz = 0;
    int subtreeSize = Traverse(sub, NULL);
    cciQueue_t *qu = CreateCCIQueue();
    Enqueue(qu, newPointer(sub));
    while (! CCIQueueEmpty(qu)) {
        this = GETPOINTER(Dequeue(qu), cciBinTreeNode_t);
        if (! this) {
            break;
        }
        if (! BinTreeSearch(host, this->value, NULL)) {
            break;
        }
        sz++;
        if (this->left) {
            Enqueue(qu, newPointer(this->left));
        }
        if (this->right) {
            Enqueue(qu, newPointer(this->right));
        }
    }
    DeleteCCIQueue(qu);
    return sz == subtreeSize;
}

void test_expectNotSubtree() {
    int arr[8] = {46, 23, 24, 11, 26, 37, 1, 33};
    int foo[5] = {-1, -2, -10, 3, 5};
    //            46
    //    23
    //  11  24
    //1       26
    //          37
    //        33
    cciBinTreeNode_t *root = createMockTreeFromArray(arr, 8);
    cciBinTreeNode_t *sub = createMockTreeFromArray(foo, 3);
    assert(! isSubtree(root, sub));
}

void test_expectSubtree() {
    int arr[8] = {46, 23, 24, 11, 26, 37, 1, 33};
    //            46
    //    23
    //  11  24
    //1       26
    //          37
    //        33
    cciBinTreeNode_t *root = createMockTreeFromArray(arr, 8);
    cciBinTreeNode_t *sub = BinTreeSearch(root, newInt(26), NULL);
    assert(isSubtree(root, sub));
}

void SetUpGlobal() {
    InitFactory();
}

void TearDownGlobal() {
    CloseFactory();
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}