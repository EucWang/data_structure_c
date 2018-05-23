//
// Created by wangxn on 2018/5/22.
//

#include "testDynamicProgramming.h"
#include "../../../lib/arr_tool/arrTool.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

//--------------------------------------------------------------------------------------------

typedef struct Stock_{
    int value;
    int index;
}Stock;

void exchange(Stock* stock1, Stock* stock2) {
    int tmpV = stock1->value;
    int tmpI = stock1->index;
    stock1->value = stock2->value;
    stock1->index = stock2->index;
    stock2->value = tmpV;
    stock2->index = tmpI;
}

void _qsortStock(Stock* nums, int left, int right){
    if(left >= right){
        return;  //递归终止条件
    }
    srand((int)time(0));
    int randLocIndex = rand() % (right - left) + left;  //获得一个随机位置
    int tmpValue, tmpIndex;
    //交换随机位置和最左边位置的值
    exchange(&nums[left], &nums[randLocIndex]);
    int i,j,key, keyIndex;
    key = nums[left].value;  //分治的比较值
    keyIndex = nums[left].index;
    i = left;
    j = right;
    while(i<j){
        while(i<j && nums[j].value>=key){  //右边找到一个小于key的索引位置
            j--;
        }
        while(i<j && nums[i].value<=key){  //左边找到一个大于key 的索引位置
            i++;
        }
        if(i<j) {             //交换两个位置的值
            exchange(&nums[i], &nums[j]);
        }
    }
    nums[left].value = nums[i].value;
    nums[left].index = nums[i].index;
    nums[i].value = key;
    nums[i].index = keyIndex;
    //经过上面一轮循环, 右边的值全部大于左边的值
    //然后分两块区域, 继续进行排序
    _qsortStock(nums, left, i - 1);
    _qsortStock(nums, i+1, right);
}
/**
 * 快速排序
 */
void qsortStockArr(Stock* nums, int numsSize){
    _qsortStock(nums, 0, numsSize - 1);
}

char* stockToString(Stock* stock) {
    char* buf = malloc(30 * sizeof(char));
    sprintf(buf, "[value=%d,index=%d]", stock->value, stock->index);
    return buf;
}

void printStockArr(Stock* stocks, int size) {
    printf("[\n");
    for (int i = 0; i < size; ++i) {
        printf("\t%s", stockToString(&stocks[i]));
    }
    printf("\n]\n");
}

int maxProfit(int* prices, int pricesSize){
    int maxProfit = 0;

    Stock* stocks = malloc(pricesSize * sizeof(Stock));
    for (int i = 0; i < pricesSize; ++i) {
        stocks[i].index = i;
        stocks[i].value = prices[i];
    }
    qsortStockArr(stocks, pricesSize);
    int perfectBuyIndex =0;
    int perfectSellIndex = pricesSize - 1;
    int i= perfectBuyIndex;
    int j = perfectSellIndex;
    while (i < pricesSize) {
        j = pricesSize - 1;
        while (j > i) {
            if (stocks[j].index > stocks[i].index) {
                int tmpMax = stocks[j].value - stocks[i].value;
                if(tmpMax > maxProfit) {
                    perfectBuyIndex = stocks[i].index;
                    perfectSellIndex = stocks[j].index;
                    maxProfit = tmpMax;
                    break;
                }
            }
            j--;
        }
        i++;
    }
    return maxProfit;
}

/**
 * 第二种解法
 * @param prices
 * @param pricesSize
 * @return
 */
int maxProfit2(int* prices, int pricesSize) {
    int maxProfit = 0;
    int i = 0;
    int j;
    while (i < pricesSize) {
        j = pricesSize - 1;
        while (j > i) {
            if (prices[j] > prices[i]) {
                int tmpMax = prices[j] - prices[i];
                if(tmpMax > maxProfit) {
                    maxProfit = tmpMax;
//                    break;
                }
            }
            j--;
        }
        i++;
    }
    return maxProfit;
}

/**
 * 第三种方法
 *
 * 将问题转换成 最大连续子数组和问题
 *
 * @param prices
 * @param pricesSize
 * @return
 */
int maxProfit3(int* prices, int pricesSize) {
    if(prices == NULL || pricesSize <= 1){
        return 0;
    }

    int i;
    for (i = 0; i < pricesSize - 1; ++i) {   //得到每一天的股票相对于前一天的股票收益值(正:增长; 负:下跌)
        prices[i] = prices[i+1] - prices[i];
    }
    pricesSize--;

    int retVal = prices[0];             //
    int maxProfit = prices[0];
    for (i = 1; i < pricesSize; ++i) {
        if (maxProfit > 0) {
            maxProfit += prices[i];
        } else {
            maxProfit = prices[i];
        }

        if (maxProfit > retVal) {
            retVal = maxProfit;
        }
    }

    return retVal>0?retVal:0;
}

/**
 * 第四中解法
 * @param prices
 * @param pricesSize
 * @return
 */
int maxProfit4(int* prices, int pricesSize) {
    if(prices == NULL || pricesSize <= 1){
        return 0;
    }

    int maxProfit = 0;
    int min = INT_MAX;

    for (int i = 0; i < pricesSize; ++i) {
        min = (min>prices[i]) ? prices[i] : min;  //前面i个数里的最小值
        maxProfit = (maxProfit > (prices[i] - min)) ? maxProfit : prices[i] - min;  //和前面的最小值的差值是否是最大的,
    }
    return maxProfit;
}

/**
 * 买卖股票的最佳时机
    给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
    如果你最多只允许完成一笔交易（即买入和卖出一支股票），设计一个算法来计算你所能获取的最大利润。
    注意你不能在买入股票前卖出股票。

    示例 1:
        输入: [7,1,5,3,6,4]
        输出: 5
        解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
             注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。
    示例 2:
        输入: [7,6,4,3,1]
        输出: 0
        解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
 */
void testMaxProfit(){

    int arr1[] = {7, 1, 5, 3, 6, 4};
    printfArr(arr1, 6);
    printf("the max profit is %d\n", maxProfit4(arr1, 6));

    int arr2[] = {7,6 ,4, 3, 1};
    printfArr(arr2, 5);
    printf("the max profit is %d\n", maxProfit4(arr2, 5));

}

void testDynamicProgramming(){
//    testClimbStairs();
    testMaxProfit();
}