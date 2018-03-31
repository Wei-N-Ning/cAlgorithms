
add_tinytest_executable(admHeapTest test_heap.c)
target_link_libraries(admHeapTest admChapter4)
add_test(NAME "ADM::Chapter4::HeapTest" COMMAND admHeapTest)

add_executable(admHeapProf test_heap_prof.c)
target_link_libraries(admHeapProf admChapter4)
