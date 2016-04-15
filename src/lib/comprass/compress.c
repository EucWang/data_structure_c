//
// Created by wangxn on 2016/4/12.
//

#include <limits.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "bit_ctrl.h"
#include "compress.h"
#include "../bitree/pqueue.h"


static int huffnode_compare(HuffNode *node1, HuffNode *node2) {
    if (node1 == NULL || node2 == NULL) {
        return -1;
    }

    int diff = node1->symbol - node2->symbol;
    if (diff > 0) {
        return 1;
    } else if (diff < 0) {
        return -1;
    } else {
        return diff;
    }
}

static void huffnode_destroy(HuffNode *node) {
    if (node != NULL) {
        free(node);
    }
}


/**
 * 频率比较
 * 在优先级队列中,频率越低,优先级越高
 */
static int compare_freq(const void *tree1, const void *tree2) {
    HuffNode *root1, *root2;

    root1 = (HuffNode *) bitree_data(bitree_root((const BiTree *) tree1));
    root2 = (HuffNode *) bitree_data(bitree_root((const BiTree *) tree2));

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
 * 根据频率数组,构建一颗哈夫曼二叉树
 * 频率数组的索引就是对应其频率的原始字节数据
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
        //有出现频率不为0,则为该值分配一个树,值存到树中的根节点中
        //用HuffNode封装这个值和它出现的频率
        if (freqs[c] != 0) {
            //为编码和频率建立一个二叉树
            if ((init = (BiTree *) malloc(sizeof(BiTree))) == NULL) {
                pqueue_destroy(&pQueue);
                return -1;
            }
            bitree_init(init, (void *) huffnode_compare, NULL);

            //新生成一个放入到二叉树中的结点
            if ((data = (HuffNode *) malloc(sizeof(HuffNode))) == NULL) {
                pqueue_destroy(&pQueue);
                return -1;
            }
            //为结点数据赋值
            data->symbol = c;
            data->freq = freqs[c];

            //将结点插入到二叉树中
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

    for (c = 1; c <= size - 1; ++c) {

        //生成一个临时二叉树, 作为存储产生的合并树
        if ((merge = (BiTree *) malloc(sizeof(BiTree))) == NULL) {
            pqueue_destroy(&pQueue);
            return -1;
        }
        bitree_init(merge, (void *) huffnode_compare, NULL);

        //提取两个二叉树树, 这两个树的根节点有最小的频率值,提起之后,优先级队列中就不存在这两棵树了
        if (pqueue_extract(&pQueue, (void **) (&left)) != 0 ||
            pqueue_extract(&pQueue, (void **) (&right)) != 0) {
            pqueue_destroy(&pQueue);
            free(merge);
            return -1;
        }

        //为合并树的根节点的数据分配空间,并且初始化
        if ((data = (HuffNode *) malloc(sizeof(HuffNode))) == NULL) {
            pqueue_destroy(&pQueue);
            free(merge);
            return -1;
        }
        memset(data, 0, sizeof(HuffNode));

        //两个合并树的根节点的频率和作为data的频率, 
        data->freq = ((HuffNode *) bitree_data(bitree_root(left)))->freq +
                     ((HuffNode *) bitree_data(bitree_root(right)))->freq;

        //合并树,新生成的树就是merge树
        if (bitree_merge(merge, left, right, data) != 0) {
            pqueue_destroy(&pQueue);
            bitree_destroy(merge);
            free(merge);
            return -1;
        }

        //将合并的树插入到优先级队列,并且释放其他的内存
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
    //将这唯一一颗二叉树提取到tree中,销毁优先级队列
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
    //node节点必须不是叶子节点
    if (!bitree_is_eob(node)) {

        //node的左子节点不是叶子结点时,递归调用
        if (!bitree_is_eob(bitree_left(node))) {
            build_table(bitree_left(node), code << 1, size + 1, table);
        }
        //node的右子节点不是叶子结点时,递归调用
        if (!bitree_is_eob(bitree_right(node))) {
            build_table(bitree_right(node), (code << 1) | 0x0001, size + 1, table);
        }
        //node的左子节点和右子节点同时是叶子节点时
        if (bitree_is_eob(bitree_left(node)) && bitree_is_eob(bitree_right(node))) {
            //格式化code为大头模式
            code = htons(code);
            //这个node节点的symbol
            unsigned char c = ((HuffNode *) bitree_data(node))->symbol;
            //为table中对应的HuffCode设置值
            table[c].used = 1;
            table[c].code = code;
            table[c].size = size;
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
    for (c = 0; c <= UCHAR_MAX; ++c) {
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
    }

    //缩放频率让其可以用一个字节表示频率
    for (c = 0; c < UCHAR_MAX; ++c) {
        scale = (int) (freqs[c] / ((double) max / (double) UCHAR_MAX));
        if (scale == 0 && freqs[c] != 0) {
            freqs[c] = 1;
        } else {
            freqs[c] = scale;
        }
    }

    //构建树,生成的哈夫曼树存放在tree中
    if (build_tree(freqs, &tree) != 0) {
        return -1;
    }
    //对table内存空间初始化
    for (c = 0; c < UCHAR_MAX; ++c) {
        memset(&table[c], 0, sizeof(HuffCode));
    }
    //创建表,哈夫曼编码的表,为这个表中的具体字段赋值
    build_table(bitree_root(tree), 0x0000, 0, table);

    bitree_destroy(tree);
    free(tree);

    //写头部信息, 为comp分配大小为一个int型数据的大小加上UCHAR_MAX再加一
    hsize = sizeof(int) + (UCHAR_MAX + 1);  //comp的字节大小
    if ((comp = (unsigned char *) malloc(hsize)) == NULL) {
        return -1;
    }
    //将原始数据的容量大小写入到comp中
    memcpy(comp, &size, sizeof(int));
    //将频率数组中的内容写入到comp后序的内存空间中
    for (c = 0; c <= UCHAR_MAX; ++c) {
        comp[sizeof(int) + c] = (unsigned char) freqs[c];
    }

    ipos = 0;
    opos = hsize * 8; //opos初始指向comp的末尾

    //size是原始数据的大小,遍历原始数据,获取原始数据的每一个字节
    while (ipos < size) {
        c = original[ipos]; //从原始数据中取出一个字节
        for (i = 0; i < table[c].size; ++i) {  //遍历哈夫曼编码的每一位
            if (opos % 8 == 0) {  //如果opos已经指向了comp的范围之外,则扩充comp的内存大小,增加一个字节
                if ((temp = (unsigned char *) realloc(comp, (opos / 8) + 1)) == NULL) {
                    free(comp);
                    return -1;
                }
                comp = temp;
            }

            //size不会大于16, short的字节数为2, cpos就是从左起的需要遍历的哈夫曼编码的指定位的索引
            //这个是从高位开始写入,先获取最高的位的,然后直到最低位
            cpos = (sizeof(short) * 8) - table[c].size + i;
            //获取哈夫曼编码的给定位的状态
            //虽然在内存中是大头模式,比如 二进制10,两字节是0000 0010 0000 0000
            //这里取位,比如取14位, 依然将其转换成小头模式,从左往右显示 0000 0000 0000 0010
            //那么这里只需要获得两位的有效位数就是二进制的10
            //大头模式和小偷模式,不影响计算字节位在字节中的顺序
            int status = bit_get((unsigned char *) &table[c].code, cpos);
            //将这一字节指定位的状态写入到comp中
            bit_set(comp, opos, status);
            opos++;
        }
        ipos++;
    }
    *compressed = comp;
    return ((opos - 1) / 8) + 1; //返回压缩之后的数据的大小
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

    //压缩数据的头部信息,第一个int型数据的内容包含原始数据的大小
    //后面紧跟的UCHAR_MAX个字节是频率数组的内容
    //再后面跟的就是对应原始数据的哈夫曼编码了
    hsize = sizeof(int) + (UCHAR_MAX + 1);
    memcpy(&size, compressed, sizeof(int)); //获取第一个int型数据的内容,传递给size

    printf("%d\n", size);

    //获取频率数组
    for (c = 0; c <= UCHAR_MAX; ++c) {
        freqs[c] = compressed[sizeof(int) + c];
        if (freqs[c] > 0) {
            printf("%c,%d ; ", c, freqs[c]);
        }
    }

    //根据频率数组构造哈夫曼树,
    if (build_tree(freqs, &tree) != 0) {
        return -1;
    }
    //对哈夫曼编码进行解码
    ipos = hsize * 8;   //指向哈夫曼编码开始的位置的那个字节的位
    opos = 0;
    node = bitree_root(tree);  //哈夫曼树的根元素

    while (opos < size) {
        state = bit_get(compressed, ipos); //获取第一位
        ipos++;

        //根据位状态去遍历哈夫曼树,
        if (state == 0) {
            if (bitree_is_eob(node) || bitree_is_eob(bitree_left(node))) {
                bitree_destroy(tree);
                free(tree);
                return -1;
            } else {
                node = bitree_left(node);
            }
        } else {
            if (bitree_is_eob(node) || bitree_is_eob(bitree_right(node))) {
                bitree_destroy(tree);
                free(tree);
                return -1;
            } else {
                node = bitree_right(node);
            }
        }

        //直到找到一个结点,这个节点的左子节点和右子节点都是叶子节点
        if (bitree_is_eob(bitree_left(node)) && bitree_is_eob(bitree_right(node))) {
            if (opos > 0) {
                //为orig增加一个字节的内存空间
                if ((temp = (unsigned char *) realloc(orig, opos + 1)) == NULL) {
                    bitree_destroy(tree);
                    free(tree);
                    free(orig);
                    return -1;
                }
                orig = temp;
            } else {
                //如果opos小于等于0, 则为orig只分配一个字节的内存空间
                if ((orig = (unsigned char *) malloc(1)) == NULL) {
                    bitree_destroy(tree);
                    free(tree);
                    return -1;
                }
            }

            //将原始的字节数值赋值给orig,node重新指向树根节点,opos自增1,开始下轮循环
            orig[opos] = ((HuffNode *) bitree_data(node))->symbol;
            opos++;
            node = bitree_root(tree);
        }
    }
    bitree_destroy(tree);
    free(tree);
    *original = orig;
    return opos;
}

/**
 * @param window: 移动窗口
 * @param buffer: 前置缓冲区
 * @param offset: 偏移量
 * @param next:   前向缓冲区中该短语后面一个字节的指针
 *
 * @return 返回找到的短语的长度
 */
static int compare_win(const unsigned char *window/*in*/,
                       const unsigned char *buffer/*in*/,
                       int *offset/*out*/,
                       unsigned char *next/*out*/) {
    int match, longest, i, j, k;
    *offset = 0;
    *next = buffer[0];

    for (k = 0; k < LZ77_WINDOW_SIZE; ++k) {
        i = k;
        j = 0;
        match = 0;

        while (i < LZ77_WINDOW_SIZE && j < LZ77_BUFFER_SIZE - 1) {
            if (window[i] != buffer[j]) {
                break;
            }
            match++;
            i++;
            j++;
        }

        if (match > longest) {  //找到最长的短语,
            *offset = k;        //该短语在活动窗口中的偏移值
            longest = match;    //该短语的长度
            *next = buffer[j];  // 前向缓冲区中该短语后面一个字节的指针
        }
    }
    return longest;   //返回该短语的长度
}


/**
 * 用lz77算法解压缩缓冲区compressed中的数据,
 * 假定缓冲区包含的数据由lz77_compress压缩.
 * 修复后的数据存入缓冲区original中
 * 由于函数调用者并不知道original需要多大的空间,
 * 因此要通过lz77_uncompressed函数调用malloc来动态分配存储空间
 * 当这块空间不在使用时,由调用者调用函数free来释放空间
 *
 * 这里滑动窗口大小为8字节,前向缓冲区大小为4字节
 * 在实际中,滑动窗口典型的大小为4kb(4096字节),前向缓冲区大小通常小于100字节
 *
 * @param original: 没有压缩的数据
 * @param compressed: 压缩之后的数据
 * @param size:  没有压缩的数据的内存大小,字节单位
 */
int lz77_compress(const unsigned char *original/*in*/,
                  unsigned char **compressed/*out*/,
                  int size/*in*/) {

    unsigned char window[LZ77_WINDOW_SIZE];   //滑动窗口的数组, 4096个字节
    unsigned char buffer[LZ77_BUFFER_SIZE];   //前置缓冲区的数组  32个字节
    unsigned char
            *comp,    //作为输出的压缩之后数据的缓冲区
            *temp,    //作为替换comp的临时缓冲区
            next;     //遍历原始数据时,有pharseToken时,在前置缓冲区中这个pharseToken后面的的一个字节的值
    int     offset,
            length,
            remaining,
            hsize,
            ipos,
            opos,
            tpos,
            i,
            token,
            tbits;

    *compressed = NULL;
    hsize = sizeof(int);


    //分配4个字节的空间
    if ((comp = (unsigned char *) malloc(hsize)) == NULL) {
        return -1;
    }

    //comp中保存原始数据大小的值
    memcpy(comp, &size, sizeof(int));

    memset(window, 0, LZ77_WINDOW_SIZE); //初始化window
    memset(buffer, 0, LZ77_BUFFER_SIZE); //初始化buffer

    //开始加载前向缓冲区
    ipos = 0;
    for (i = 0; i < LZ77_BUFFER_SIZE && ipos < size; ++i) {
        buffer[i] = original[ipos];
        ipos++;
    }

    //压缩数据
    opos = hsize * 8; //如果hsize是4个字节,那么opos的值就是32
    remaining = size;  //remaining的值为原始数据的大小, 字节单位

    //开始遍历原始数据
    while (remaining > 0) {

        //遍历活动窗口,在前置缓冲区中寻找短语,如果length大于0,就是有,否则没有
        //length 是phraseToken的长度,offset是phraseToken在活动窗口中的偏移量,next是前置缓冲区中下一个字节的指针
        if ((length = compare_win(window, buffer, &offset, &next)) != 0) {
            //构造一个phraseToken, 一个int型的4个字节
            token = 0x00000001 << (LZ77_PHRASE_BITS - 1);//int的1,左移26位,应该是 : 0x02000000
            //26- 1- 12 = 13
            //将offset放入到token中偏移13位的位置
            token = token | (offset << (LZ77_PHRASE_BITS - LZ77_TYPE_BITS - LZ77_WINOFF_BITS));

            //26- 1 - 12 - 5 = 8
            //将phraseToken的长度信息放入到token中偏移8位的位置
            token = token | (length << (LZ77_PHRASE_BITS - LZ77_TYPE_BITS - LZ77_WINOFF_BITS - LZ77_BUFLEN_BITS));

            //最后8位,放置前置缓冲区中下一个字节的内容
            token = token | next;

            //遍历数据时获取的token的容量,是26位的就是pharseToken
            tbits = LZ77_PHRASE_BITS;
        }else {
            token = 0x00000000;  //编码一个symbolToken
            token = token | next;  //将前置缓冲区中的下一个字符放入到token中
            //遍历数据时获取的token的容量,是9位的就是原始数据
            tbits = LZ77_SYMBOL_BITS; //set the number of bits in the token
        }

        token = htonl(token); //确保token是采用大头格式的

        //将token写入到压缩数据的buffer中
        for (i = 0; i < tbits; ++i) {
            //遇到opos为8的整数时,则压缩数据的buf就再多分配一个字节的容量
            if (opos % 8 == 0) {
                if ((temp = (unsigned char *) realloc(comp, (opos / 8) + 1)) == NULL) {
                    free(comp);
                    return -1;
                }
                comp = temp;
            }
            //获取token中对应位的索引
            //long是8个字节, 64 - tbits + i;
            tpos = (sizeof(unsigned long) * 8) - tbits + i;
            //根据索引获取对应位的状态
            int status = bit_get((unsigned char *) (&token), tpos);
            //将这个状态设置到comp中,也就是压缩数据的流中
            bit_set(comp, opos, status);
            //压缩数据的流的索引前进一位
            opos ++;
        }
    }

    length++;

    memmove(&window[0], &window[length], LZ77_WINDOW_SIZE - length);
    memmove(&window[LZ77_WINDOW_SIZE - length], &buffer[0], length);
    memmove(&buffer[0], &buffer[length], LZ77_BUFFER_SIZE - length);

    for (i = LZ77_BUFFER_SIZE - length; i < LZ77_BUFFER_SIZE && ipos < size; ++i) {
        buffer[i] = original[ipos];
        ipos++;
    }
    remaining = remaining - length;

    //TODO

    return 0;
}

int lz77_uncompress(const unsigned char *compressed,
                    unsigned char **original) {
    return 0;
}
