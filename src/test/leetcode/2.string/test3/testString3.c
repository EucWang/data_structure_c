//
// Created by wangxn on 2018/5/13.
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "testString3.h"

int firstUniqChar(char* s) {
    int len = strlen(s);
    if(len == 0) {
        return -1;
    }else if(len == 1){
        return 0;
    }
    int retVal = -1;
    short* dict = malloc(26 * sizeof(short));
    memset(dict, -1, 26*sizeof(short));
    int index =0, i =0;
    for(i =0; i<len; i++){
        index = s[i] - 'a';
        if (dict[index] == -1){
            dict[index] = i;
        }else if(dict[index] > -1){
            dict[index] = - 2;
        }else{
            continue;
        }
    }
    for(i = 0; i<len; i++) {
        if (dict[s[i]-'a'] >-1){
            retVal = dict[s[i]-'a'];
            break;
        }
    }

    free(dict);
    return retVal;
}

/**
 * 字符串中的第一个唯一字符
    给定一个字符串，找到它的第一个不重复的字符，并返回它的索引。如果不存在，则返回 -1。

    案例:

    s = "leetcode"
    返回 0.

    s = "loveleetcode",
    返回 2.


    注意事项：您可以假定该字符串只包含小写字母。
 */
void testString3(){
    char* s = "leetcode";
    printf("in \'%s\' the first unique letter at index : %d\n", s, firstUniqChar(s));
    s = "loveleetcode";
    printf("in \'%s\' the first unique letter at index : %d\n", s, firstUniqChar(s));
     s = "cc";
    printf("in \'%s\' the first unique letter at index : %d\n", s, firstUniqChar(s));
}
