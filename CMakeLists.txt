cmake_minimum_required(VERSION 3.8)
project(cciSolutionsC)

enable_testing()

set(CMAKE_C_FLAGS "-Wno-implicit-function-declaration")

include(cmake/tinyCUnit.cmake)

# CCI
add_subdirectory(src/cci)
add_subdirectory(tests/cci)

# ADM
add_subdirectory(src/adm/utilities)
#add_subdirectory(src/adm/chapter4)
#add_subdirectory(src/adm/chapter5)
#add_subdirectory(src/adm/chapter8)
add_subdirectory(tests/adm/utilities)
#add_subdirectory(tests/adm/chapter3)
#add_subdirectory(tests/adm/chapter4)
#add_subdirectory(tests/adm/chapter5)
#add_subdirectory(tests/adm/chapter8)

# geeksforgeeks
#add_subdirectory(tests/g4g)

# general implementations
#add_subdirectory(tests/avl)
#add_subdirectory(tests/avl/others)