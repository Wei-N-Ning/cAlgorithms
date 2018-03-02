//
// Created by wein on 3/3/18.
//

#include <cciList.h>
#include <tinyCUnit.h>

int main(int argc, char **argv) {
    InitializeTinyTests();

    NewTinyTest("CreateAndDeleteList") ((void) {
        cciList_t *l = NewList();
        AssertTrue(l);
        AssertEqual(0, l->size);
        DeleteList(l);
    });

    NewTinyTest("AppendIntExpectNewSize") ((void) {
        cciList_t *l = NewList();
        AppendInt(l, 134);
        AppendInt(l, 134);
        AssertEqual(2, l->size);
        DeleteList(l);
    });

    RunTinyTests();
    return 0;
}