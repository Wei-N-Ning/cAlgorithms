
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