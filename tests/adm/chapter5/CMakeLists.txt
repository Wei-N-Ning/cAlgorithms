
add_tinytest_executable(admSimpleGraphTests test_simpleGraph.c)
target_link_libraries(admSimpleGraphTests admChapter5)
add_test(NAME "ADM::Chapter5::SimpleGraphTests" COMMAND admSimpleGraphTests)

add_tinytest_executable(admSimpleGraphBFSTests test_bfs.c)
target_link_libraries(admSimpleGraphBFSTests admChapter5)
add_test(NAME "ADM::Chapter5::SimpleGraphBFSTests" COMMAND admSimpleGraphBFSTests)

add_executable(admSimpleGraphBFSProf test_bfs_prof.c)
target_link_libraries(admSimpleGraphBFSProf admChapter5)

add_tinytest_executable(admSimpleGraphDFSTests test_dfs.c)
target_link_libraries(admSimpleGraphDFSTests admChapter5)
add_test(NAME "ADM::Chapter5::SimpleGraphDFSTests" COMMAND admSimpleGraphDFSTests)


