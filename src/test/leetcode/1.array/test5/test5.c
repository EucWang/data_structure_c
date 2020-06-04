#include <stdio.h>
#include <stdlib.h>
 
void printfArr(int* nums, int numsSize){
    printf("[");
    for(int i=0; i<numsSize; i++){
        printf("%d ", nums[i]);
    }
    printf("]\n");
}

void _qsort(int* nums, int left, int right) {
    if(left >= right){return;}
    
    int tmp;
    int randLocIndex = rand() % (right - left) + left;
    
    tmp = nums[left];
    nums[left] = nums[randLocIndex];
    nums[randLocIndex] = tmp;
    
    int i;
    int j;
    int key;
    key = nums[left];
    i = left;
    j = right;
    
    while(i<j) {
        while(i<j && nums[j] >= key){j--;}
        while(i<j && nums[i] <= key){i++;}
        if(i<j){
            tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
        }
    }
    
    nums[left] = nums[i];
    nums[i] = key;

    _qsort(nums, i+1, right);
    _qsort(nums, left, i-1);
}

int singleNumber(int* nums, int numsSize) {
    _qsort(nums, 0, numsSize-1);
    int i = 0;
    while(i<numsSize){
        if(nums[i] == nums[i+1]){
            i = i + 2;
        }else{
            return nums[i];
        }
    }
    return 95535;
}

/**
 * 只出现一次的数字
    给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
    说明：
    你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？
    示例 1:
        输入: [2,2,1]
        输出: 1
    示例 2:
        输入: [4,1,2,1,2]
        输出: 4
 */ 
int main(){

    int arr[] ={2,2,1};
    int arr2[] = {4,1,2,1,2};

    printf("arr signle number is :%d\n", singleNumber(arr, 3));
    printf("arr2 signle number is : %d\n", singleNumber(arr2, 5));
}
