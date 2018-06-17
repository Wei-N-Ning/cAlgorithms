
add_tinytest_executable(avlTreeByOthers
    test.cpp
)

target_sources(avlTreeByOthers
    PUBLIC
    avl_tree.h
    test.cpp
)

target_include_directories(avlTreeByOthers
    PUBLIC
    .
)

set_target_properties(avlTreeByOthers
    PROPERTIES
    CXX_STANDARD 11
)