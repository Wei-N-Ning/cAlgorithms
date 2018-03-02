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
    src/chapter1/cciHashTable.h)
target_include_directories(cciChapter1
    PUBLIC
    src/chapter1)
add_executable(cciStringsTests
    tests/chapter1/test_strings.c)
add_test(NAME "CCI Chapter1 Strings Tests" COMMAND cciStringsTests)
target_link_libraries(cciStringsTests cciChapter1 tinyCUnit)
add_executable(cciHashTableTests
    tests/chapter1/test_hashTable.c)
add_test(NAME "CCI Chapter1 HashTable Tests" COMMAND cciHashTableTests)
target_link_libraries(cciHashTableTests cciChapter1 tinyCUnit)
