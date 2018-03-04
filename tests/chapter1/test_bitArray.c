//
// Created by wein on 3/4/18.
//

#include <cciBitArray.h>
#include <tinyCUnit.h>

void unitTests() {
    InitializeTinyTests();

    NewTinyTest("create delete bit array") ((void) {
        cciBitArray_t *ba = BaNew(1, 119);
        AssertEqual(119, ba->size);
        BaDelete(ba);
    });

    NewTinyTest("set bit, expect bit") ((void) {
        cciBitArray_t *ba = BaNew(0, 23);
        AssertEqual(0, BaGet(ba, 17));
        BaSet(ba, 17, 1);
        AssertEqual(1, BaGet(ba, 17));
        BaSet(ba, 17, 0);
        AssertEqual(0, BaGet(ba, 17));
        BaDelete(ba);
    });

    RunTinyTests();
}

int main(int argc, char **argv) {
    unitTests();
    return 0;
}
