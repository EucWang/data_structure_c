#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
//
// Created by wangxn on 2016/4/6.
//

/**
 *  我们主要通过临接表链表结构来表示图[有向图]
 *  链表中的每个结构体都包含两个成员：
 *   一个顶点以及与该顶点相临接的一个顶点集合。
 *  AdjList 表示邻接表链表中的结点，每一个邻接表实现为一个集合。
 *  Graph 代表图这种数据结构。
 *  这个结构体由5个成员组成：
 *     vcount:  表示图中顶点的个数
 *     ecount:  表示图中边的个数
 *     match:   数据的匹配函数
 *     destroy: 数据的销毁函数
 *     adjlists:  表示临接表链表
 */

#include <stdlib.h>
#include "../list/list.h"
#include "../set/set.h"

/**
 *临接表链表中的结点的数据结构
 */
typedef struct AdjList_{

    /**
     * 结点的数据
     */
    void *vertex;
    
    /**
     * 对应这个结点的临接表链表的集合
     */
    Set adjacent;    
}AdjList;

/**
 * 图的数据结构
 */
typedef struct Graph_{
    /**
     * 结点的个数
     */
    int vcount;
    /**
     * 边的个数
     */
    int ecount;
    
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);

    /**
     * 邻接表链表集合
     */
    List adjlists;
}Graph;

/**
 * 定义结点的颜色, 这个颜色代表图中节点在深度优先搜素/广度优先搜索 时 的状态
 * 默认都是白色,表示节点没有被遍历
 * 黑色,表示节点已经遍历过
 * 灰色,表示节点已经被加入到搜索队列中了,但是还没有遍历,等待遍历
 */
typedef enum VertexColor_{
    white, gray, black
}VertexColor;

/*public interface*/

void graph_init(Graph *graph,
                int (*match)(const void *key1, const void *key2),
                void (*destroy)(void *data)
    );

/**
 * 图的销毁
 */
void graph_destroy(Graph *graph);

/**
 * 插入结点
 */
int graph_ins_vertex(Graph *graph, const void *data);

/**
 * 插入边
 */
int graph_ins_edge(Graph *graph, const void *data1, const void *data2);

/**
 * 移除结点, 同时移除结点的所有边
 * 将一个AdjList结构体从邻接表结构链表中移除
 * 首先确保该顶点不存在于任何邻接表中,
 * 但顶点要存在与邻接表结构链表里,且该顶点的邻接表为空
 * 然后调用list_rem_next从邻接表链表中移除合适的AdjList结构体
 * 最后,更新vcount值
 */
int graph_rem_vertex(Graph *graph, void **data);

/**
 * 移除边,只移除边
 * 将由data2所指定的顶点从data1所指定的顶点的邻接表中移除.
 * 首先确保data1在图中.
 * 然后调用set_remove来讲data2从data1所指定的顶点的邻接表中移除,
 * 然后更新ecount值
 */
int graph_rem_edge(Graph *graph, void *data1, void **data2);

/**
 * 获取邻接表链表集合,返回一个AdjList结构体,
 * 其中包含指定顶点的邻接顶点集合
 * 为了实现这个操作,检索邻接表结构链表
 * 知道找到其中包含指定顶点的那个AdjList结构体
 */
int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist);

/**
 * 判断顶点data1是否与data2有邻接关系
 * 为了实现该操作,首先在邻接表链表结构中定位由data1所指定的顶点,
 * 然后调用set_is_member来判断data2是否在data1的邻接表中
 */
int graph_is_adjacent(const Graph *graph, const void *data1, const void *data2);

/**
 * 获取邻接表链表
 */
#define graph_adjlists(graph) ((graph)->adjlists)

/**
 * 获取结点数
 */
#define graph_vcount(graph) ((graph)->vcount)

/**
 * 获取边数
 */
#define graph_ecount(graph) ((graph)->ecount)

#endif
