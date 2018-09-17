
add_tinytest_executable(chapter81TripleStep test_81tripleStep.c)
target_link_libraries(chapter81TripleStep cciArrayList m)
add_test(NAME "cci::Chapter8::8-1-TripleStep" COMMAND chapter81TripleStep)

#add_tinytest_executable(chapter83MagicIndex test_83magicIndex.c)
#target_link_libraries(chapter83MagicIndex admChapter4)
#add_test(NAME "cci::Chapter8::8-3-MagicIndex" COMMAND chapter83MagicIndex)

add_tinytest_executable(chapter84PowerSet test_84powerSet.c)
target_link_libraries(chapter84PowerSet cciHashTable cciArrayList)
add_test(NAME "cci::Chapter8::8-4-PowerSet" COMMAND chapter84PowerSet)
#
#add_tinytest_executable(chapter87PermutationsWODUps test_87permutationsWoDups.c)
#target_link_libraries(chapter87PermutationsWODUps admChapter4)
#
#add_tinytest_executable(chapter88PermutationsWDups test_88permutationsWDups.c)
