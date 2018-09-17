//
// Created by wein on 3/3/18.
//

#include <cci/cciHashTable.h>
#include <assert.h>
#include <stdlib.h>

void RunTinyTests();

void test_createHashTable() {
    cciHashTable_t *tb = CCI_NewHashTable(16);
    assert(tb);
    assert(!CCIValue_ISVALID(CCI_SGet(tb, "doom")));
    CCI_DeleteHashTable(tb);
}

void test_setGetValue() {
    cciHashTable_t *tb = CCI_NewHashTable(16);
    CCI_SSet(tb, "doom.year", CCIValue_newInt(1993));
    assert(CCIValue_ISVALID(CCI_SGet(tb, "doom.year")));
    assert(1993 == CCIValue_GETINT(CCI_SGet(tb, "doom.year")));
    CCI_DeleteHashTable(tb);
}

void test_overrideExistingValue() {
    cciHashTable_t *tb = CCI_NewHashTable(16);
    CCI_SSet(tb, "doom.level", CCIValue_newInt(13));
    assert(13 == CCIValue_GETINT(CCI_SGet(tb, "doom.level")));
    CCI_SSet(tb, "doom.level", CCIValue_newInt(144));
    assert(144 == CCIValue_GETINT(CCI_SGet(tb, "doom.level")));
    CCI_DeleteHashTable(tb);
}

void test_acceptEmptyStringKey() {
    cciHashTable_t *tb = CCI_NewHashTable(16);
    CCI_SSet(tb, "", CCIValue_newInt(15));
    assert(CCIValue_ISVALID(CCI_SGet(tb, "")));
    assert(15 == CCIValue_GETINT(CCI_SGet(tb, "")));
    CCI_SSet(tb, "", CCIValue_newInt(166));
    assert(166 == CCIValue_GETINT(CCI_SGet(tb, "")));
    CCI_DeleteHashTable(tb);
}

void test_whenKeysCollidedExpectExtraSlotsAllocated() {
    cciHashTable_t *tb = CCI_NewHashTable(1);
    CCI_SSet(tb, "this", CCIValue_newInt(15));
    CCI_SSet(tb, "that", CCIValue_newInt(25));
    CCI_SSet(tb, "thor", CCIValue_newInt(125));
    CCI_SSet(tb, "them", CCIValue_newInt(-8));
    assert(-8 == CCIValue_GETINT(CCI_SGet(tb, "them")));
    assert(125 == CCIValue_GETINT(CCI_SGet(tb, "thor")));
    assert(25 == CCIValue_GETINT(CCI_SGet(tb, "that")));
    assert(15 == CCIValue_GETINT(CCI_SGet(tb, "this")));
    CCI_DeleteHashTable(tb);
}

void test_popKeyExpectKeyRemoved() {
    cciHashTable_t *tb = CCI_NewHashTable(16);
    CCI_SSet(tb, "this", CCIValue_newInt(15));
    CCI_SSet(tb, "that", CCIValue_newInt(25));
    CCI_SSet(tb, "thor", CCIValue_newInt(125));
    CCI_SSet(tb, "them", CCIValue_newInt(-8));
    CCI_SPop(tb, "thor");
    CCI_SPop(tb, "this");
    assert(!CCIValue_ISVALID(CCI_SGet(tb, "thor")));
    assert(!CCIValue_ISVALID(CCI_SGet(tb, "this")));
    CCI_SSet(tb, "this", CCIValue_newInt(-134));
    CCI_SSet(tb, "thor", CCIValue_newInt(98));
    assert(-134 == CCIValue_GETINT(CCI_SGet(tb, "this")));
    assert(98 == CCIValue_GETINT(CCI_SGet(tb, "thor")));
    CCI_DeleteHashTable(tb);
}

void test_whenKeysCollidedExpectSlotsDeallocated() {
    cciHashTable_t *tb = CCI_NewHashTable(1);
    CCI_SSet(tb, "this", CCIValue_newInt(15));
    CCI_SSet(tb, "that", CCIValue_newInt(25));
    CCI_SSet(tb, "thor", CCIValue_newInt(125));
    CCI_SSet(tb, "them", CCIValue_newInt(-8));
    CCI_SPop(tb, "thor");
    CCI_SPop(tb, "this");
    assert(!CCIValue_ISVALID(CCI_SGet(tb, "thor")));
    assert(!CCIValue_ISVALID(CCI_SGet(tb, "this")));
    assert(-8 == CCIValue_GETINT(CCI_SGet(tb, "them")));
    assert(25 == CCIValue_GETINT(CCI_SGet(tb, "that")));
    CCI_DeleteHashTable(tb);
}

struct FooNode {
};
typedef struct FooNode fooNode_t;

fooNode_t *CreateFooNode() {
    return malloc(sizeof(fooNode_t));
}

void DeleteFooNode(fooNode_t *n) {
    free(n);
}

void xtest_usePointerForKey() {
    fooNode_t *n1 = CreateFooNode();
    fooNode_t *n2 = CreateFooNode();
    cciHashTable_t *tb = CCI_NewHashTable(16);
    CCI_ISet(tb, (uint64_t) n1, CCIValue_newInt(0xDEAD));
    CCI_ISet(tb, (uint64_t) n2, CCIValue_newInt(0xBEEF));
    assert(2 == CCI_HashTableNumKeys(tb));
    assert(0xDEAD == CCIValue_GETINT(CCI_IGet(tb, (uint64_t) n1)));
    assert(0xBEEF == CCIValue_GETINT(CCI_IPop(tb, (uint64_t) n2)));
    assert(!CCIValue_ISVALID(CCI_IGet(tb, 0x123)));
    assert(1 == CCI_HashTableNumKeys(tb));
    CCI_DeleteHashTable(tb);
    DeleteFooNode(n1);
    DeleteFooNode(n2);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
