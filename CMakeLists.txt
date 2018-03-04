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
    src/chapter1/cciArrayList.h)
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

