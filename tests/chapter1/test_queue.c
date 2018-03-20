//
// Created by wein on 3/20/18.
//

#include <cciQueue.h>
#include <assert.h>

void RunTinyTests();

void test_createQueue() {
    cciQueue_t *qu = CreateCCIQueue();
    assert(qu);
    assert(CCIQueueEmpty(qu));
    DeleteCCIQueue(qu);
}

void test_enqueueOneExpectElement() {
    cciQueue_t *qu = CreateCCIQueue();
    Enqueue(qu, newInt(23));
    assert(! CCIQueueEmpty(qu));
    assert(23 == GETINT(Front(qu)));
    DeleteCCIQueue(qu);
}

void test_enqueueManyExpectElementsOrder() {
    cciQueue_t *qu = CreateCCIQueue();
    Enqueue(qu, newInt(23));
    Enqueue(qu, newInt(123));
    Enqueue(qu, newInt(2));
    Enqueue(qu, newInt(3));
    assert(23 == GETINT(Front(qu)));
    DeleteCCIQueue(qu);
}

void test_dequeueOneExpectNewFront() {
    cciQueue_t *qu = CreateCCIQueue();
    Enqueue(qu, newInt(123));
    Enqueue(qu, newInt(2));
    Enqueue(qu, newInt(3));
    assert(123 == GETINT(Dequeue(qu)));
    assert(2 == GETINT(Front(qu)));
    assert(2 == GETINT(Dequeue(qu)));
    assert(3 == GETINT(Front(qu)));
    Dequeue(qu);
    // invalid value
    assert(0 == GETINT(Dequeue(qu)));
    DeleteCCIQueue(qu);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}