
add_tinytest_executable(minimalEditing test_minEditing.c)
target_link_libraries(minimalEditing admChapter8)
add_test(NAME "ADM::Chapter8::MinimalEditing" COMMAND minimalEditing)