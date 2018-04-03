
add_tinytest_executable(admReadlineTest test_readline.c)
target_link_libraries(admReadlineTest admUtilities)
add_test(NAME "ADM::Utilities::Readline" COMMAND admReadlineTest)
