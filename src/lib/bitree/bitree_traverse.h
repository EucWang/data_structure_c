// 二叉树遍历
// Created by wangxn on 2016/4/1.
//

#ifndef DATA_STRUCTURE_TEST_BITREE_TRAVERSE_H
#define DATA_STRUCTURE_TEST_BITREE_TRAVERSE_H

#include "../list/list.h"
#include "bitree.h"
#include "bitree_traverse.h"

/**
 * 前序遍历二叉树
 */
int preorder(const BiTreeNode *node, List *list);

/**
 * 中序遍历二叉树
 */
int inorder(const BiTreeNode *node, List *list);

/**
 * 后序遍历二叉树
 */
int postorder(const BiTreeNode *node, List *list);

#endif //DATA_STRUCTURE_TEST_BITREE_TRAVERSE_H
