add_library(admChapter5
    admSimpleGraph.c
    admSimpleGraph.h)
target_include_directories(admChapter5
    PUBLIC
    .)

target_link_libraries(admChapter5
    PUBLIC
    admUtilities
    admChapter4)
