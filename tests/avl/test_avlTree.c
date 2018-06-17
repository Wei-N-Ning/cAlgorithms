
#include <cciBinaryTree.h>
#include <stddef.h>
#include <assert.h>

void RunTinyTests();

void setUp() {
    InitFactory();
}

void tearDown() {
    CloseFactory();
}

// The height of a tree with no elements is 0
// The height of a tree with 1 element is 1
// The height of a tree with > 1 element is
//      equal to 1 + the height of its tallest subtree.
void test_assertTreeHeight() {
    cciBinTreeNode_t* node = CreateBinTreeNode(NULL);
    assert(1 == Height(node));
    cciBinTreeNode_t* child = CreateBinTreeNode(node);
    node->left = child;
    assert(2 == Height(node));
}

// RR: single right rotation
// LL: single left rotation
// RL: double right rotation
// LR: double left rotation
// recall that in a binary search tree
// the values of *ALL* the child nodes in the left
// branch of a node must be smaller than its own
// value
void test_singleRotation() {
    ;
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}