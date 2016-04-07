//
// 图广度优先搜索的头文件
// Created by wangxn on 2016/4/7.
//

/**
 * 广度优先搜素可以确定最短的路径选择.
 * 可以确定2个结点之间最小的跳数
 */

#ifndef DATA_STRUCTURE_C_GRAPH_BFS_H
#define DATA_STRUCTURE_C_GRAPH_BFS_H

#include "graph.h"
#include "../list/list.h"

/**
 * define a structure for vertices in a breadth-first search.
 */
typedef struct BfsVertex_{
    /*
     * 指向图中的顶点的数据域的指针
     */
    void *data;
    /**
     * 在搜索过程中维护顶点的颜色
     */
    VertexColor color;
    /**
     * hops维护从起始结点开始到顶点的跳数统计
     */
    int hops;
}BfsVertex;

/**
 * 广度优先搜素
 * 广度优先搜素可以确定最短的路径选择.
 * 可以确定2个结点之间最小的跳数
 * 该函数会修改图graph,因此如果有必要需要在调用本函数之前先对图创建拷贝.
 * hops中返回顶点的是指向graph中实际顶点的指针
 * 因此,调用者必须保证只要访问hops,graph中的存储空间就必须保持有效
 * graph中的每一个顶点都是一个BfsVertex类型的结构体
 * @param graph: 图,模拟网络
 * @param start: 代表起点,
 * @param hops:  返回的跳数的链表.
 */
int bfs(Graph *graph, BfsVertex *start, List *hops);

#endif //DATA_STRUCTURE_C_GRAPH_BFS_H
