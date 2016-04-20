//
// Created by wangxn on 2016/4/20.
//

#include "graph_algorithm.h"
#include "../list/list.h"
#include "graph.h"

#include <float.h>
#include <stdio.h>
#include <stdlib.h>


MstVertex *mst_vertex_get_init(void *data,
                               double weight,
                               int (*match)(const void *key1, const void *key2),
                               void (*destroy)(void *data)) {
    MstVertex * retval = (MstVertex *)malloc(sizeof(MstVertex));
    if (retval == NULL) {
        printf("%s\n", "bfs_vertex_get_init() function fail, call malloc() fail");
        return NULL;
    }
    retval->data = data;
    retval->color = white;
    retval->weight = weight;
    retval->key = DBL_MAX;

    retval->match = match;
    retval->destroy = destroy;

    return retval;
}

int mst_vertex_match(MstVertex *m1, MstVertex *m2) {
    if (m1->match != NULL) {
        return m1->match(m1->data, m2->data);
    } else {
        return -1;
    }
}

void mst_vertex_destroy(MstVertex *mstVertex) {
    if (mstVertex == NULL) {
        return;
    }

    if (mstVertex->destroy != NULL) {
        mstVertex->destroy(mstVertex->data);
    }

    free(mstVertex);
}


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
int mst(Graph *graph/*in*/,
        const MstVertex *start/*in*/,
        List *span/*out*/,
        int (*match)(const void *key1, const void *key2)/*in*/) {

    MstVertex *mst_vertex, *mst_temp, *adj_vertex;
    AdjList * adjList, *data;
    double minimum;
    int found, i;

    list_resetIterator(&(graph->adjlists));
    //遍历图中的所有顶点的列表,取出每个顶点
    while (list_hasNext(&(graph->adjlists))) {
        list_moveToNext(&(graph->adjlists));
        list_iterator(&(graph->adjlists), (void **)&data);
        mst_vertex = (MstVertex *)(data->vertex);

        //比较当前顶点和传参的start顶点
        if (match(mst_vertex, start)) {
        //相同,设置为起始顶点,设置颜色,键值,父结点,以及found(表示找到了起始节点)
            mst_vertex->color = white;
            mst_vertex->key = 0;      //起始节点不同于其他节点的地方,key为0
            mst_vertex->parent = NULL;
        } else {
        //不相同,设置颜色,键值,父结点
            mst_vertex->color = white;
            mst_vertex->key = DBL_MAX;
            mst_vertex->parent = NULL;
        }
    }

    //判断found参数是否为1,否则退出函数
    if (!found) {
        return -1;
    }

    i = 0;
    while (i < graph_vcount(graph)) {
        minimum = DBL_MAX;

        //循环遍历图中的所有顶点,
        list_resetIterator(&graph_adjlists(graph));
        while (list_hasNext(&graph_adjlists(graph))) {
            list_moveToNext(&graph_adjlists(graph));
            list_iterator(&graph_adjlists(graph), (void **)(&data));
            mst_temp = (MstVertex *)(data->vertex);

            //找到颜色为白色, 键值最小的顶点以及其键值
            //初始时,只有起始节点的key为0,其他的节点的key都是DBL_MAX,所以找到的也就是起始节点
            if (mst_temp->color == white && mst_temp->key < minimum) {
                minimum = mst_temp->key;
                mst_vertex = mst_temp;
                adjList = data;
            }
        }

        //将这个顶点的颜色置为黑色
        mst_vertex->color = black;

        //遍历这个顶点的所有相邻顶点
        list_resetIterator(&(adjList->adjacent));
        while (list_hasNext(&(adjList->adjacent))) {
            list_moveToNext(&(adjList->adjacent));
            list_iterator(&(adjList->adjacent), (void **)(&adj_vertex));

            //并遍历图的所有顶点的列表,找到相邻顶点在图中顶点列表中的结构体
            list_resetIterator(&graph_adjlists(graph));
            while (list_hasNext(&graph_adjlists(graph))) {
                list_moveToNext(&graph_adjlists(graph));
                list_iterator(&graph_adjlists(graph), (void **)(&data));
                mst_temp = (MstVertex *)(data->vertex);
                //如果找到了
                if (match(mst_temp, adj_vertex)) {
                    //在这个顶点的颜色为白色,并且其weight值小于key值的情况下
                    //key值最小的是起始节点为0, 其他的节点的key都是DBL_MAX, 这是初始情况
                    if (mst_temp->color == white && adj_vertex->weight < mst_temp->key) {
                        // 设置key值为weight值
                        mst_temp->key = adj_vertex->weight;
                        //设置parent为当前while循环找到的顶点,
                        mst_temp->parent = mst_vertex;
                    }
                    //并且退出循环
                    break;
                }
            }
        }
        i++;
    }

    //初始化span的list集合
    list_init(span, NULL);
    //遍历图的所有节点
    list_resetIterator(&(graph_adjlists(graph)));
    while (list_hasNext(&(graph_adjlists(graph)))) {
        list_moveToNext(&(graph_adjlists(graph)));
        list_iterator(&(graph_adjlists(graph)), (void **) (&data));
        mst_temp = (MstVertex *)data->vertex;
        if (mst_temp->color == black) {
            //将图中的所有颜色为黑色的顶点加入到span中的尾部
            if (list_ins_next(span, list_tail(span), mst_temp) != 0) {
                list_destroy(span);
                return -1;
            }
        }
    }

    return 0;
}