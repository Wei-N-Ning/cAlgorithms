add_library(admUtilities
    admReadline.c
    admReadline.h
    admToStr.c
    admToStr.h)
target_include_directories(admUtilities
    PUBLIC
    .)