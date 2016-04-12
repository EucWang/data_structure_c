//
// Created by wangxn on 2016/4/12.
//

#include <limits.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#include "bit_ctrl.h"
#include "compress.h"
#include "../bitree/pqueue.h"

/**
 * 频率比较
 */
static int compare_freq(const void *tree1, const void *tree2) {
    HuffNode *root1, *root2;

    root1 = (HuffNode *)bitree_data(bitree_root((const BiTree *)tree1));
    root2 = (HuffNode *)bitree_data(bitree_root((const BiTree *)tree2));

    if (root1->freq < root2->freq) {
        return 1;
    } else if (root1->freq > root2->freq) {
        return -1;
    } else {
        return 0;
    }
}

/**
 * 销毁树
 */
static void destroy_tree(void *tree) {
    bitree_destroy(tree);
    free(tree);
    return;
}

/**
 * 创建树
 */
static int build_tree(int *freqs, BiTree **tree) {
    BiTree *init, *merge, *left, *right;
    PQueue pQueue;
    HuffNode *data;
    int size, c;

    *tree = NULL;

    //初始化一个优先级队列
    //优先级队列中的每一项都是一个二叉树,
    //比较的函数就是compare_freq,比较二叉树根的freq字段
    pqueue_init(&pQueue, compare_freq, destroy_tree);

    //遍历频率的一维int数组
    for (c = 0; c <= UCHAR_MAX; ++c) {

        if (freqs[c] != 0) {
            //为编码和频率建立一个二叉树
            if ((init = (BiTree *)malloc(sizeof(BiTree))) == NULL) {
                pqueue_destroy(&pQueue);
                return -1;
            }
            //TODO, 这个调用貌似不和规矩
            bitree_init(init, NULL, NULL);

            if ((data = (HuffNode *) malloc(sizeof(HuffNode))) == NULL) {
                pqueue_destroy(&pQueue);
                return -1;
            }

            data->symbol = c;
            data->freq = freqs[c];

            if (bitree_ins_left(init, NULL, data) != 0) {
                free(data);
                bitree_destroy(init);
                free(init);
                pqueue_destroy(&pQueue);
                return -1;
            }

            //将二叉树插入到优先队列中
            if (pqueue_insert(&pQueue, init) != 0) {
                bitree_destroy(init);
                free(init);
                pqueue_destroy(&pQueue);
                return -1;
            }
        }
    }

    //在优先级队列中合并树

    size = pqueue_size(&pQueue);

    for (c = 0; c < size - 1; ++c) {

        //允许存储下一个合并树
        if ((merge = (BiTree *) malloc(sizeof(BiTree))) == NULL) {
            pqueue_destroy(&pQueue);
            return -1;
        }

        //提取两个树
        //这两个树的根节点有最小的频率值
        if (pqueue_extract(&pQueue, (void **) (&left)) != 0 &&
                pqueue_extract(&pQueue, (void **) (&right)) != 0) {
            pqueue_destroy(&pQueue);
            free(merge);
            return -1;
        }

        //为合并树的根节点的数据分配的空间
        if ((data = (HuffNode *) malloc(sizeof(HuffNode))) == NULL) {
            pqueue_destroy(&pQueue);
            free(merge);
            return -1;
        }
        memset(data, 0, sizeof(HuffNode));

        //两个合并树的根节点的频率和作为data 的频率
        data->freq = ((HuffNode *) bitree_data(bitree_root(left)))->freq +
        ((HuffNode *) bitree_data(bitree_root(right)))->freq;


        //合并树
        if (bitree_merge(merge, left, right, data) != 0) {
            pqueue_destroy(&pQueue);
            bitree_destroy(merge);
            free(merge);
            return -1;
        }

        //将合并的书插入到优先级队列,并且释放其他的内存
        if (pqueue_insert(&pQueue, merge) != 0) {
            pqueue_destroy(&pQueue);
            bitree_destroy(merge);
            free(merge);
            return -1;
        }

        free(left);
        free(right);
    }

    //在优先级队列中剩下的唯一一棵树就是哈夫曼树
    if (pqueue_extract(&pQueue, (void **) tree) != 0) {
        pqueue_destroy(&pQueue);
        return -1;
    } else {
        pqueue_destroy(&pQueue);
    }
    return 0;
}

/**
 * 创建表
 */
static void build_table(BiTreeNode *node,
                        unsigned short code,
                        unsigned char size,
                        HuffCode *table) {

    if (!bitree_is_eob(node)) {
        if (!bitree_is_eob(bitree_left(node))) {
            build_table(bitree_left(node), code << 1, size + 1, table);
        }

        if (!bitree_is_eob(bitree_right(node))) {
            build_table(bitree_right(node), (code << 1) | 0x0001, size + 1, table);
        }

        if (bitree_is_eob(bitree_left(node)) && bitree_is_eob(bitree_right(node))) {

            code = htons(code);

            table[((HuffNode *)bitree_data(node))->symbol].used = 1;
            table[((HuffNode *)bitree_data(node))->symbol].code = code;
            table[((HuffNode *)bitree_data(node))->symbol].size = size;
        }
    }
    return;
}






