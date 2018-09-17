
add_library(admChapter8
    minEditDistsNaive.c
    minEditDistsNaive.h
    minEditDists.c
    minEditDists.h)
target_include_directories(admChapter8
    PUBLIC
    .
)
target_link_libraries(admChapter8
    PUBLIC
    cciList
    cciHashTable
    cciArrayList
    cciQueue
    cciStack)