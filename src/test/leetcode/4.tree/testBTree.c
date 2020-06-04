//
// Created by wangxn on 2018/5/17.
//

#include <stdio.h>
#include "testBTree.h"
#include "BTree.h"
#include "../../../lib/arr_tool/arrTool.h"
#include <limits.h>

void testMaxDepth(){

    TreeNode *root = createBTree(3);
    TreeNode *t1 = createBTree(9);
    TreeNode *t2 = createBTree(20);
    TreeNode *t3 = createBTree(15);
    TreeNode *t4 = createBTree(7);
    
    addLeaf(root, t1, t2);
    addLeaf(t2, t3, t4);

    int depth = maxDepth(root);
    printf("tree depth is %d\n", depth);

}

void testMaxDepth2(){

    TreeNode *root = createBTree(3);

    TreeNode *t1 = createBTree(9);
    TreeNode *t2 = createBTree(20);

    TreeNode *t3 = createBTree(15);
    TreeNode *t4 = createBTree(7);

    TreeNode *t5 = createBTree(5);
    TreeNode *t6 = createBTree(6);

    TreeNode *t7 = createBTree(7);
    TreeNode *t8 = createBTree(8);

    TreeNode *t9 = createBTree(9);
    TreeNode *t10 = createBTree(10);

    TreeNode *t11 = createBTree(11);
    TreeNode *t12 = createBTree(12);

    TreeNode *t13 = createBTree(13);
    TreeNode *t14 = createBTree(14);

    TreeNode *t15 = createBTree(15);
    TreeNode *t16 = createBTree(16);

    TreeNode *t17 = createBTree(17);
    TreeNode *t18 = createBTree(18);

    TreeNode *t19 = createBTree(19);
    TreeNode *t20 = createBTree(20);

    TreeNode *t21 = createBTree(21);

    addLeaf(root, t1, t2);
    addLeaf(t2, t3, t4);
    addLeaf(t4, t6,t5);
    addLeaf(t6,t14,t13);
    addLeaf(t14,t19,t18);

    addLeaf(t3,t8,t7);
    addLeaf(t8,t15, NULL);
    addLeaf(t15, NULL, t20);
    addLeaf(t20, t21,NULL);

    addLeaf(t1, t10, t9);
    addLeaf(t10, t12, t11);
    addLeaf(t11, t17,t16);

    int depth = maxDepth(root);
    printf("tree depth is %d\n", depth);

}

void printTreeNode(TreeNode* item) {
    if(item) {
        printf("%d\t", item->val);
        printTreeNode(item->left);
        printTreeNode(item->right);
    } else{
        printf("\n");
    }
}

void testArr2BTree(){
    printf("\ntest arr1\n");
    int arr[] = {
            1,
            2,      3,
            INT_MIN,  4,  5,  6,
            INT_MIN, INT_MIN, INT_MIN, 7, 8
    };
    printfArr(arr,12);
    TreeNode* root = array2BTree(arr, 12);
    printTreeNode(root);

    //arr2
    int arr2[] = {
            3, 9, 20, INT_MIN, INT_MIN, 15, 7
    };
    printf("\ntest arr2\n");
    printfArr(arr2,7);
    TreeNode* root2 = array2BTree(arr2, 7);
    printTreeNode(root2);
}

void testIsValidBST() {
    int arr[] = {2, 1, 3};
    TreeNode *root = array2BTree(arr, 3);
    printf("retVal is %d\n", isValidBST2(root));

    int arr2[] = {5, 1, 4, 0, 0, 3, 6};
    TreeNode *root2 = array2BTree(arr2, 7);
    printf("retVal is %d\n", isValidBST2(root2));

    int arr3[] = {10, 5, 15, INT_MIN, INT_MIN, 6, 20};
    TreeNode *root3 = array2BTree(arr3, 7);
    printf("retVal is %d\n", isValidBST2(root3));

    int arr4[] = {5, 14, INT_MIN, 1};
    TreeNode *root4 = array2BTree(arr4, 4);
    printf("retVal is %d\n", isValidBST2(root4));

}

/**
 *  给定一个二叉树，检查它是否是镜像对称的。
 */
void testIsSymmetric() {
    int arr[] = {1, 2, 2, 3, 4, 4, 3};
    TreeNode *root = array2BTree(arr, 7);
    printf("retVal is %d\n", isSymmetric(root));

    int arr2[] = {1, 2, 2, INT_MIN, 3, INT_MIN, 3};
    TreeNode *root2 = array2BTree(arr2, 7);
    printf("retVal is %d\n", isSymmetric(root2));
}

/**
 * 二叉树的层次遍历
        给定一个二叉树，返回其按层次遍历的节点值。
 */
