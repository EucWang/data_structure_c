//
// Created by wangxn on 2016/4/19.
//

#ifndef DATA_STRUCTURE_C_CBC_DES_H
#define DATA_STRUCTURE_C_CBC_DES_H

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
 */
void cbc_des_encipher(const unsigned char *plaintext,
                      unsigned char *ciphertext,
                      const unsigned char *key,
                      int size);

/**
 * DES算法, CBC分组模式, 解密
 *
 * 接受一个size字节大小的密文缓冲区作为参数,使用key作为密钥来对其解密
 * 为了保持对称,初始向量也要解密,并作为明文的第一个分组返回
 */
void cbc_des_decipher(const unsigned char *ciphertext,
                      unsigned char *plaintext,
                      const unsigned char *key,
                      int size);

#endif //DATA_STRUCTURE_C_CBC_DES_H
