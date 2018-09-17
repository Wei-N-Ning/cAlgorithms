//You have two very large binary trees: T1, with millions of nodes, and T2, with hun-
//dreds of nodes. Create an algorithm to decide if T2 is a subtree of T1.

// verdict:
// instead of testing the ownership for each Node in sub tree,
// I should implement a tree match subroutine that verifies
// both the ownership and connectivity - (ownership alone is
// not enough to guarantee subtree is part of the host-tree)

#include <cci/cciBinaryTree.h>
#include <cci/cciQueue.h>
#include <cci/cciValue.h>
#include <assert.h>

void RunTinyTests();

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

int isSubtree(cciBinTreeNode_t *host, cciBinTreeNode_t *sub) {
    cciBinTreeNode_t *this;
    int sz = 0;
    int subtreeSize = Traverse(sub, NULL);
    cciQueue_t *qu = CCI_CreateQueue();
    CCI_Enqueue(qu, CCIValue_newPointer(sub));
    while (! CCI_QueueEmpty(qu)) {
        this = CCIValue_GETPOINTER(CCI_Dequeue(qu), cciBinTreeNode_t);
        if (! this) {
            break;
        }
        if (! BinTreeSearch(host, this->value, NULL)) {
            break;
        }
        sz++;
        if (this->left) {
            CCI_Enqueue(qu, CCIValue_newPointer(this->left));
        }
        if (this->right) {
            CCI_Enqueue(qu, CCIValue_newPointer(this->right));
        }
    }
    CCI_DeleteQueue(qu);
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
    cciBinTreeNode_t *sub = BinTreeSearch(root, CCIValue_newInt(26), NULL);
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