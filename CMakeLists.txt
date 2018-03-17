cmake_minimum_required(VERSION 3.0)
project(cciSolutionsC)

enable_testing()

# test utils (tiny c unit)
add_library(tinyCUnit INTERFACE)
target_include_directories(tinyCUnit
    INTERFACE
    tests/utils)


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
    src/chapter1/cciBitArray.h)
target_include_directories(cciChapter1
    PUBLIC
    src/chapter1)

add_executable(cciStringsTests
    tests/chapter1/test_strings.c)
add_test(NAME "CCI::Chapter1::StringsTests" COMMAND cciStringsTests)
target_link_libraries(cciStringsTests cciChapter1 tinyCUnit)

add_executable(cciHashTableTests
    tests/chapter1/test_hashTable.c)
add_test(NAME "CCI::Chapter1::HashTableTests" COMMAND cciHashTableTests)
target_link_libraries(cciHashTableTests cciChapter1 tinyCUnit)

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


# ---- chapter N ----
include(tinyCUnit.cmake)
add_tinytest_executable(test_routeBetweenNodes
    tests/chapterN/test_routeBetweenNodes.c)
target_link_libraries(test_routeBetweenNodes cciChapter1)

add_tinytest_executable(test_paintFill
    tests/chapterN/test_paintFill.c)

add_tinytest_executable(test_buildOrder
    tests/chapterN/test_buildOrder.c)
