//
// Created by wein on 3/18/18.
//

#include <stdio.h>
#include <string.h>
#include <cciBinaryTree.h>
#include <cciValue.h>
#include <assert.h>

void RunTinyTests();

cciBinTreeNode_t *createNode(int x, cciBinTreeNode_t *parent) {
    cciBinTreeNode_t *n = CreateBinTreeNode(parent);
    SETINT(n->value, x);
    return n;
}

cciBinTreeNode_t *createMockTree() {
    cciBinTreeNode_t *top = createNode(13, NULL);
    top->left = createNode(2, top);
    top->left->left = createNode(-34, top->left);
    top->left->right = createNode(9, top->left);
    top->right = createNode(114, top);
    top->right->left = createNode(45, top->right);
    top->right->right = createNode(145, top->right);
    return top;
}

cciBinTreeNode_t *createMockTreeFromArray(const int *arr, size_t num) {
    cciBinTreeNode_t *top = createNode(arr[0], NULL);
    for (int i=1; i<num; ++i) {
        BinTreeInsert(top, newInt(arr[i]), NULL);
    }
    return top;
}

cciBinTreeNode_t *search(cciBinTreeNode_t *n, int x) {
    return BinTreeSearch(n, newInt(x), NULL);
}

cciBinTreeNode_t *findMin(cciBinTreeNode_t *n) {
    return BinTreeMin(n, NULL);
}

cciBinTreeNode_t *findMax(cciBinTreeNode_t *n) {
    return BinTreeMax(n, NULL);
}

cciBinTreeNode_t *insert(cciBinTreeNode_t *n, int x) {
    return BinTreeInsert(n, newInt(x), NULL);
}

cciBinTreeNode_t *batchInsert(cciBinTreeNode_t *n, const int *arr, size_t num) {
    for (int i=0; i<num; ++i) {
        BinTreeInsert(n, newInt(arr[i]), NULL);
    }
}

