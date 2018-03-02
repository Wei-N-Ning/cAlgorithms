//
// Created by wein on 3/2/18.
//

#include <tinyCUnit.h>
#include <cciStrings.h>

int main(int argc, char **argv) {
    InitializeTinyTests();

    NewTinyTest("PlaceHolder") ((void) {
        AssertEqual(1, placeholder());
    });

    RunTinyTests();
    return 0;
}
