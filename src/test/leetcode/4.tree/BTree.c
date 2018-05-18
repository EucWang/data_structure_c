//
// Created by wangxn on 2018/5/17.
//

#include "BTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
TreeNode* createBTree(int val){
    TreeNode* node = malloc(sizeof(TreeNode));
    if (node == NULL) {
        printf("\n##### malloc TreeNode fail, memory error. ####\n");
        return NULL;
    }
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void addLeaf(TreeNode* root, TreeNode* left, TreeNode* right){
    root->left = left;
    root->right = right;
}

/**
 * 将一个数组转换成一个二叉树,
 * 第一个元素对应根节点,
 * 第二个元素, 第三个元素 表示 根节点的左子树, 右子树
 * 第三个, 第四个, 第五个, 第六个 元素 表示 左子树的左子树,右子树,  右子树的左子树,右子树,
 * 依次类推
 * @param nums
 * @return
 */
TreeNode* array2BTree(int* nums, int size){
    if (size <= 0 || nums == NULL) {
        return NULL;
    }

    TreeNode* trees = malloc(size * sizeof(TreeNode));
    memset(trees, 0, size * sizeof(TreeNode));

    int depth = 0;
    int index = 0;
    while ((index = (pow(2, depth) - 1)) < size) {  // 2的n次方- 1 为这一层 最左的一个元素在 数组中的索引值
        for (int i = 0; i < pow(2, depth) && index < size; ++i) {
            if (nums[index] && nums[index] != INT_MIN) {
                (trees[index]).val = nums[index];
                int leftLeafIndex = pow(2, depth+1) - 1 + i*2;
                int rightLeafIndex = leftLeafIndex + 1;
                if (leftLeafIndex < size) {
                    trees[index].left = trees + leftLeafIndex;
                }
                if (rightLeafIndex < size) {
                    trees[index].right = trees + rightLeafIndex;
                }
            } else{
                int parentIndex = pow(2, depth-1) - 1 + i/2;   //让父节点的子节点指向NULL
                if(i%2){   //0 left: 1: right;
                    trees[parentIndex].right = NULL;
                } else{
                    trees[parentIndex].left = NULL;
                }
            }
            index++;
        }
        depth++;
    }
    return trees;
}

/**
 *  二叉树的最大深度
        给定一个二叉树，找出其最大深度。
        二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。
    说明:
        叶子节点是指没有子节点的节点。
    示例：
        给定二叉树 [3,9,20,null,null,15,7]，
        3
       / \
      9  20
        /  \
       15   7
        返回它的最大深度 3 。
 * @param root
 * @return
 */
int maxDepth(TreeNode* root){
    int deep = 0;
    if (root != NULL) {
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);

        if (leftDepth >= rightDepth) {
            deep = leftDepth + 1;
        } else {
            deep = rightDepth + 1;
        }
    }
    return deep;
}

bool validNode(TreeNode* item, int min, int max, TreeNode* mostLeft, TreeNode* mostRight) {
    if(item) {
        if (item != mostLeft && item != mostRight) {
            if (item->val <= min || item->val >= max) {
                return false;
            }
        } else if (item == mostLeft) {
            if (item->val >= max) {
                return false;
            }
        } else if (item == mostRight) {
            if (item->val <= min) {
                return false;
            }
        }
        return validNode(item->left, min, item->val, mostLeft, mostRight) && validNode(item->right, item->val, max, mostLeft, mostRight);
    }

    return true;
}

/**
 * 得到最左子树,或者最右子树的节点
 * @param item
 * @param isLeftOrRight  true: is Left, false : is right
 * @return
 */
TreeNode* getMostLeftOrRight(TreeNode* item, bool isLeftOrRight) {
    if (isLeftOrRight){
        if (item->left) {
            return getMostLeftOrRight(item->left, isLeftOrRight);
        }
    } else {
        if (item->right) {
            return getMostLeftOrRight(item->right, isLeftOrRight);
        }
    }
    return item;
}

/**
 * 验证二叉搜索树
    给定一个二叉树，判断其是否是一个有效的二叉搜索树。
    一个二叉搜索树具有如下特征：
        节点的左子树只包含小于当前节点的数。
        节点的右子树只包含大于当前节点的数。
        所有左子树和右子树自身必须也是二叉搜索树。
    示例 1:  输入:   2
                   / \
                  1   3
        输出: true
    示例 2:  输入:   5
                   / \
                  1   4
                     / \
                    3   6
        输出: false
    解释:   输入为: [5,1,4,null,null,3,6]。   根节点的值为 5 ，但是其右子节点值为 4 。

    思路:
        中值比较,
        先拿到树最最子树节点的值即为当前树的最小可能值
        同时拿到最右子树节点的值即为当前树可能的最大值,
        然后依次判断左树和右树

 * @param root
 * @return
 */
