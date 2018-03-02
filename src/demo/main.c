//
// Include this header in your test executable
//

#include "tinyCUnit.h"

int sut() {
    return 10;
}

int main(int argc, char **argv) {

    InitializeTinyTests();

    NewTinyTest (int, (void) {
        int actual = sut();
        AssertEqual(10, actual);
        return 1;
    });

    NewTinyTest (int, (void) {
        int actual = sut();
        AssertTrue(actual > 9);
        return 1;
    });

    RunTinyTests();

    return 0;
}
