#include <time.h>
#include <stdlib.h>
#include <stdio.h>


/**
 * 创建一个二维数组，
 * @param size 数组单个元素的内存大小
 * @param row  行数
 * @param col 列数
 * 
 */ 
void ** createArr2(int size, int row, int col){

    void ** retVal = malloc(sizeof(void *) * row);

    for (int i = 0; i < col; i++) {
        void * tmp = malloc(size * col);
        retVal[i] = tmp;
        memset(tmp, 0, sizeof(tmp));
    }
    
    return retVal;
}

/**
 * 释放上面创建的二维数组的空间
 *释放 由 createArr2()函数创建的二维数组的内存空间
 * @param arr2 , 三重指针，指向二维数组，
 * return void  使用完之后，二维数组的指针会被置为NULL
 */
void freeArr2(void *** arr2p, int row) {
    void ** arr2 = *arr2p;
    for (size_t i = 0; i < row; i++)    {
        free(arr2[i]);
    }
    free(arr2);
    *arr2p = NULL;
}


/**
 * 打印数组
 */ 
void printfArr(int* nums, int numsSize){
    printf("[");
    for(int i=0; i<numsSize; i++){
        printf("%d ", nums[i]);
    }
    printf("]\n");
}

/**
 * 控制台输出二维数组
 * @param nums
 * @param numsRow
 * @param numsCol
 */
void printfArr2(int** nums, int numsRow, int numsCol){
    printf("[\n");
    for (int i = 0; i < numsRow; ++i) {
        printf("\t");
        printfArr(nums[i], numsCol);
    }
    printf("\n]");
}

void _qsort(int* nums, int left, int right){
    // printf("srotArr3..\n");
    if(left >= right){
        return;  //递归终止条件
    }

    srand((int)time(0));
    int randLocIndex = rand() % (right - left) + left;  //获得一个随机位置
    int tmp;

    //交换随机位置和最左边位置的值
    tmp = nums[left];
    nums[left] = nums[randLocIndex];
    nums[randLocIndex] = tmp;

    int i,j,key;
    key = nums[left];  //分治的比较值
    i = left;
    j = right;

    while(i<j){

        while(i<j && nums[j]>=key){  //右边找到一个小于key的索引位置
            j--;
        }

        while(i<j && nums[i]<=key){  //左边找到一个大于key 的索引位置
            i++;
        }

        if(i<j) {             //交换两个位置的值
            tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
        }
    }

    nums[left] = nums[i];
    nums[i] = key;
    // printf("sort a time, key value is %d", key);
    // printfArr(nums,13);

    //经过上面一轮循环, 右边的值全部大于左边的值

    //然后分两块区域, 继续进行排序
    _qsort(nums, left, i - 1);
    _qsort(nums, i+1, right);
}
/**
 * 快速排序
 */
void qsortArr(int* nums, int numsSize){
    _qsort(nums, 0, numsSize - 1);
}
