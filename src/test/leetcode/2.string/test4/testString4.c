//
// Created by wangxn on 2018/5/14.
//

#include "testString4.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool isAnagrgram(char* s, char* t) {

    int lenS = strlen(s);
    int lenT = strlen(t);
    if (lenS == 0 && lenS == lenT) {
        return true;
    }

    if(lenS != lenT){
        return false;
    }


//    for (int i = 0; i < lenS; ++i) {
//        if(s[i] != t[i]){
//            if (s[i+1] == t[i] || s[i] == t[i+1]) {
//                i++;
//                continue;
//            } else{
//                return false;
//            }
//        }
//    }
    short sArr[26] = {0};
    short tArr[26] = {0};
    for (int i = 0; i < lenS; ++i) {
        sArr[s[i] - 'a'] += 1;
        tArr[t[i] - 'a'] += 1;
    }

    for (int i = 0; i < 26; ++i) {
        if(sArr[i] != tArr[i]){
            return false;
        }
    }

    return true;
}

/**
 * 有效的字母异位词
    给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的一个字母异位词。

    示例 1:

        输入: s = "anagram", t = "nagaram"
        输出: true
    示例 2:

        输入: s = "rat", t = "car"
        输出: false
    说明:
        你可以假设字符串只包含小写字母。

    进阶:
        如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？
 */
void testString4(){

    char* s = "anagram";
    char* t = "nagaram";

    printf("\'%s\' is anagram to \'%s\'? %d\n", s,t, isAnagrgram(s, t));

    char* s1 = "rat";
    char* t1 = "cat";

    printf("\'%s\' is anagram to \'%s\'? %d\n", s1,t1, isAnagrgram(s1, t1));

    char* s2 = "abdc";
    char* t2 = "dbac";

    printf("\'%s\' is anagram to \'%s\'? %d\n", s2,t2, isAnagrgram(s2, t2));
}

