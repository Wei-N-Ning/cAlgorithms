
add_tinytest_executable(commonAncestorTest test_commonAncestor.c)
target_link_libraries(commonAncestorTest cciBinaryTree)
add_test(NAME "CCI::Chapter4::4-6-Common-Ancestor" COMMAND commonAncestorTest)

add_tinytest_executable(isSubtreeTest test_isSubtree.c)
target_link_libraries(isSubtreeTest cciBinaryTree cciQueue)
add_test(NAME "CCI::Chapter4::4-7-Is-Subtree" COMMAND isSubtreeTest)

add_tinytest_executable(findPathsBySumTest test_findPathsBySum.c)
target_link_libraries(findPathsBySumTest cciArrayList cciQueue cciBinaryTree m)
add_test(NAME "CCI::Chapter4::4-8-Find-Paths-by-Sum" COMMAND findPathsBySumTest)

add_tinytest_executable(successorOfBSTNode test_successor.c)
target_link_libraries(successorOfBSTNode cciBinaryTree)
add_test(NAME "CCI::Chapter4::4-6-Successor" COMMAND successorOfBSTNode)