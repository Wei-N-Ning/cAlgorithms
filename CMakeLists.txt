cmake_minimum_required(VERSION 3.0)
project(cciSolutionsC)

enable_testing()

set(CMAKE_C_FLAGS "-Wno-implicit-function-declaration")

# test utils (tiny c unit)
add_library(tinyCUnit INTERFACE)
target_include_directories(tinyCUnit
    INTERFACE
    tests/utils)
include(tinyCUnit.cmake)

# ---- chapter 1 ----

add_library(cciChapter1
    src/chapter1/cciStrings.c
    src/chapter1/cciStrings.h
    src/chapter1/cciHashTable.c
    src/chapter1/cciHashTable.h
    src/chapter1/cciList.c
    src/chapter1/cciList.h
    src/chapter1/cciArrayList.c
    src/chapter1/cciArrayList.h
    src/chapter1/cciBitArray.c
    src/chapter1/cciBitArray.h
    src/chapter1/cciValue.c
    src/chapter1/cciValue.h
    src/chapter1/cciBinaryTree.c
    src/chapter1/cciBinaryTree.h
    src/chapter1/cciStack.c
    src/chapter1/cciStack.h
    src/chapter1/cciQueue.c
    src/chapter1/cciQueue.h)
target_include_directories(cciChapter1
    PUBLIC
    src/chapter1)

add_executable(cciStringsTests
    tests/chapter1/test_strings.c)
add_test(NAME "CCI::Chapter1::StringsTests" COMMAND cciStringsTests)
target_link_libraries(cciStringsTests cciChapter1 tinyCUnit)

#add_executable(cciHashTableTests
#    tests/chapter1/test_hashTable.c)
#add_test(NAME "CCI::Chapter1::HashTableTests" COMMAND cciHashTableTests)
#target_link_libraries(cciHashTableTests cciChapter1 tinyCUnit)

add_executable(cciListTests
    tests/chapter1/test_list.c)
target_link_libraries(cciListTests cciChapter1 tinyCUnit)
add_test(NAME "CCI::Chapter1::ListTests" COMMAND cciListTests)

add_executable(cciArrayListTests
    tests/chapter1/test_arrayList.c)
target_link_libraries(cciArrayListTests cciChapter1 tinyCUnit)
add_test(NAME "CCI::Chapter1::ArrayListTests" COMMAND cciArrayListTests)

add_executable(cciBitArrayTests
    tests/chapter1/test_bitArray.c)
target_link_libraries(cciBitArrayTests cciChapter1 tinyCUnit)
add_test(NAME "CCI::Chapter1::BitArrayTests" COMMAND cciBitArrayTests)

add_tinytest_executable(cciValueTests
    tests/chapter1/test_value.c)
target_link_libraries(cciValueTests cciChapter1)
add_test(NAME "CCI::Chapter1::Value" COMMAND cciValueTests)

add_tinytest_executable(cciBinaryTreeTests
    tests/chapter1/test_binaryTree.c)
target_link_libraries(cciBinaryTreeTests cciChapter1)
add_test(NAME "CCI::Chapter1::BinaryTree" COMMAND cciBinaryTreeTests)

add_executable(cciBinaryTreePerf
    tests/chapter1/test_binaryTree_perf.c)
target_link_libraries(cciBinaryTreePerf cciChapter1)
set_target_properties(cciBinaryTreePerf
    PROPERTIES
    CMAKE_C_FLAGS "-pg")

add_executable(cciArrayListPerf
    tests/chapter1/test_arrayList_perf.c)
target_link_libraries(cciArrayListPerf cciChapter1)
set_target_properties(cciArrayListPerf
    PROPERTIES
    CMAKE_C_FLAGS "-pg")

add_tinytest_executable(cciStackTests
    tests/chapter1/test_stack.c)
target_link_libraries(cciStackTests cciChapter1)

add_executable(cciStackPerf
    tests/chapter1/test_stack_perf.c)
target_link_libraries(cciStackPerf cciChapter1)
set_target_properties(cciStackPerf
    PROPERTIES
    CMAKE_C_FLAGS "-pg")

add_tinytest_executable(cciQueueTests
    tests/chapter1/test_queue.c)
target_link_libraries(cciQueueTests cciChapter1)

add_executable(cciQueuePerf
    tests/chapter1/test_queue_perf.c)
target_link_libraries(cciQueuePerf cciChapter1)
set_target_properties(cciQueuePerf
    PROPERTIES
    CMAKE_C_FLAGS "-pg")

############### adm

add_tinytest_executable(admHashStringTests
    tests/adm/chapter3/hashString.c)
add_test(NAME "ADM::Chapter3::HashString" COMMAND admHashStringTests)
