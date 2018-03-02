//
// Created by wein on 3/3/18.
//

#include <cciList.h>
#include <tinyCUnit.h>

int main(int argc, char **argv) {
    InitializeTinyTests();

    NewTinyTest("PlaceHolder") ((void) {
        AssertTrue(1);
    });

    RunTinyTests();
    return 0;
}