void testLevelOrder1(){
    int arr[] = {3,9, 20, INT_MIN, INT_MIN, 15, 7};
    TreeNode* root = array2BTree(arr, 7);

    int* a = 0;
    int rowSize = 0;
    int** retArr = levelOrder(root, &a, &rowSize);
    printf("column size is:\n[");
    for (int i = 0; i < rowSize; ++i) {
        printf("%d ", *(a+i));
    }
    printf("]\n");

    printf("row size is %d\n", rowSize);

    for (int j = 0; j < rowSize; ++j) {
        printf("[");
        for (int i = 0; i < *(a + j); ++i) {
            printf("%d ", retArr[j][i]);
        }
        printf("]\n");
    }
}
void testLevelOrder2(){
    int arr[] = {10, 5, 15, INT_MIN, INT_MIN, 6, 20};
    TreeNode* root = array2BTree(arr, 7);

    int* a = 0;
    int rowSize = 0;
    int** retArr = levelOrder(root, &a, &rowSize);
    printf("column size is:\n[");
    for (int i = 0; i < rowSize; ++i) {
        printf("%d ", *(a+i));
    }
    printf("]\n");

    printf("row size is %d\n", rowSize);

    for (int j = 0; j < rowSize; ++j) {
        printf("[");
        for (int i = 0; i < *(a + j); ++i) {
            printf("%d ", retArr[j][i]);
        }
        printf("]\n");
    }
}

void testLevelOrder3(){
    int arr[] = {1,2,3, INT_MIN, 4, 5,6, INT_MIN, INT_MIN, INT_MIN, 7};
    TreeNode* root = array2BTree(arr, 11);

    int* a = 0;
    int rowSize = 0;
    int** retArr = levelOrder(root, &a, &rowSize);
    printf("column size is:\n[");
    for (int i = 0; i < rowSize; ++i) {
        printf("%d ", *(a+i));
    }
    printf("]\n");

    printf("row size is %d\n", rowSize);

    for (int j = 0; j < rowSize; ++j) {
        printf("[");
        for (int i = 0; i < *(a + j); ++i) {
            printf("%d ", retArr[j][i]);
        }
        printf("]\n");
    }
}

void printTree(TreeNode* root) {

    int* a = 0;
    int rowSize = 0;
    int** retArr = levelOrder(root, &a, &rowSize);
//    printf("column size is:\n[");
//    for (int i = 0; i < rowSize; ++i) {
//        printf("%d ", *(a+i));
//    }
//    printf("]\n");

//    printf("row size is %d\n", rowSize);

    for (int j = 0; j < rowSize; ++j) {
        printf("[");
        for (int i = 0; i < *(a + j); ++i) {
            printf("%d ", retArr[j][i]);
        }
        printf("]\n");
    }
}

void testLevelOrder4(){
    int arr[] = {1};
    TreeNode* root = array2BTree(arr, 1);
    printTree(root);
}

void testSize(){
    int arr[] = {3,9, 20, INT_MIN, INT_MIN, 15, 7};
    int size = 0;

    TreeNode* root = array2BTree(arr, 7);
    sizeOfTree(root, &size);
    printf("size of tree is %d\n", size);


    int arr2[] = {1, 2, 2, 3, 4, 4, 3};
    TreeNode *root2 = array2BTree(arr2, 7);
    size = 0;
    sizeOfTree(root2, &size);
    printf("size of tree is %d\n", size);

    int arr3[] = {1};
    TreeNode *root3 = array2BTree(arr2, 1);
    size = 0;
    sizeOfTree(root3, &size);
    printf("size of tree is %d\n", size);
}

void testCountOfTreeAtDepth(){
    int arr[] = {3,9, 20, INT_MIN, INT_MIN, 15, 7};
    int size = 0;

    TreeNode* root = array2BTree(arr, 7);
    sizeOfTree(root, &size);
    printf("size of tree is %d\n", size);

    int count1 = 0;
    countOfTreeAtDepth(root, &count1, 1);
    printf("count at depth %d is %d\n", 1, count1);
    int count2 = 0;
    countOfTreeAtDepth(root, &count2, 2);
    printf("count at depth %d is %d\n", 2, count2);
    int count3 = 0;
    countOfTreeAtDepth(root, &count3, 3);
    printf("count at depth %d is %d\n", 3, count3);
}

void testSortedArrToBST() {

    int arr[] = {-10, -3, 0, 5, 9};
    TreeNode* root = sortedArrayToBST(arr, 5);
    printTree(root);
}

void testBTree(){
//    testArr2BTree();
//    testMaxDepth();
//    testMaxDepth2();
//    testIsValidBST();
//    testIsSymmetric();

//    testLevelOrder1();
//    testLevelOrder2();
//    testLevelOrder3();
//    testLevelOrder4();

//    testSize();
//    testCountOfTreeAtDepth();

    testSortedArrToBST();
}