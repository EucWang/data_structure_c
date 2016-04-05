//
// Created by wangxn on 2016/4/5.
//

#include "bitree_avl.h"
#include <stdio.h>
#include <string.h>


static void destroy_right(BiTree_AVL *tree_avl, BiTreeNode *node);

static void destroy_left(BiTree_AVL *tree_avl, BiTreeNode *node);

static void rotate_left(BiTreeNode **node);

static void rotate_right(BiTreeNode **node);

static int insert(BiTree_AVL *tree_avl,
                  BiTreeNode **node,
                  const void *data,
                  int *balance);

static int hide(BiTree_AVL *tree_avl, BiTreeNode *node, const void *data);

static int lookup(BiTree_AVL *tree_avl, BiTreeNode *node, void **data);


/**
 * 初始化
 */
void bitree_avl_init(BiTree_AVL *tree_avl,
                     int (*compare)(const void *key1, const void *key2),
                     void (*destroy)(void *data)) {
    bitree_init(tree_avl, compare, destroy);
    return;
}


/**
 * 销毁
 */
void bitree_avl_destroy(BiTree_AVL *tree_avl) {
    destroy_left(tree_avl, NULL);
    memset(tree_avl, 0, sizeof(BiTree_AVL));
    return;
}


/**
 * 插入
 */
int bitree_avl_insert(BiTree_AVL *tree_avl, const void *data) {
    int balanced = 0;
    return insert(tree_avl, &bitree_root(tree_avl), data, &balanced);
}


/**
 * 移除
 */
int bitree_avl_remove(BiTree_AVL *tree_avl, const void *data) {
    return hide(tree_avl, bitree_root(tree_avl), data);
}


/**
 * 查找
 */
int bitree_avl_lookup(BiTree_AVL *tree_avl, void **data) {
    return lookup(tree_avl, bitree_root(tree_avl), data);
}


/**
 * 内部实现的各个函数
 */

static void destroy_right(BiTree_AVL *tree_avl, BiTreeNode *node) {
    AvlNode **position;

    if (bitree_avl_size(tree_avl) == 0) {
        printf("%s\n", "static void destroy_right fail, tree size is zero");
        return;
    }

    if (node == NULL) {
        position = &(tree_avl->root);
    } else {
        position = &(node->right);
    }

    if (*position != NULL) {
        destroy_left(tree_avl, *position);
        destroy_right(tree_avl, *position);

        if (tree_avl->destroy != NULL) {
            void * node_data = ((AvlNode *)(*position)->data)->data;
            if (node_data != NULL) {
                tree_avl->destroy(node_data);
                printf("%s\n", "static void destroy_right free node_data");
            }
        }
        free((AvlNode *)(*position)->data);
        printf("%s\n", "static void destroy_right free avl_node success");
        free(*position);
        printf("%s\n", "static void destroy_right free node success");
        *position = NULL;
        tree_avl->size--;
    }
    printf("%s\n", "static void destroy_right success");
    return;
}


static void destroy_left(BiTree_AVL *tree_avl, BiTreeNode *node) {
    AvlNode **position;

    if (bitree_avl_size(tree_avl) == 0) {
        printf("%s\n", "static void destroy_left fail, tree size is zero");
        return;
    }

    if (node == NULL) {
        position = &(tree_avl->root);
    } else {
        position = &(node->left);
    }

    if (*position != NULL) {
        destroy_left(tree_avl, *position);
        destroy_right(tree_avl, *position);

        if (tree_avl->destroy != NULL) {
            void * node_data = ((AvlNode *)(*position)->data)->data;
            if (node_data != NULL) {
                tree_avl->destroy(node_data);
                printf("%s\n", "static void destroy_left free node_data");
            }
        }
        free((AvlNode *)(*position)->data);
        printf("%s\n", "static void destroy_left free avl_node success");
        free(*position);
        printf("%s\n", "static void destroy_left free node success");
        *position = NULL;
        tree_avl->size--;
    }
    printf("%s\n", "static void destroy_left success");
    return;
}

static void rotate_left(BiTreeNode **node) {
    BiTreeNode *left, *grandchild;

    left = bitree_left(*node);

    if(((AvlNode *)bitree_data(left))->factor == BITREE_AVL_LFT_HEAVY) {  //LL rotation
        bitree_left(*node) = bitree_right(left); //将left的右子节点踢给node,作为node的左节点
        bitree_right(left) = *node;              //将node作为left的右节点
        *node = left;                            //将left子节点提到原来node的位置

        ((AvlNode *)bitree_data(*node))->factor = BITREE_AVL_BALANCED;  //重置平衡为0
        ((AvlNode *)bitree_data(left))->factor = BITREE_AVL_BALANCED;
    } else {                                                              //LR rotaion
        grandchild = bitree_right(left);
        //TODO

    }

}

static void rotate_right(BiTreeNode **node) {

}

static int insert(BiTree_AVL *tree_avl,
                  BiTreeNode **node,
                  const void *data,
                  int *balance) {

}

/**
 * 移除二叉搜索树中node下的data数据元素,
 * 并非真正的移除,只是将node的元素可用指示器置为不可用
 * 隐藏数据
 */
static int hide(BiTree_AVL *tree_avl, BiTreeNode *node, const void *data) {
    int cmpval, retval;

    if (bitree_is_eob(node)) {
        printf("%s\n", "static hide() function is fail,  the arg node is end of leaf");
        return -1;
    }

    void *node_data = ((AvlNode *) bitree_data(node))->data;
    cmpval = tree_avl->compare(data, node_data);
    if (cmpval < 0) {
        retval = hide(tree_avl, bitree_left(node), data);  //move to left
    } else if (cmpval > 0) {
        retval = hide(tree_avl, bitree_right(node), data);  //move to right
    } else {
        ((AvlNode *) bitree_data(node))->hidden = 1;        //mark the node as hidden
        retval = 0;
    }
    return retval;
}

static int lookup(BiTree_AVL *tree_avl, BiTreeNode *node, void **data) {
    int cmpval, retval;

    if (bitree_is_eob(node)) {
        printf("%s\n", "static lookup() function is fail,  the arg node is end of leaf");
        return -1;
    }

    void *node_data = ((AvlNode *) bitree_data(node))->data;
    cmpval = tree_avl->compare(*data, node_data);
    if (cmpval < 0) {
        retval = lookup(tree_avl, bitree_left(node), data);  //move to left
    } else if (cmpval > 0) {
        retval = lookup(tree_avl, bitree_right(node), data);  //move to right
    } else {
        if (!((AvlNode *) bitree_data(node))->hidden) {  //不是被移除的成员
            *data = &node_data;
            retval = 0;
        } else {
            printf("%s\n", "static lookup() fail, find the data, but the data has remove from tree");
            return -1;
        }
    }
    return retval;
}