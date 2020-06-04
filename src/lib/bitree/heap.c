//
// Created by wangxn on 2016/4/6.
//
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../mylog/mylog.h"

#define heap_parent(npos) ((int)((npos) -1) /2)  //计算一个节点其父结点在数组中的索引值

#define heap_left(npos) (((npos)* 2) + 1)    //计算一个节点其左子结点在数组中的索引值

#define heap_right(npos) (((npos)* 2) + 2)   //计算一个节点其右子结点在数组中的索引值


/**
 * 在对堆进行其他操作之前必须进行初始化函数调用
 * compare 函数会被堆的各种操作调用,用来比较堆中的结点
 * destroy 函数会被heap_destroy调用,用来释放data数据的内存空间,
 */
void heap_init(
        Heap *heap,
        int (*compare)(const void *key1, const void *key2),
        void (*destroy)(void *data)) {

    heap->size = 0;
    heap->compare = compare;
    heap->destroy = destroy;
    heap->tree = NULL;

    return;
}

/**
 * 在堆调用heap_destrory之后不在允许进行其他操作,除非再次调用heap_init
 */
void heap_destroy(Heap *heap) {

    int i;
    if (heap->destroy != NULL) {
        for (i = 0; i < heap_size(heap); ++i) {
            heap->destroy(heap->tree[i]);
        }
    }
    free(heap->tree);
    memset(heap, 0, sizeof(heap));
    return;
}

/**
 * 如果插入数据成功,返回0, 否则,返回-1
 * 函数处理过程:
 *  1.新插入的结点将首先放到数组的末尾,
 *  2. 如果破坏了树的结构,则对结点进行重新排列
 *  3.只考虑插入结点所在的分支,从新节点开始,将结点向树的上方层层移动,比较每个结点和它的父结点.
 *  4.在每一层上,如果父结点与子节点的位置不正确,就交换节点的内容
 *  5.交换过程不断进行直到某一层不再需要进行交换为止,或者直到树的顶点
 *  6.更新size成员的值
 */
int heap_insert(Heap *heap, const void *data) {

    void *temp;
    int ipos, ppos;

    int new_size = (heap_size(heap) + 1) * sizeof(void *);
    //realloc是给一个已经分配了地址的指针重新分配空间
    //第一个参数为原有的空间地址,
    //第二个参数是重新申请的地址长度
    temp = realloc(heap->tree, new_size);
    if (temp == NULL) {
        _LOG(__FILE__, __LINE__, LogLevel[IC_ERROR_LEVEL], -1, "realloc fail.");
        return -1;
    }

    heap->tree = temp;

    heap->tree[heap_size(heap)] = (void *) data; //新数据放入到数组最后一个新分配的位置

    ipos = heap_size(heap);    //新节点的索引值
    ppos = heap_parent(ipos);  //新节点的父结点的索引值

    while (ipos > 0 &&
           heap->compare(heap->tree[ppos], heap->tree[ipos]) < 0) {
        temp = heap->tree[ppos];              //交换新结点和其父结点
        heap->tree[ppos] = heap->tree[ipos];
        heap->tree[ipos] = temp;

        //向上移动一层
        ipos = ppos;
        ppos = heap_parent(ipos);
    }

    heap->size++;
    return 0;
}

/**
 * 如果结点释放成功,返回0, 否则返回-1
 * 从堆中释放顶部的结点,返回时,data指向被释放结点中存储的数据.
 * 与data相关的内容空间将由函数的调用者来管理
 * 函数处理过程:
 * 1. 将data指向将要释放结点的数据
 * 2.保存最后一个结点的内容
 * 3. 树大小减一, 为树重新分配一个稍小的存储空间
 * 4.将最后一个结点的内容拷贝到根节点中.显然,这个操作会破坏堆固有的特性,然后重新调整树的结构,重新排列
 * 5.从根节点开始沿树干层层向下移动,与结点的两个子节点比较.
 * 6.需要将父结点与位置最混乱的那个子节点进行交换.
 * 7.交换知道不再需要进行交换为止,或者到达一个叶子结点为止.
 * 8.更新size成员的值
 */
int heap_extract(Heap *heap, void **data) {
    void *save, *temp;
    int ipos, lpos, rpos, mpos;

    if (heap_size(heap) == 0) {
        _LOG(__FILE__, __LINE__, IC_INFO_LEVEL,  -2, "heap size is zero ,do nothing");
        return -1;
    }

    *data = heap->tree[0];  //获取根节点

    save =  heap->tree[heap_size(heap) - 1]; //获取最后一个节点

    if (heap_size(heap) - 1 > 0) {
        int new_size = (heap->size - 1) * sizeof(void *);
        //realloc是给一个已经分配了地址的指针重新分配空间
        //第一个参数为原有的空间地址,
        //第二个参数是重新申请的地址长度
        temp = (void *)realloc(heap->tree, new_size);
        if (temp == NULL) {
            _LOG(__FILE__, __LINE__, IC_ERROR_LEVEL, -1, "realloc fail.");
            return -1;
        }

        heap->tree = temp;
        heap->size--;
    } else {
        free(heap->tree);  //只有一个元素在堆中时的情况,直接清空堆就可以了
        heap->tree = NULL;
        heap->size = 0;
        return 0;
    }

    heap->tree[0] = save;

    ipos = 0;                 //根节点的索引

    while (1) {
        lpos = heap_left(ipos);   //根节点的左子节点的索引
        rpos = heap_right(ipos);  //根节点的右子节点的索引

        //左子节点先和父结点比较,保存2个中最小的值
        if (lpos < heap_size(heap) &&
                heap->compare(heap->tree[lpos], heap->tree[ipos]) > 0) {
            mpos = lpos;
        } else {
            mpos = ipos;
        }

        //左子节点先和父结点比较的结果再和右子节点比较,
        if (rpos < heap_size(heap) &&
                heap->compare(heap->tree[rpos], heap->tree[mpos]) > 0) {
            mpos = rpos;
        }

        if (mpos == ipos) {
            break; //已经不再需要重新排列了
        } else {
            temp = heap->tree[mpos];              //交换新结点和其子结点
            heap->tree[mpos] = heap->tree[ipos];
            heap->tree[ipos] = temp;

            ipos = mpos;  //向下移动一层级
        }
    }
    return 0;
}