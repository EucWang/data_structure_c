//
// Created by wangxn on 2018/5/14.
//

#include "testString9.h"
#include "../../../../lib/arr_tool/arrTool.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * 最长公共前缀
    编写一个函数来查找字符串数组中的最长公共前缀。
    如果不存在公共前缀，返回空字符串 ""。
    示例 1:
        输入: ["flower","flow","flight"]
        输出: "fl"
    示例 2:
        输入: ["dog","racecar","car"]
        输出: ""
    解释: 输入不存在公共前缀。
    说明:
        所有输入只包含小写字母 a-z 。
 * @param strs
 * @param strsSize
 * @return
 */
char* longestCommonPrefix(char** strs, int strsSize) {

    if (strsSize <= 0 || strs == NULL ) {
        return "";
    }

    if (strsSize == 1){
        return strs[0];
    }

    char* retVal = malloc((strlen(strs[0]) + 1) * sizeof(char));
    memset(retVal, 0, (strlen(strs[0]) + 1) * sizeof(char));

    bool flag = false;
    for (int i = 0; i < strlen(strs[0]); ++i) {
        char tmp = strs[0][i];  //第一列第一个字符
        flag = true;
        for (int j = 1; j < strsSize; ++j) {
            if(tmp != strs[j][i] || i >= strlen(strs[j])) {
                flag = false;
                break;
            }
        }
        if(flag){
            retVal[i] = tmp;
        } else{
            break;
        }
    }
    return retVal;
}


void test1(){
    char* s1 = "flower";
    char* s2 = "flow";
    char* s3 = "flight";
    char* s[] = {s1, s2, s3};

    printf("\nresult is \'%s\'\n", longestCommonPrefix(s, 3));

}

void test2(){
    char* s1 = "dog";
    char* s2 = "racecar";
    char* s3 = "car";
    char* s[] = {s1, s2, s3};

    printf("\nresult is \'%s\'\n", longestCommonPrefix(s, 3));

}
void test3(){
    char* s1 = "a";
    char* s2 = "ac";
    char* s[] = {s1, s2};

    printf("\nresult is \'%s\'\n", longestCommonPrefix(s, 2));

}

void testString9() {
//    test1();
//    test2();
    test3();
}
