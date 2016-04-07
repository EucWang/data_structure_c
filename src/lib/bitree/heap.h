// 堆
// Created by wangxn on 2016/4/6.
//

#ifndef DATA_STRUCTURE_C_HEAP_H
#define DATA_STRUCTURE_C_HEAP_H

/**
 * 用二叉树实现一个堆,
 * 其节点按照树的层次结构存放在一个数组中,
 * 结构Heap是堆的数据结构
 * 共有4个成员
 *  size    堆中节点的个数
 *  compare  比较data的函数
 *  destroy  销毁data 的函数
 *  tree     堆中存储节点的数组
 */



typedef struct Heap_{
    /**
     *  堆中节点的个数
     */
    int size;

    /**
     * 比较data的函数
     */
    int (*compare)(const void *key1, const void *key2);

    /**销毁data 的函数
     */
    void (*destroy)(void *data);

    /**
     * 堆中存储节点的数组
     */
    void **tree;
}Heap;

void heap_init(
        Heap *heap,
        int (*compare)(const void *key1, const void *key2),
        void (*destroy)(void *data)
        );

void heap_destroy(Heap *heap);

int heap_insert(Heap *heap, const void *data);

int heap_extract(Heap *heap, void **data);

#define heap_size(heap) ((heap)->size)



#endif //DATA_STRUCTURE_C_HEAP_H
