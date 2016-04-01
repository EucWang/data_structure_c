//
// Created by wangxn on 2016/4/1.
//

#include "bitree_traverse.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * 前序遍历二叉树
 */
int preorder(const BiTreeNode *node, List *list) {

    if (!bitree_is_eob(node)) {
        if (list_ins_next(list, list_tail(list), bitree_data(node)) != 0) {
            printf("%s\n", "preorder() insert node into list fail.");
            return -1;
        }

        if (!bitree_is_eob(bitree_left(node))) {
            if (preorder(bitree_left(node), list) != 0) {
                printf("%s\n", "preorder() insert node into list fail.");
                return -1;
                //TODO
            }
        }
    }


    return 0;
}

/**
 * 中序遍历二叉树
 */
int inorder(const BiTreeNode *node, List *list){
    return 0;
}


/**
 * 后序遍历二叉树
 */
int postorder(const BiTreeNode *node, List *list){
    return 0;
}
