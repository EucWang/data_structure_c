//
// Created by wangxn on 2018/5/21.
//

#include "testSort.h"
#include "../../../lib/arr_tool/arrTool.h"
#include <stdbool.h>
#include <stdio.h>


bool isBadVersion(int n) {
    if(n >= 1702766719){
        return true;
    } else{
        return false;
    }
}

void findBadVersion(int left, int right, int* result) {
    int index = left + ((right-left)/2);
    if(isBadVersion(index)) {
        if(index == 1 || !isBadVersion(index-1)) {
            *result = index;
            return;
        }

        findBadVersion(left, index-1, result);
    }else {
        if(isBadVersion(index+1)){
            *result = index+1;
            return;
        }
        findBadVersion(index+1, right, result);
    }
}

/**
 * 第一个错误的版本
    你是产品经理，目前正在带领一个团队开发新的产品。
    不幸的是，你的产品的最新版本没有通过质量检测。
    由于每个版本都是基于之前的版本开发的，所以错误的版本之后的所有版本都是错的。
    假设你有 n 个版本 [1, 2, ..., n]，你想找出导致之后所有版本出错的第一个错误的版本。
    你可以通过调用 bool isBadVersion(version) 接口来判断版本号 version 是否在单元测试中出错。
    实现一个函数来查找第一个错误的版本。
    你应该尽量减少对调用 API 的次数。
    示例:
        给定 n = 5
        调用 isBadVersion(3) -> false
        调用 isBadVersion(5) -> true
        调用 isBadVersion(4) -> true
        所以，4 是第一个错误的版本。
 * @param n
 * @return
 */
int firstBadVersion(int n) {
    if(isBadVersion(n)) {
        if(n == 1 || !isBadVersion(n-1)) {
            return n;
        }

        int retVal = -1;
        findBadVersion(1, n, &retVal);
        return retVal;
    }

    return n+1;
}


void moveRight(int* nums, int numsSize, int startIndex) {
    for (int i = numsSize - 1; i >= startIndex ; --i) {
        nums[i+1] = nums[i];
    }
}


/**
 * 合并两个有序数组
    给定两个有序整数数组 nums1 和 nums2，将 nums2 合并到 nums1 中，使得 num1 成为一个有序数组。
    说明:
        初始化 nums1 和 nums2 的元素数量分别为 m 和 n。
        你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
    示例:
        输入:
            nums1 = [1,2,3,0,0,0], m = 3
            nums2 = [2,5,6],       n = 3
        输出: [1,2,2,3,5,6]
 * @param nums1
 * @param nums1Size
 * @param nums2
 * @param nums2Size
 */
void testMergeTwoArr(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int i = 0, j = 0;
    while(1) {
        if(j >= nums2Size){
            break;
        }

        if (i >= nums1Size) {
            while (j < nums2Size) {
                nums1[i++] = nums2[j++];
            }
            break;
        }

        if(nums2[j] > nums1[i]){
            i++;
        } else if(nums2[j] <= nums1[i]) {
            moveRight(nums1, nums1Size, i);
            nums1Size++;
            nums1[i] = nums2[j];
            i++;
            j++;
        }
    }

}

void testMerge2Arr(){

    int nums1[] = {1,2,3,0,0,0};
    int nums2[] = {2,5,6};

    testMergeTwoArr(nums1, 3, nums2,3);

    printfArr(nums1, 6);
}


/**
 * 2126753390 versions
1702766719 is the first bad version.
 */
void testBadVersion(){

    printf("bad version start at %d\n", firstBadVersion(2126753390));
}

void testSort() {
    //testMerge2Arr();
    testBadVersion();
}