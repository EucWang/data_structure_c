
#ifndef C_ARRAY_TOOL_H
#define C_ARRAY_TOOL_H

#ifdef _cplusplus
extern "C"{
#endif

/**
 * 快速排序
 */ 
void qsortArr(int* nums, int numsSize);

/**
 * 控制台打印数组
 */ 
void printfArr(int* nums, int numsSize);


/**
 * 控制台输出二维数组
 * @param nums
 * @param numsRow
 * @param numsCol
 */
void printfArr2(int** nums, int numsRow, int numsCol);


/**
 *释放 由 createArr2()函数创建的二维数组的内存空间
 * @param arr2 , 三重指针，指向二维数组，
 * return void  使用完之后，二维数组的指针会被置为NULL
 */
void freeArr2(void *** arr2, int row, int col);


/**
 * 创建一个二维数组，
 * @param size 数组单个元素的内存大小
 * @param row  行数
 * @param col 列数
 * 
 */ 
void ** createArr2(int size, int row, int col);

#ifdef _cplusplus
}
#endif

#endif //C_ARRAY_TOOL_H