void batchRemove(cciBinTreeNode_t *n, const int *arr, size_t num) {
    for (int i=0; i<num; ++i) {
        BinTreeRemove(n, newInt(arr[i]), NULL);
    }
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

void test_findMinExpectValue() {
    cciBinTreeNode_t *top = createMockTree();
    cciBinTreeNode_t *found = findMin(top);
    assert(found);
    assert(-34 == GETINT(found->value));
}

void test_findMinFromSubTree() {
    cciBinTreeNode_t *top = createMockTree();
    cciBinTreeNode_t *found = findMin(top->right);
    assert(found);
    assert(45 == GETINT(found->value));
}

void test_findMaxExpectValue() {
    cciBinTreeNode_t *top = createMockTree();
    cciBinTreeNode_t *found = findMax(top);
    assert(found);
    assert(145 == GETINT(found->value));
}

void test_findMaxFromSubTree() {
    cciBinTreeNode_t *top = createMockTree();
    cciBinTreeNode_t *found = findMax(top->left);
    assert(found);
    assert(9 == GETINT(found->value));
}

void test_traverseExpectTotalNodesVisited() {
    cciBinTreeNode_t *top = createMockTree();
    assert(7 == Traverse(top, NULL));
    assert(3 == Traverse(top->left, NULL));
}

static void countNode(cciBinTreeNode_t *n, void *state) {
    (*(int *)state)++;
}

void test_traverseUseVisitorExpectTotalNodesVisited() {
    cciBinTreeNode_t *top = createMockTree();
    int count = 0;
    cciBinTreeNodeVisitor_t v = CreateBinTreeVisitor(countNode, &count);
    Traverse(top, &v);
    assert(7 == count);
}

static void collectNodeValue(cciBinTreeNode_t *n, void *state) {
    int value = GETINT(n->value);
    char *s = (char *)state;
    size_t len = strlen(s);
    s += len;
    if (len) {
        sprintf(s, ",%d", value);
    } else {
        sprintf(s, "%d", value);
    }
}

static int toString(cciBinTreeNode_t *n, char *o_s) {
    cciBinTreeNodeVisitor_t v = CreateBinTreeVisitor(collectNodeValue, o_s);
    return Traverse(n, &v);
}

void test_traverseAndCollect() {
    cciBinTreeNode_t *top = createMockTree();
    char s[64] = "\0";
    cciBinTreeNodeVisitor_t v = CreateBinTreeVisitor(collectNodeValue, s);
    Traverse(top, &v);
    assert(0 == strcmp("-34,2,9,13,45,114,145", s));
}

void test_insertExpectNewNode() {
    cciBinTreeNode_t *top = createMockTree();
    cciBinTreeNode_t *n = insert(top, 31);
    char s[64] = "\0";
    int num;
    num = toString(top, s);
    assert(n);
    assert(31 == GETINT(n->value));
    assert(8 == num);
    assert(0 == strcmp("-34,2,9,13,31,45,114,145", s));
}

void test_insertSameValueExpectNoNewNode() {
    cciBinTreeNode_t *top = createMockTree();
    cciBinTreeNode_t *n = insert(top, 114);
    char s[64] = "\0";
    int num;
    num = toString(top, s);
    assert(n);
    assert(114 == GETINT(n->value));
    assert(7 == num);
    assert(0 == strcmp("-34,2,9,13,45,114,145", s));
}

void test_insertOneFreeNodeWithNewValueExpectSuccess() {
    cciBinTreeNode_t *top = createMockTree();
    cciBinTreeNode_t *n = createNode(71, NULL);
    char s[64] = "\0";
    assert(BinTreeInsertNode(top, n, NULL));
    toString(top, s);
    assert(0 == strcmp("-34,2,9,13,45,71,114,145", s));
}

void test_insertOneFreeNodeWithExistingValueExpectFail() {
    cciBinTreeNode_t *top = createMockTree();
    cciBinTreeNode_t *n = createNode(145, NULL);
    assert(! BinTreeInsertNode(top, n, NULL));
}

void test_insertSubTreeExpectNewStrcture() {
    int groups1[8] = {46, 23, 24, 11, 26, 37, 1, 33};
    int groups2[5] = {10, 8, 2, 17, 4096};
    char s[64] = "\0";
    cciBinTreeNode_t *t1 = createMockTreeFromArray(groups1, 8);
    cciBinTreeNode_t *t2 = createMockTreeFromArray(groups2, 5);
    cciBinTreeNode_t *t3 = createMockTreeFromArray(groups1, 8);

    // this will NOT automatically reorder the structure
    BinTreeInsertNode(t1, t2, NULL);
    toString(t1, s);
    assert(0 == strcmp("1,2,8,10,17,4096,11,23,24,26,33,37,46", s));
    memset(s, 0, sizeof(s));

    // this will
    batchInsert(t3, groups2, 5);
    toString(t3, s);
    assert(0 == strcmp("1,2,8,10,11,17,23,24,26,33,37,46,4096", s));
}

void test_removeValueAtTopExpectEmptyTree() {
    int groups1[8] = {46, 23, 24, 11, 26, 37, 1, 33};
    cciBinTreeNode_t *t1 = createMockTreeFromArray(groups1, 8);
    cciBinTreeNode_t *t2 = BinTreeRemove(t1, t1->value, NULL);
    assert(! t2);
}

void test_removeValueExpectNewStructure() {
    int groups1[8] = {46, 23, 24, 11, 26, 37, 1, 33};
    char s[64] = "\0";
    cciBinTreeNode_t *t1 = createMockTreeFromArray(groups1, 8);
    toString(t1, s);
    assert(0 == strcmp("1,11,23,24,26,33,37,46", s));
    memset(s, 0, sizeof(s));
    cciBinTreeNode_t *t2 = BinTreeRemove(t1, newInt(26), NULL);
    toString(t2, s);
    assert(0 == strcmp("1,11,23,24,33,37,46", s));
}

void test_insertRemoveRoundTrip() {
    int groups1[8] = {46, 23, 24, 11, 26, 37, 1, 33};
    int groups2[5] = {10, 8, 2, 17, 4096};
    char s[64] = "\0";
    cciBinTreeNode_t *t = createNode(0, NULL);
    batchInsert(t, groups1, 8);
    batchInsert(t, groups2, 5);
    batchRemove(t, groups1, 7);  // left: 33
    batchRemove(t, groups2, 4);  // left: 4096
    toString(t, s);
    assert(0 == strcmp("0,33,4096", s));
}

static void collectDistanceToRoot(cciBinTreeNode_t *n, void *state) {
    int *index = (int *)state;
    int *arr = index + 1;
    int distance = 0;
    cciBinTreeNode_t *temp = n;
    while (temp) {
        temp = temp->parent;
        distance++;
    }
    arr[*index] = distance;
    (*index) += 1;
}

static void minmax(int *arr, size_t num, int *o_min, int *o_max) {
    for (int i=0; i<num; ++i) {
        if (arr[i] > *o_max) {
            *o_max = arr[i];
            continue;
        }
        if (arr[i] < *o_min) {
            *o_min = arr[i];
            continue;
        }
    }
}

// balance factor: the ratio between the longest path and the shortest path
void test_computeBalanceFactor() {
    int groups1[8] = {46, 23, 24, 11, 26, 37, 1, 33};
    //            46
    //    23
    //  11  24
    //1       26
    //          37
    //        33
    // 5: 1
    int arr[9] = {0};  // current index + distances
    int longest = 1;
    int shortest = 1;
    cciBinTreeNode_t *t = createMockTreeFromArray(groups1, 8);
    struct CCIBinTreeNodeVisitor v = CreateBinTreeVisitor(collectDistanceToRoot, arr);
    Traverse(t, &v);
    minmax(arr + 1, 8, &shortest, &longest);
    assert(6 == longest);
    assert(1 == shortest);  // balance factor: 6.0 (unbalanced)
}

void test_testHeight() {
    int groups1[8] = {46, 23, 24, 11, 26, 37, 1, 33};
    //            46
    //    23
    //  11  24
    //1       26
    //          37
    //        33
    cciBinTreeNode_t *n = createMockTreeFromArray(groups1, 8);
    assert(1 == Height(n));
    assert(4 == Height(search(n, 1)));
    assert(6 == Height(search(n, 33)));
}

int main(int argc, char **argv) {
    InitFactory();
    RunTinyTests();
    CloseFactory();
    return 0;
}
