//
// Created by wein on 3/4/18.
//

#include <cciBitArray.h>

#include <assert.h>

void RunTinyTests();

void test_createAndDelet() {
    cciBitArray_t *ba = BaNew(1, 119);
    assert(119 == ba->size);
    assert(4 == ba->slots);
    BaDelete(ba);
}

void test_setBitExpectBit() {
    cciBitArray_t *ba = BaNew(0, 23);
    assert(0 == BaGet(ba, 17));
    BaSet(ba, 17, 1);
    assert(1 == BaGet(ba, 17));
    BaSet(ba, 17, 0);
    assert(0 == BaGet(ba, 17));
    BaDelete(ba);
}

void test_createFromUint() {
    BitSlot o;
    cciBitArray_t *ba = CreateFromUInt(0b1001110000111010);
    assert(0 == BaGet(ba, 0));
    assert(1 == BaGet(ba, 1));
    assert(0 == BaGet(ba, 9));
    assert(1 == BaGet(ba, 10));
    assert(1 == BaGet(ba, 11));
    assert(1 == BaGet(ba, 11));
    assert(1 == BaGet(ba, 15));
    Output(ba, &o, 0);
    assert(0b1001110000111010 == o);
    BaDelete(ba);
}

void test_outputExpectValue() {
    BitSlot o;
    cciBitArray_t *ba = CreateFromUInt(0b1001110000111010);
    Output(ba, &o, 0);
    assert(0b1001110000111010 == o);
    BaDelete(ba);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
