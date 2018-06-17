add_tinytest_executable(avlTreeTest test_avlTree.c)
target_link_libraries(avlTreeTest cciChapter1)
add_test(NAME "AVL::AVL Tree Test" COMMAND avlTreeTest)
