add_tinytest_executable(cciStringsTests
    test_strings.c)
add_test(NAME "CCI::Chapter1::StringsTests" COMMAND cciStringsTests)
target_link_libraries(cciStringsTests cciChapter1)

add_tinytest_executable(cciListTests
    test_list.c)
target_link_libraries(cciListTests cciChapter1)
add_test(NAME "CCI::Chapter1::ListTests" COMMAND cciListTests)

add_executable(cciListProf
    test_list_prof.c)
target_link_libraries(cciListProf cciChapter1)

add_tinytest_executable(cciArrayListTests
    test_arrayList.c)
target_link_libraries(cciArrayListTests cciChapter1)
add_test(NAME "CCI::Chapter1::ArrayListTests" COMMAND cciArrayListTests)

add_tinytest_executable(cciBitArrayTests
    test_bitArray.c)
target_link_libraries(cciBitArrayTests cciChapter1)
add_test(NAME "CCI::Chapter1::BitArrayTests" COMMAND cciBitArrayTests)

add_tinytest_executable(cciValueTests
    test_value.c)
target_link_libraries(cciValueTests cciChapter1)
add_test(NAME "CCI::Chapter1::Value" COMMAND cciValueTests)

add_tinytest_executable(cciBinaryTreeTests
    test_binaryTree.c)
target_link_libraries(cciBinaryTreeTests cciChapter1)
add_test(NAME "CCI::Chapter1::BinaryTree" COMMAND cciBinaryTreeTests)

add_executable(cciBinaryTreePerf
    test_binaryTree_perf.c)
target_link_libraries(cciBinaryTreePerf cciChapter1)
set_target_properties(cciBinaryTreePerf
    PROPERTIES
    CMAKE_C_FLAGS "-pg")

add_executable(cciArrayListPerf
    test_arrayList_perf.c)
target_link_libraries(cciArrayListPerf cciChapter1)
set_target_properties(cciArrayListPerf
    PROPERTIES
    CMAKE_C_FLAGS "-pg")

add_tinytest_executable(cciStackTests
    test_stack.c)
target_link_libraries(cciStackTests cciChapter1)
add_test(NAME "CCI::Chapter1::Stack" COMMAND cciStackTests)

add_executable(cciStackPerf
    test_stack_perf.c)
target_link_libraries(cciStackPerf cciChapter1)
set_target_properties(cciStackPerf
    PROPERTIES
    CMAKE_C_FLAGS "-pg")

add_tinytest_executable(cciQueueTests
    test_queue.c)
target_link_libraries(cciQueueTests cciChapter1)
add_test(NAME "CCI::Chapter1::Queue" COMMAND cciQueueTests)

add_executable(cciQueuePerf
    test_queue_perf.c)
target_link_libraries(cciQueuePerf cciChapter1)
set_target_properties(cciQueuePerf
    PROPERTIES
    CMAKE_C_FLAGS "-pg")

add_tinytest_executable(cciHashTableTests
    test_hashTable.c)
target_link_libraries(cciHashTableTests cciChapter1)
add_test(NAME "CCI::Chapter1::HashTableTests" COMMAND cciHashTableTests)

add_executable(cciHashTableMetrics
    test_hashTable_metrics.c)
target_link_libraries(cciHashTableMetrics cciChapter1)

add_executable(cciHashTablePerf
    test_hashTable_perf.c)
target_link_libraries(cciHashTablePerf cciChapter1)
