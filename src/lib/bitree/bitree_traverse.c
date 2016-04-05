//
// Created by wangxn on 2016/4/1.
//

#include "bitree_traverse.h"
#include <stdio.h>


/**
 * 前序遍历二叉树
 */
int preorder(const BiTreeNode *node, List *list) {

    if (!bitree_is_eob(node)) {
        if (list_ins_next(list, list_tail(list), bitree_data(node)) != 0) {
            printf("%s\n", "preorder() insert node into list fail.");
            return -1;
        }

        //不是没有下级节点的节点
        if (!bitree_is_eob(bitree_left(node))) {
            if (preorder(bitree_left(node), list) != 0) { //递归调用
                printf("%s\n", "preorder() left tree order fail.");
                return -1;
            }

            if(!bitree_is_eob(bitree_right(node))) {
            	if(preorder(bitree_right(node), list) != 0) {//递归调用
                    printf("%s\n", "preorder() right tree order end.");
            		return -1;
            	}
            }
        }
    }

    return 0;
}

/**
 * 中序遍历二叉树
 */
int inorder(const BiTreeNode *node, List *list){
	if(!bitree_is_eob(node)){
		if(!bitree_is_eob(bitree_left(node))){
			if(inorder(bitree_left(node), list) != 0){
				printf("%s\n","inorder() left tree order end");
				return -1;
			}
		}

		if(list_ins_next(list, list_tail(list), bitree_data(node)) != 0){
			printf("%s\n", "inorder() add node to list fail.");
			return -1;
		}

		if(!bitree_is_eob(bitree_right(node))){
			if(inorder(bitree_right(node), list) != 0){
				printf("%s\n", "inorder() right tree order end");
				return -1;
			}
		}
	}

    return 0;
}


/**
 * 后序遍历二叉树
 */
int postorder(const BiTreeNode *node, List *list){

	if(!bitree_is_eob(node)){
		if(!bitree_is_eob(bitree_left(node))){
			if(inorder(bitree_left(node), list) != 0){
				printf("%s\n","postorder() left tree order end");
				return -1;
			}
		}
		if(!bitree_is_eob(bitree_right(node))){
			if(inorder(bitree_right(node), list) != 0){
				printf("%s\n", "postorder() right tree order end");
				return -1;
			}
		}
		if(list_ins_next(list, list_tail(list), bitree_data(node)) != 0){
			printf("%s\n", "postorder() add node to list fail.");
			return -1;
		}
	}

    return 0;
}
