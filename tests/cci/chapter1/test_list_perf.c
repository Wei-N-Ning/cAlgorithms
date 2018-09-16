//
// Created by wein on 3/24/18.
//

#include <cci/cciList.h>

#include <time.h>
#include <stdio.h>

static void testRoundTripInt() {
    int size = 20000;
    double microsec = 0.0;
    clock_t before, after;
    printf("start integration test: integer round trip (problem size: %d)......", size);
    before = clock();
    cciList_t *l = CCI_NewList();
    for (int i=0; i<size; ++i) {
        CCI_ListAppend(l, CCIValue_newInt(i));
    }
    after = clock();
    microsec = after - before;
    printf("DONE\n%f s (%f ms)\n", microsec/1000000, microsec/1000);
}

int main(int argc, char **argv) {
    testRoundTripInt();
    return 0;
}