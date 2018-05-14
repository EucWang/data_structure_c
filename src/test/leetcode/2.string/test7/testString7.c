//
// Created by wangxn on 2018/5/14.
//

#include "testString7.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * 实现 strStr() 函数。

    给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。

    示例 1:

        输入: haystack = "hello", needle = "ll"
        输出: 2
    示例 2:

        输入: haystack = "aaaaa", needle = "bba"
        输出: -1
    说明:
        当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。

        对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与C语言的 strstr() 以及 Java的 indexOf() 定义相符。
 * @param haystack
 * @param needle
 * @return
 */
int strStr(char* haystack, char* needle) {

    if (haystack == NULL || needle == NULL) {
        return -1;
    }

    int hLen = strlen(haystack);
    int nLen = strlen(needle);

    if (hLen < nLen) {
        return -1;
    }

    if (hLen == 0 || nLen == 0) {
        return 0;
    }

    int retIndex = -1;
    int indexN = 0;
    int i = 0;
    while (i < hLen) {
        if (haystack[i] == needle[indexN]) {
            if (retIndex == -1){
                retIndex = i;   //初始位置
            }
            if (i == hLen - 1 && retIndex >= 0 && hLen - retIndex < nLen) {
                retIndex = -1;  //已经到haystack最后一个元素了, 但是还没有对needle匹配完, 重置retIndex
            }
            if (indexN == nLen - 1 && retIndex >= 0) {   //已经匹配到needle最后一个元素了, 并且retIndex 大于等于0,
                break;
            }
            indexN++;
        } else{
            if (retIndex >= 0){
                i = retIndex;
                indexN = 0;
                retIndex = -1;
            }
        }
        i++;
    }
    return retIndex;
}

void testString7(){
    char* h1 = "hello";
    char* n1 = "ll";
    printf("\nhaystack 2.string is : %s \nneedle 2.string is : %s\nfirst index at :%d\n", h1, n1, strStr(h1,n1));


    char* h2 = "mississippi";
    char* n2 = "issip";
    printf("\nhaystack 2.string is : %s \nneedle 2.string is : %s\nfirst index at :%d\n", h2, n2, strStr(h2,n2));

    char* h3 = "mississippi";
    char* n3 = "issipi";
    printf("\nhaystack 2.string is : %s \nneedle 2.string is : %s\nfirst index at :%d\n", h3, n3, strStr(h3,n3));
}