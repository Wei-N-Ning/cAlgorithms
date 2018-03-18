//
// Created by wein on 3/18/18.
//

#include <stdio.h>
#include <cciBinaryTree.h>
#include <cciValue.h>
#include <assert.h>

void RunTinyTests();

cciBinTreeNode_t *createNode(int x) {
    cciBinTreeNode_t *n = CreateBinTreeNode();
    SETINT(n->value, x);
    return n;
}

cciBinTreeNode_t *createMockTree() {
    cciBinTreeNode_t *top = createNode(13);
    top->left = createNode(2);
    top->left->left = createNode(-34);
    top->left->right = createNode(9);
    top->right = createNode(114);
    top->right->left = createNode(45);
    top->right->right = createNode(145);
    return top;
}

cciBinTreeNode_t *search(cciBinTreeNode_t *n, int x) {
    return Search(n, newInt(x), NULL);
}

void test_searchExpectNotFound() {
    cciBinTreeNode_t *n = createMockTree();
    assert(! search(n, 0xDEAD));
    assert(! search(n, 7));
    assert(! search(n, 100));
}

void test_searchExpectFound() {
    cciBinTreeNode_t *n = createMockTree();
    assert(search(n, 13));
    assert(search(n, 2));
    assert(search(n, -34));
    assert(search(n, 9));
    assert(search(n, 114));
    assert(search(n, 45));
    assert(search(n, 145));
}

void test_searchInSubTree() {
    cciBinTreeNode_t *top = createMockTree();
    assert(! search(top->right, 13));
    assert(search(top->left, 2));
    assert(search(top->right, 114));
    assert(search(top->right, 45));
    assert(search(top->right, 145));
}

int main(int argc, char **argv) {
    InitFactory();
    RunTinyTests();
    CloseFactory();
    return 0;
}
