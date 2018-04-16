//
// Created by wein on 4/15/18.
//
// post
// https://www.geeksforgeeks.org/size-subarray-maximum-sum/
//
// max_sum = 0
// record = 0
// for elem in arr
//    max_sum += elem
//    if max_sum > record
//       record = max_sum
//    else
//       max_sum = 0

// time complexity is n

void RunTinyTests();

void test_nothing() {
    ;
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}