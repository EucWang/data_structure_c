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
    printf("root");
    int retval = insert(tree_avl, &bitree_root(tree_avl), data, &balanced);
    printf("\n");
    return  retval;
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
//    AvlNode **position;
    BiTreeNode **position;

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
//    AvlNode **position;
    BiTreeNode **position;

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
    	//			       node                                   grandchild
    	//          left            right                      left         node
    	//         gl  grandchild                             gl   x       x2
    	//             [x]      [x2]
    	//
        grandchild = bitree_right(left);    //node的左子节点的右子节点 ====简称 R2
        bitree_right(left) = bitree_left(grandchild);   // R2 的左子节点替代R2的位置，作为node的左子节点的右子节点
        bitree_left(grandchild) = left;    //将left作为 R2的左子节点， R2作为left的父节点，R2顶替node的位置
        bitree_left(*node) = bitree_right(grandchild);  //R2的右子节点踢给node的左子节点位置，
        bitree_right(grandchild) = *node;       //R2的右子节点指向node,node作为R2的子节点

        switch(((AvlNode *)bitree_data(grandchild))->factor) {
        case BITREE_AVL_LFT_HEAVY:
        	((AvlNode *)bitree_data(*node))->factor = BITREE_AVL_RGT_HEAVY;
        	((AvlNode *)bitree_data(left))->factor = BITREE_AVL_BALANCED;
        	break;
        case BITREE_AVL_BALANCED:
        	((AvlNode *)bitree_data(*node))->factor = BITREE_AVL_BALANCED;
        	((AvlNode *)bitree_data(left))->factor = BITREE_AVL_BALANCED;
        	break;
        case BITREE_AVL_RGT_HEAVY:
        	((AvlNode *)bitree_data(*node))->factor = BITREE_AVL_BALANCED;
        	((AvlNode *)bitree_data(left))->factor = BITREE_AVL_LFT_HEAVY;
        	break;
        }
    	((AvlNode *)bitree_data(grandchild))->factor = BITREE_AVL_BALANCED;
        *node = grandchild;                     //原来node的父节点现在作为grandchild的父节点
    }
    return;
}

static void rotate_right(BiTreeNode **node) {
    BiTreeNode *right, *grandchild;

    right = bitree_right(*node);

    if(((AvlNode *)bitree_data(right))->factor == BITREE_AVL_RGT_HEAVY) {  //LL rotation
        bitree_right(*node) = bitree_left(right); //将left的右子节点踢给node,作为node的左节点
        bitree_left(right) = *node;              //将node作为left的右节点
        *node = right;                            //将left子节点提到原来node的位置

        ((AvlNode *)bitree_data(*node))->factor = BITREE_AVL_BALANCED;  //重置平衡为0
        ((AvlNode *)bitree_data(right))->factor = BITREE_AVL_BALANCED;
    } else {                                                              //LR rotaion
    	//			       node                                   grandchild
    	//          left              right                     node         right
    	//                   grandchild                                     [x]
    	//             		         [x]
    	//
        grandchild = bitree_left(right);    //node的右子节点的左子节点 ====简称 R2
        bitree_left(right) = bitree_right(grandchild);   // R2 的左子节点替代R2的位置，作为node的左子节点的右子节点
        bitree_left(grandchild) = right;    //将left作为 R2的左子节点， R2作为left的父节点，R2顶替node的位置
        bitree_right(*node) = bitree_left(grandchild);  //R2的右子节点踢给node的左子节点位置，
        bitree_left(grandchild) = *node;       //R2的右子节点指向node,node作为R2的子节点

        switch(((AvlNode *)bitree_data(grandchild))->factor) {
        case BITREE_AVL_LFT_HEAVY:
        	((AvlNode *)bitree_data(*node))->factor = BITREE_AVL_BALANCED;
        	((AvlNode *)bitree_data(right))->factor = BITREE_AVL_RGT_HEAVY;
        	break;
        case BITREE_AVL_BALANCED:
        	((AvlNode *)bitree_data(*node))->factor = BITREE_AVL_BALANCED;
        	((AvlNode *)bitree_data(right))->factor = BITREE_AVL_BALANCED;
        	break;
        case BITREE_AVL_RGT_HEAVY:
        	((AvlNode *)bitree_data(*node))->factor = BITREE_AVL_LFT_HEAVY;
        	((AvlNode *)bitree_data(right))->factor = BITREE_AVL_BALANCED;
        	break;
        }
    	((AvlNode *)bitree_data(grandchild))->factor = BITREE_AVL_BALANCED;
        *node = grandchild;                     //原来node的父节点现在作为grandchild的父节点
    }
    return;
}

