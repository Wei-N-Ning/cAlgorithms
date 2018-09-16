add_library(cciValue cciValue.c cciValue.h)
target_include_directories(cciValue PUBLIC ../)

add_library(cciArrayList cciArrayList.c cciArrayList.h)
target_link_libraries(cciArrayList PUBLIC cciValue)
target_include_directories(cciArrayList PUBLIC ../)

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
