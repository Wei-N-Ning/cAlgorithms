//
// Created by wein on 4/15/18.
//

// post:
// https://www.geeksforgeeks.org/longest-common-substring-space-optimized-dp-solution/
//
// given str X, Y
// ...xsxssdxxsxsxx
// ...nnnnyyysxsy
// struct Record {
//   int xIdx;
//   int yIdx;
//   size_t length;
//   char sequence[n];  // n = sizeof(X)
// }
// maxr = new record (previous)
// curr = new record
// for xIdx, chr in X
//    yIdx = (if chr not in Y)
//       if curr.length > maxr.length
//         maxr = curr
//       curr = new record
//       continue
//    add record to curr (xIdx, yIdx, length + 1, sequence[length] = chr)
// last comparison between maxr and curr

void RunTinyTests();

void test_nothing() {
    ;
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
