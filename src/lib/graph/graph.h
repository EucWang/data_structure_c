#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

/**
 *  我们主要通过临接表链表结构来表示图
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
#include "../lib/list/list.h"
#include "../lib/set/set.h"

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
 * 定义结点的颜色
 * 默认都是白色
 */
typedef enum VertexColor_{
    white, gray, black
}VertexColor;

/*public interface*/

void graph_init(Graph *graph,
                int (*match)(const void *key1, const void *key2),
                void (*destroy)(void *data)
    );

void graph_destroy(Graph *graph);

int graph_ins_vertex(Graph *graph, const void *data);

int graph_ins_edge(Graph *graph, const void *data1, const void *data2);

int graph_rem_vertex(Graph *graph, void **data);

int graph_rem_edge(Graph *graph, void *data1, void **data2);

int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist);

int graph_is_adjacent(const Graph *graph, const void *data1, const void *data2);

#define graph_adjlists(graph) ((graph)->adjlist)

#define graph_vcount(graph) ((graph)->vcount)

#define graph_ecount(graph) ((graph)->ecount)









#endif
