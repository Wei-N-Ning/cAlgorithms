
#include "./avl_tree.h"

#include <algorithm>
#include <string>
#include <cstdint>
#include <cassert>

void RunTinyTests();

typedef AVLTree<int, int> IntAVLTree;
typedef IntAVLTree::Node Node;

void ExpectNodeEq(int expected_key, int8_t expected_factor, const Node* node) {
    assert(node != nullptr);
    assert(expected_key == node->item->Key());
    assert(expected_factor == node->balance_factor);
}

class AVLTreeTest {
public:
    IntAVLTree tree_;

    AVLTreeTest() = default;
    ~AVLTreeTest() = default;

    IntAVLTree& tree() {
        return tree_;
    }

    void MakePreDoubleRightRotationTree() {
        tree_.Add(5, 5);
        ExpectNodeEq(5, IntAVLTree::kE, tree_.Root());

        tree_.Add(3, 3);
        ExpectNodeEq(5, IntAVLTree::kL, tree_.Root());
        ExpectNodeEq(3, IntAVLTree::kE, tree_.Root()->Left());

        tree_.Add(9, 9);
        ExpectNodeEq(5, IntAVLTree::kE, tree_.Root());
        ExpectNodeEq(3, IntAVLTree::kE, tree_.Root()->Left());
        ExpectNodeEq(9, IntAVLTree::kE, tree_.Root()->Right());

        tree_.Add(7, 7);
        ExpectNodeEq(5, IntAVLTree::kR, tree_.Root());
        ExpectNodeEq(3, IntAVLTree::kE, tree_.Root()->Left());
        ExpectNodeEq(9, IntAVLTree::kL, tree_.Root()->Right());
        ExpectNodeEq(7, IntAVLTree::kE, tree_.Root()->Right()->Left());

        tree_.Add(10, 10);
        ExpectNodeEq(5, IntAVLTree::kR, tree_.Root());
        ExpectNodeEq(3, IntAVLTree::kE, tree_.Root()->Left());
        ExpectNodeEq(9, IntAVLTree::kE, tree_.Root()->Right());
        ExpectNodeEq(7, IntAVLTree::kE, tree_.Root()->Right()->Left());
        ExpectNodeEq(10, IntAVLTree::kE, tree_.Root()->Right()->Right());
    }

    void MakePreDoubleLeftRotationTree() {
        tree_.Add(9, 9);
        tree_.Add(5, 5);
        tree_.Add(11, 11);
        tree_.Add(3, 3);
        tree_.Add(7, 7);

        ExpectNodeEq(9, IntAVLTree::kL, tree_.Root());
        ExpectNodeEq(5, IntAVLTree::kE, tree_.Root()->Left());
        ExpectNodeEq(11, IntAVLTree::kE, tree_.Root()->Right());
        ExpectNodeEq(3, IntAVLTree::kE, tree_.Root()->Left()->Left());
        ExpectNodeEq(7, IntAVLTree::kE, tree_.Root()->Left()->Right());
    }
};

static AVLTreeTest* TEST = nullptr;

void setUp() {
    TEST = new AVLTreeTest;
}

void tearDown() {
    delete TEST;
    TEST = nullptr;
}

void test_RemoveRoot() {
    auto& tree_ = TEST->tree();
    tree_.Add(919, 2);
    tree_.Add(915, 2);
    tree_.Add(409, 409);

    //   915
    // 409 919
    tree_.Remove(915);
    assert(tree_.IsEmpty());
}

void test_AddOneNode() {
    auto& tree_ = TEST->tree();
    assert(! tree_.Get(1));
    assert(tree_.IsBalanced());
    tree_.Add(1, 1);
    assert(1 == tree_.Get(1)->Value());
    ExpectNodeEq(1, IntAVLTree::kE, tree_.Root());
}

void test_AddTwoNodesRightSide() {
    auto& tree_ = TEST->tree();
    tree_.Add(3, 3);
    tree_.Add(5, 5);
    ExpectNodeEq(3, IntAVLTree::kR, tree_.Root());
    ExpectNodeEq(5, IntAVLTree::kE, tree_.Root()->Right());
}

void test_AddThreeNodesRightSide() {
    auto& tree_ = TEST->tree();
    tree_.Add(3, 3);
    tree_.Add(5, 5);
    tree_.Add(7, 7);
    ExpectNodeEq(5, IntAVLTree::kE, tree_.Root());
    ExpectNodeEq(3, IntAVLTree::kE, tree_.Root()->Left());
    ExpectNodeEq(7, IntAVLTree::kE, tree_.Root()->Right());
}

