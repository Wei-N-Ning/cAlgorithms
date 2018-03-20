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
