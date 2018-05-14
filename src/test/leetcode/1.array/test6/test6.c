#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test6.h"
#include "../../../../lib/arr_tool/arrTool.h"



/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {

    qsortArr(nums1, nums1Size);
    qsortArr(nums2, nums2Size);

    int retNumsSize = nums1Size>nums2Size?nums2Size:nums1Size;

    int *retNums = malloc(retNumsSize * sizeof(int));

    bool flag = true;
    int i = 0, j = 0, k = 0;
    int *tmpArr;
    int tmp;
    if (nums1Size > nums2Size) {  //保持第一个数组的长度小于等于第二个数组,
        tmpArr = nums1;    //交换两个数组,以及数组的长度
        nums1 = nums2;
        nums2 = tmpArr;

        tmp = nums1Size;
        nums1Size = nums2Size;
        nums2Size = tmp;

    }

    while(i < nums1Size && j < nums2Size) {
        if(flag) {
            while(i < nums1Size && j < nums2Size && nums1[i] > nums2[j]) {
                j++;
            }
            if(i < nums1Size && j < nums2Size) {
                if (nums1[i] == nums2[j]) {
                    retNums[k++] = nums1[i++];
                    j++;
                }else {
                    flag = false;
                    i++;
                }
            }
        } else {
            while(i < nums1Size && j < nums2Size && nums1[i] < nums2[j]) {
                i++;
            }
            if(i < nums1Size && j < nums2Size) {
                if (nums1[i] == nums2[j]) {
                    retNums[k++] = nums1[i++];
                    j++;
                }else {
                    flag = true;
                    j++;
                }
            }
        }
    }
    *returnSize = k;
    return retNums;
}

/**
 * 两个数组的交集 II
    给定两个数组，写一个方法来计算它们的交集。

    例如:
        给定 nums1 = [1, 2, 2, 1], nums2 = [2, 2], 返回 [2, 2].

    注意：

       输出结果中每个元素出现的次数，应与元素在两个数组中出现的次数一致。
       我们可以不考虑输出结果的顺序。
    跟进:

        如果给定的数组已经排好序呢？你将如何优化你的算法？
        如果 nums1 的大小比 nums2 小很多，哪种方法更优？
        如果nums2的元素存储在磁盘上，内存是有限的，你不能一次加载所有的元素到内存中，你该怎么办？
 */
void testArr6(){
//    int arr[] = {1, 2, 2, 1};
//    int arrLength = 4;
//
//    int arr1[] = {2, 2};
//    int arr2Length = 2;

    int arr[] = {1,2,3,4,5,6,1, 5};
    int arrLength = 8;
    int arr1[] = {3,5,2,7,1,6,5};
    int arr2Length = 7;

    int* retSize = malloc(sizeof(int));
    int* nums = intersect(arr, arrLength, arr1, arr2Length, retSize);
    printf("result arr is :\n");
    printfArr(nums, *retSize);
}
