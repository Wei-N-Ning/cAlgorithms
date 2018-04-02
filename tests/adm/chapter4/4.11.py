#!/usr/bin/env python


def swap(arr, lhs, rhs):
    if lhs == rhs:
        return
    tmp = arr[lhs]
    arr[lhs] = arr[rhs]
    arr[rhs] = tmp
    

def main(arr, pivotIndex):
    pivotValue = arr[pivotIndex]
    leftIndex = -1;
    for i in xrange(len(arr)):
        if arr[i] <= pivotValue:
            leftIndex += 1
            swap(arr, i, leftIndex)
    if leftIndex < len(arr) - 1:
        swap(arr, leftIndex + 1, pivotIndex)
    return arr, leftIndex + 1
    

if __name__ == '__main__':
    sut = [0, 0, 0, 1, 1, 1, 2, 2, 1, 1, 4, 5, 9, 2, 3, 1]
    sut, pivotIndex = main(sut, len(sut) - 1)
    print sut, pivotIndex
    lpart = sut[: pivotIndex]
    rpart = sut[pivotIndex: ]
    print lpart, rpart
    lpart, _ = main(lpart, len(lpart) - 1)
    rpart, _ = main(rpart, len(rpart) - 1)
    print lpart, rpart
    
