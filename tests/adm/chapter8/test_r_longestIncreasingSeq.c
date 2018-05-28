//
// Created by wein on 5/21/18.
//
// this is the second revision of the solution, inspired by the Python version
//
// given a numeric sequence
// S: 31415926535
// find the longest increasing sequence
// for each Ni in S
//   for each Nj in N0 to Ni-1
//     if Ni > Nj:
//        take the longest one
//

#include <assert.h>
#include <stdlib.h>
#include <memory.h>

#define INVALID (-1)

typedef struct __RECORD {
    int prev;
    int length;
} Record;

Record *initRecords(int sz) {
    Record *records = malloc(sz * sizeof(Record));
    while (sz--) {
        records[sz].prev = INVALID;
        records[sz].length = 1;
    }
    return records;
}

void DeleteRecords(Record *records) {
    free(records);
}

int solve(const char *arr) {
    int sz = (int)strlen(arr);
    Record *records = initRecords(sz);
    for (int i = 1; i < sz; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[i] < arr[j]) {
                continue;  // Ni does not create an increasing sequence; ignore
                           // Note it accepts elements that are greater-or-equal to the previous elements
            }
            if (records[j].length + 1> records[i].length) {
                records[i].length = records[j].length + 1;  // Ni create a longer increasing sequence
                records[i].prev = j;  // keep track of the previous index for backtracking
            }
        }
    }
    int length = 0;  // do backtracking here...
    for (int i = 0; i < sz; ++i) {
        if (length < records[i].length) {
            length = records[i].length;
        }
    }
    DeleteRecords(records);
    return length;
}

void RunTinyTests();

void test_givenSequenceExpectLength() {
    const char *s = "32152477943867147994414428719375";
    int length = solve(s);  // 11 12444444479
    assert(11 == length);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