bool isValidBST(TreeNode *root){

    if (root ==NULL){  //空树的情况
        return true;
    }

    if (root->left == NULL && root->right == NULL) {  //只有一个节点的情况
        return true;
    }


    TreeNode* mostLeft = getMostLeftOrRight(root, true);
    TreeNode* mostRight = getMostLeftOrRight(root, false);

    if (mostLeft->val >= mostRight->val) {
        return false;
    }

    return validNode(root, mostLeft->val, mostRight->val, mostLeft, mostRight);
}

/**
 *
 * @param item
 * @param currentMin
 * @param hasMostLeft
 * @return
 */
bool isOrder(TreeNode* item, int* currentMin, bool* hasMostLeft) {

    if (item == NULL) {
        return true;
    }

    if (!isOrder(item->left, currentMin, hasMostLeft)) {   //先遍历左子树, 会一直找到最左子树节点
        return false;
    }

    if (!(*hasMostLeft)) {
        *hasMostLeft = true;
        *currentMin = item->val;  //找到最左子树节点, 得到整个树的最小值
    } else {
        if (item->val <= *currentMin) {   //当前节点的值比 真个树的最小值还小, 返回false
            return false;
        } else {
            *currentMin = item->val;    //当前最小值赋值
        }
    }

    if (!isOrder(item->right, currentMin, hasMostLeft)) {  //然后遍历右子树
        return false;
    }

    return true;

}

/**
 * 验证二叉搜索树 第二种实现方式
 *
 * 先遍历到整棵树最左子树节点上, 然后依次遍历左子节点, 当前节点, 右节点,和当前树中的最小值比较,
 *
 * @param root
 * @return
 */
bool isValidBST2(TreeNode* root) {
    int last = 0;
    bool hasMostLeft = false;
    return isOrder(root, &last, &hasMostLeft);
}

/**
 * 递归方式比较两个树是否是镜像
 * @param left
 * @param right
 * @return
 */
bool equalTree(TreeNode* left, TreeNode* right) {
    if (left == NULL && right == NULL) {
        return true;
    } else if (left == NULL || right == NULL) {
        return false;
    }
    if (left->val != right->val) {
        return false;
    }
    return equalTree(left->left, right->right) && equalTree(left->right, right->left);
}

/**
 * 对称二叉树: 给定一个二叉树，检查它是否是镜像对称的。
    例如，二叉树 [1,2,2,3,4,4,3] 是对称的。    1
                                           / \
                                          2   2
                                         / \ / \
                                        3  4 4  3
    但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:    1
                                                       / \
                                                      2   2
                                                       \   \
                                                       3    3
    说明:    如果你可以运用递归和迭代两种方法解决这个问题，会很加分。
 * @param root
 * @return
 */
bool isSymmetric(TreeNode *root) {
    if (root == NULL) {
        return true;
    }
    if (root->left == NULL && root->right == NULL) {
        return true;
    } else if (root->left == NULL || root->right == NULL) {
        return false;
    }
    return equalTree(root->left, root->right);
}

/**
 * 当前树所有节点的数量
 * @param root
 * @param size
 */
void sizeOfTree(TreeNode* root, int* size) {
    if (root != NULL) {
        (*size)++;
        sizeOfTree(root->left, size);
        sizeOfTree(root->right, size);
    }
}

/**
 * 递归遍历树, 获取第depth层有多少个节点
 * @param item             in
 * @param count            out   统计的位于第depth层的节点数
 * @param currentDepth     in    当前递归到哪一层
 * @param targetDepth      in    目标层数
 */
void countNext(TreeNode* item, int** count, int currentDepth, int targetDepth) {
    if (item == NULL) {
        return;
    }

    if (targetDepth == currentDepth) {
        (**count)++;
    } else if( targetDepth > currentDepth){
        countNext(item->right, count, currentDepth + 1, targetDepth);
        countNext(item->left, count, currentDepth + 1, targetDepth);
    }
}

/**
 * 获取位于第depth层的树节点的数量
 * @param root
 * @param count
 * @param depth
 */
