//
// Created by wangxn on 2018/6/4.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include "testMathIssue.h"

#define FIZZ "Fizz"
#define BUZZ "Buzz"
#define FizzBuzz "FizzBuzz"

char* unsignedInt2Str(int n) {
    int length = 1;
    int tmp = n;
    while ((tmp / 10) != 0) {
        tmp = tmp/10;
        length++;
    }
    char* str = malloc((length + 1) * sizeof(char));
    memset(str, 0, (length + 1) * sizeof(char));
    int i = length - 1;
    tmp = n;
    while (i >= 0) {
        str[i] = '0' + (tmp%10);     
        if ((tmp / 10) == 0) {
            break;
        }
        tmp = tmp / 10;    
        i--;
    }
    return str;
}

/**
 * Fizz Buzz
写一个程序，输出从 1 到 n 数字的字符串表示。
    1. 如果 n 是3的倍数，输出“Fizz”；
    2. 如果 n 是5的倍数，输出“Buzz”；
    3.如果 n 同时是3和5的倍数，输出 “FizzBuzz”。
示例：
    n = 15,
    返回:    [   "1",
                "2",
                "Fizz",
                "4",
                "Buzz",
                "Fizz",
                "7",
                "8",
                "Fizz",
                "Buzz",
                "11",
                "Fizz",
                "13",
                "14",
                "FizzBuzz"]
 */
char** fizzBuzz(int n, int* returnSize){
    *returnSize = n;
    char** retVal = malloc(n * sizeof(char*));
    if (retVal == NULL) {
        return NULL;
    }

    for (int i = 1; i <= n; ++i) {
        if (i % 3 == 0 && i % 5 == 0) {
            retVal[i-1] = FizzBuzz;
        } else if (i % 3 == 0 && i % 5 != 0) {
            retVal[i-1] = FIZZ;
        } else if (i % 3 != 0 && i % 5 == 0) {
            retVal[i-1] = BUZZ;
        } else {
            retVal[i-1] = unsignedInt2Str(i);
        }
    }

    return retVal;
}

void testMathIssue(){

    int retSize = 0;
    char** retStr = fizzBuzz(15, &retSize);
    printf("retSize is %d\n", retSize);
    for (int i = 0; i < retSize; i++) {
        printf("%s\t", retStr[i]);
    }

//    char *str0 = unsignedInt2Str(0);
//    printf("str0 is %s\n", str0);
//    char *str1 = unsignedInt2Str(1);
//    printf("str1 is %s\n", str1);
//    char *str11 = unsignedInt2Str(11);
//    printf("str11 is %s\n", str11);
//    char *str132 = unsignedInt2Str(132);
//    printf("str132 is %s\n", str132);
//    char *str231 = unsignedInt2Str(231);
//    printf("str231 is %s\n", str231);
//    char *str901 = unsignedInt2Str(901);
//    printf("str901 is %s\n", str901);
//    char *str210 = unsignedInt2Str(210);
//    printf("str210 is %s\n", str210);

}