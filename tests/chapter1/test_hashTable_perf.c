//
// Created by wein on 3/21/18.
//

#include <cciHashTable.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *_SUT = "iddqd idkfa idnoclip iddt thereisnospoon"
    "whoisthedaddy thereisacow upupdowndownleftrightleftright ab"
    "giveall";

static randomSliceSUT(char *o_s, size_t len) {
    for (size_t i=0; i<len-1; i++) {
        o_s[i] = _SUT[rand() % strlen(_SUT)];
    }
    o_s[len-1] = '\0';
}

void populateTable(cciHashTable_t *tb) {
    char token[5];
    size_t size = HashTableSize(tb);
    for (size_t i=0; i<size; ++i) {
        randomSliceSUT(token, 5);
        SSet(tb, token, newFloat(3.5));
    }
}

void printTable(cciHashTable_t *tb) {
    size_t size = HashTableSize(tb);
    size_t *buf = malloc(sizeof(size_t) * size);
    HashTableDistri(tb, buf);
    for (size_t i=0; i<size; ++i) {
        printf("%d %d\n", (int)i, (int)buf[i]);
    }
    free(buf);
}

int main(int argc, char **argv) {
    cciHashTable_t *tb = NewHashTable(50);
    populateTable(tb);
    printTable(tb);
    DeleteHashTable(tb);
    return 0;
}
