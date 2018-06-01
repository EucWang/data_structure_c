//
// Created by wangxn on 2018/5/28.
//

#include <stdlib.h>
#include "TestDesignIssue.h"
#include "../../../lib/arr_tool/arrTool.h"
//#include <time.h>
#include <stdio.h>
#include <time.h>

typedef struct {
    int* nums;
    int* shuffleNums;
    int size;
    int seed;
}Solution;

Solution* solutionCreate(int* nums, int size) {
    Solution* s = malloc(sizeof(Solution));

    int *arr = malloc((size * sizeof(int)));
    int *arr2 = malloc((size * sizeof(int)));
    for (int i = 0; i < size; i++) {
        arr[i] = nums[i];
        arr2[i] = nums[i];
    }
    
    s->nums = arr;
    s->shuffleNums = arr2;
    s->size = size;
    s->seed = 1;
    return s;
}

int* solutionReset(Solution* obj, int* returnSize) {
    *returnSize = obj->size;
    return obj->nums;
}

int* solutionShuffle(Solution* obj, int* returnSize) {
    int i, tmp;
    srand((int)(time(0)) + obj->seed++);
    for (i = 0; i < obj->size; i++) {
        int randIndex = rand() % (obj->size - i) + i;  //获得一个随机位置
        if (randIndex != i) {
            tmp = obj->shuffleNums[i];
            obj->shuffleNums[i] = obj->shuffleNums[randIndex];
            obj->shuffleNums[randIndex] = tmp;
        }
    }
    *returnSize = obj->size;
    return obj->shuffleNums;
}

void solutionFree(Solution* obj) {
    if (obj != NULL) {
        if(obj->nums != NULL) {
            printf("free solution arr\n");
            free(obj->nums);
        }
        if(obj->shuffleNums != NULL) {
            printf("free solution shuffleNums\n");
            free(obj->shuffleNums);
        }
        printf("free solution memory");
        free(obj);
    }
}

void shuffleAndPrint(Solution* solution) {
    int retSize = 0;
    int *arr2 = solutionShuffle(solution, &retSize);
    printf("shuffle arr :\n");
    printfArr(arr2, retSize);
}

/**
 * Shuffle an Array
    打乱一个没有重复元素的数组。
    示例:

        // 以数字集合 1, 2 和 3 初始化数组。
        int[] nums = {1,2,3};
        Solution solution = new Solution(nums);
        // 打乱数组 [1,2,3] 并返回结果。任何 [1,2,3]的排列返回的概率应该相同。
        solution.shuffle();
        // 重设数组到它的初始状态[1,2,3]。
        solution.reset();
        // 随机返回数组[1,2,3]打乱后的结果。
        solution.shuffle();
 */
void testSuffleArray(){

    int arr[] = {1,2,3};
    printf("original arr is:\n");
    printfArr(arr, 3);
    Solution *solution = solutionCreate(arr, 3);
    shuffleAndPrint(solution);
    shuffleAndPrint(solution);
    shuffleAndPrint(solution);
    shuffleAndPrint(solution);

    int retSize = 0;
    int* nums = solutionReset(solution, & retSize);
    printf("after reset :\n");
    printfArr(nums, retSize);

    printf("seed is %d\n", solution->seed);
    solutionFree(solution);
}


////////////////////////////////////////////////////////
typedef struct StackNode_ {
    int val;
    struct StackNode_* next;
    struct StackNode_* biggerNext;

}StackNode;

typedef struct {
    StackNode* top;
    StackNode* min;
    int size;
    int maxSize;
} MinStack;


/** initialize your data structure here. */
MinStack* minStackCreate(int maxSize) {
    MinStack* retVal = malloc(sizeof(MinStack));
    retVal->top = NULL;
    retVal->min = NULL;
    retVal->maxSize = maxSize;
    retVal->size = 0;
    return retVal;
}

