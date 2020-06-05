//
// Created by wangxn on 2016/4/1.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bitree.h"
#include <math.h>

/**
 * 二叉树的初始化
 */
void bitree_init(BiTree *tree, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data)) {

    tree->size = 0;
    tree->destroy = destroy;
    tree->compare = compare;
    tree->root = NULL;
    return;
}

/**
 * 二叉树的销毁
 */
void bitree_destroy(BiTree *tree) {

    //remove all the nodes from the tree
    bitree_rem_left(tree, NULL);

    memset(tree, 0, sizeof(BiTree));
    return;
}

/**
 * 将数组数据加入到二叉树指定某节点下， 
 * @param tree  二叉树指针
 * @param node  二叉树某个节点, node为空，或者node必须是叶子节点
 * @param leftOrRight  是左子树还是右子树 1：左子树； 0： 右子树
 * @param data 数组数据， 这里按照 满二叉树形式的数组
 * @param length 数组长度
 */ 
int bitree_from_arr(BiTree *tree, BiTreeNode *node, int leftOrRight, const void ** data, int length) {
    if (tree == NULL) { return -1; }
    if(leftOrRight != 0 && leftOrRight != 1) { return -1; }
    if(data == NULL) { return -1; }

    BiTreeNode *new_node, **postion;

    if (node == NULL) {
        //插入的node的位置为NULL的情况下,向root节点插入数据,但必须树中没有数据的情况下才可以
        if (bitree_size(tree) > 0) {
            printf("%s\n", "bitree_ins_left() args:node == NULL but tree's size not zero. insert fail");
            return -1;
        }
        postion = &tree->root;
    } else {
        if (leftOrRight) { 
            if(bitree_left(node) != NULL) {
                printf("%s\n", "bitree_ins_left() node's left child node is not null. insert fail");
                return -1;
            }
            postion = &node->left;
        } else {
            if(bitree_right(node) != NULL) {
                printf("%s\n", "bitree_ins_right() node's right child node is not null. insert fail");
                return -1;
            }
            postion = &node->right;
        }
    }
    
    BiTreeNode ** newNodes = malloc(length * sizeof(void *));
    int i;
    for (i = 0; i < length; i++) {
        newNodes[i] = (BiTreeNode *) malloc(sizeof(BiTreeNode));
        if (newNodes[i] == NULL) {
            printf("%s\n", "bitree_ins_left() malloc new memory fail. insert fail");
            return -1;
        }

        newNodes[i]->data = (void *)(*(data + i));
        newNodes[i]->left = NULL;
        newNodes[i]->right = NULL;
    }

    //构造数组的子二叉树
    int deep = 1;
    int curLineIdx = 0;
    newNodes[0]->left = newNodes[1];
    newNodes[0]->right = newNodes[2];
    for (i = 1; i < length; i++) {
        if(i >= pow(2, deep+1)) {
            deep++;
        }
        curLineIdx = i - pow(2, deep);
        int left = pow(2, deep+1) + curLineIdx * 2;
        int right = pow(2, deep+1) + curLineIdx * 2 + 1;
        if ( left < length) {
            newNodes[i]->left = newNodes[left];
        }            
        if (right < length) {
            newNodes[i]->right = newNodes[right];
        }
    }
    
    *postion = newNodes[0];
    free(newNodes);
    tree->size += length;
}

/**
 * 向二叉树的指定节点的左子节点位置插入数据
 * @param tree:
 * @param node: 插入的node的位置为NULL的情况下,向root节点插入数据,但必须树中没有数据的情况下才可以
 * @param data:
 * @return : 返回0: 表示成功, 返回-1: 表示失败
 */
int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data) {
    BiTreeNode *new_node, **postion;

    if (node == NULL) {
        //插入的node的位置为NULL的情况下,向root节点插入数据,但必须树中没有数据的情况下才可以
        if (bitree_size(tree) > 0) {
            printf("%s\n", "bitree_ins_left() args:node == NULL but tree's size not zero. insert fail");
            return -1;
        }

        postion = &tree->root;
    } else {
        if (bitree_left(node) != NULL) {
            printf("%s\n", "bitree_ins_left() node's left child node is not null. insert fail");
            return -1;
        }
        postion = &node->left;
    }

    new_node = (BiTreeNode *) malloc(sizeof(BiTreeNode));
    if (new_node == NULL) {
        printf("%s\n", "bitree_ins_left() malloc new memory fail. insert fail");
        return -1;
    }

    new_node->data = (void *) data;
    new_node->left = NULL;
    new_node->right = NULL;
    *postion = new_node;

    tree->size++;
    return 0;
}

