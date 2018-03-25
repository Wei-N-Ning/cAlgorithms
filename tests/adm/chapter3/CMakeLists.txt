add_tinytest_executable(admHashStringTests
    hashString.c)
add_test(NAME "ADM::Chapter3::HashString" COMMAND admHashStringTests)