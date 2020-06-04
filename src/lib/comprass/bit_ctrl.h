// 简单的位操作需要用到的方法
// Created by wangxn on 2016/4/12.
//

/**
 * 每个位操作都可以操作缓冲区中的数据,缓冲区由无符号字符作为指针来指定
 * 该指针指向足够多的字节来表示缓冲区中位数.
 * 如果缓冲区中的位数不是8的倍数,
 * 那么说明最后一个字节的某些位没有使用
 */

#ifndef DATA_STRUCTURE_C_BIT_CTRL_H
#define DATA_STRUCTURE_C_BIT_CTRL_H



/**
 * 返回值  :  相应位所处的状态, 1或者0
 * 获取缓冲区bits中处于位置pos的位的状态.缓冲区最左边的位置为0位.
 */
int bit_get(const unsigned char *bits, int pos);

/**
 * 设置缓冲区bits中处于位置pos的位的状态(根据state值来设置).
 * 缓冲区最左边的位置为0位.
 * 状态值必须是0或者1
 */
void bit_set(unsigned char *bits/*in*/,
             int pos/*in*/,
             int state/*in*/);

/**
 * 按位计算两个缓冲区bits1和bits2的异或值,
 * 其中每个缓冲区包含size个位,
 * 然后将结果返回bitsx中
 * 按位异或的过程是将两个二进制操作数进行计算,
 * 如果操作数中处于位置i的两位相同,得到0,如果处于位置i的两位不同,则返回1.
 * bitsx所需要的存储空间由函数调用者来管理
 */
void bit_xor(const unsigned char *bits1/*in*/,
            const unsigned char *bits2/*in*/,
            unsigned char *bitsx/*out*/,
            int size/*in*/);

/**
 * 轮转缓冲区bits(含size位),将位值向左移count位.
 * 此操作完成后,处于最左端的count位移动到缓冲区最右端,而且其他的位也相应的轮转
 */
void bit_rot_left(unsigned char *bits/*in,out*/,
                  int size/*in*/,
                  int count/*in*/);

#endif //DATA_STRUCTURE_C_BIT_CTRL_H
