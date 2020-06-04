// 数据压缩的头文件
// Created by wangxn on 2016/4/12.
//

#ifndef DATA_STRUCTURE_C_COMPRESS_H
#define DATA_STRUCTURE_C_COMPRESS_H

#include "../bitree/bitree.h"
#include "../bitree/bitree_avl.h"
#include "../bitree/bitree_traverse.h"

/**
 * 哈夫曼树的节点的结构体
 */
typedef struct HuffNode_{
    unsigned char symbol;
    int freq;
}HuffNode;

/**
 * 哈夫曼编码表的实体的结构体
 */
typedef struct HuffCode_{
    /**
     * 默认为1的标志位,指示此条目是否已经存放一个代码
     */
    unsigned char used;

    /**
     * 存放在条目中的哈夫曼编码
     */
    unsigned  short code;

    /**
     * 编码包含的位数,每个编码都是一个短整数,不会大于16位
     */
    unsigned  char size;
}HuffCode;

/**
 * define the number of bits required for lz77 token members
 */
#define LZ77_TYPE_BITS 1
#define LZ77_WINOFF_BITS 12
#define LZ77_BUFLEN_BITS 5
#define LZ77_NEXT_BITS 8

/**
 * define the size of the sliding window and the look-ahead buffer
 * for lz77.
 * Each must be less than or equal to 2 raised to LZ77_WINOFF_BITS and
 * LZ77_BUFLEN_BITS respectively
 */
#define LZ77_WINDOW_SIZE 4096
#define LZ77_BUFFER_SIZE 32

/**
 * define the number of bits for lz77 phrase tokens
 * 1 +１２　＋　５　＋8 = 26位
 */
#define LZ77_PHRASE_BITS (LZ77_TYPE_BITS+LZ77_WINOFF_BITS+LZ77_NEXT_BITS+LZ77_BUFLEN_BITS)

/**
 * define the number of bits for lz77 symbol tokens
 * 1 + 8 = 9 ,9位
 */
#define LZ77_SYMBOL_BITS (LZ77_TYPE_BITS+LZ77_NEXT_BITS)


/**
 * public interface
 */

/**
 * 霍夫曼编码
 * 基于最小冗余编码的压缩算法:
 *          如果知道一组数据中符号出现的频率,就可以用一种特殊的方式来表示符号从而减少数据需要的存储空间
 *          使用较少的位对出现频率高的符号编码,用较多的位对出现频率低的符号编码.
 *          一个符号可以是任何大小的数据,但是往往它只占一个字节.
 * 熵
 *  每个数据集都有一定的信息量, 一组数据的熵就是数据中每个符号熵的总和
 *  计算公式:
 *          lg(概率),
 *          比如z在32个符号的数据集中出现了8次,1/4的概率,求lg(1/4) = 2,那么熵就是2位,
 *
 * 霍夫曼树,一颗二叉树.
 * 构造霍夫曼树:
 *      1. 将每个符号和频率放到它自身的树种.
 *      2. 将两个频率最小的根节点的树节点合并,然后将频率之和存放到树的新结点中
 *      3. 重复步骤2,直到最后只剩下一棵树
 *
 * 霍夫曼编码就是在不断寻找两颗最适合合并的树,因此是贪婪算法
 *
 * 建立霍夫曼树是数据解压缩的一部分.
 * 用霍夫曼树压缩数据,给定一个具体的符号,从树的根开始,然后沿着符号的叶子结点追踪.
 * 在向下追踪的过程中.
 * 当向左分支移动时,向当前编码末尾追加0,
 * 当向右移动时,向当前编码末尾追加1.
 * 那么符号的霍夫曼编码可以表示为 U=101, V=01,.,
 *
 * 操作:
 *      先扫描数据,确定每个符号出现的频率,将频率存放到数组freqs中.
 *      完成对数据的扫描后,频率值得到了一定限度的缩放,因此他们可以只用一个字节来表示.
 *      当确定数据中某个符号的最大出现频率,并且相应确定其他频率之后,这个扫描过程结束.
 *      由于数据中没有出现的符号应该只是频率值为0的符号,所以执行一个简单的测试来确保党任何非0频率值其缩减为小于1时,最终应该将其设置为1
 *
 *      然后, 调用函数build_tree来建立霍夫曼树
 *      首先将数据中至少出现过一次的符号插入优先队列中.树中的结点由数据结构HuffNode定义.
 *      此结构包含两个成员, symbol为数据中的符号, freq为频率.
 *      每棵树初始时只包含一个结点,此节点存储一个符号和它的缩放频率
 *      通过优先队列用一个循环对树做size-1次合并.
 *      在每次迭代过程中,两次调用函数pqueue_extract来提取根节点频率最小的两棵二叉树,然后合并为一棵树,将两棵树的频率和存放到新树的根节点中,
 *      接着将新的树保存回优先级队列中.
 *      循环持续知道size-1次迭代完成,此时优先级队列中只有一颗二叉树,就是霍夫曼树
 *
 *      利用霍夫曼树,调用函数build_table建立一个霍夫曼编码表,此表指明每个符号的编码.
 *      表中的每个条目都是一个HuffCode结构.包含3个成员:used是一个默认为1的标志位,只是此条目是否已经存放过一个代码
 *      code是存放在条目中的霍夫曼编码,size是编码包含的位数,每个编码都是一个短整数,且没有编码会大于16位
 *
 *      使用一个有序的遍历方法来遍历霍夫曼树,从而构建这个表.
 *      每次执行build_table的过程中,code记录当前生成的霍夫曼编码,size保存编码的位数
 *      在存放每个编码的同时,调用网路函数htons,以确保编码是以大端字节格式存放,
 *
 *      产生压缩数据时,使用ipos来保存原始数据中正在处理的当前字节,并用opos来保存向压缩数据缓冲区写入的当前位.
 *
 *
 *
 * @param original : 压缩前的数据
 * @param compressed :压缩后返回的数据
 * @param size : 压缩前数据的大小
 */
int huffman_compress(const unsigned char *original/*in*/,
                     unsigned char **compressed/*out*/,
                     int size/*in*/);

/**
 * 要解压缩用霍夫曼树编码的数据,要一位一位的读取压缩数据
 * 从树的根开始,当在数据中遇到0时,向树的左分支移动,遇到1,向有分支移动,遇到叶子结点,就找到符号.
 */
int huffman_uncompress(const unsigned char *compressed,
                        unsigned char **original);


/**
 * LZ77是一种基于字典的算法
 * 它通过用小的标记代替数据中多次重复出现的长串的方法来压缩数据.
 * 其处理的符号不一定是文本字符,可以是任何大小的符号,但其通常选择一个字节的符号
 *
 * 用LZ77算法压缩缓冲区original中的数据,original包含size个字节的空间.
 * 压缩后的数据存入缓冲区compressed中
 * 由于函数调用者并不知道compressed需要多大的存储空间.
 * 因此要通过lz77_compress函数调用malloc来动态的分配存储空间.
 * 当这块存储空间不再使用时,由调用者调用函数free来释放空间
 *
 * 如果数据压缩成功, 返回压缩后数据的字节数,否则,返回-1
 */
int lz77_compress(const unsigned char *original,
                  unsigned char **compressed,
                    int size);

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
 */
int lz77_uncompress(const unsigned char *compressed,
                    unsigned char **original);


#endif //DATA_STRUCTURE_C_COMPRESS_H
