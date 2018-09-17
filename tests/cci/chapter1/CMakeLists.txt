add_tinytest_executable(cciArrayListTests test_arrayList.c)
target_link_libraries(cciArrayListTests PUBLIC cciArrayList)
add_test(NAME "CCI::Chapter1::ArrayListTests" COMMAND cciArrayListTests)

add_executable(cciArrayListPerf test_arrayList_perf.c)
target_link_libraries(cciArrayListPerf PUBLIC cciArrayList)
add_test(NAME "CCI::Chapter1::ArrayListPerf" COMMAND cciArrayListPerf)

add_tinytest_executable(cciListTests test_list.c)
target_link_libraries(cciListTests cciList)
add_test(NAME "CCI::Chapter1::ListTests" COMMAND cciListTests)

add_executable(cciListPerf test_list_perf.c)
target_link_libraries(cciListPerf cciList)
add_test(NAME "CCI:Chapter1::ListPerf" COMMAND cciListPerf)


add_tinytest_executable(cciStackTests test_stack.c)
target_link_libraries(cciStackTests PUBLIC cciStack)
add_test(NAME "CCI::Chapter1::StackTest" COMMAND cciStackTests)

add_executable(cciStackPerf test_stack_perf.c)
target_link_libraries(cciStackPerf PUBLIC cciStack)
add_test(NAME "CCI::Chapter1::StackPerf" COMMAND cciStackPerf)

add_tinytest_executable(cciQueueTests test_queue.c)
target_link_libraries(cciQueueTests PUBLIC cciQueue)
add_test(NAME "CCI::Chapter1::QueueTests" COMMAND cciQueueTests)

add_executable(cciQueuePerf test_queue_perf.c)
target_link_libraries(cciQueuePerf PUBLIC cciQueue)
add_test(NAME "CCI::Chapter1::QueuePerf" COMMAND cciQueuePerf)

add_tinytest_executable(cciHashTableTests test_hashTable.c)
target_link_libraries(cciHashTableTests cciHashTable)
add_test(NAME "CCI::Chapter1::HashTableTests" COMMAND cciHashTableTests)

add_executable(cciHashTableMetrics test_hashTable_metrics.c)
target_link_libraries(cciHashTableMetrics PUBLIC cciHashTable)
add_test(NAME "CCI::Chapter1::HashTableMetrics" COMMAND cciHashTableMetrics)

add_executable(cciHashTablePerf test_hashTable_perf.c)
target_link_libraries(cciHashTablePerf PUBLIC cciHashTable)
add_test(NAME "CCI::Chapter1::HashTablePerf" COMMAND cciHashTablePerf)

add_tinytest_executable(cciBitArrayTest test_bitArray.c)
target_link_libraries(cciBitArrayTest PUBLIC cciBitArray)
add_test(NAME "CCI::Chapter1::BitArrayTest" COMMAND cciBitArrayTest)

#
#add_tinytest_executable(cciBinaryTreeTests
#    test_binaryTree.c)
#target_link_libraries(cciBinaryTreeTests cciChapter1)
#add_test(NAME "CCI::Chapter1::BinaryTree" COMMAND cciBinaryTreeTests)
#
#add_executable(cciBinaryTreePerf
#    test_binaryTree_perf.c)
#target_link_libraries(cciBinaryTreePerf cciChapter1)
#set_target_properties(cciBinaryTreePerf
#    PROPERTIES
#    CMAKE_C_FLAGS "-pg")
#

