cmake_minimum_required(VERSION 3.9)
project(cciSolutionsC)

add_executable(demo src/demo/main.c)
set_target_properties(demo
    PROPERTIES
    C_STANDARD 99)