void test_DoubleRightRotation1() {
    auto& tree_ = TEST->tree();
    TEST->MakePreDoubleRightRotationTree();

    tree_.Add(6, 6);
    ExpectNodeEq(7, IntAVLTree::kE, tree_.Root());
    ExpectNodeEq(5, IntAVLTree::kE, tree_.Root()->Left());
    ExpectNodeEq(9, IntAVLTree::kR, tree_.Root()->Right());
    assert(! tree_.Root()->Right()->Left());
    ExpectNodeEq(10, IntAVLTree::kE, tree_.Root()->Right()->Right());
    ExpectNodeEq(3, IntAVLTree::kE, tree_.Root()->Left()->Left());
    ExpectNodeEq(6,  IntAVLTree::kE, tree_.Root()->Left()->Right());
}

void test_DoubleRightRotation2() {
    auto& tree_ = TEST->tree();
    TEST->MakePreDoubleRightRotationTree();

    tree_.Add(8, 8);
    ExpectNodeEq(7, IntAVLTree::kE, tree_.Root());
    ExpectNodeEq(5, IntAVLTree::kL, tree_.Root()->Left());
    ExpectNodeEq(9, IntAVLTree::kE, tree_.Root()->Right());
    ExpectNodeEq(8, IntAVLTree::kE, tree_.Root()->Right()->Left());
    ExpectNodeEq(10, IntAVLTree::kE, tree_.Root()->Right()->Right());
    ExpectNodeEq(3, IntAVLTree::kE, tree_.Root()->Left()->Left());
    assert(! tree_.Root()->Left()->Right());
}

void test_DoubleLeftRotation1() {
    auto& tree_ = TEST->tree();
    TEST->MakePreDoubleLeftRotationTree();

    tree_.Add(6, 6);
    ExpectNodeEq(7, IntAVLTree::kE, tree_.Root());
    ExpectNodeEq(5, IntAVLTree::kE, tree_.Root()->Left());
    ExpectNodeEq(9, IntAVLTree::kR, tree_.Root()->Right());
    ExpectNodeEq(3, IntAVLTree::kE, tree_.Root()->Left()->Left());
    ExpectNodeEq(6, IntAVLTree::kE, tree_.Root()->Left()->Right());
    assert(! tree_.Root()->Right()->Left());
    ExpectNodeEq(11, IntAVLTree::kE, tree_.Root()->Right()->Right());
}

void test_DoubleLeftRotation2() {
    auto& tree_ = TEST->tree();
    TEST->MakePreDoubleLeftRotationTree();

    tree_.Add(8, 8);
    ExpectNodeEq(7, IntAVLTree::kE, tree_.Root());
    ExpectNodeEq(5, IntAVLTree::kL, tree_.Root()->Left());
    ExpectNodeEq(9, IntAVLTree::kE, tree_.Root()->Right());
    ExpectNodeEq(3, IntAVLTree::kE, tree_.Root()->Left()->Left());
    assert(! tree_.Root()->Left()->Right());
    ExpectNodeEq(11, IntAVLTree::kE, tree_.Root()->Right()->Right());
    ExpectNodeEq(8, IntAVLTree::kE, tree_.Root()->Right()->Left());
}

void test_RightRotation() {
    auto& tree_ = TEST->tree();
    TEST->MakePreDoubleRightRotationTree();

    tree_.Add(6, 6);
    ExpectNodeEq(7, IntAVLTree::kE, tree_.Root());

    tree_.Add(2, 2);
    assert(IntAVLTree::kL == tree_.Root()->balance_factor);
    assert(5 == tree_.Root()->Left()->item->Key());
    assert(IntAVLTree::kL == tree_.Root()->Left()->balance_factor);
    assert(3 == tree_.Root()->Left()->Left()->item->Key());
    assert(IntAVLTree::kL == tree_.Root()->Left()->Left()->balance_factor);
    assert(2 == tree_.Root()->Left()->Left()->Left()->item->Key());
    assert(IntAVLTree::kE ==
           tree_.Root()->Left()->Left()->Left()->balance_factor);

    tree_.Add(1, 1);
    assert(7 == tree_.Root()->item->Key());
    assert(IntAVLTree::kL == tree_.Root()->balance_factor);

    assert(IntAVLTree::kL == tree_.Root()->Left()->balance_factor);
    assert(5 == tree_.Root()->Left()->item->Key());

    assert(IntAVLTree::kE == tree_.Root()->Left()->Left()->balance_factor);
    assert(2 == tree_.Root()->Left()->Left()->item->Key());

    assert(IntAVLTree::kE ==
           tree_.Root()->Left()->Left()->Left()->balance_factor);
    assert(1 == tree_.Root()->Left()->Left()->Left()->item->Key());

    assert(IntAVLTree::kE ==
           tree_.Root()->Left()->Left()->Right()->balance_factor);
    assert(3 == tree_.Root()->Left()->Left()->Right()->item->Key());
}

