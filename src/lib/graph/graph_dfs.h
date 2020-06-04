// 图的深度优先搜索
// Created by wangxn on 2016/4/8.
//

#ifndef DATA_STRUCTURE_C_GRAPH_DFS_H
#define DATA_STRUCTURE_C_GRAPH_DFS_H

#include "graph.h"
#include "../list/list.h"

/**
 * 深度优先搜索需要用到的结构体
 */
typedef  struct  DfsVertex_{
    void *data;
    VertexColor color;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
}DfsVertex;

/**
 * 结构体DfsVertex获取以及初始化
 */
DfsVertex * dfs_vertex_get_init(void *data,
                                int (*match)(const void *key1, const void *key2),
                                void (*destroy)(void *data));


/**
 * 结构体DfsVertex的匹配校验
 */
int dfs_vertex_match(DfsVertex *b1, DfsVertex *b2);

/**
 * DfsVertex 结构的销毁方法
 */
void dfs_vertex_destroy(DfsVertex *bfsVertex);



/**
 * 深度优先搜索
 * 有向无环图
 * 因此所有的边都是从左到右的方向
 * 这意味着所有满足先决条件的课程将出现在需要这种先决条件的课程的左边
 * 正规来说,有向无环图 G = (V , E) 的拓扑排序是其顶点的一个线性排序,
 * 以便如果 G 中存在一条边 (u, v) ,那么在线性顺序中u出现在v前面,
 * 在许多情况下,满足此条件的顺序有多个
 */
int graph_dfs(Graph *graph, List *ordered);

#endif //DATA_STRUCTURE_C_GRAPH_DFS_H