static int insert(BiTree_AVL *tree_avl,
                  BiTreeNode **node,
                  const void *data,
                  int *balanced) {

    AvlNode *avl_data;
    int cmpval, retval;

    //如果node代表了一个叶子节点
    if (bitree_is_eob(*node)) {
        avl_data = (AvlNode *) malloc(sizeof(AvlNode));                //生成一个新的节点插入到树中
        if (avl_data == NULL) {
            printf("%s\n", "static insert() function fail, malloc err");
            return -1;
        }

        avl_data->factor = BITREE_AVL_BALANCED;
        avl_data->hidden = 0;
        avl_data->data = (void *)data;
        return bitree_ins_left(tree_avl, *node, avl_data);
    }else {      //node不是叶子节点
        void * tmp_data = ((AvlNode *)bitree_data(*node))->data;
        cmpval = tree_avl->compare(data, tmp_data);
        if (cmpval < 0) {
            //移动到该节点的左子节点,判断左子节点是否是叶子节点
            if (bitree_is_eob(bitree_left(*node))) {
                printf("->left");
                avl_data = (AvlNode *) malloc(sizeof(AvlNode));                //生成一个新的节点插入到树中
                if (avl_data == NULL) {
                    printf("%s\n", "static insert() function fail, malloc err");
                    return -1;
                }

                avl_data->factor = BITREE_AVL_BALANCED;
                avl_data->hidden = 0;
                avl_data->data = (void *)data;

                if (bitree_ins_left(tree_avl, *node, avl_data) != 0) {
                    printf("%s\n", "static insert() function fail , call bitree_ins_left() fail.");
                    return -1;
                }

                *balanced = 0;
            }else {  //左子节点不是叶子节点
                retval = insert(tree_avl, &(bitree_left(*node)), data, balanced);
                if (retval != 0) {
                    return  retval;
                }
            }

            //如下确保树保持平衡
            if (!(*balanced)) {
                switch (((AvlNode *) bitree_data(*node))->factor) {
                    case BITREE_AVL_LFT_HEAVY:
                        rotate_left(node);
                        *balanced = 1;
                        break;
                    case BITREE_AVL_BALANCED:
                        ((AvlNode *)bitree_data(*node))->factor = BITREE_AVL_LFT_HEAVY;
                        break;
                    case BITREE_AVL_RGT_HEAVY:
                        ((AvlNode *)bitree_data(*node))->factor = BITREE_AVL_BALANCED;
                        *balanced = 1;
                        break;
                }
            }
        } else if(cmpval > 0){ //移动到右子节点
            if (bitree_is_eob(bitree_right(*node))) {
                printf("->left");
                avl_data = (AvlNode *) malloc(sizeof(AvlNode));                //生成一个新的节点插入到树中
                if (avl_data == NULL) {
                    printf("%s\n", "static insert() function fail, malloc err");
                    return -1;
                }

                avl_data->factor = BITREE_AVL_BALANCED;
                avl_data->hidden = 0;
                avl_data->data = (void *)data;

                if (bitree_ins_right(tree_avl, *node, avl_data) != 0) {
                    printf("%s\n", "static insert() function fail , call bitree_ins_left() fail.");
                    return -1;
                }

                *balanced = 0;
            }else {  //左子节点不是叶子节点
                retval = insert(tree_avl, &(bitree_right(*node)), data, balanced);
                if (retval != 0) {
                    return  retval;
                }
            }

            //如下确保树保持平衡
            if (!(*balanced)) {
                switch (((AvlNode *) bitree_data(*node))->factor) {
                    case BITREE_AVL_LFT_HEAVY:
                        ((AvlNode *)bitree_data(*node))->factor = BITREE_AVL_BALANCED;
                        *balanced = 1;
                        break;
                    case BITREE_AVL_BALANCED:
                        ((AvlNode *)bitree_data(*node))->factor = BITREE_AVL_RGT_HEAVY;
                        break;
                    case BITREE_AVL_RGT_HEAVY:
                        rotate_right(node);
                        *balanced = 1;
                        break;
                }
            }
        }else {
            //当找到同样的数据的时候的处理
            if (!((AvlNode *) bitree_data(*node))->hidden) {
                printf("%s\n", "find same data, but the data was not hidden, do nothing");
                return -1;
            } else {
                //插入一条新数据
                if (tree_avl->destroy != NULL) {
                    tree_avl->destroy(((AvlNode *) bitree_data(*node))->data);
                }

                ((AvlNode *) bitree_data(*node))->data = (void *)data;
                ((AvlNode *) bitree_data(*node))->hidden = 0;
                *balanced = 1;
            }
        }
    }
	return 0;
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
