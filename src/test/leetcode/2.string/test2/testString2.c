//
// Created by wangxn on 2018/5/13.
//

#include <stdbool.h>
#include "testString2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * 将字符串转换成int数字
 */
int string2Int(char* s){

    bool isPositive = (s[0] != '-');

    int retVal = 0;
    int i=0;
    int index = 1;
    int tmp;

    //  -2,147,483,648~2,147,483,647
    for (i = strlen(s) - 1; i>= (isPositive?0:1); i--, index*=10) {
        tmp = (s[i] - 0x30);
        if (index == 1000000000) {
            if(tmp > 2) {   //大于20,0000,0000（20亿）
              return 0;
            }
        }
        tmp = tmp * index;
        retVal += tmp;
    }
    if (!isPositive) {
        retVal = - retVal;
    }

//    if (isPositive && retVal <0){
//        retVal = 0;
//    } else if(!isPositive && retVal > 0){
//        retVal = 0;
//    }
    return retVal;
}

/**
 * 递归调用， 获得十进制int数的字符串
 * @param x  原始int数， 或者每次除以10之后的值
 * @param retString   待返回的字符串
 * @param index    当前int数的个位数的在字符串中的索引
 */
void num2str(int x, char *retString, int index){
    char retVal = 0;
    if(x>=10){
        retVal = 0x30 + x % 10;
        num2str(x / 10, retString, index - 1);
    } else{
        retVal = 0x30 + x;
    }

    retString[index] = retVal;
}

void getIntSize(int x, int* size){
    if (x >= 10) {
        *size = (*size) + 1;
        getIntSize(x / 10, size);
    }
}

/**
 * 有符号整数
 * 将10进制数转换成字符串
 * @param x
 */
char* int2String(int x){
    bool isPositive = (x>=0);
    int abX = abs(x);
    int i = 1;
    int sizeX = 1;   //10进制int数的位数


    getIntSize(abX, &sizeX);
    printf("size of abX is: %d\n", sizeX);
    if (!isPositive) {  //负数多一位符号标识
        sizeX++;
    }

    char* retVal = malloc((sizeX+1)* sizeof(char));  //分配一个字符串数组
    retVal[sizeX] = '\0';
    if(!isPositive){
        retVal[0] = '-';
    }

    num2str(abX, retVal, sizeX - 1);
    return retVal;
}

/**
 * 将字符串表示的int数 翻转依然得到字符串表示的int数
 * @param strX
 * @return
 */
char* reverseStr(char *strX){
    int len = strlen(strX);
    char* retVal = malloc((len + 1) * sizeof(char));
    bool isPositive = (strX[0] != '-');

    *(retVal + len) = '\0';
    if (!isPositive) {
        retVal[0] = '-';
    }

    if (isPositive) {  //正数
        for (int i = 0; i < len; ++i) {
            *(retVal+i) = *(strX + (len - i - 1));
        }
    } else{           //负数
        for (int i = 0, j = 1; i < len, j<len; ++i,++j) {
            *(retVal + j) = *(strX + (len - i - 1));
        }
    }

    return retVal;
}


int reverse(int x) {
    char* strX = int2String(x);
    char* reverseStrX = reverseStr(strX);
    int retVal = string2Int(reverseStrX);

    free(strX);
    free(reverseStrX);

    if (x * retVal <0){
        retVal = 0;
    }

    return retVal;
}

/**
 * 颠倒整数
给定一个 32 位有符号整数，将整数中的数字进行反转。
    示例 1:
        输入: 123
        输出: 321
     示例 2:
        输入: -123
        输出: -321
    示例 3:
        输入: 120
        输出: 21
    注意:
    假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−2e31,  2e31 − 1]。根据这个假设，如果反转后的整数溢出，则返回 0。
 */
void testString2(){
//    printf("%d revese to %d\n", 123, reverse(123));
//    printf("%d revese to %d\n", -123, reverse(-123));
//    printf("%d revese to %d\n", 145673456, reverse(145673456));
//    printf("%d revese to %d\n", 1534236469, reverse(1534236469));
//    printf("%d revese to %d\n", -2147483412, reverse(-2147483412));
    printf("%d revese to %d\n", 1534236469, reverse(1534236469));
}
