//
// Created by wein on 3/21/18.
//

#include <cciHashTable.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

static const char *_SUT = "iddqd idfa idkfa idnoclip iddt "
    "thereisnospoon whoisthedaddy thereisacow "
    "upupdowndownleftrightleftright ab "
    "giveall nofog";

static void randomSliceSUT(char *o_s, size_t len, size_t base) {
    for (size_t i=0; i<len-1; i++) {
        o_s[i] = _SUT[rand() % base];
    }
    o_s[len-1] = '\0';
}

#define TOKEN_SIZE 10

struct token {
    char s[TOKEN_SIZE];
};

// TODO: tokens are out of scope when this function returns but 
// those svalues (cciValues wrapping char *) are left in the hash
// table and subsequently accessed by readTable() function;
// it will cause segfault at strcmp()
// think about a better solution
void populateTable(cciHashTable_t *tb, struct token *tokens, size_t size) {
    for (size_t i=0; i<size; ++i) {
        SSet(tb, tokens[i].s, newFloat(3.5));
    }
}

void readTable(cciHashTable_t *tb, struct token *tokens, size_t size) {
    for (size_t i=0; i<size; ++i) {
        SGet(tb, tokens[i].s);
    }
}

void generateTokens(struct token *tokens, size_t size) {
    size_t base = strlen(_SUT);
    for (size_t i=0; i<size; ++i) {
        randomSliceSUT(tokens[i].s, TOKEN_SIZE, base);
    }
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
    clock_t start;
    clock_t end;
    double msecSet = 0.0;
    double msecGet = 0.0;
    struct token *tokensSet = NULL;
    struct token *tokensGet = NULL;

    for (int i=0; i<numWorkloads; ++i) {
        tb = NewHashTable(workloads[i]);

        tokensSet = malloc(sizeof(struct token) * workloads[i]);
        generateTokens(tokensSet, workloads[i]);        
        
        tokensGet = malloc(sizeof(struct token) * workloads[i]);
        generateTokens(tokensGet, workloads[i]);

        start = clock();
        populateTable(tb, tokensSet, workloads[i]);
        end = clock();
        msecSet = end - start;

        start = clock();
        readTable(tb, tokensGet, workloads[i]);
        end = clock();
        msecGet = end - start;

        printf("%d %f %f\n", (int)workloads[i], msecSet, msecGet);
        DeleteHashTable(tb);
        free(tokensGet);
        free(tokensSet);
    }
    return 0;
}
