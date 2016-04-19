// 图算法的头文件 ,包含三种算法问题
//  最小生成树
//  最短路径
//  旅行商问题
// Created by wangxn on 2016/4/19.
//

#ifndef DATA_STRUCTURE_C_GRAPH_ALGORITHM_H
#define DATA_STRUCTURE_C_GRAPH_ALGORITHM_H

#include "graph.h"
#include "../list/list.h"

/**
 * 定义最小生成树的顶点的结构体
 */
typedef struct MstVertex_{
    void *data;

    /**
     * 权重
     */
    double weight;

    /**
     * 遍历时的状态颜色
     * 白,灰,黑
     */
    VertexColor color;

    double key;

    struct MstVertex_ *parent;
}MstVertex;

/**
 * 最短路径的问题的顶点的结构体
 */
typedef  struct PathVertex_{
    void *data;
    double weight;
    VertexColor color;
    double d;
    struct PathVertex_ *parent;
}PathVertex;

/**
 * 旅行商问题用到的顶点的结构体
 */
typedef struct TspVertex_{
    void *data;
    double x, y;
    VertextColor color;
}TspVertex;


/**
 * 最小生成树
 *
 * 给定一个无方向的带权图G=(V,E)
 * 最小生成树为集合T,
 * T是以最小代价连接V中所有顶点所用边E的最小集合.
 * 集合T中的边能形成一棵树,这是因为每个顶点(除了第一个顶点,即根节点)都能向上找到它的一个父结点
 *
 * Prim算法
 *
 */
int mst(Graph *graph,
        const MstVertex *start,
        List *span,
        int (*match)(const void *key1, const void *key2));

/**
 * 最短路径
 */
int shortest(Graph *graph,
        const PathVertex *start,
        List *paths,
        int (*match)(const void *key1, const ));

/**
 * 旅行商问题
 */
int tsp(List *vertices,
        const TspVertex *start,
        List *tour,
        int (*match)(const void *key1, const void *key2));


#endif //DATA_STRUCTURE_C_GRAPH_ALGORITHM_H
