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
        AssertEqual(4, ba->slots);
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

    NewTinyTest("create from uint, expect bits") ((void) {
        BitSlot o;
        cciBitArray_t *ba = CreateFromUInt(0b1001110000111010);
        AssertEqual(0, BaGet(ba, 0));
        AssertEqual(1, BaGet(ba, 1));
        AssertEqual(0, BaGet(ba, 9));
        AssertEqual(1, BaGet(ba, 10));
        AssertEqual(1, BaGet(ba, 11));
        AssertEqual(1, BaGet(ba, 11));
        AssertEqual(1, BaGet(ba, 15));
        Output(ba, &o, 0);
        AssertEqual(0b1001110000111010, o);
        BaDelete(ba);
    });

    NewTinyTest("output, expect value") ((void ) {
        BitSlot o;
        cciBitArray_t *ba = CreateFromUInt(0b1001110000111010);
        Output(ba, &o, 0);
        AssertEqual(0b1001110000111010, o);
        BaDelete(ba);
    });

    RunTinyTests();
}

int main(int argc, char **argv) {
    unitTests();
    return 0;
}
