//
// Created by wangxn on 2016/4/8.
//

#include <stdlib.h>
#include <stdio.h>
#include "graph_dfs.h"


/**
 * 结构体DfsVertex获取以及初始化
 */
DfsVertex *dfs_vertex_get_init(void *data,
                               int (*match)(const void *key1, const void *key2),
                               void (*destroy)(void *data)) {
    DfsVertex *dfsVertex = (DfsVertex *) malloc(sizeof(DfsVertex));
    if (dfsVertex == NULL) {
        return NULL;
    }

    dfsVertex->data = data;
    dfsVertex->match = match;
    dfsVertex->destroy = destroy;
    return  dfsVertex;
}


/**
 * 结构体DfsVertex的匹配校验
 */
int dfs_vertex_match(DfsVertex *b1, DfsVertex *b2) {
    if (b1->match != NULL) {
        return b1->match(b1->data, b2->data);
    }
    return -1;
}

/**
 * DfsVertex 结构的销毁方法
 */
void dfs_vertex_destroy(DfsVertex *bfsVertex) {
    if (bfsVertex == NULL) {
        return;
    }
    if (bfsVertex->destroy != NULL) {
        bfsVertex->destroy(bfsVertex->data);
    }

    free(bfsVertex);
}


/**
 * 递归遍历每一个路径
 *
 *
 */
static int dfs_main(Graph *graph, AdjList *adjList, List *ordered) {

//    AdjList *clr_adjlist,
            AdjList *adj_adjlist;
    DfsVertex *clr_vertex;
//    *adj_vertex;

    //将当前节点状态颜色置为灰色
    ((DfsVertex *) adjList->vertex)->color = gray;

    //遍历当前结点的邻接表集合
    list_resetIterator(&(adjList->adjacent));
    while (list_hasNext(&(adjList->adjacent))) {
        list_moveToNext(&(adjList->adjacent));
        list_iterator(&(adjList->adjacent), (void **) &clr_vertex);

        //校验链接表集合中的数据是否在图中存在,并且获取该数据在图中的结点
        if (graph_adjlist(graph, clr_vertex, &adj_adjlist) != 0) {
            printf("%s\n", "dfs_main() fail, call graph_adjlist() function fail, the data do not in the graph");
            return -1;
        }

        clr_vertex = (DfsVertex *) (adj_adjlist->vertex);

        //当邻接表集合中的数据的状态颜色为白色的时候, 递归调用本函数
        if (clr_vertex->color == white) {
            if (dfs_main(graph, adj_adjlist, ordered) != 0) {
                printf("%s\n", "recycle call dfs_main() fail.");
                return -1;
            }
        }
    }

    //遍历结束
    //将当前节点的颜色置为黑色
    ((DfsVertex *) adjList->vertex)->color = black;
    //将当前结点插入到返回的结果的链表的头部
    if (list_ins_next(ordered, NULL, ((DfsVertex *) adjList->vertex)) != 0) {
        printf("%s\n", "dfs_main() fail, call list_ins_next() function fail.");
        return -1;
    }

    return 0;
}


/**
 * 深度优先搜索
 * 有向无环图
 * 因此所有的边都是从左到右的方向
 * 这意味着所有满足先决条件的课程将出现在需要这种先决条件的课程的左边
 * 正规来说,有向无环图 G = (V , E) 的拓扑排序是其顶点的一个线性排序,
 * 以便如果 G 中存在一条边 (u, v) ,那么在线性顺序中u出现在v前面,
 * 在许多情况下,满足此条件的顺序有多个
 *
 * 对任务做拓扑排序
 * @param: graph 图
 * @param: ordered 完成拓扑排序后返回的顶点链表
 *
 * ordered中保存了指向图graph中顶点的指针,必须保证在访问ordered时,graph图中的存储空间保持有效
 *
 * dfs的最后一个循环保证对图中所有未相连的元素完成检索
 * 在dfs_main中逐个完成顶点的搜索并将其涂黑,
 * 然后插入链表ordered的头部.
 * 最后,ordered就包含完成拓扑排序后的顶点
 */
int graph_dfs(Graph *graph, List *ordered) {

    //对图中的每一个节点遍历, 将所有节点的状态颜色置为white
    AdjList *adjList;
    DfsVertex *dfsVertex;

    list_resetIterator(&(graph->adjlists));
    while (list_hasNext(&(graph->adjlists))) {
        list_moveToNext(&(graph->adjlists));
        list_iterator(&(graph->adjlists), (void **) (&adjList));

        dfsVertex = (DfsVertex *) adjList->vertex;
        dfsVertex->color = white;
    }

    //对待返回的链表ordered初始化
    list_init(ordered, NULL);

    //对图中的结点重新遍历, 调用其他函数处理
    //dfs的最后一个循环保证对图中所有未相连的元素完成检索
    list_resetIterator(&(graph->adjlists));
    while (list_hasNext(&(graph->adjlists))) {
        list_moveToNext(&(graph->adjlists));
        list_iterator(&(graph->adjlists), (void **) (&adjList));

        dfsVertex = (DfsVertex *) adjList->vertex;

        if (dfsVertex->color == white) {
            if (dfs_main(graph, adjList, ordered) != 0) {
                list_destroy(ordered);
                printf("%s\n", "graph_dfs() fail, call dfs_main() function fail");
                return -1;
            }
        }
    }
    return 0;
}
