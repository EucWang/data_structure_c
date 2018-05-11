//
// Created by wangxn on 2018/5/10.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include "test10.h"


int stringToInt(char ch){
    if (ch > '0' && ch <= '9') {
        return ch - 48;
    }else{
        return 0;
    }
}

/**
 * 判断一个 9x9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可。
        数字 1-9 在每一行只能出现一次。
        数字 1-9 在每一列只能出现一次。
        数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。

        一个有效的数独（部分已被填充）不一定是可解的。
        只需要根据以上规则，验证已经填入的数字是否有效即可。
        给定数独序列只包含数字 1-9 和字符 '.' 。
        给定数独永远是 9x9 形式的。
 * @param board
 * @param boardRowSize
 * @param boardColSize
 * @return
 */
bool isValidSudoku(char** board, int boardRowSize, int boardColSize) {
    bool* validArr = malloc(boardRowSize * sizeof(bool));

    for(int i=0; i<boardRowSize; i++){
        memset(validArr, false, boardRowSize * sizeof(bool));
        for (int j = 0; j < boardColSize; j++) {
            int item = stringToInt(board[i][j]);
            if(item != 0) {
                if(!validArr[item - 1]){
                    validArr[item - 1] = true;
                }else{
                    printf("scan row, then duplicate at board[%d][%d]\n", i, j);
                    free(validArr);
                    return false;
                }
            }
        }
    }

    for(int i=0; i<boardColSize; i++){
        memset(validArr, false, boardRowSize * sizeof(bool));
        for (int j = 0; j < boardRowSize; j++) {
            int item = stringToInt(board[j][i]);
            if(item != 0) {
                if(!validArr[item - 1]){
                    validArr[item - 1] = true;
                }else{
                    printf("scan col, then duplicate at board[%d][%d]\n", j, i);
                    free(validArr);
                    return false;
                }
            }
        }
    }

    for(int i=0; i<3; i++){
        for(int j =0; j<3; j++){
            memset(validArr, false, boardRowSize * sizeof(bool));
            for (int k = 0; k < 9; k++) {
                int item = stringToInt(board[i*3 + k/3][j*3 + k%3]);
                if(item != 0) {
                    if(!validArr[item - 1]){
                        validArr[item - 1] = true;
                    }else{
                        printf("scan cell, then duplicate at board[%d][%d]\n", j, i);
                        free(validArr);
                        return false;
                    }
                }
            }
        }
    }

    free(validArr);
    return true;
}

void testSudo1(){
    char a1[] = {'5', '3', '.', '.','7','.','.','.','.'};
    char a2[] = {'6','.','.','1','9','5','.','.','.'};
    char a3[] = {'.','9','8','.','.','.','.','6','.'};
    char a4[] = {'8','.','.','.','6','.','.','.','3'};
    char a5[] = {'4','.','.','8','.','3','.','.','1'};
    char a6[] = {'7','.','.','.','2','.','.','.','6'};
    char a7[] = {'.','6','.','.','.','.','2','8','.'};
    char a8[] = {'.','.','.','4','1','9','.','.','5'};
    char a9[] = {'.','.','.','.','8','.','.','7','9'};
    char* arr[] = {a1, a2, a3, a4, a5, a6, a7, a8, a9};

    bool retVal = isValidSudoku(arr, 9, 9);
    printf("result value is %d\n", retVal);
}

void testSudo2(){

    char a1[] =  {'8','3','.','.','7','.','.','.','.'};
    char a2[] ={'6','.','.','1','9','5','.','.','.'};
    char a3[] = {'.','9','8','.','.','.','.','6','.'};
    char a4[] = {'8','.','.','.','6','.','.','.','3'};
    char a5[] ={'4','.','.','8','.','3','.','.','1'};
    char a6[] ={'7','.','.','.','2','.','.','.','6'};
    char a7[] =  {'.','6','.','.','.','.','2','8','.'};
    char a8[] ={'.','.','.','4','1','9','.','.','5'};
    char a9[] ={'.','.','.','.','8','.','.','7','9'};

    char* arr[] = {a1, a2, a3, a4, a5, a6, a7, a8, a9};

    bool retVal = isValidSudoku(arr, 9, 9);
    printf("result value is %d\n", retVal);
}

void test10(){
    testSudo1();
    testSudo2();
}
