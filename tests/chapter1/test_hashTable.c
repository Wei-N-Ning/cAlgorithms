//
// Created by wein on 3/3/18.
//

#include <cciHashTable.h>
#include <tinyCUnit.h>


int main(int argc, char **argv) {
    InitializeTinyTests();

    NewTinyTest("Place Holder") ((void) {
        NewHashTable();
    });

    RunTinyTests();
    return 0;
}
