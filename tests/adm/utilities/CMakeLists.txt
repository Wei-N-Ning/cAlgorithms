
add_tinytest_executable(admReadlineTest test_readline.c)
target_link_libraries(admReadlineTest admUtilities cciChapter1)
add_test(NAME "ADM::Utilities::Readline" COMMAND admReadlineTest)
