//
// Created by wein on 3/4/18.
//

#include <cci/cciBitArray.h>

#include <assert.h>

void RunTinyTests();

void test_createAndDelet() {
    cciBitArray_t *ba = CCI_BaNew(1, 119);
    assert(119 == ba->size);
    assert(4 == ba->slots);
    CCI_BaDelete(ba);
}

void test_setBitExpectBit() {
    cciBitArray_t *ba = CCI_BaNew(0, 23);
    assert(0 == CCI_BaGet(ba, 17));
    CCI_BaSet(ba, 17, 1);
    assert(1 == CCI_BaGet(ba, 17));
    CCI_BaSet(ba, 17, 0);
    assert(0 == CCI_BaGet(ba, 17));
    CCI_BaDelete(ba);
}

void test_createFromUint() {
    CCI_BitSlot o;
    cciBitArray_t *ba = CCI_CreateBaFromUInt(0b1001110000111010);
    assert(0 == CCI_BaGet(ba, 0));
    assert(1 == CCI_BaGet(ba, 1));
    assert(0 == CCI_BaGet(ba, 9));
    assert(1 == CCI_BaGet(ba, 10));
    assert(1 == CCI_BaGet(ba, 11));
    assert(1 == CCI_BaGet(ba, 11));
    assert(1 == CCI_BaGet(ba, 15));
    CCI_BaOutput(ba, &o, 0);
    assert(0b1001110000111010 == o);
    CCI_BaDelete(ba);
}

void test_outputExpectValue() {
    CCI_BitSlot o;
    cciBitArray_t *ba = CCI_CreateBaFromUInt(0b1001110000111010);
    CCI_BaOutput(ba, &o, 0);
    assert(0b1001110000111010 == o);
    CCI_BaDelete(ba);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
