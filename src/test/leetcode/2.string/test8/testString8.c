//
// Created by wangxn on 2018/5/14.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "testString8.h"

/**
 * 数数并说
        报数序列是指一个整数序列，按照其中的整数的顺序进行报数，得到下一个数。其前五项如下：
        1.     1
        2.     11
        3.     21
        4.     1211
        5.     111221
        1 被读作  "one 1"  ("一个一") , 即 11。
        11 被读作 "two 1s" ("两个一"）, 即 21。
        21 被读作 "one 2",  "one 1" （"一个二" ,  "一个一") , 即 1211。

        给定一个正整数 n ，输出报数序列的第 n 项。

    注意：整数顺序将表示为一个字符串。
    示例 1:
        输入: 1
        输出: "1"
    示例 2:
        输入: 4
        输出: "1211"
 * @param n
 * @return
 */
char* countAndSay(int n) {

    if(n < 1){
        return NULL;
    }else if (n == 1) {
        return "1";
    } else {
        char* str = countAndSay(n - 1);
        int len = strlen(str);
        char* retVal = malloc((2*len + 1)* sizeof(char));
        memset(retVal, 0, (2*len + 1)*sizeof(char));

        int index = 0;
        short count = 0;
        char tmpVal = '\0';
        for (int i = 0; i < len; ++i) {
            if (tmpVal == 0) {
                tmpVal = str[i];
                count = 1;
            } else if(tmpVal == str[i]){ //previous value equals to current item value
                count++;
            } else if (tmpVal != str[i]) {

                if (index < 2 *(len - 1)) {
                    retVal[index++] = (char)(count + 0x30);
                    retVal[index++] = tmpVal;
                } else{
                    //重新分配一个更大的空间
                    printf("\nneed more space[for]\tcurrent n is:%d\n", n);
                }

                count = 1;
                tmpVal = str[i];
            }
        }

        if (count > 0 && tmpVal > 0) {
            if (index < (2 * len - 1)) {
                retVal[index++] = (char)(0x30 + count);
                retVal[index++] = tmpVal;
            } else{
                printf("\nneed more space\tcurrent n is:%d\n", n);
            }
        }

//        free(str);
        return retVal;
    }
}

void testString8() {
    printf("\n%d countAndSay is:%s\n", 1, countAndSay(1));
    printf("\n%d countAndSay is:%s\n", 2, countAndSay(2));
    printf("\n%d countAndSay is:%s\n", 3, countAndSay(3));
    printf("\n%d countAndSay is:%s\n", 4, countAndSay(4));
    printf("\n%d countAndSay is:%s\n", 5, countAndSay(5));
    printf("\n%d countAndSay is:%s\n", 6, countAndSay(6));
    printf("\n%d countAndSay is:%s\n", 7, countAndSay(7));
    printf("\n%d countAndSay is:%s\n", 8, countAndSay(8));
    printf("\n%d countAndSay is:%s\n", 9, countAndSay(9));
    printf("\n%d countAndSay is:%s\n", 10, countAndSay(10));

}