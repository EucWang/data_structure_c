// 二叉树
// Created by wangxn on 2016/4/1.
//

#ifndef DATA_STRUCTURE_TEST_BITREE_H
#define DATA_STRUCTURE_TEST_BITREE_H

#include <stdlib.h>

/**
 * 二叉树子节点
 */
typedef  struct BiTreeNode_{
    void *data;
    struct BiTreeNode_ *left;
    struct BiTreeNode_ *right;
}BiTreeNode;

/**
 * 二叉树的结构体
 */
typedef struct BiTree_{
    int size;   //所有节点数目
    int (*compare)(const void *key1, const void *key2);  //节点的比较函数
    void (*destroy)(void *data);  //节点的销毁函数
    BiTreeNode *root;      //根节点
}BiTree;

/**
 * 公共接口
 */

/**
 * 二叉树的初始化
 */
void bitree_init(BiTree *tree, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data));

/**
 * 二叉树的销毁
 */
void bitree_destroy(BiTree *tree);

/**
 * 插入数据, 必须有compare方法
 */
int bitree_ins(BiTree *tree, const void *data);

/**
 * 向二叉树的指定节点的左子节点位置插入数据
 */
int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data);

/**
 * 向二叉树的指定节点的右子节点位置插入数据
 */
int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data);

/**
 * 从二叉树的指定节点的左子节点位置删除数据
 */
void bitree_rem_left(BiTree *tree, BiTreeNode *node);

/**
 * 从二叉树的指定节点的右子节点位置删除数据
 */
void bitree_rem_right(BiTree *tree, BiTreeNode *node);

/**
 * 将left和right所指定的两颗二叉树合并为单颗二叉树.
 * 合并完成之后, 参数data所代表的数据存储在merge的根节点中,而
 * left和right则代表该根节点的左右子树.
 * 一旦完成合并,left和right就好像在他们之上执行了bitree_destroy操作一样
 */
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data);

/**
 * 当前二叉树中的子元素数量
 */
#define bitree_size(tree) ((tree)->size)

/**
 * 二叉树的根节点
 */
#define  bitree_root(tree) ((tree)->root)

/**
 * 判断由参数node 所标识的节点是否为二叉树中某个分支的结束
 */
#define  bitree_is_eob(node) ((node) == NULL)

/**
 * 判断参数哦node所指定的节点是否为二叉树中的叶子节点
 */
#define  bitree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)

/**
 * 参数node所指定的节点中存储的数据
 */
#define  bitree_data(node) ((node)->data)

/**
 * node 所指定的节点的左子节点
 */
#define  bitree_left(node) ((node)->left)

/**
 * node所指定的右子节点
 */
#define  bitree_right(node) ((node)->right)

#endif //DATA_STRUCTURE_TEST_BITREE_H
