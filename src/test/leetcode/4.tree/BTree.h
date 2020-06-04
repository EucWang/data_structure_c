//
// Created by wangxn on 2018/5/17.
//

#ifndef DATA_STRUCTURE_C_TREE_H
#define DATA_STRUCTURE_C_TREE_H

#include <stdbool.h>

typedef struct TreeNode_ {
    int val;
    struct TreeNode_* left;
    struct TreeNode_* right;
}TreeNode;

TreeNode* createBTree(int val);

TreeNode* array2BTree(int* nums, int size);

void addLeaf(TreeNode* root, TreeNode* left, TreeNode* right);


int maxDepth(TreeNode* root);

/**
 * 验证二叉搜索树
 * 中值比对
 * @param root
 * @return
 */
bool isValidBST(TreeNode *root);

/**
 * 验证二叉搜索树
 * 左中右 遍历, 和最小值比对
 * @param root
 * @return
 */
bool isValidBST2(TreeNode *root);

/**
 * 给定一个二叉树，检查它是否是镜像对称的
 * 递归比对
 * @param root
 * @return
 */
bool isSymmetric(TreeNode *root);


void sizeOfTree(TreeNode* root, int* count);

/**
 * 计算第depth层树有多少个节点
 * @param root
 * @param count
 * @param depth
 */
void countOfTreeAtDepth(TreeNode* root, int* count, int depth);

/**
 * 二叉树的层次遍历 : 给定一个二叉树，返回其按层次遍历的节点值。
 * @param root
 * @param columnSizes
 * @param returnSize
 * @return
 */
int** levelOrder(TreeNode* root, int** columnSizes, int* returnSize);

/**
 * 将有序数组转换为二叉搜索树
    将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树。
    本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。
 * @param nums
 * @param numsSize
 * @return
 */
TreeNode* sortedArrayToBST(int* nums, int numsSize);
#endif //DATA_STRUCTURE_C_TREE_H
