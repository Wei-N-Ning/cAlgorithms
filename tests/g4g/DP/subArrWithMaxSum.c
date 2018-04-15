//
// Created by wein on 4/15/18.
//
// post
// https://www.geeksforgeeks.org/size-subarray-maximum-sum/
//
// observation shows that,
// if all elements in the array are 0, the sub array with max sum
// will contain each element only;
// therefore the base comparison is:
// sum[elem] < sum([elem + next_elem])
// if so, the sub array is extended to [elem, next_elem]
// otherwise it is reset to [next_elem]

// time complexity is n

void RunTinyTests();

void test_nothing() {
    ;
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}