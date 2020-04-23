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
// ADM P302
// We distinguish an increasing sequence from a run, where the elements must be
// physical neighbors of each other. The selected elements of both must be sorted in
// increasing order from left to right. For example, consider the sequence

// The longest increasing sequence containing the nth number will be formed by
// appending it to the longest increasing sequence to the left of n that ends on a
// number smaller than Sn

#include <assert.h>
#include <stdio.h>
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
            if (arr[i] <= arr[j]) {
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
    printf("%d ", length);
}

// note the sequences does not have to be contiguous
// read the notes in the header and review ADM P302
void test_long_sequence() {
    const char *s = "31415926512333444555588888999997932384626";
    //                1 1     1233344455558888899999 9
    // num: 25
    int length = solve(s);
    printf("%d ", length);
}

void test_ridiculous_sequence() {
    const char *s = "1324235436436132423423423412342342"
                    "4563246523643264523645326456234536"
                    "3475843683724928347832750752837807"
                    "6786876786786878667856785768576856"
                    "7978789787987987978978978979789789"
                    "1324235436436132423423423412342342"
                    "4563246523643264523645326456234536"
                    "3475843683724928347832750752837807"
                    "6786876786786878667856785768576856"
                    "7978789787987987978978978979789789"
                    "1324235436436132423423423412342342"
                    "4563246523643264523645326456234536"
                    "3475843683724928347832750752837807"
                    "6786876786786878667856785768576856"
                    "7978789787987987978978978979789789"
                    "1324235436436132423423423412342342"
                    "4563246523643264523645326456234536"
                    "3475843683724928347832750752837807"
                    "6786876786786878667856785768576856"
                    "7978789787987987978978978979789789"
                    "1324235436436132423423423412342342"
                    "4563246523643264523645326456234536"
                    "3475843683724928347832750752837807"
                    "6786876786786878667856785768576856"
                    "7978789787987987978978978979789789"
                    "1324235436436132423423423412342342"
                    "4563246523643264523645326456234536"
                    "3475843683724928347832750752837807"
                    "6786876786786878667856785768576856"
                    "7978789787987987978978978979789789";
    int length = solve(s);
    printf("%d ", length);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
