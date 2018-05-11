//
// Created by wangxn on 2018/5/9.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../../lib/arr_tool/arrTool.h"

bool upgradeOneDigit(int* digits, int index) {
    int tmp = digits[index] + 1;
    if(tmp < 10){
        digits[index] = tmp;
        return false;
    }else {
        digits[index] = tmp%10;
        return true;
    }
}

int* newPulsArr(int* oldArr, int oldArrSize, int* newSize) {
    int* newArr = malloc((oldArrSize + 1) * sizeof(int));
    for(int i=0; i<oldArrSize; i++){
        newArr[i+1] = oldArr[i];
    }
    newArr[0] = 1;
    *newSize = oldArrSize + 1;
    return newArr;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne(int* digits, int digitsSize, int* returnSize) {
    int* retVal = malloc(digitsSize * sizeof(int));
    memcpy(retVal, digits, digitsSize * sizeof(int));
    *returnSize = digitsSize;
    int i;
    int* tmp;
    bool upgrade = false;
    for(i = digitsSize - 1; i>=0; i--){
        if (i == digitsSize - 1){
            upgrade = upgradeOneDigit(retVal, i);
            if(digitsSize == 1 && upgrade) {   //only one digit
                tmp = newPulsArr(retVal, digitsSize, returnSize);
                free(retVal);
                retVal = tmp;
            }
        } else {
            if (!upgrade) {
                break;
            }else{
                upgrade = upgradeOneDigit(retVal, i);

                if (upgrade && i == 0) {
                    tmp = newPulsArr(retVal, digitsSize, returnSize);
                    free(retVal);
                    retVal = tmp;
                }
            }
        }
    }
    return  retVal;
}


void printAndTest(int* arr, int arrSize, int* retArr, int* retSize){
    retArr = plusOne(arr, arrSize, retSize);
    printf("\nbefore arr is:\n");
    printfArr(arr, arrSize);
    printf("after plusOne, then arr2 is:\n");
    printfArr(retArr, *retSize);
    free(retArr);
}

/**
 * 加一
    给定一个非负整数组成的非空数组，在该数的基础上加一，返回一个新的数组。
    最高位数字存放在数组的首位， 数组中每个元素只存储一个数字。
    你可以假设除了整数 0 之外，这个整数不会以零开头。

    示例 1:
        输入: [1,2,3]
        输出: [1,2,4]
        解释: 输入数组表示数字 123。
    示例 2:
        输入: [4,3,2,1]
        输出: [4,3,2,2]
        解释: 输入数组表示数字 4321。
 */
void test7(){
    int arr[] = {1,2,3};
    int arr2[]  = {4,3,2,2};
    int arr3[] = {9, 9};
    int arr4[] = {9};
    int arr5[] = {0};

    int* retSize = malloc(sizeof(int));
    int* retArr;

    printAndTest(arr, 3, retArr, retSize);
    printAndTest(arr2, 4, retArr, retSize);
    printAndTest(arr3, 2, retArr, retSize);
    printAndTest(arr4, 1, retArr, retSize);
    printAndTest(arr5, 1, retArr, retSize);
}