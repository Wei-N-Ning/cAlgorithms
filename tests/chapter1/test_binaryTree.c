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
    top->right->left = createNode(145);
    return top;
}

void test_searchExpectNotFound() {
    cciBinTreeNode_t *n = createMockTree();
    assert(! Search(n, newInt(0xDEAD), NULL));
}

void test_searchExpectFound() {
    cciBinTreeNode_t *n = createMockTree();
    assert(Search(n, newInt(9), NULL));
}

int main(int argc, char **argv) {
    InitFactory();
    RunTinyTests();
    CloseFactory();
    return 0;
}
