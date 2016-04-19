//
// Created by wangxn on 2016/4/18.
//

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "../comprass/bit_ctrl.h"
#include "encrypt.h"

/**
 * define a mapping for the key transformation
 */
static  const int DesTransform[56] = {
        57, 49, 41, 33, 25, 17, 9,  1,  58, 50, 42, 34, 26, 18,
        10, 2,  59, 51, 43, 35, 27, 19, 11, 3,  60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15, 7,  62, 54, 46, 38, 30, 22,
        14, 6,  61, 53, 45, 37, 29, 21, 13, 5,  28, 20, 12, 4
};

/**
 * Define the number of rotations for computing subkeys
 */
static const int DesRotations[16] = {
  1,1, 2,2,
  2,2, 2,2,
  1,2, 2,2,
  2,2, 2,1
};

/**
 * Define a mapping for the permuted choice for subkeys
 */
static  const int DesPermuted[48] = {
        14, 17, 11, 24, 1,  5,  3,  28, 15, 6,  21, 10,
        23, 19, 12, 4,  26, 8,  16, 7,  27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

/**
 * Define a mapping for the initial permutation of data blocks
 */
static const int DesInitial[64] = {
        58, 50, 42, 34, 26, 18, 10, 2,  60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,  64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9,  1,  59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,  63, 55, 47, 39, 31, 23, 15, 7
};

static const int DesExpansion[48] = {
        32, 1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
        8,  9,  10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
};

static  const int DesSbox[8][4][16] = {
        /*1*/{
                     {14, 4,  13, 1,  2,  15, 11, 8,  3,  10, 6,  12, 5, 9,  0, 7},
                     {0,  15, 7,  4,  14, 2,  13, 1,  10, 6,  12, 11, 9, 5,  3, 8},
                     {4,  1,  14, 8,  13, 6,  2,  11, 15, 12, 9,  7,  3, 10, 5, 0},
                     {15, 12, 8,  2,  4,  9,  1,  7,  5,  11, 3,  14, 10, 0, 6, 13},
        },
        /*2*/{
                     {15, 1,  8,  14, 6,  11, 3,  4,  9,  7, 2,  13, 12, 0, 5,  10},
                     {3,  13, 4,  7,  15, 2,  8,  14, 12, 0, 1,  10, 6,  9, 11, 5},
                     {0,  14, 7,  11, 10, 4,  13, 1,  5,  8, 12, 6,  9,  3, 2,  15},
                     {13, 8,  10, 1,  3,  15, 4,  2,  11, 6, 7,  12, 0,  5, 14, 9},
        },
        /*3*/{
                     {10, 0,  9,  14, 6,  3,  15, 5,  1,  13, 12, 7,  11, 4,  2,  8},
                     {13, 7,  0,  9,  3,  4,  6,  10, 2,  8,  5,  14, 12, 11, 15, 1},
                     {13, 6,  4,  9,  8,  15, 3,  0,  11, 1,  2,  12, 5,  10, 14, 7},
                     {1,  10, 13, 0,  6,  9,  8,  7,  4,  15, 14, 3,  11, 5,  2,  12},
        },
        /*4*/{
                     {7,  13, 14, 3, 0,  6,  9,  10, 1,  2, 8, 5,  11, 12, 4,  15},
                     {13, 8,  11, 5, 6,  15, 0,  3,  4,  7, 2, 12, 1,  10, 14, 9},
                     {10, 6,  9,  0, 12, 11, 7,  13, 15, 1, 3, 14, 5,  2,  8,  4},
                     {3,  15, 0,  6, 10, 1,  13, 8,  9,  4, 5, 11, 12, 7,  2,  14},
        },
        /*5*/{
                     {2,  12, 4,  1,  7,  10, 11, 6,  8,  5,  3,  15, 13, 0, 14, 9},
                     {14, 11, 2,  12, 4,  7,  13, 1,  5,  0,  15, 10, 3,  9, 8,  6},
                     {4,  2,  1,  11, 10, 13, 7,  8,  15, 9,  12, 5,  6,  3, 0,  14},
                     {11, 8,  12, 7,  1,  14, 2,  13, 6,  15, 0,  9,  10, 4, 5,  3},
        },
        /*6*/{
                     {12, 1,  10, 15, 9, 2,  6,  8,  0,  13, 3,  4,  14, 7,  5,  11},
                     {10, 15, 4,  2,  7, 12, 9,  5,  6,  1,  13, 14, 0,  11, 3,  8},
                     {9,  14, 15, 5,  2, 8,  12, 3,  7,  0,  4,  10, 1,  13, 11, 6},
                     {4,  3,  2,  12, 9, 5,  15, 10, 11, 14, 1,  7,  6,  0,  8,  13},
        },
        /*7*/{
                     {4,  11, 2,  14, 15, 0, 8,  13, 3,  12, 9, 7,  5,  10, 6, 1},
                     {13, 0,  11, 7,  4,  9, 1,  10, 14, 3,  5, 12, 2,  15, 8, 6},
                     {1,  4,  11, 13, 12, 3, 7,  14, 10, 15, 6, 8,  0,  5,  9, 2},
                     {6,  11, 13, 8,  1,  4, 10, 7,  9,  5,  0, 15, 14, 2,  3, 12},
        },
        /*8*/{
                     {13, 2,  8,  4, 6,  15, 11, 1,  10, 9,  3,  14, 5,  0,  12, 7},
                     {1,  15, 13, 8, 10, 3,  7,  4,  12, 5,  6,  11, 0,  14, 9,  2},
                     {7,  11, 4,  1, 9,  12, 14, 2,  0,  6,  10, 13, 15, 3,  5,  8},
                     {2,  1,  14, 7, 4,  10, 8,  13, 15, 12, 9,  0,  3,  5,  6,  11},
        },

};

/**
 * define a mapping for the P-box permutation of data blocks
 */
static const int DesPbox[32] = {
  16,7,20,21,29,12,28,17,1, 15,23,26,5, 18,31,10,
  2, 8,24,14,32,27,3, 9, 19,13,30,6, 22,11,4, 25
};

/**
 * define a mapping for the final permutation of data blocks
 */
static const int DesFinal[64] = {
        40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9,  49, 17, 57, 25
};

/**
 * define a type for whether to encipher or decipher data
 */
typedef  enum DesEorD_{
    encipher, decipher
}DesEorD;


/**
 * 变更,排列,交换
 */
static  void permute(unsigned char *bits/*in,out*/,
                     const int *mapping/*in*/,
                     int n/*in*/) {
    unsigned char temp[8];
    int i, count_bit;

    //对n/8的结果取整数,表示字节数
    count_bit = (int)ceil(n / 8);
    //对temp数组清零,清零字节数由count_bit确定
    memset(temp, 0, count_bit);

    //遍历mapping,共遍历n个数
    for (i = 0; i < n; ++i) {
        //数组mapping的第i个值指定bits中的第多少位,取出这一位的状态值
        int status = bit_get(bits, mapping[i] - 1);
        //将bits中的某一位的状态设置进入到temp中得的第i位
        bit_set(temp, i, status);
    }

    //将temp中的内容复制到bits中,共复制n位所占的字节数
    memcpy(bits, temp, count_bit);
    return;
}

/**
 * 应用DES加密解密的主要方法
 * @param source :
 * @param target :
 * @param key    :
 * @param derection :  表示是加密还是解密
 *
 */
static int des_main(const unsigned char *source,
                    unsigned char *target,
                    const unsigned char *key,
                    DesEorD direction){

    static  unsigned char subkeys[16][17];
    unsigned char temp[8],
                lkey[4],
                rkey[4],
                lblk[6],
                rblk[6],
                fblk[6],
                xblk[6],
                sblk;

    int row,
        col,
        i,
        j,
        k,
        p;

    /**
     * if key is NULL, use the subkeys as computed in a previous call.
     */
    if (key != NULL) {
        //对密钥做一下备份,在密钥的备份上做操作
        memcpy(temp, key, 8);

        //将密钥初始转换,得到一组56位的密钥
        permute(temp, DesTransform, 56);

        //将密钥分成两组28位的数据,
        //先清零两组密钥
        memset(lkey, 0, 4);
        memset(rkey, 0, 4);

        //0~27位放入到lkey中, 28~57位放入到rkey中
        for (j = 0; j < 28; ++j) {
            bit_set(lkey, j, bit_get(temp, j));
            bit_set(rkey, j, bit_get(temp, j + 28));
        }

        //compute the subkeys for each round
        for (i = 0; i < 16; ++i) {

            //根据DesRotations数组中的值分别对lkey和rkey进行翻转操作
            bit_rot_left(lkey, 28, DesRotations[i]);
            bit_rot_left(rkey, 28, DesRotations[i]);

            //对lkey 和rkey分别进行遍历
            //取出其每一位的状态值,
            //放入到subkeys[i]中,lkey的位的值放入到前28位,rkey的位的值放入到后28位
            for (j = 0; j < 28; ++j) {
                int status_lkey = bit_get(lkey, j);
                int status_rkey = bit_get(rkey, j);

                bit_set(subkeys[i], j, status_lkey);
                bit_set(subkeys[i], j + 28, status_rkey);
            }

            //对subkeys[i]进行转换,由56位转成48位,转换表由数组DesPermuted指定
            permute(subkeys[i], DesPermuted, 48);
        }
    }//对key的预处理操作完成


    //备份source到temp中,然后对temp进行操作,只备份8个字节的数据,也就是只处理64位数据
    memcpy(temp, source, 8);

    //对源进行初始化转换,转换表由DesInitial数组指定,位数不变,依然是64位
    permute(temp, DesInitial, 64);

    //将转换之后的源,分成两组, 每组32位,lblk前32位, rblk后32位
    memcpy(lblk, &temp[0], 4);
    memcpy(rblk, &temp[4], 4);

    for (i = 0; i < 16; ++i) {

        //将rblk的32位复制到fblk中
        memcpy(fblk, rblk, 4);

        //将fblk中的32位转换并扩展到48位
        permute(fblk, DesExpansion, 48);

        //如果是加密
        if (direction == encipher) {
            //将fblk与subkeys[i]进行异或处理,结果放置在xblk中
            bit_xor(fblk, subkeys[i], xblk, 48);
        } else/*如果是解密*/ {
            //将fblk与subkeys[15 - i]进行异或处理,结果放置在xblk中
            bit_xor(fblk, subkeys[15 - i], xblk, 48);
        }
        //将异或之后的结果复制到fblk中
        memcpy(fblk, xblk, 6);

        //开始S盒转换, 将每6位转换成4位,这样48位就又转成成32位
        p = 0;
        for (j = 0; j < 8; ++j) {
            //分割成6位6位的去取,转换成S盒中对应的行数列数,找到对应的S盒中的一个4位的值
            int r0 = bit_get(fblk, (j * 6) + 0);
            int r5 = bit_get(fblk, (j * 6) + 5);
            row = 2 * r0 + 1 * r5;

            int r1 = bit_get(fblk, (j * 6) + 1);
            int r2 = bit_get(fblk, (j * 6) + 2);
            int r3 = bit_get(fblk, (j * 6) + 3);
            int r4 = bit_get(fblk, (j * 6) + 4);
            col = 8 * r1 + 4 * r2 + 2 * r3 + 1 * r4;

            //根据获取的行数列数,从DesSbox的第j个盒子中取出一个4位的值,
            sblk = (unsigned char)DesSbox[j][row][col];
            for (k = 4; k < 8; ++k) {
                //这个值在低4位,所以遍历低4位,从左往右数,右边是低位,左边是高位
                int status = bit_get(&sblk, k);
                //将状态值复制到fblk中的第p位,循环完成之后,fblk就是总共32位的值
                bit_set(fblk, p, status);
                p++;
            }
        }

        //进行p盒转换,位数不变
        permute(fblk, DesPbox, 32);

        //上面对fblk的操作都是对rblk的一系列的操作,
        //这里,将rblk与lblk进行异或操作,结果放置在xblk中,
        bit_xor(lblk, fblk, xblk, 32);

        //将异或之后的结果放入到rblk中,上一步的rblk的值放入到lblk中
        memcpy(lblk, rblk, 4);
        memcpy(rblk, xblk, 4);
        //进入下一轮的循环,如此操作16次
    }

    //将如上进过16次处理的rblk和lblk的值放入到target的前4字节和后4字节中
    memcpy(&target[0], rblk, 4);
    memcpy(&target[4], lblk, 4);

    //最终转换
    permute(target, DesFinal, 64);

    return 0;
}

/**
 * 采用DES算法将明文plaintext的一个64位的明文组加密
 * 在key中指定64位的密钥,这个64位的密钥,会通过计算将最后8位忽略掉,得到56位的密钥
 * ciphertext是返回的64位的密文组
 * 由调用者负责管理ciphertext所需要的存储空间
 * 为了得到较高的效率,des_encipher可以重用之前的调用中计算出的子密钥,
 * 这可以在之后的调用中将NULL传给key,以此开启这种功能
 *
 * 因为DES设置的位操作很多,因此DES通常都在硬件层实现.
 * 但是软件实现也有它的价值所在.
 *
 * DES一个特点就是,同样的过程既可以用来进行加密操作也可以用来进行解密.
 * 所以des_encipher和des_decipher都是调用des_main
 * 在des_main中使用其参数deirection来确定到参数source提供的数据是明文还是密文
 * direction只是简单的修改了密钥的顺序.
 * 在des_encipher中,奖direction设置为encipher
 *
 * 1.计算子密钥
 *      1.1 提供的是64位的值
 *      1.2 通过DES中的密钥的转换表,将这个64位的值转换成一个56位的值
 *      1.3 将56位的值分成两个28位的组
 *      1.4 针对每个子密钥,根据子密钥的序列值(代表16个子密钥中的第几个)旋转这两组值,每个子密钥的旋转次数不同然后重新合并
 *      1.5 将重组的密钥按照一个置换表将56位的缩小为48位
 *
 * 2.对数据块进行加密,解密
 *      2.1 每次对原文中固定的64位的数据块进行处理
 *      2.2 初始置换
 *      2.3 置换之后的数据分成两个32位的组,L0 和R0
 *      2.4 对数据块重复执行16轮的一系列操作.
 *      2.5 每一轮, 先将32位数据进行置换,将其扩展为48位的数据
 *      2.6 将48位的值与这一轮的子密钥Ki的异或值,产生一个48位的中间值
 *      2.7 将这个中间值通过8个单独的S盒执行8次替换操作.每个S盒从48位中取出对应的6位,并从表中找出一个4位的值,将4位值写入到缓冲区的4j位置处
 *      2.8 缓冲区的值就是一个32位的值.然后将这个值再通过p盒置换
 *      2.9 将32位的结果与传入本轮操作的原始数据的左分组L(i-1)之间的异或值
 *      2.10 将左右分组交换然后开始下一轮,只是在最后一轮中,不用交换左右分组
 *      2.11 全部完成16轮操作后,将最后的右分组和左分组连接起来,组成64位的数据
 *      2.12 将组成的64位数据进行最终置换,得到密文
 *
 *  @param plaintext: 必须是64位的8字节的数据
 *  @param ciphertext: 输出的加密的内容,也是一个64位加密之后的数据
 *  @param key: 必须是64位的8字节的数据
 */
void des_encipher(const unsigned char *plaintext,
                  unsigned char *ciphertext,
                  const unsigned  char *key) {

    des_main(plaintext, ciphertext, key, encipher);
    return;
}

/**
 * DES解密
 *  @param ciphertext: 必须是64位的8字节的数据,带解密的密文
 *  @param ciphertext: 输出的源的内容,也是一个64位的8字节的明文
 *  @param key: 必须是64位的8字节的数据
 */
void des_decipher(const unsigned char *ciphertext,
                    unsigned char *plaintext,
                    const unsigned char *key) {
    des_main(ciphertext, plaintext, key, decipher);
    return;
}