void countOfTreeAtDepth(TreeNode* root, int* count, int depth) {
    if (root == NULL || depth < 1) {
        *count = -1;
        return;
    }
    if (root != NULL && depth == 1) {
        *count = 1;
        return;
    }
    countNext(root->right, &count, 2, depth);
    countNext(root->left, &count, 2, depth);
}

/**
 * 递归获得第targetDepth层所有的节点数据
 * @param item       in  递归遍历的节点
 * @param container  out 节点数据保存的数组
 * @param size       in  当前这一层有多少节点
 * @param curIndex   in  当前item在当前层所有节点中的索引
 * @param curDepth    in  当前递归的层数
 * @param targetDepth  in 当前目标需要到达的层数
 */
void getValAtDepth(TreeNode* item, int* container, int size, int* curIndex, int curDepth, int targetDepth) {
    if (item == NULL) {
        return;
    }
    if (*curIndex >= size) {
        return;
    }
    if (targetDepth == curDepth) {
        *(container+ *curIndex) = item->val;
        (*curIndex)++;
    } else if(targetDepth > curDepth){
        getValAtDepth(item->left, container, size, curIndex, curDepth + 1, targetDepth);
        getValAtDepth(item->right, container, size, curIndex, curDepth + 1, targetDepth);
    }
}

/**
 * @param root       in  树根节点
 * @param container  out 待保存的数据
 * @param size       in  当前层有多少节点
 * @param depth      in  当前需要获取的是第depth层
 */
void getValOfTreeAtDepth(TreeNode* root, int** container, int size, int depth){
    if (root == NULL || depth < 1) {
        return;
    }

    int* arr = malloc(size * sizeof(int));   //分配tmp个int
    memset(arr,0, size * sizeof(int));
    *container = arr;

    if (root != NULL && depth == 1) {
        *arr = root->val;
        return;
    }

    int index = 0;
    getValAtDepth(root->left, arr, size, &index, 2, depth);
    getValAtDepth(root->right, arr, size, &index, 2, depth);

}

/**
 * 二叉树的层次遍历 : 给定一个二叉树，返回其按层次遍历的节点值。 （即逐层地，从左到右访问所有节点）。
    例如: 给定二叉树: [3,9,20,null,null,15,7],        3
                                                   / \
                                                  9  20
                                                    /  \
                                                   15   7
    返回其层次遍历结果：   [ [3],
                          [9,20],
                          [15,7] ]
 * @param root
 * @param columnSizes
 * @param returnSize
 * @return
 */
int** levelOrder(/*in*/TreeNode* root, /*out*/int** columnSizes, /*out*/int* returnSize) {
    *returnSize = maxDepth(root);  //最大深度
    int nodeCount;

    int* a = malloc((*returnSize) * sizeof(int));
    memset(a, 0, (*returnSize)* sizeof(int));
    *columnSizes = a;

    int** retVal = malloc((*returnSize) * sizeof(int*));
    for (int i = 0; i < *returnSize; ++i) {               //遍历每一层
        nodeCount = 0;
        countOfTreeAtDepth(root, &nodeCount, i+1);  //得到第i层的节点数
        *(a + i) = nodeCount;

        getValOfTreeAtDepth(root, (retVal + i), nodeCount, i+1);  //获得第i层所有节点的数据
    }
    return retVal;
}

TreeNode* getChildTree(int* nums, int left, int right) {
    if (right < left) {
        return NULL;
    }else if (right == left) {
        return createBTree(nums[left]);
    } else{
        int middle = left + (right - left + 1)/2;

        TreeNode* child = createBTree(nums[middle]);

        child->left = getChildTree(nums, left, middle - 1);
        child->right = getChildTree(nums, middle + 1, right);

        return child;
    }
}

/**
 *  将有序数组转换为二叉搜索树 : 将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树。
    本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。
    示例:给定有序数组: [-10,-3,0,5,9],
        一个可能的答案是：[0,-3,9,-10,null,5]，它可以表示下面这个高度平衡二叉搜索树：     0
                                                                                 / \
                                                                               -3   9
                                                                               /   /
                                                                             -10  5
 * @param nums
 * @param numsSize
 * @return
 */
TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    if (nums == NULL || numsSize <= 0) {
        return NULL;
    }

    TreeNode* root;
    if (numsSize == 1) {
        root = createBTree(*nums);
        return root;
    }

    int left = 0;
    int right = numsSize -1;
    return getChildTree(nums, left, right);
}