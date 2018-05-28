
add_tinytest_executable(minimalEditingNaive test_minEditingNaive.c)
target_link_libraries(minimalEditingNaive admChapter8)
add_test(NAME "ADM::Chapter8::MinimalEditingNaive" COMMAND minimalEditingNaive)

add_tinytest_executable(minimalEditing test_minEditing.c)
target_link_libraries(minimalEditing admChapter8)
add_test(NAME "ADM::Chapter8::MinimalEditing" COMMAND minimalEditing)

add_tinytest_executable(substringMatching test_substringMatching.c)
target_link_libraries(substringMatching admChapter8)
add_test(
    NAME
    "ADM::Chapter8::SubstringMatching"
    COMMAND
    substringMatching
)

add_tinytest_executable(longestCommSub test_longestCommSub.c)
target_link_libraries(longestCommSub admChapter8)
add_test(
    NAME
    "ADM::Chapter8::LongestCommSub"
    COMMAND
    longestCommSub
)

# 2nd revision
add_tinytest_executable(minEditingTestR test_r_minEditing.c)
add_test(
    NAME "ADM::Chapter8::MinEditing-2nd-Revision"
    COMMAND minEditingTestR
)

# 2nd revision
add_tinytest_executable(linearPartitionR test_r_linearPartition.c)
add_test(
    NAME "ADM::Chapter8::LinearPartition-2nd-Revision"
    COMMAND linearPartitionR
)

# 2nd revision (using min editing 2nd revision)
add_tinytest_executable(longestIncreasingSequenceR test_r_longestIncreasingSeq.c)
add_test(
    NAME "ADM::Chapter8::LongestIncreasingSequence-2nd-Revision"
    COMMAND longestIncreasingSequenceR
)