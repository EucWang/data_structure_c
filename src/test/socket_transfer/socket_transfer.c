// 利用哈夫曼编码进行压缩解压缩,
//  的优化网络传输的函数实现的文件
// Created by wangxn on 2016/4/13.
//

#include <sys/types.h>
#include <sys/socket.h>

#include "../../lib/comprass/compress.h"
#include "socket_transfer.h"




/**
 * 发送数据
 * 调用标志套接字函数send
 *
 * @param s : 一个已经建立连接的套接字描述符
 * @param data: 要发送数据的缓冲区
 * @param size: data的数据大小
 * @param flags: 要传入send的正常flags参数
 *
 */
int send_comp(int s/*in*/,
              const unsigned char *data/*in*/,
              int size/*in*/,
              int flags/*in*/) {

    unsigned  char *compressed;
    int size_comp;

    if ((size_comp = huffman_compress(data, &compressed, size)) < 0) {
        return -1;
    }

    if (send(s, (char *)(&size_comp), sizeof(int), flags) != sizeof(int)) {
        return  -1;
    }


    if (send(s, (char *)(compressed), size_comp, flags) != size_comp) {
        return  -1;
    }

    free(compressed);
    return 0;
}

/**
 * 接受数据
 * 调用标准套接字函数recv接受从send_comp发送过来的数据.
 *
 * @param s : 一个已经建立连接的套接字描述符
 * @param data: 指向解压缩数据的指针
 * @param size: 返回的data的数据大小
 * @param flags: 要传入recv的正常flags参数
 *
 */
int recv_comp(int s/*in*/,
              unsigned char **data/*out*/,
              int *size/*out*/,
              int flags/*in*/) {
    unsigned char *compressed;
    int size_comp;

    if (recv(s, (char *)&size_comp, sizeof(int), flags) != sizeof(int)) {
        return -1;
    }

    if ((compressed = (unsigned char *) malloc(size_comp)) == NULL) {
        return -1;
    }

    if (recv(s, (char *) compressed, size_comp, flags) != size_comp) {
        free(compressed);
        return  -1;
    }

    if ((*size = huffman_uncompress(compressed, data)) < 0) {
        return  -1;
    }

    free(compressed);
    return  0;
}