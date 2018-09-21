
add_tinytest_executable(longestSubarr DP/longestSubarr.c)
add_test(NAME "GeeksForGeeks::DP::LongestSubarr" COMMAND longestSubarr)

add_tinytest_executable(longestCommonSubstr DP/longestCommonSubstr.c)
add_test(NAME "GeeksForGeeks::DP::LongestCommonSubStr" COMMAND longestCommonSubstr)

add_tinytest_executable(minSumOfPath DP/minSumOfPath.c)
add_test(NAME "GeeksForGeeks::DP::MinimumSumOfPathInTriangle" COMMAND minSumOfPath)

add_tinytest_executable(subArrWithMaxSum DP/subArrWithMaxSum.c)
add_test(NAME "GeeksForGeeks::DP::SubArrayWithMaxSum" COMMAND subArrWithMaxSum)

add_tinytest_executable(minJumpsToReachEnd DP/minJumpsToReachEnd.c)
add_test(NAME "GeeksForGeeks::DP::MinimumNumberOfJumpsToReachEnd" COMMAND minJumpsToReachEnd)

add_tinytest_executable(palindrome DP/palindrome.c)
add_test(NAME "GeeksForGeeks::DP::Palindrome" COMMAND palindrome)