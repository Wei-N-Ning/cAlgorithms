//
// Created by wein on 4/15/18.
//

/*
 * post:
 * https://www.geeksforgeeks.org/maximum-subarray-sum-excluding-certain-elements/
 *
 * arr A, B
 * alloc list of arr C
 * if head of A != tail of A
 *   take one element from the head of A, (head = 0)
 *   if elem in B
 *     save sub arr [old_head, head) in C, if not empty
 *     head++
 *   take on element from the tail of A, (tail = n - 1)
 *   if elem in B
 *     save sub arr (tail, old_tail] in C, if not empty
 *     tail--
 * find and return the longest arr in C
 *
 * complexity:
 * #1: construct internal binary search tree from B, mlogm
 * #2: for each elem in A:
 *     test elem's membership in B (nlogm)
 * #3: collect the result from C, constant
 *
 * mlogm + nlogm = (n + m) logm
 */

void RunTinyTests();

void test_nothing() {
    ;
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}