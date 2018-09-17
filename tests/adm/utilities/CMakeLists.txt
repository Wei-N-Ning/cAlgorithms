
add_tinytest_executable(admReadlineTest test_readline.c)
target_link_libraries(admReadlineTest admUtilities)
add_test(NAME "ADM::Utilities::Readline" COMMAND admReadlineTest)

add_tinytest_executable(admToStrTest test_toStr.c)
target_link_libraries(admToStrTest admUtilities)
add_test(NAME "ADM::Utilities::ToStr" COMMAND admToStrTest)
