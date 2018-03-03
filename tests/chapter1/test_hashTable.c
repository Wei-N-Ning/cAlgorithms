//
// Created by wein on 3/3/18.
//

#include <cciHashTable.h>
#include <tinyCUnit.h>


int main(int argc, char **argv) {
    InitializeTinyTests();

    NewTinyTest("create and delete hash table") ((void) {
        cciHashTable_t *tb = NewHashTable();
        AssertTrue(tb);
        DeleteHashTable(tb);
    });

    NewTinyTest("set value, get value from key") ((void) {
        cciHashTable_t *tb = NewHashTable();
        SSetInt(tb, "there", 1330);
        SSetInt(tb, "there is", 1331);
        SSetInt(tb, "there is a", 1332);
        SSetInt(tb, "there is a cow", 1337);
        AssertEqual(1330, SGetInt(tb, "there"));
        AssertEqual(1331, SGetInt(tb, "there is"));
        AssertEqual(1332, SGetInt(tb, "there is a"));
        AssertEqual(1337, SGetInt(tb, "there is a cow"));
        DeleteHashTable(tb);
    });

    NewTinyTest("given invalid key, expect errCode") ((void) {
        cciHashTable_t *tb = NewHashTable();
        SSetInt(tb, "there is a cow", 1337);
        SGetInt(tb, "there is a coew");
        AssertEqual(CCIHASHTABLE_KEY_NOTFOUND, tb->errCode);
        DeleteHashTable(tb);
    });

    RunTinyTests();
    return 0;
}
