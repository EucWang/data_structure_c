//
// Created by wangxn on 2016/4/18.
//

#ifndef DATA_STRUCTURE_C_ENCRYPT_H
#define DATA_STRUCTURE_C_ENCRYPT_H

/**
 * in a secure implementation, Huge should be at least 400 decimal digists,
 * instead of the 10 below (ULONG_MAX = 4294967295, 这是32位4字节的unsigned long的最大值)
 * 64位8字节的unsigned long  应该更大
 */
typedef  unsigned long Huge;

/**
 * 定义RSA的公钥的结构体
 */
typedef struct RsaPubKey_{
    Huge e;
    Huge n;
}RsaPubKey;

/**
 * 定义RSA的私钥的结构体
 */
typedef  struct RsaPriKey_{
    Huge d;
    Huge n;
}RsaPriKey;

/**
 * 接口方法
 */

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
                  const unsigned  char *key);

/**
 * 采用DES将密文ciphertext的一个64位分组解密
 * 本函数假设ciphertext包含的是之前des_encipher加密过的密文.
 * 在key中指定64位的密钥.
 * plaintext是返回的64位的明文分组.
 * 由调用者负责管理plaintext的存储空间
 * 为了获得较高的效率,des_decipher可以重用之前调用中计算的子密钥.
 * 可以在随后的调用中将NULL传给key, 以此来开启这种功能
 *
 *  @param ciphertext: 必须是64位的8字节的数据,待解密的密文
 *  @param ciphertext: 输出的源的内容,也是一个64位的8字节的明文
 *  @param key: 必须是64位的8字节的数据
 */
void des_decipher(const unsigned char *ciphertext,
                  unsigned char *plaintext,
                  const unsigned char *key);

void rsa_encipher(Huge plaintext,
                  Huge *ciphertext,
                  RsaPubKey pubKey);

void rsa_decipher(Huge ciphertext,
                   Huge *plaintext,
                   RsaPriKey prikey);

#endif //DATA_STRUCTURE_C_ENCRYPT_H
