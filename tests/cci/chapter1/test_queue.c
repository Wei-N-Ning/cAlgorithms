//
// Created by wein on 3/20/18.
//

#include <cci/cciQueue.h>
#include <assert.h>

void RunTinyTests();

void test_createQueue() {
    cciQueue_t *qu = CCI_CreateQueue();
    assert(qu);
    assert(CCI_QueueEmpty(qu));
    CCI_DeleteQueue(qu);
}

void test_enqueueOneExpectElement() {
    cciQueue_t *qu = CCI_CreateQueue();
    CCI_Enqueue(qu, CCIValue_newInt(23));
    assert(! CCI_QueueEmpty(qu));
    assert(23 == CCIValue_GETINT(CCI_QueueFront(qu)));
    CCI_DeleteQueue(qu);
}

void test_enqueueManyExpectElementsOrder() {
    cciQueue_t *qu = CCI_CreateQueue();
    CCI_Enqueue(qu, CCIValue_newInt(23));
    CCI_Enqueue(qu, CCIValue_newInt(123));
    CCI_Enqueue(qu, CCIValue_newInt(2));
    CCI_Enqueue(qu, CCIValue_newInt(3));
    assert(23 == CCIValue_GETINT(CCI_QueueFront(qu)));
    CCI_DeleteQueue(qu);
}

void test_dequeueOneExpectNewFront() {
    cciQueue_t *qu = CCI_CreateQueue();
    CCI_Enqueue(qu, CCIValue_newInt(123));
    CCI_Enqueue(qu, CCIValue_newInt(2));
    CCI_Enqueue(qu, CCIValue_newInt(3));
    assert(123 == CCIValue_GETINT(CCI_Dequeue(qu)));
    assert(2 == CCIValue_GETINT(CCI_QueueFront(qu)));
    assert(2 == CCIValue_GETINT(CCI_Dequeue(qu)));
    assert(3 == CCIValue_GETINT(CCI_QueueFront(qu)));
    CCI_Dequeue(qu);
    // invalid value
    assert(0 == CCIValue_GETINT(CCI_Dequeue(qu)));
    CCI_DeleteQueue(qu);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}