// 图算法的头文件 ,包含三种算法问题
//  最小生成树
//  最短路径
//  旅行商问题
// Created by wangxn on 2016/4/19.
//

#ifndef DATA_STRUCTURE_C_GRAPH_ALGORITHM_H
#define DATA_STRUCTURE_C_GRAPH_ALGORITHM_H

#include "../list/list.h"
#include "graph.h"

/**
 * 定义最小生成树的顶点的结构体
 */
typedef struct MstVertex_{
    void *data;

    /**
     * 权重
     * 当这个结构体在父结点的链接节点表中时,这个值表示父结点到当前节点的边的权重
     */
    double weight;

    /**
     * 遍历时的状态颜色
     * 白,灰,黑
     */
    VertexColor color;

    /**
     * 键值
     */
    double key;

    struct MstVertex_ *parent;

    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
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
    VertexColor color;
}TspVertex;

/**
 * 获取最小生成树需要的结构体
 */
MstVertex *mst_vertex_get_init(void *data,
                               double weight,
                               int (*match)(const void *key1, const void *key2),
                               void (*destroy)(void *data));

/**
 * 最小生成树需要的结构体的匹配函数
 */
int mst_vertex_match(MstVertex *m1, MstVertex *m2);

/**
 * 最小生成树需要的结构体的销毁函数
 */
void mst_vertex_destroy(MstVertex *mstVertex);

/**
 * 最小生成树
 *
 * 给定一个无方向的带权图G=(V,E)
 * 最小生成树为集合T,
 * T是以最小代价连接V中所有顶点所用边E的最小集合.
 * 集合T中的边能形成一棵树,这是因为每个顶点(除了第一个顶点,即根节点)都能向上找到它的一个父结点
 *
 * 从一个图中提取一棵树,这棵树包含所有的顶点,但是有最少的边
 *
 * Prim算法
 *
 *      每次选择一个与当前顶点最近的一个顶点,并将两个顶点之间的边加入到树中.
 *      贪心算法,但是可以提供不止于较优而是最优的结果
 *      不断的选择顶点,并计算边的权值,同时判断是否还有更有效的连接方式.类似于广度优先搜索,需要维护每个顶点的色值和键值
 *
 *      在图中所有的白色顶点中,选择键值最小的顶点u作为起始顶点,并标记其为黑色
 *      遍历与起始顶点的所有顶点v,设置v的键值为边(u,v)的权值,同时将u设置为v的父结点,并设置为黑色
 *
 *
 * 为一个无方向的带权图graph计算最小生成树.
 * 最小生成树从顶点start开始计算
 * 此操作会改变graph,
 * graph中的每个顶点必须包含MstVertex类型的数据.
 * 通过设置MstVertex.weight来指定每个边的权值
 * weight的值由传入graph_ins_edge的参数data2决定
 * M身体Vertex.data保存与顶点相关的数据,例如顶点标识符
 * graph.match用来比较MstVertex.data成员
 *
 * 一旦计算完成,最小生成树的相关数据将会返回到span,
 * span是存储MstVertex结构体的列表.
 * 在span中,父结点为NULL的顶点为最小生成树的根节点.
 * 其他每个顶点的parent成员都指向span中位于该顶点之前的那个顶点.
 * 访问span中的顶点,graph中的内存空间必须有效.
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
