//
// Created by wangxn on 2018/5/22.
//

#include "testDynamicProgramming.h"
#include <stdbool.h>
#include <stdio.h>

int climbStairs(int n){
    int x = 1, y = 1;
    int tmp = 1;
    for (int i = 2; i <= n; ++i) {
        tmp = x + y;
        x = y;
        y = tmp;
    }
    return tmp;
}


/**
 * 爬楼梯
    假设你正在爬楼梯。需要 n 步你才能到达楼顶。
    每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
    注意：给定 n 是一个正整数。
    示例 1：
        输入： 2
        输出： 2
        解释： 有两种方法可以爬到楼顶。
        1.  1 步 + 1 步
        2.  2 步
    示例 2：
        输入： 3
        输出： 3
        解释： 有三种方法可以爬到楼顶。
        1.  1 步 + 1 步 + 1 步
        2.  1 步 + 2 步
        3.  2 步 + 1 步
 */
void testClimbStairs(){
    printf("climb stairs , total count of stairs is %d, have %d type to climb.\n", 2, climbStairs(2));
    printf("climb stairs , total count of stairs is %d, have %d type to climb.\n", 3, climbStairs(3));
    printf("climb stairs , total count of stairs is %d, have %d type to climb.\n", 4, climbStairs(4));
    printf("climb stairs , total count of stairs is %d, have %d type to climb.\n", 5, climbStairs(5));
    printf("climb stairs , total count of stairs is %d, have %d type to climb.\n", 6, climbStairs(6));
    printf("climb stairs , total count of stairs is %d, have %d type to climb.\n", 7, climbStairs(7));
    printf("climb stairs , total count of stairs is %d, have %d type to climb.\n", 8, climbStairs(8));
    printf("climb stairs , total count of stairs is %d, have %d type to climb.\n", 9, climbStairs(9));

}

void testDynamicProgramming(){

    testClimbStairs();
}