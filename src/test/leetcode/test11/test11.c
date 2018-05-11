//
// Created by wangxn on 2018/5/10.
//

#include <stdlib.h>
#include <stdio.h>
#include "test11.h"
#include "../../../lib/arr_tool/arrTool.h"


/**
 * 旋转图像
    给定一个 n × n 的二维矩阵表示一个图像。
    将图像顺时针旋转 90 度。

    说明：
        你必须在原地旋转图像，这意味着你需要直接修改输入的二维矩阵。
        请不要使用另一个矩阵来旋转图像。
 * @param matrix
 * @param matrixRowSize
 * @param matrixColSizes
 */
void rotate(int** matrix, int matrixRowSize, int *matrixColSizes) {

    int* tmp = malloc((matrixRowSize - 1) * sizeof(int));
    int i = 0, j = 0, k = 0;

    for (int i = 0; i < (matrixRowSize / 2); i++) {
        int circleSize = matrixRowSize - 1 - i * 2;

        for (int j = i+1; j < matrixRowSize - i; j++) {
            tmp[j-i-1] = matrix[i][j];   //缓存第一行,除了第一个元素
        }

        //第一列 复制到第一行, 除了最后一个元素
//        for(int j = matrixRowSize - i - 1; j>=i; j--){
        for(int j = i, k = matrixRowSize - i - 1;k>i, j< matrixRowSize - i - 1; j++, k--){
            matrix[i][k] = matrix[j][i];
        }

        //最后一行复制到第一列, 除了最后一个元素
        for (int j = i; j < matrixRowSize - i - 1; j++) {
            matrix[j][i] = matrix[matrixRowSize - i - 1][j];
        }

        //最后一列复制到最后一行, 除了最上面的元素
        for (int j = i, k = matrixRowSize - i - 1; j < matrixRowSize - i - 1, k>i; j++, k--) {
            matrix[matrixRowSize - i - 1][j] = matrix[k][matrixRowSize - i - 1];
        }

        //缓存的第一行复制到最后一列,
        for (int j = 0, k = i + 1; j < circleSize; j++, k++) {
            matrix[k][matrixRowSize - i - 1] = tmp[j];
        }

        printfArr2(matrix, matrixRowSize, matrixRowSize);
    }

    free(tmp);
}

void printAndTest11(){

    int arr1[] = {1,2,3};
    int arr2[] = {4,5,6};
    int arr3[] = {7,8,9};
    int* arr[] = {arr1,arr2, arr3};
    int colsSize = 0;
    printf("before rotate arr:\n");
    printfArr2(arr, 3, 3);
    rotate(arr,3,&colsSize);
    printf("\nafter rotate arr:\n");
    printfArr2(arr, 3,3);
}
void printAndTest112(){

    int arr1[] = {1,2,3,4};
    int arr2[] = {5,6,7,8};
    int arr3[] = {9,10,11,12};
    int arr4[] = {13,14,15, 16};
    int* arr[] = {arr1,arr2, arr3, arr4};
    int colsSize = 0;
    printf("before rotate arr:\n");
    printfArr2(arr, 4, 4);
    rotate(arr,4,&colsSize);
    printf("\nafter rotate arr:\n");
    printfArr2(arr, 4,4);
}

void printAndTest113(){

    int arr1[] = {1,2,3,4,5};
    int arr2[] = {6,7,8,9,10};
    int arr3[] = {11,12,13,14,15};
    int arr4[] = {16,17,18,19,20};
    int arr5[] = {21,22,23,24,25};

    int* arr[] = {arr1,arr2, arr3, arr4,arr5};
    int colsSize = 0;
    printf("before rotate arr:\n");
    printfArr2(arr, 5, 5);
    rotate(arr,5,&colsSize);
    printf("\nafter rotate arr:\n");
    printfArr2(arr, 5,5);
}

void printAndTest114(){

    int arr1[] = {1, 2, 3, 4, 5, 6};
    int arr2[] = {7, 8, 9, 10,11,12};
    int arr3[] = {13,14,15,16,17,18};

    int arr4[] = {19,20,21,22,23,24};
    int arr5[] = {25,26,27,28,29,30};
    int arr6[] = {31,32,33,34,35,36};

    int* arr[] = {arr1,arr2, arr3, arr4,arr5,arr6};
    int colsSize = 0;
    printf("before rotate arr:\n");
    printfArr2(arr, 6, 6);
    rotate(arr,6,&colsSize);
    printf("\nafter rotate arr:\n");
    printfArr2(arr, 6,6);
}

void test11(){
    printAndTest114();
}
