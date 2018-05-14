//
// Created by wangxn on 2018/5/14.
//

#include "testString5.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool isPalindrome2(char* s) {
    int i, j;
    i = 0 ;
    j = strlen(s) - 1;

    while(i < j) {
        if(!isalnum(s[i])) {
            i++;
            continue;
        }

        if(!isalnum(s[j])) {
            j--;
            continue;
        }

        if(tolower(s[i]) != tolower(s[j])) {
            return  false;
        }
        i++;
        j--;
    }
    return true;
}

bool isPalindrome(char* s) {

    if (s == NULL) {
        return false;
    }

    int len = strlen(s);
    if (len == 0) {
        return true;
    }

    int i = 0;
    int j = len - i - 1;
    while( i < j) {
        if (!(s[i] >= 65 && s[i] <= 90) &&
                !(s[i] >= 97 && s[i] <= 122) &&
                !(s[i] >= 48 && s[i] <= 57)) {
            i++;
            continue;
        }
        if (!(s[j] >= 65 && s[j] <= 90) &&
                !(s[j] >= 97 && s[j] <= 122) &&
                !(s[j] >= 48 && s[j] <= 57)) {
            j--;
            continue;
        }

        if (s[i] == s[j]) {
            i++;
            j--;
            continue;
        } else {
            if (s[i] >= 65 && s[i] <= 90) {
                if(s[i] + 32 == s[j]){
                    i++;
                    j--;
                    continue;
                } else{
                    return false;
                }
            } else if( s[i] >= 97 && s[i] <= 122) {
                if(s[i] -32 == s[j]) {
                    i++;
                    j--;
                    continue;
                } else{
                    return false;
                }
            } else{
                return false;
            }
        }
    }

    return true;
}

/**
 * 验证回文字符串
    给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。

    说明：本题中，我们将空字符串定义为有效的回文串。

    示例 1:

    输入: "A man, a plan, a canal: Panama"
    输出: true
    示例 2:

    输入: "race a car"
    输出: false
 */
void testString5() {
    char* s = "A man, a plan, a canal: Panama";
    printf("\'%s\' is palindrome 2.string or not ? %d.\n", s, isPalindrome2(s));

    char* s1 = "race a car";
    printf("\'%s\' is palindrome 2.string or not ? %d.\n", s1, isPalindrome2(s1));

    char* s2 = "ab2a";
    printf("\'%s\' is palindrome 2.string or not ? %d.\n", s2, isPalindrome2(s2));
}