/**
 * 向二叉树的指定节点的右子节点位置插入数据
 * @return : 返回0: 表示成功, 返回-1: 表示失败
 */
int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data) {
    BiTreeNode *new_node, **postion;

    if (node == NULL) {
        //插入的node的位置为NULL的情况下,向root节点插入数据,但必须树中没有数据的情况下才可以
        if (bitree_size(tree) > 0) {
            printf("%s\n", "bitree_ins_right() args:node == NULL but tree's size not zero. insert fail");
            return -1;
        }

        postion = &tree->root;
    } else {
        if (bitree_right(node) != NULL) {
            printf("%s\n", "bitree_ins_right() node's right child node is not null. insert fail");
            return -1;
        }
        postion = &node->right;
    }

    new_node = (BiTreeNode *) malloc(sizeof(BiTreeNode));
    if (new_node == NULL) {
        printf("%s\n", "bitree_ins_right() malloc new memory fail. insert fail");
        return -1;
    }

    new_node->data = (void *) data;
    new_node->left = NULL;
    new_node->right = NULL;
    *postion = new_node;

    tree->size++;
    return 0;
}

int bitree_ins(BiTree *tree, const void *data) {
    if (tree->compare == NULL) {
        printf("%s\n", "bitree_ins() fail, not find function compare()");
        return -1;
    }

    BiTreeNode **current = &(tree->root);

    printf("root");
    while (1) {
        if (*current != NULL) {
            if (tree->compare((*current)->data, data) > 0) {
                current = &((*current)->left);
                printf("->left");
            } else {
                current = &((*current)->right);
                printf("->right");
            }
        } else {
            BiTreeNode *new_node = (BiTreeNode *) malloc(sizeof(BiTreeNode));
            if (new_node == NULL) {
                printf("%s\n", "bitree_ins_right() malloc new memory fail. insert fail");
                return -1;
            }

            new_node->data = (void *) data;
            new_node->left = NULL;
            new_node->right = NULL;
            (*current) = new_node;
            tree->size++;
            break;
        }
    }
    printf("\n");
}

/**
 * 从二叉树的指定节点的左子节点位置删除数据
 */
void bitree_rem_left(BiTree *tree, BiTreeNode *node) {
    BiTreeNode **position;
    if (bitree_size(tree) == 0) {
        printf("%s\n", "bitree_rem_left() no child node in tree, remove nothing");
        return;
    }

    //如果node参数为NULL,则尝试删除根节点
    if (node == NULL) {
        position = &tree->root;
    } else {
        position = &node->left;
    }

    //递归调用
    if (*position != NULL) {
        bitree_rem_left(tree, *position);
        bitree_rem_right(tree, *position);

        if (tree->destroy != NULL) {
            printf("%s\n", "bitree_rem_left() when remove node from tree, destroy data in node.");
            tree->destroy((*position)->data);
        }

        free(*position);
        *position = NULL;
        tree->size--;
    }

    return;
}

/**
 * 从二叉树的指定节点的右子节点位置删除数据
 */
void bitree_rem_right(BiTree *tree, BiTreeNode *node) {
    BiTreeNode **position;
    if (bitree_size(tree) == 0) {
        printf("%s\n", "bitree_rem_right() no child node in tree, remove nothing");
        return;
    }

    //如果node参数为NULL,则尝试删除根节点
    if (node == NULL) {
        position = &tree->root;
    } else {
        position = &node->right;
    }

    //递归调用
    if (*position != NULL) {
        bitree_rem_left(tree, *position);
        bitree_rem_right(tree, *position);

        if (tree->destroy != NULL) {
            printf("%s\n", "bitree_rem_right() when remove node from tree, destroy data in node.");
            tree->destroy((*position)->data);
        }

        free(*position);
        *position = NULL;
        tree->size--;
    }

    return;
}

/**
 * 将left和right所指定的两颗二叉树合并为单颗二叉树.
 * 合并完成之后, 参数data所代表的数据存储在merge的根节点中,而
 * left和right则代表该根节点的左右子树.
 * 一旦完成合并,left和right就好像在他们之上执行了bitree_destroy操作一样
 */
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data) {

    bitree_init(merge, NULL, left->destroy);

    if (bitree_ins_left(merge, NULL, data) != 0) {
        bitree_destroy(merge);
        printf("%s\n", "bitree_merge() insert data to the merged bitree root node fail");
        return -1;
    }

    bitree_root(merge)->left = bitree_root(left);
    bitree_root(merge)->right = bitree_root(right);

    merge->size = merge->size + bitree_size(left) + bitree_size(right);

    left->root = NULL;
    left->size = 0;
    right->root = NULL;
    right->size = 0;

    return 0;
}
