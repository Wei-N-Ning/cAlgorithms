cmake_minimum_required(VERSION 3.0)
project(cciSolutionsC)

enable_testing()

set(CMAKE_C_FLAGS "-Wno-implicit-function-declaration")

include(cmake/tinyCUnit.cmake)

# CCI
add_subdirectory(src/chapter1)
add_subdirectory(tests/chapter1)
add_subdirectory(tests/chapter4)

# ADM
add_subdirectory(src/adm/chapter4)
add_subdirectory(src/adm/chapter5)
add_subdirectory(tests/adm/chapter3)
add_subdirectory(tests/adm/chapter4)
add_subdirectory(tests/adm/chapter5)