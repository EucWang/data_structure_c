
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

#ifdef _cplusplus
}
#endif

#endif //C_ARRAY_TOOL_H