/*
 * @param original : 压缩前的数据
 * @param compressed :压缩后返回的数据
 * @param size : 压缩前数据的大小
 */
int huffman_compress(const unsigned char *original/*in*/,
                     unsigned char **compressed/*out*/,
                     int size/*in*/) {

    BiTree *tree;
    HuffCode table[UCHAR_MAX + 1];
    int freqs[UCHAR_MAX + 1];
    int max, scale, hsize, ipos, opos, cpos, c, i;
    unsigned char *comp, *temp;

    *compressed = NULL;

    //对频率数组初始化
    for (c = 0; c < UCHAR_MAX; ++c) {
        freqs[c] = 0;
    }

    //第一次扫描,对原始数据进行遍历,获取每一种字节的出现频率,
    ipos = 0;
    if (size > 0) {
        while (ipos < size) {
            freqs[original[ipos]]++;
            ipos++;
        }
    }

    //max最大值为256
    max = UCHAR_MAX;

    //对频率数组进行遍历
    for (c = 0; c < UCHAR_MAX; ++c) {
        //如果有哪个字节出现的频率超过256,一个字节显示的容量,那么为max重新赋值
        if (freqs[c] > max) {
            max = freqs[c];
        }

        //缩放频率让其可以用一个字节表示
        for (c = 0; c < UCHAR_MAX; ++c) {
            scale = (int) (freqs[c] / ((double) max / (double) UCHAR_MAX));
            if (scale == 0 && freqs[c] != 0) {
                freqs[c] = 1;
            } else {
                freqs[c] = scale;
            }
        }
        //构建树
        if (build_tree(freqs, &tree) != 0) {
            return  -1;
        }

        for (c = 0; c < UCHAR_MAX; ++c) {
            memset(&table[c], 0, sizeof(HuffCode));
        }

        build_table(bitree_root(tree), 0x0000, 0, table);

        bitree_destroy(tree);
        free(tree);

        hsize = sizeof(int) + (UCHAR_MAX + 1);

        if ((comp = (unsigned char *) malloc(hsize)) == NULL) {
            return -1;
        }

        memcpy(comp, &size, sizeof(int));

        for (c = 0; c < UCHAR_MAX; ++c) {
            comp[sizeof(int) + c] = (unsigned char) freqs[c];
        }

        ipos = 0;
        opos = hsize *8;

        while (ipos < size) {
            c = original[ipos];

            for (i = 0; i < table[c].size; ++i) {
                if (opos % 8 == 0) {
                    if ((temp = (unsigned char *) realloc(comp, (opos / 8) + 1)) == NULL) {
                        free(comp);
                        return -1;
                    }
                    comp = temp;
                }
                cpos = (sizeof(short) * 8) - table[c].size + i;
                bit_set(comp, opos, bit_get((unsigned char *) &table[c].code, cpos));
                opos ++;
            }
            ipos++;
        }

        *compressed = comp;

        return ((opos - 1)/ 8) + 1;
    }
}



/**
 * 要解压缩用霍夫曼树编码的数据,要一位一位的读取压缩数据
 * 从树的根开始,当在数据中遇到0时,向树的左分支移动,遇到1,向有分支移动,遇到叶子结点,就找到符号.
 */
int huffman_uncompress(const unsigned char *compressed,
                       unsigned char **original) {

    BiTree *tree;
    BiTreeNode *node;
    int freqs[UCHAR_MAX + 1];
    int hsize, size, ipos, opos, state, c;
    unsigned char *orig, *temp;

    *original = orig = NULL;

    hsize = sizeof(int) + (UCHAR_MAX + 1);
    memcpy(&size, compressed, sizeof(int));

    for (c = 0; c < UCHAR_MAX; ++c) {
        freqs[c] = compressed[sizeof(int) + c];
    }

    if (build_tree(freqs, &tree) != 0) {
        return -1;
    }

    ipos = hsize * 8;
    opos = 0;
    node = bitree_root(tree);

    while (opos < size) {
        state = bit_get(compressed, ipos);
        ipos++;

        if (state == 0) {
            if (bitree_is_eob(node) || bitree_is_eob(bitree_left(node))) {
                bitree_destroy(tree);
                free(tree);
                return -1;
            } else {
                node = bitree_left(node);
            }
        } else {
            if (bitree_is_eob(node) || bitree_right(node)) {
                bitree_destroy(tree);
                free(tree);
                return -1;
            } else {
                node = bitree_right(node);
            }
        }

        if (bitree_is_eob(bitree_left(node)) && bitree_is_eob(bitree_right(node))) {
            if (opos > 0) {
                if ((temp = (unsigned char *) realloc(orig, opos + 1)) == NULL) {
                    bitree_destroy(tree);
                    free(tree);
                    free(orig);
                    return -1;
                }
                orig = temp;
            } else {
                if ((orig = (unsigned char *) malloc(1)) == NULL) {
                    bitree_destroy(tree);
                    free(tree);
                    return -1;
                }
            }

            orig[opos] = ((HuffNode *)bitree_data(node))->symbol;
            opos ++;
            node = bitree_root(tree);
        }
    }
    bitree_destroy(tree);
    free(tree);
    *original = orig;
    return opos;
}