void minStackPush(MinStack* obj, int x) {
    if (obj != NULL) {
        StackNode* node = malloc(sizeof(StackNode));
        node->val = x;

        StackNode* tmp;
        if (obj->top == NULL) {  //栈为空
            obj->top = node;
            obj->min = node;

            node->next = NULL;
            node->biggerNext = NULL;
        }else {                     //栈不为空
            tmp = obj->top;
            obj->top = node;
            node->next = tmp;       //重新设置栈顶元素
            node->biggerNext = NULL;

            //插入最小的数
            if (obj->min->val >= node->val) {   //压栈元素 比栈内最小元素还小, 更换最小元素
                tmp = obj->min;
                obj->min = node;
                node->biggerNext = tmp;
            } else {                           //压栈元素 大小位于栈中, 遍历插入队列中
                tmp = obj->min;
                while (tmp != NULL) {
                    if (tmp->biggerNext != NULL && tmp->biggerNext->val >= node->val) {
                        node->biggerNext = tmp->biggerNext;
                        tmp->biggerNext = node;
                        break;
                    } else{
                        if (tmp->biggerNext == NULL) {
                            tmp->biggerNext = node;
                            break;
                        } else{
                            tmp = tmp->biggerNext;
                        }
                    }
                }
            }
        }
        obj->size++;
    }
}

void minStackPop(MinStack* obj) {
    StackNode *node = obj->top;
    obj->top = node->next;

    StackNode* item = obj->min;
    if (item == node) {
        obj->min = obj->min->biggerNext;
    }else {
        while (item != NULL) {
            if (item->biggerNext != NULL && item->biggerNext == node) {
                item->biggerNext = item->biggerNext->biggerNext;
            } else {
                item = item->biggerNext;
            }
        }
    }

    free(node);
    obj->size--;
}

int minStackTop(MinStack* obj) {
    if (obj != NULL && obj->top != NULL) {
        return obj->top->val;
    } else {
        return INT_MAX;
    }
}

int minStackGetMin(MinStack* obj) {
    if(obj != NULL && obj->min != NULL){
        return obj->min->val;
    } else{
        return INT_MAX;
    }
}

void minStackFree(MinStack* obj) {
    if (obj != NULL) {
        StackNode* node = obj->top;
        StackNode* tmp;
        while (node != NULL) {
            tmp = node->next;
            free(node);
            node = tmp;
        }

        free(obj);
    }
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * struct MinStack* obj = minStackCreate(maxSize);
 * minStackPush(obj, x);
 * minStackPop(obj);
 * int param_3 = minStackTop(obj);
 * int param_4 = minStackGetMin(obj);
 * minStackFree(obj);
 */


/**
 * 最小栈
    设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。

        push(x) -- 将元素 x 推入栈中。
        pop() -- 删除栈顶的元素。
        top() -- 获取栈顶元素。
        getMin() -- 检索栈中的最小元素。
    示例:
        MinStack minStack = new MinStack();
        minStack.push(-2);
        minStack.push(0);
        minStack.push(-3);
        minStack.getMin();   --> 返回 -3.
        minStack.pop();
        minStack.top();      --> 返回 0.
        minStack.getMin();   --> 返回 -2.
 */
void testMinStack(){

    MinStack *stack = minStackCreate(10);

//    minStackPush(stack, NULL);
    minStackPush(stack, -2);
    minStackPush(stack, 0);
    minStackPush(stack, -3);

    int i = minStackGetMin(stack);
    printf("min value in stack is:%d\n", i);

    minStackPop(stack);
    int top = minStackTop(stack);
    printf("top value is %d\n", top);

    int min = minStackGetMin(stack);
    printf("min value in stack is:%d\n", min);
}

void testMinStack2() {

    MinStack *stack = minStackCreate(10);
    minStackPush(stack, -7);
    int i = minStackGetMin(stack);
    printf("min value in stack is:%d\n", i);

    minStackPush(stack, -5);
    int top = minStackTop(stack);
    printf("top value is %d\n", top);
    minStackPush(stack, -3);
    minStackPop(stack);
//    int min = minStackGetMin(stack);
//    printf("min value in stack is:%d\n", min);

}

void testDesignIssue() {
//    testSuffleArray();
    testMinStack2();
}