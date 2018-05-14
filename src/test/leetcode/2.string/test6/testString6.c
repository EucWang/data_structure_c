//
// Created by wangxn on 2018/5/14.
//

#include "testString6.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * 实现 atoi，将字符串转为整数。
    在找到第一个非空字符之前，需要移除掉字符串中的空格字符。
    如果第一个非空字符是正号或负号，选取该符号，并将其与后面尽可能多的连续的数字组合起来，这部分字符即为整数的值。
    如果第一个非空字符是数字，则直接将其与之后连续的数字字符组合起来，形成整数。
    字符串可以在形成整数的字符后面包括多余的字符，这些字符可以被忽略，它们对于函数没有影响。
    当字符串中的第一个非空字符序列不是个有效的整数；或字符串为空；或字符串仅包含空白字符时，则不进行转换。
    若函数不能执行有效的转换，返回 0。
    说明：
    假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−231,  231 − 1]。
    如果数值超过可表示的范围，
    则返回  INT_MAX (231 − 1) 或 INT_MIN (−231) 。
 * @param str
 * @return
 */
int myAtoi(char* str) {
    if (str == NULL) {
        return 0;
    }
    int len = strlen(str);

    int iStart = -1;
    int iEnd = len - 1;
    int i = 0;
    while (i < len) {
        if (iStart < 0){
            if (isdigit(str[i]) ||  str[i]=='-') {
                iStart = i;
            } else if (str[i]=='+'){
                iStart = i+1;
            } else if (!isspace(str[i])){
                    return 0;
            }
        } else {
            //找到一个开始有效序列了
            if (!isdigit(str[i])) {
                iEnd = i - 1;
                break;
            }
        }
        i++;
    }

    if (iStart >= 0 && iEnd >= iStart && iEnd < len) {
        char* s = malloc((iEnd - iStart + 2) * sizeof(char));
        memset(s, 0, (iEnd - iStart + 2) * sizeof(char));
        for (int i = iStart, j = 0; i <= iEnd ; ++i, j++) {
            s[j] = str[i];
        }
//        printf("valid 2.string is :\'%s\'\n", s);

        if (strlen(s) == 1 && s[0] == '-'){  //只有1个'-'号的情况
            return 0;
        }

        int retVal = -1;
        int tmp = 0;
        int positive = (s[0] != '-'?1:-1);
        //-2,147,483,648~2,147,483,647
        for (int i = s[0] != '-'?0:1; i < strlen(s); ++i) {
            tmp = (s[i] - 48);
            if (retVal < 0) {
                retVal = tmp;
            } else{
                if (retVal < 214748364  || (retVal == 214748364 &&
                        ((positive == -1 && tmp <9) ||
                                (positive == 1 && tmp < 8)
                        ))){
                    retVal = retVal * 10 + tmp;
                } else{
                    if (positive == -1) {
                        return INT_MIN;
                    } else if (positive == 1) {
                        return INT_MAX;
                    }
                }
            }
        }
        retVal *= positive;
        return retVal;
    }

    return 0;
}

void testString6() {
    char* s1 = "     -42";
    printf("\'%s\' atoi then number is : %d\n", s1, myAtoi(s1));
    char* s2 = "4193 with words";
    printf("\'%s\' atoi then number is : %d\n", s2, myAtoi(s2));
    char* s3 = "42";
    printf("\'%s\' atoi then number is : %d\n", s3, myAtoi(s3));
    char* s4 = "words and 987";
    printf("\'%s\' atoi then number is : %d\n", s4, myAtoi(s4));
    char* s5 = "-91283472332";
    printf("\'%s\' atoi then number is : %d\n", s5, myAtoi(s5));
    char* s6 = "3.14159";
    printf("\'%s\' atoi then number is : %d\n", s6, myAtoi(s6));
}