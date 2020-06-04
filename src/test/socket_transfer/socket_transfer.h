//
// Created by wangxn on 2016/4/13.
//

#ifndef DATA_STRUCTURE_C_SOCKET_TRANSFER_H
#define DATA_STRUCTURE_C_SOCKET_TRANSFER_H

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
int send_comp(int s,
              const unsigned char *data,
              int size,
              int flags);
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
int recv_comp(int s,
              unsigned char **data,
              int *size,
              int flags);

#endif //DATA_STRUCTURE_C_SOCKET_TRANSFER_H
