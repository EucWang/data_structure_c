// 优先队列
// Created by wangxn on 2016/4/6.
//

#ifndef DATA_STRUCTURE_C_PQUEUE_H
#define DATA_STRUCTURE_C_PQUEUE_H

/**
 * 实现优先队列可以有很多种方式,
 * 使用Heap来实现优先队列是一种简单的可行方案
 * 优先队列与堆的操作基本相同,优先队列仅仅比堆多一个接口
 * 并且堆数据类型作为实现方式.
 * 为了实现这些接口,只需要将优先队列的相应操作定义成堆的操作就可以了
 * 优先队列中独有的操作pqueue_peek与pqueue_extract相类似,只是pqueue_peek返回队列中优先级最高的元素而不删除他
 */

#include "heap.h"

typedef Heap PQueue;

#define  pqueue_init heap_init

#define  pqueue_destroy heap_destroy

#define  pqueue_insert heap_insert

#define  pqueue_extract heap_extract

#define  pqueue_peek(pqueue) ((pqueue)->tree == NULL ? NULL : (pqueue)->tree[0])

#define pqueue_size heap_size

#endif //DATA_STRUCTURE_C_PQUEUE_H
