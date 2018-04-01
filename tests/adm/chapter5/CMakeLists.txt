
add_tinytest_executable(admSimpleGraphTests test_simpleGraph.c)
target_link_libraries(admSimpleGraphTests admChapter5)
add_test(NAME "ADM::Chapter5::SimpleGraphTests" COMMAND admSimpleGraphTests)
