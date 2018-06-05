//
// Created by wangxn on 2018/6/4.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
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

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/**
 * 计数质数
    统计所有小于非负整数 n 的质数的数量。
    示例:
        输入: 10
        输出: 4
        解释: 小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。
 * @param n
 * @return
 */
int countPrimes(int n) {
    int retVal = 0;

    int j;
    bool isPrimes = false;
    for (int i = 2; i < n; ++i) {
        if (i == 2 || i == 3 || i == 5 || i == 7) {
            retVal++;
            continue;
        }
        j = 2;
        isPrimes = true;
        int max = sqrt(i);
        while (j < max) {
            if ((i % j) == 0) {
                isPrimes = false;
                break;
            }
            j++;
        }
        if (isPrimes)retVal++;
    }
    return retVal;
}

/**
 * 用筛法求素数的基本思想是：把从1开始的、某一范围内的正整数从小到大顺序排列， 1不是素数，首先把它筛掉。剩下的数中选择最小的数是素数，然后去掉它的倍数。依次类推，直到筛子为空时结束。
 * 如有：
        1 2 3 4 5 6 7 8 9 10  11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
    1 不是素数，去掉。剩下的数中2最小，是素数，去掉2的倍数，余下的数是：
        2 3 5 7 9 11 13 15 17 19 21 23 25 27 29
    剩下的数中3最小，是素数，去掉3的倍数，如此下去直到所有的数都被筛完，求出的素数为：
        2 3 5 7 11 13 17 19 23 29
 * @param n
 * @return
 */
int countPrimes2(int n) {
    if (n <= 1) {
        return 0;
    }
    bool or[n];
    for (int i = 0; i < n; ++i) {
        or[i] = true;
    }
    or[0] = false;
    or[1] = false;
    int count = 0;
    for (int i = 2; i < n; ++i) {  //从2开始数
        if (or[i]) {
            count++;
            int k = 2;
            while (i * k < n) {
                or[i*k] = false;
                k++;
            }
        }else{
            continue;
        }
    }
    printf("[");
    for (int i = 0; i < n; ++i) {
        if (or[i]) {
            printf("%d\t", i);
        }
    }
    printf("]\n");
    return count;
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

/**
 * 3的幂    给定一个整数，写一个函数来判断它是否是 3 的幂次方。
    示例 1:     输入: 27
                输出: true
    示例 2:     输入: 0
                输出: false
    示例 3:     输入: 9
                输出: true
    示例 4:      输入: 45
                输出: false
    进阶：   你能不使用循环或者递归来完成本题吗？
 * @param n
 * @return
 */
bool isPowerOfThree(int n) {
    if (n <= 0) {
        return false;
    }
    while (n > 1) {
        if(n % 3 != 0){
            return false;
        }
        n = (n/3);
    }

    return true;
}

bool isPowerOfThree2(int n) {
    int tmp = 1, i = 0;
    while(tmp <= n) {
        tmp = pow(3, i);
        if(tmp == n){
            return true;
        } else if (tmp > n) {
            return false;
        } else if (tmp < n) {
            i++;
        }
    }

    return false;
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#define I 1
#define V 5
#define X 10
#define L 50
#define C 100
#define D 500
#define M 1000

int singleRomanToInt(char s) {
    int retVal = 0;
    switch (s) {
        case 'I':
            retVal = 1;
            break;
        case 'V':
            retVal = 5;
            break;
        case 'X':
            retVal = 10;
            break;
        case 'L':
            retVal = 50;
            break;
        case 'C':
            retVal = 100;
            break;
        case 'D':
            retVal = 500;
            break;
        case 'M':
            retVal = 1000;
            break;
        default:
            break;
    }
    return retVal;
}

/**
 * 罗马数字转整数
罗马数字包含以下七种字符：I， V， X， L，C，D 和 M。
    字符          数值
    I             1
    V             5
    X             10
    L             50
    C             100
    D             500
    M             1000
    例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。
    通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：
    I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
    X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。
    C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
    给定一个罗马数字，将其转换成整数。输入确保在 1 到 3999 的范围内。
    示例 1:     输入: "III"         输出: 3
    示例 2:     输入: "IV"          输出: 4
    示例 3:     输入: "IX"          输出: 9
    示例 4:    输入: "LVIII"        输出: 58      解释: C = 100, L = 50, XXX = 30, III = 3.
    示例 5:      输入: "MCMXCIV"    输出: 1994    解释: M = 1000, CM = 900, XC = 90, IV = 4.
 * @param s
 * @return
 */
int romanToInt(char* s) {
    size_t len = strlen(s);
    int* arr = malloc(len * sizeof(int));
    int retVal = 0;
    for (int i = 0; i < len; ++i) {
        arr[i] = singleRomanToInt(s[i]);
        if (i >= 1) {
            if(arr[i] > arr[i - 1]){
                arr[i - 1] = - arr[i - 1];
            }
            retVal += arr[i - 1];
        }
    }
    retVal += arr[len - 1];
    free(arr);
    return retVal;
}



void testFizzBuzz(){
    int retSize = 0;
    char** retStr = fizzBuzz(15, &retSize);
    printf("retSize is %d\n", retSize);
    for (int i = 0; i < retSize; i++) {
        printf("%s\t", retStr[i]);
    }
}

void testCountPrimes(){
    printf("count of primes is [%d] when n is %d\n", countPrimes2(2), 2);
    printf("count of primes is [%d] when n is %d\n", countPrimes2(5), 5);
    printf("count of primes is [%d] when n is %d\n", countPrimes2(10), 10);
    printf("count of primes is [%d] when n is %d\n", countPrimes2(20), 20);
}

void testIsPowerOfThree() {
    printf("%d is power of three? %d\n", 27, isPowerOfThree(27));
    printf("%d is power of three? %d\n", 0, isPowerOfThree(0));
    printf("%d is power of three? %d\n", 9, isPowerOfThree(9));
    printf("%d is power of three? %d\n", 45, isPowerOfThree(45));
}

void testMathIssue(){
//    testFizzBuzz();
//    testCountPrimes();
    testIsPowerOfThree();
}