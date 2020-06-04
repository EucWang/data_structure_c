//
// Created by wangxn on 2016/4/6.
//

#include "test.h"
#include "./student/student.h"
#include "../lib/bitree/bitree_avl.h"
#include <stdio.h>

static void printBitree(BiTreeNode *node);

void bitree_avl_test() {
    BiTree_AVL bitree;

    bitree_avl_init(&bitree, (void *) studn_compare, (void *) studn_destroy);

    bitree_avl_insert(&bitree, studn_get_init(1, "zhangsan", 1, 32, 9));
    bitree_avl_insert(&bitree, studn_get_init(2, "lisi", 1, 32, 8));
    bitree_avl_insert(&bitree, studn_get_init(3, "wangdazhui", 1, 32, 9));
    bitree_avl_insert(&bitree, studn_get_init(4, "zhangquandan", 1, 32, 10));
    bitree_avl_insert(&bitree, studn_get_init(5, "zhangfei", 1, 32, 9));
    bitree_avl_insert(&bitree, studn_get_init(6, "liucuihua", 0, 22, 11));
    bitree_avl_insert(&bitree, studn_get_init(7, "liucuihua", 0, 22, 11));
    bitree_avl_insert(&bitree, studn_get_init(8, "liucuihua", 0, 22, 11));
    bitree_avl_insert(&bitree, studn_get_init(9, "liucuihua", 0, 22, 11));
    bitree_avl_insert(&bitree, studn_get_init(10, "liucuihua", 0, 22, 11));
    bitree_avl_insert(&bitree, studn_get_init(11, "liucuihua", 0, 22, 11));
    bitree_avl_insert(&bitree, studn_get_init(12, "liucuihua", 0, 22, 11));
    bitree_avl_insert(&bitree, studn_get_init(13, "liucuihua", 0, 22, 11));
    bitree_avl_insert(&bitree, studn_get_init(14, "liucuihua", 0, 22, 11));
    bitree_avl_insert(&bitree, studn_get_init(15, "liucuihua", 0, 22, 11));
    bitree_avl_insert(&bitree, studn_get_init(16, "liucuihua", 0, 22, 11));
    bitree_avl_insert(&bitree, studn_get_init(17, "liucuihua", 0, 22, 11));
    bitree_avl_insert(&bitree, studn_get_init(18, "liucuihua", 0, 22, 11));
    bitree_avl_insert(&bitree, studn_get_init(19, "liucuihua", 0, 22, 11));
    bitree_avl_insert(&bitree, studn_get_init(20, "liucuihua", 0, 22, 11));
    bitree_avl_insert(&bitree, studn_get_init(21, "liucuihua", 0, 22, 11));

    printf("%s%d\n", "bitree avl size :", bitree_avl_size(&bitree));


    BiTreeNode *node = bitree_root(&bitree);
    printBitree(node);
    printf("\n");

    printf("%s\n", "============== release data begin ===============");
    bitree_destroy(&bitree);
    printf("%s\n", "============== release data end ===============");
}

static void printBitree(BiTreeNode *node) {
    if (bitree_is_eob(node)) {
        printf("-1");
        return;
    }
    Student *student = (Student *) ((AvlNode *) (node->data))->data;
    if (student != NULL) {
        printf("%d", student->_id);
    } else {
        printf("-1");
        return;
    }

    if (node->left == NULL && node->right == NULL) {
        return;
    } else if (node->left == NULL && node->right != NULL) {
        printf(": {");
        printf("-1");
        printf("; ");
        printBitree(node->right);
        printf("}");
    } else if (node->right == NULL && node->left != NULL) {
        printf(": {");
        printBitree(node->left);
        printf("; -1");
        printf("}");
    } else {
        printf(": {");
        printBitree(node->left);
        printf("; ");
        printBitree(node->right);
        printf("}");
    }

}