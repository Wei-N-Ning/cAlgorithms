//Design an algorithm and write code to find the first common ancestor of two nodes
//    in a binary tree. Avoid storing additional nodes in a data structure. NOTE: This is not
//necessarily a binary search tree.

// first solution
// simple but not efficient
// let the root be R, those two subjects P,Q
// check if R "covers" P and Q
// that is, there is a path connecting R to the child node
// if so, test R's left child then R's right child in
// a greedy recursion, so that the child becomes parent
// but when both children fail the test, return the current
// parent node

// second solution

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include <cciBinaryTree.h>

void RunTinyTests();

///////// if pointer-to-parent is given

typedef struct Node {
    struct Node *parent;
    struct Node *child;
    int value;
} node_t;

size_t height(node_t *n) {
    size_t h = 0;
    for (; n->parent; n = n->parent, ++h) ;
    return h;
}

int isConnected(node_t *top, node_t *bottom) {
    while (top) {
        if (top == bottom) {
            return 1;
        }
        top = top->child;
    }
    return 0;
}

node_t *find(node_t *n1, node_t *n2) {
    while (n1) {
        if (n1 == n2 || isConnected(n1, n2)) {
            return n1;
        }
        n1 = n1->parent;
    }
    return NULL;
}

node_t *createNode(node_t *p, int v) {
    node_t *n = malloc(sizeof(node_t));
    n->value = v;
    n->child = NULL;
    n->parent = p;
    if (p) {
        p->child = n;
    }
    return n;
}

node_t *createBranch(node_t *root, const int *values, size_t num) {
    node_t *p = root;
    node_t *n = NULL;
    for (int i=0; i<num; ++i) {
        n = createNode(p, values[i]);
        p = n;
    }
    return n;
}

void deleteBranch(node_t *root) {
    node_t *toFree = NULL;
    node_t *this = root;
    while (this) {
        toFree = this;
        this = this->child;
        free(toFree);
    }
}

node_t *child(node_t *n, size_t num) {
    size_t count = 0;
    while (n->child) {
        if (num > 0 && count == num) {
            break;
        }
        n = n->child;
        count += 1;
    }
    return n;
}

static int sut[5] = {2, 14, 155, 25, 545};

void test_createDeleteBranch() {
    node_t *root = createNode(NULL, -1);
    createBranch(root, sut, 3);
    assert(155 == child(root, 0)->value);
    assert(155 == child(root, 3)->value);
    assert(14 == child(root, 2)->value);
    assert(2 == height(child(root, 2)));
    assert(isConnected(root, child(root, 0)));
    deleteBranch(root);
}

void test_givenTwoSeparateBranchesExpectNoCommonAncestor() {
    node_t *root1 = createNode(NULL, -1);
    node_t *root2 = createNode(NULL, -13);
    node_t *c1;
    node_t *c2;
    createBranch(root1, sut, 3);
    createBranch(root2, sut + 1, 2);
    c1 = child(root1, 2);
    c2 = child(root2, 0);
    assert(! find(c1, c2));
    deleteBranch(root1);
    deleteBranch(root2);
}

void test_givenTwoJoinedBRanchesExpectCommonAncestor() {
    node_t *root = createNode(NULL, -1);
    node_t *c1;
    node_t *c2;
    createBranch(root, sut, 5);  // -1, 2, 14, 155, 25, 545
                                 //                      c1
                                 //        c2
    c1 = child(root, 0);
    c2 = child(root, 2);
    assert(c2 == find(c1, c2));
    deleteBranch(root);
}

static cciBinTreeNode_t *createTreeNode(int x, cciBinTreeNode_t *parent) {
    cciBinTreeNode_t *n = CreateBinTreeNode(parent);
    SETINT(n->value, x);
    return n;
}

static cciBinTreeNode_t *createMockTreeFromArray(const int *arr, size_t num) {
    cciBinTreeNode_t *top = createTreeNode(arr[0], NULL);
    for (int i=1; i<num; ++i) {
        BinTreeInsert(top, newInt(arr[i]), NULL);
    }
    return top;
}

static int cover(cciBinTreeNode_t *n, cciBinTreeNode_t *sub) {
    if (! n) {
        return 0;
    }
    if (n == sub) {
        return 1;
    }
    return cover(n->left, sub) || cover(n->right, sub);
}

void test_coverTest() {
    int arr[8] = {46, 23, 24, 11, 26, 37, 1, 33};
    //            46
    //    23
    //  11  24
    //1       26
    //          37
    //        33
    cciBinTreeNode_t *r = createMockTreeFromArray(arr, 8);
    assert(! cover(BinTreeSearch(r, newInt(11), NULL), BinTreeSearch(r, newInt(37), NULL)));
    assert(! cover(BinTreeSearch(r, newInt(23), NULL), BinTreeSearch(r, newInt(46), NULL)));
    assert(cover(BinTreeSearch(r, newInt(23), NULL), BinTreeSearch(r, newInt(26), NULL)));
}

static cciBinTreeNode_t *findCommonAncestor(cciBinTreeNode_t *r, cciBinTreeNode_t *sub1, cciBinTreeNode_t *sub2) {
    if (cover(r->left, sub1) && cover(r->left, sub2)) {
        return findCommonAncestor(r->left, sub1, sub2);
    }
    if (cover(r->right, sub1) && cover(r->right, sub2)) {
        return findCommonAncestor(r->right, sub1, sub2);
    }
    return r;
}

void test_findCommonAncestor() {
    int arr[8] = {46, 23, 24, 11, 26, 37, 1, 33};
    //            46
    //    23
    //  11  24
    //1       26
    //          37
    //        33
    cciBinTreeNode_t *r = createMockTreeFromArray(arr, 8);
    assert(r == findCommonAncestor(r, BinTreeSearch(r, newInt(11), NULL), BinTreeSearch(r, newInt(46), NULL)));
    assert(
        BinTreeSearch(r, newInt(23), NULL) == findCommonAncestor(
            r, BinTreeSearch(r, newInt(11), NULL), BinTreeSearch(r, newInt(33), NULL)
        )
    );
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