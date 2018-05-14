//
// Created by wangxn on 2018/5/11.
//

#include "test1.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * 反转字符串
    请编写一个函数，其功能是将输入的字符串反转过来。
 * @param s
 * @return
 */
char* reverseString(char* s){
    int len = strlen(s);
    char* retVal = malloc((len + 1) * sizeof(char));
    char tmp;
    int i = 0;
    for (int i = 0; i < len; ++i) {
        *(retVal+i) = *(s+ (len - i - 1));
    }
    *(retVal + len) = '\0';
    return retVal;
}

void testString1(){
    char* s = "hello";
    printf("\noriginal 2.string is: %s", s);
    printf("\nreverse 2.string then it's : %s", reverseString(s));
}
