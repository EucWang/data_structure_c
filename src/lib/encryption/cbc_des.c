//
// Created by wangxn on 2016/4/19.
//

#include "encrypt.h"
#include "cbc_des.h"
#include "../comprass/bit_ctrl.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * DES算法一次只能处理64位的数据,
 * 我们要处理的数据远远大于64位,
 * 每次处理64位,重复加密解密过程,直到处理完所有的分组,
 * 这种重复方式成为分组加密模式
 *
 * ECB模式:electronic code book:
 *      最普通的方式,就是将每一次处理完生成的密文添加到之前生成的密文之后,
 *      简单,不安全,
 *      只有破解了一小段数据,就可以依次建立密码本,对其他数据进行破解
 *
 * CBC模式:
 *      在加密一个明文分组前,将前一个输出的密文分组与该明文分组求异或,然后再加密.
 *      解密时,将前一个输出的明文分组同接下来待解密的密文分组求异或,然后再解密
 *
 *      通常, 会在明文的开始处增加一个随机的数据块,
 *      这个增加的随机数据块称为初始向量.
 *      按照正常的方式对其加密,
 *      然后将加密后的初始向量作为接下来加密和解密第一个分组数据的反馈.
 *
 * DES算法, CBC分组模式, 加密
 *
 * 这里, 假设明文的第一个分组是64位的初始向量.
 * 接受一个size字节大小的明文缓冲区作为参数,使用key作为密钥对其加密
 *
 * @param plaintext: 明文
 * @param ciphertext: 加密输出之后的密文
 * @param key:       加密用到的key,必须是64位8字节的
 * @param size:    明文的字节大小
 */
void cbc_des_encipher(const unsigned char *plaintext,
                      unsigned char *ciphertext,
                      const unsigned char *key,
                      int size) {
    unsigned char temp[8];
    int i;
    //对第一个8字节64位进行加密,加密之后的内容放入到ciphertext的前8个字节中
    des_encipher(&plaintext[0], &ciphertext[0], key);

    i = 8;
    while (i < size) {
        //将上一8个字节加密的密文与当前8个字节的明文进行异或操作,结果放入到temp中,temp是64位的
        bit_xor(&plaintext[i], &ciphertext[i - 8], temp, 64);
        //将异或之后的结果作为明文进行加密,key使用上一次的密钥,加密之后的密文放入到对应的ciphertext的8个字节的空间中
        des_encipher(temp, &ciphertext[i], NULL);
        //进入循环的自增
        i = i + 8;
    }
    return;
}

/**
 * DES算法, CBC分组模式, 解密
 *
 * 接受一个size字节大小的密文缓冲区作为参数,使用key作为密钥来对其解密
 * 为了保持对称,初始向量也要解密,并作为明文的第一个分组返回
 */
void cbc_des_decipher(const unsigned char *ciphertext,
                      unsigned char *plaintext,
                      const unsigned char *key,
                      int size) {

    unsigned char temp[8];
    int i;
    //对第一个8字节64位进行解密,加密之后的内容放入到ciphertext的前8个字节中
    des_decipher(&ciphertext[0], &plaintext[0], key);

    i = 8;
    while (i < size) {
        //对下一个8字节进行解密,解密之后的内容放入到temp中
        des_decipher(&ciphertext[i], temp, NULL);
        //将解密之后的内容与上一个密文进行异或,得到的结果放入到plaintext中对应的8位的位置
        bit_xor(&ciphertext[i - 8], temp, &plaintext[i], 64);
        i = i + 8;
    }
    return;

}
