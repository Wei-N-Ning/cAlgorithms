//
// Created by wein on 3/3/18.
//

#include <assert.h>

#include <cciHashTable.h>
#include <cciValue.h>

void RunTinyTests();

void test_createHashTable() {
    cciHashTable_t *tb = NewHashTable();
    assert(tb);
    assert(! ISVALID(SGet(tb, "doom")));
    DeleteHashTable(tb);
}

void test_setGetValue() {
    cciHashTable_t *tb = NewHashTable();
    SSet(tb, "doom.year", newInt(1993));
    assert(ISVALID(SGet(tb, "doom.year")));
    assert(1993 == GETINT(SGet(tb, "doom.year")));
    DeleteHashTable(tb);
}

//void test_overrideExistingValue() {
//    cciHashTable_t *tb = NewHashTable();
//    SSet(tb, "doom.level", newInt(13));
//    assert(13 == GETINT(SGet(tb, "doom.level")));
//    SSet(tb, "doom.level", newInt(14));
//    assert(14 == GETINT(SGet(tb, "doom.level")));
//    DeleteHashTable(tb);
//}

//void test_acceptEmptyStringKey() {
//    cciHashTable_t *tb = NewHashTable();
//    SSet(tb, "", newInt(15));
//    assert(ISVALID(SGet(tb, "")));
//    assert(15 == GETINT(SGet(tb, "")));
//    SSet(tb, "", newInt(16));
//    assert(16 == GETINT(SGet(tb, "")));
//    DeleteHashTable(tb);
//}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
