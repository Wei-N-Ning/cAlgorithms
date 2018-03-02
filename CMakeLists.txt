cmake_minimum_required(VERSION 3.0)
project(cciSolutionsC)

enable_testing()

# test utils (tiny c unit)
add_library(tinyCUnit INTERFACE)
target_include_directories(tinyCUnit
    INTERFACE
    tests/utils)

# chapter 1
add_library(cciChapter1
    src/chapter1/cciStrings.c
    src/chapter1/cciStrings.h)
target_include_directories(cciChapter1
    PUBLIC
    src/chapter1)
add_executable(cciChapter1Tests
    tests/chapter1/test_strings.c)
add_test(NAME "CCI Chapter1 Tests" COMMAND cciChapter1Tests)
target_link_libraries(cciChapter1Tests cciChapter1 tinyCUnit)

