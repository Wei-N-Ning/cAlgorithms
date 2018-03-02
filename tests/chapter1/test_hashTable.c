//
// Created by wein on 3/3/18.
//

#include <cciHashTable.h>
#include <tinyCUnit.h>


int main(int argc, char **argv) {
    InitializeTinyTests();

    NewTinyTest("CreateAndDeleteHashTable") ((void) {
        cciHashTable_t *tb = NewHashTable();
        AssertTrue(tb);
        DeleteHashTable(tb);
    });

    NewTinyTest("SetGetIntKeyValuePairs") ((void) {
        cciHashTable_t *tb = NewHashTable();
        ISetInt(tb, 123, 456);
//        AssertEqual(456, IGetInt(tb, 123));
        DeleteHashTable(tb);
    });

    RunTinyTests();
    return 0;
}
