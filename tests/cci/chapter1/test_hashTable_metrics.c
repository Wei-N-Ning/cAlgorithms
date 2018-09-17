//
// Created by wein on 3/21/18.
//

#include <cci/cciHashTable.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *_SUT = "iddqd idkfa idnoclip iddt thereisnospoon"
    "whoisthedaddy thereisacow upupdowndownleftrightleftright ab"
    "giveall";

static void randomSliceSUT(char *o_s, size_t len) {
    for (size_t i=0; i<len-1; i++) {
        o_s[i] = _SUT[rand() % strlen(_SUT)];
    }
    o_s[len-1] = '\0';
}

#define TOKEN_SIZE 10

struct token {
    char s[TOKEN_SIZE];
};

void populateTable(cciHashTable_t *tb) {
    size_t size = CCI_HashTableSize(tb);
    struct token *tokens = malloc(sizeof(struct token) * size);
    for (size_t i=0; i<size; ++i) {
        randomSliceSUT(tokens[i].s, TOKEN_SIZE);
        CCI_SSet(tb, tokens[i].s, CCIValue_newFloat(3.5));
    }
    free(tokens);
}

void printMetrics(cciHashTable_t *tb) {
    size_t size = CCI_HashTableSize(tb);
    double utilization = 0.0;
    double chainFactor = 0.0;
    double collisionRate = 0.0;
    CCI_HTMetrics(tb, &utilization, &chainFactor, &collisionRate);
    printf("%d %f %f %f\n", (int)size, utilization, chainFactor, collisionRate);
}

int main(int argc, char **argv) {
    size_t numWorkloads = 10;
    size_t workloads[255] = {
        10, 50,
        100, 500,
        1000, 5000,
        10000, 50000,
        100000, 500000
    };
    cciHashTable_t *tb = NULL;
    for (int i=0; i<numWorkloads; ++i) {
        tb = CCI_NewHashTable(workloads[i]);
        populateTable(tb);
        printMetrics(tb);
        CCI_DeleteHashTable(tb);
    }
    return 0;
}
