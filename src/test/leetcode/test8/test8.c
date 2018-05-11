//
// Created by wangxn on 2018/5/10.
//

#include <stdio.h>
#include "../../../lib/arr_tool/arrTool.h"

/**
 * index of nums is 0, swap it with index+1
 * @param nums
 * @param index
 * @return
 */
void swapItemWithZero(int* nums, int index) {
        nums[index] = nums[index+1];
        nums[index+1] = 0;
}

void moveZeros(int* nums, int numsSize){
    if (numsSize <= 1){
        return;
    }
    int i = numsSize - 1;
    int j;
    int numsOfZero = 0;
    while (i >= 0) {
        if (nums[i] == 0) {
            numsOfZero++;
            if(i != numsSize -1){
                j = i;
                while(j < numsSize - numsOfZero){
                    swapItemWithZero(nums, j++);
                }
            }
        }
        i--;
    }
}

void printAndTest8(int* arr, int arrLength){

    printf("\nbefore move zero, arr is:\n");
    printfArr(arr, arrLength);
    moveZeros(arr, arrLength);
    printf("after move zero, arr is:\n");
    printfArr(arr, arrLength);
}

void test8(){
    int arr[] = {0, 1, 0, 3, 12};
    int arrLength = 5;
    int arr1[] = {0, 0};
    int arr1Length = 2;
    int arr2[] = {0};
    int arr2Length = 1;

    printAndTest8(arr, arrLength);
    printAndTest8(arr1, arr1Length);
    printAndTest8(arr2, arr2Length);
}
