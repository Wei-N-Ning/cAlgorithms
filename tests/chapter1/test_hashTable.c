//
// Created by wein on 3/3/18.
//

#include <cciHashTable.h>
#include <assert.h>

void RunTinyTests();

void test_createHashTable() {
    cciHashTable_t *tb = NewHashTable(16);
    assert(tb);
    assert(! ISVALID(SGet(tb, "doom")));
    DeleteHashTable(tb);
}

void test_setGetValue() {
    cciHashTable_t *tb = NewHashTable(16);
    SSet(tb, "doom.year", newInt(1993));
    assert(ISVALID(SGet(tb, "doom.year")));
    assert(1993 == GETINT(SGet(tb, "doom.year")));
    DeleteHashTable(tb);
}

void test_overrideExistingValue() {
    cciHashTable_t *tb = NewHashTable(16);
    SSet(tb, "doom.level", newInt(13));
    assert(13 == GETINT(SGet(tb, "doom.level")));
    SSet(tb, "doom.level", newInt(144));
    assert(144 == GETINT(SGet(tb, "doom.level")));
    DeleteHashTable(tb);
}

void test_acceptEmptyStringKey() {
    cciHashTable_t *tb = NewHashTable(16);
    SSet(tb, "", newInt(15));
    assert(ISVALID(SGet(tb, "")));
    assert(15 == GETINT(SGet(tb, "")));
    SSet(tb, "", newInt(166));
    assert(166 == GETINT(SGet(tb, "")));
    DeleteHashTable(tb);
}

void test_whenKeysCollidedExpectExtraSlotsAllocated() {
    cciHashTable_t *tb = NewHashTable(1);
    SSet(tb, "this", newInt(15));
    SSet(tb, "that", newInt(25));
    SSet(tb, "thor", newInt(125));
    SSet(tb, "them", newInt(-8));
    assert(-8 == GETINT(SGet(tb, "them")));
    assert(125 == GETINT(SGet(tb, "thor")));
    assert(25 == GETINT(SGet(tb, "that")));
    assert(15 == GETINT(SGet(tb, "this")));
    DeleteHashTable(tb);
}

void test_popKeyExpectKeyRemoved() {
    cciHashTable_t *tb = NewHashTable(16);
    SSet(tb, "this", newInt(15));
    SSet(tb, "that", newInt(25));
    SSet(tb, "thor", newInt(125));
    SSet(tb, "them", newInt(-8));
    SPop(tb, "thor");
    SPop(tb, "this");
    assert(! ISVALID(SGet(tb, "thor")));
    assert(! ISVALID(SGet(tb, "this")));
    SSet(tb, "this", newInt(-134));
    SSet(tb, "thor", newInt(98));
    assert(-134 == GETINT(SGet(tb, "this")));
    assert(98 == GETINT(SGet(tb, "thor")));
    DeleteHashTable(tb);
}

void test_whenKeysCollidedExpectSlotsDeallocated() {
    cciHashTable_t *tb = NewHashTable(1);
    SSet(tb, "this", newInt(15));
    SSet(tb, "that", newInt(25));
    SSet(tb, "thor", newInt(125));
    SSet(tb, "them", newInt(-8));
    SPop(tb, "thor");
    SPop(tb, "this");
    assert(! ISVALID(SGet(tb, "thor")));
    assert(! ISVALID(SGet(tb, "this")));
    assert(-8 == GETINT(SGet(tb, "them")));
    assert(25 == GETINT(SGet(tb, "that")));
    DeleteHashTable(tb);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
