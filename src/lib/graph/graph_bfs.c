//
// Created by wangxn on 2016/4/7.
//


#include "graph.h"
#include "graph_bfs.h"

/**
 * 广度优先搜素
 * 广度优先搜素可以确定最短的路径选择.
 * 可以确定2个结点之间最小的跳数
 * 该函数会修改图graph,因此如果有必要需要在调用本函数之前先对图创建拷贝.
 * hops中返回顶点的是指向graph中实际顶点的指针
 * 因此,调用者必须保证只要访问hops,graph中的存储空间就必须保持有效
 * graph中的每一个顶点都是一个BfsVertex类型的结构体
 *
 * 为了记录到达每个顶点的最小跳数,将每个顶点的hop计数设置为与该顶点邻接的hop计数加1
 * 对于发现的顶点都这样处理, 并且将其着色为灰色
 * 每一个顶点的颜色和跳数信息都由邻接表结构链表中的BfsVertex来维护.
 * 最后,加载hops中所有跳数不为-1的订单,这个就是从起始结点可到达的顶点.
 * @param graph: 图,模拟网络
 * @param start: 代表起点,
 * @param hops:  返回的跳数的链表.
 */
int bfs(Graph *graph, BfsVertex *start, List *hops) {
    //TODO
}