void test_InsertMany() {
    auto& tree_ = TEST->tree();
    const int kN = 1000;
    for (int i = 1; i <= kN; i++) {
        tree_.Add(i, i);
        assert(tree_.IsBalanced());
    }
}

void test_Regression() {
    auto& tree_ = TEST->tree();
    tree_.Add(2, 2);
    ExpectNodeEq(2, IntAVLTree::kE, tree_.Root());

    tree_.Add(4, 4);
    ExpectNodeEq(2, IntAVLTree::kR, tree_.Root());
    ExpectNodeEq(4, IntAVLTree::kE, tree_.Root()->Right());

    tree_.Add(3, 3);
    ExpectNodeEq(3, IntAVLTree::kE, tree_.Root());
    ExpectNodeEq(2, IntAVLTree::kE, tree_.Root()->Left());
    ExpectNodeEq(4, IntAVLTree::kE, tree_.Root()->Right());
    tree_.Add(1, 1);
}

void test_Regression2() {
    auto& tree_ = TEST->tree();
    tree_.Add(364, 2);
    tree_.Add(919, 2);
    tree_.Add(915, 2);
    tree_.Add(825, 2);
    tree_.Add(560, 2);
    tree_.Add(449, 2);
    tree_.Add(425, 2);
    tree_.Add(160, 2);
    tree_.Add(409, 2);
    tree_.Add(423, 2);
    tree_.Add(727, 2);
    assert(tree_.IsBalanced());
}

void test_InsertRandom() {
    auto& tree_ = TEST->tree();
    auto seed = (unsigned int)clock();
    srand(seed);
    const int kN = 1000;
    for (int i = 1; i <= kN; i++) {
        auto v = rand() % 1000;
        tree_.Add(v, v);
        assert(tree_.IsBalanced());
    }
}

void test_DeleteOnlyOne() {
    auto& tree_ = TEST->tree();
    tree_.Add(1, 1);
    tree_.Remove(1);
    assert(tree_.IsEmpty());
}

void _failingTest_RemoveMany() {
    auto& tree_ = TEST->tree();
    tree_.Add(364, 2);
    tree_.Add(919, 2);
    tree_.Add(915, 2);
    tree_.Add(825, 2);
    tree_.Add(560, 2);
    tree_.Add(449, 2);
    tree_.Add(425, 425);
    tree_.Add(160, 160);
    tree_.Add(409, 409);
    tree_.Add(423, 423);
    tree_.Add(727, 727);
    assert(423 == tree_.GetLowerNearest(424)->Value());
    assert(425 == tree_.GetLowerNearest(425)->Value());
    assert(727 == tree_.GetLowerNearest(728)->Value());
    assert(! tree_.GetLowerNearest(2));
    tree_.Remove(9999);
    assert(tree_.IsBalanced());
    tree_.Remove(364);
    assert(tree_.IsBalanced());
    tree_.Remove(825);
    assert(tree_.IsBalanced());
    tree_.Remove(915);
    assert(tree_.IsBalanced());
    tree_.Remove(919);
    assert(tree_.IsBalanced());
    tree_.Remove(560);
    assert(tree_.IsBalanced());
    tree_.Remove(449);
    assert(tree_.IsBalanced());
    tree_.Remove(425);
    assert(tree_.IsBalanced());
    tree_.Remove(160);
    assert(tree_.IsBalanced());
    tree_.Remove(423);
    assert(tree_.IsBalanced());
    assert(409 == tree_.Get(409)->Value());
    tree_.Remove(409);
    assert(tree_.IsBalanced());
    tree_.Remove(727);
    assert(tree_.IsBalanced());
    tree_.Remove(727);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
