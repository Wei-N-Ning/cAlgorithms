add_library(cciValue cciValue.c cciValue.h)
target_include_directories(cciValue PUBLIC ../)

add_library(cciArrayList cciArrayList.c cciArrayList.h)
target_link_libraries(cciArrayList PUBLIC cciValue)
target_include_directories(cciArrayList PUBLIC ../)

add_library(cciList cciList.c cciList.h)
target_link_libraries(cciList PUBLIC cciValue)
target_include_directories(cciList PUBLIC ../)

#    cciStrings.c
#    cciStrings.h
#    cciHashTable.c
#    cciHashTable.h
#    cciList.c
#    cciList.h
#
#    cciBitArray.c
#    cciBitArray.h
#    cciValue.c
#    cciValue.h
#    cciBinaryTree.c
#    cciBinaryTree.h
#    cciStack.c
#    cciStack.h
#    cciQueue.c
#    cciQueue.h)
#target_include_directories(cciChapter1
#    PUBLIC
#    .)
