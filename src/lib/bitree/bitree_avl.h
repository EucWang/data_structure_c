// AVL二叉平衡树
// Created by wangxn on 2016/4/5.
//

#ifndef DATA_STRUCTURE_C_BITREE_AVL_H
#define DATA_STRUCTURE_C_BITREE_AVL_H

#include "bitree.h"

/**
 * 定义AVL树的平衡因子
 */
#define BITREE_AVL_LFT_HEAVY 1
#define BITREE_AVL_BALANCED  0
#define BITREE_AVL_RGT_HEAVY -1

typedef struct AvlNode_{
    /**
     * 包含的数据
     */
    void *data;

    /**
     * 用来标识节点是否已经移除的一个成员
     */
    int hidden;

    /**
     * 标识为该节点的平衡因子
     */
    int factor;
}AvlNode;

typedef BiTree BiTree_AVL;


/**
 * 初始化
 */
void bitree_avl_init(BiTree_AVL *tree_avl,
                     int (*compare)(const void *key1, const void *key2),
                     void (*destroy)(void *data));

/**
 * 销毁
 */
void bitree_avl_destroy(BiTree_AVL *tree_avl);

/**
 * 插入
 */
int bitree_avl_insert(BiTree_AVL *tree_avl, const void *data);


/**
 * 移除
 */
int bitree_avl_remove(BiTree_AVL *tree_avl, const void *data);

/**
 * 查找
 */
int bitree_avl_lookup(BiTree_AVL *tree_avl, void **data);

/**
 * 大小
 */
#define  bitree_avl_size(tree_avl) ((tree_avl)->size)

#endif //DATA_STRUCTURE_C_BITREE_AVL_H
