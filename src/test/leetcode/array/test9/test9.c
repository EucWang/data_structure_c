//
// Created by wangxn on 2018/5/10.
//

#include "test9.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void findTarget(int* nums, int left, int right, int target, int* targetIndex){
    if (left > right) {
        return;
    }
    for(int i=left; i<=right; i++){
        if (nums[i] == target){
            *targetIndex = i;
            break;
        }
    }
}

/**
 * 两数之和
    给定一个整数数组和一个目标值，找出数组中和为目标值的两个数。
    
    你可以假设每个输入只对应一种答案，且同样的元素不能被重复利用。
    
    示例:
        给定 nums = [2, 7, 11, 15], target = 9
        因为 nums[0] + nums[1] = 2 + 7 = 9
        所以返回 [0, 1]
 * @param nums 
 * @param numsSize 
 * @param target 
 * @return 
 */
int* twoSum(int* nums, int numsSize, int target){
    int otherTargetIndex = -1;

    for (int i = 0; i < numsSize; i++) {
        int otherTarget = target - nums[i];
        for(int j=i+1; j<numsSize; j++){
            if (nums[j] == otherTarget){
                otherTargetIndex = j;
                break;
            }
        }

        if (otherTargetIndex != -1) {
            int* retVal = malloc(2 * sizeof(int));
            retVal[0] = i;
            retVal[1] = otherTargetIndex;
            return retVal;
        }
    }
    return NULL;
}

void printAndTest9(int* arr, int arrLength, int target){
    int* targetArr = twoSum(arr, arrLength, target);
    printf("otherTarget is [%d, %d]\n", targetArr[0], targetArr[1]);
    free(targetArr);
}

void test9(){
    int arr[] = {2,7,11, 15};
    int arrLength = 4;
    int target = 9;
    printAndTest9(arr, arrLength, target);

    int arr1[] = {3,3};
    int arr1Length = 2;
    int target1 = 6;
    printAndTest9(arr1, arr1Length, target1);

    int arr2[] = {3,2,4,6};
    int arr2Length = 4;
    int target2 = 6;
    printAndTest9(arr2, arr2Length, target2);
}