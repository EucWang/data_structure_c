//
// Created by wangxn on 2016/4/12.
//



/**
 * 返回值  :  相应位所处的状态, 1或者0
 * 获取缓冲区bits中处于位置pos的位的状态.缓冲区最左边的位置为0位.
 */
int bit_get(const unsigned char *bits, int pos) {
    unsigned char mask;
    int i;
    //set a mask for the bit to get
    mask = 0x80;
    //将mask高位的1移动到对应的位
    for (i = 0; i < (pos % 8); ++i) {
        mask = mask>>1;
    }
    //获取bits中对应的字节,将这个字节和mask与操作,
    //如果对应的位不为1,则返回0,否则返回1
    return ((mask & bits[(int)(pos/8)]) == mask ? 1 : 0);
}

/**
 * 设置缓冲区bits中处于位置pos的位的状态(根据state值来设置).
 * 缓冲区最左边的位置为0位.
 * 状态值必须是0或者1
 */
void bit_set(unsigned char *bits/*in,out*/,
             int pos/*in*/,
             int state/*in*/) {

    unsigned  char mask;
    int i;

    mask = 0x80;
    //将mask高位的1移动到对应的位
    for (i = 0; i < (pos % 8); ++i) {
        mask = mask>>1;
    }

    if (state) {  //state为1
        //获取bits中对应的字节,将这个字节与mask进行或操作,那么其他的位不变,需改变的位为0,0或1为1,1或1位1
        //结果保存到bits中
        bits[pos/8] = bits[pos/8] | mask;
    } else {   //state为0
        //对mask取反,要改变的位为0,其他的位都为1,
        //获取bits中对应的字节,将这个字节与mask进行与操作,对应的为mask中为0,0与1为0,0与0为0,其他位保持原来的不变
        //结果保存到bits中
        bits[pos/8] = bits[pos/8] & (~mask);
    }
}


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
             int size/*in*/) {

    int i;
    for (i = 0; i < size; ++i) {
        if (bit_get(bits1, i) != bit_get(bits2, i)) {
            bit_set(bitsx, i, 1);
        } else {
            bit_set(bitsx, i, 0);
        }
    }
}

/**
 * 轮转缓冲区bits(含size位),将位值向左移count位.
 * 此操作完成后,处于最左端的count位移动到缓冲区最右端,而且其他的位也相应的轮转
 */
void bit_rot_left(unsigned char *bits/*in,out*/,
                  int size/*in*/,
                  int count/*in*/) {

    int fbit, lbit, i,j;

    if (size > 0) {
        //真个缓冲区都向左移,溢出的位的值放入到缓冲区的最右边的位
        //每次移动一位,都如此处理,总共移动count次
        for (j = 0; j < count; ++j) {
            //每次移动时,对每个字节的处理
            for (i = 0; i < ((size - 1)/8); ++i) {
                lbit = bit_get(&bits[i], 0);
                if (i == 0) {
                    //保存最左边的字节的最左边的位状态到fbit中
                    fbit = lbit;
                } else {
                    //如果不是最左边的那个字节,
                    //将该字节的最左边位复制给该字节左边的一个字节的最右边的位
                    bit_set(&bits[i - 1], 7, lbit);
                }
                //该字节左移一位
                bits[i] = bits[i] << 1;
            }
            //完成一轮缓冲区的全体左移,将移除的位状态复制给缓冲区最右边的位
            bit_set(bits, size - 1, fbit);
        }
    }
    return;
}