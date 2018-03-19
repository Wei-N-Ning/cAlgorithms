//
// Created by wein on 3/20/18.
//

#include <cciQueue.h>
#include <assert.h>

void RunTinyTests();

void test_createQueue() {
    cciQueue_t *qu = CreateCCIQueue();
    assert(qu);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}