//
// Created by wangxn on 2016/4/7.
//

#include <stdio.h>
#include "graph.h"
#include "graph_bfs.h"
#include "../queue/queue.h"

/**
 * 广度优先搜索结构体的初始化和内存分配的函数
 * @param: data  存储的结点数据
 * @param: match  存储的结点数据的匹配方法
 * @param: destroy 存储的结点数据的销毁方法
 */
BfsVertex *bfs_vertex_get_init(void *data,
                              int (*match)(const void *key1, const void *key2),
                              void (*destroy)(void *data)) {
    BfsVertex * retval = (BfsVertex *)malloc(sizeof(BfsVertex));
    if (retval == NULL) {
        printf("%s\n", "bfs_vertex_get_init() function fail, call malloc() fail");
        return NULL;
    }
    retval->data = data;
    retval->color = white;
    retval->hops = -1;
    retval->match = match;
    retval->destroy = destroy;
    return retval;
}

/**
 * 广度优先搜索结构体的匹配函数
 */
int bfs_vertex_match(BfsVertex *b1, BfsVertex *b2) {
    if (b1->match != NULL) {
        return b1->match(b1->data, b2->data);
    } else {
        return -1;
    }
}
/**
 * 广度优先搜索结构体的销毁函数
 */
void bfs_vertex_destroy(BfsVertex *bfsVertex) {
    if (bfsVertex == NULL) {
        return;
    }

    if (bfsVertex->destroy != NULL) {
        bfsVertex->destroy(bfsVertex->data);
    }

    free(bfsVertex);
}




/**
 * 广度优先搜索 :　获取start结点可以到达的顶点的列表
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
    Queue_my queue;
    AdjList *adjList , *crl_adjlist;
    BfsVertex *clr_vertex, *adj_vertex;


    //遍历图中所有结点的集合的所有元素,找到第开始节点,将开始结点的状态颜色变为灰色,访问层级置为0,
    //同时其他结点的状态颜色置为白色,访问层级置为-1
    list_resetIterator(&(graph->adjlists));
    while (list_hasNext((&(graph->adjlists)))) {
        list_moveToNext((&(graph->adjlists)));
        list_iterator((&(graph->adjlists)), (void **)(&crl_adjlist));
        clr_vertex = (BfsVertex *)crl_adjlist->vertex;
        if (graph->match(clr_vertex, start)) {
            clr_vertex->color = gray;
            clr_vertex->hops = 0;
        } else {
            clr_vertex->color = white;
            clr_vertex->hops = -1;
        }
    }

    //初始化队列
    queue_m_init(&queue, NULL);
    //从图中拿取开始节点,加入到队列中
    if (graph_adjlist(graph, start, &crl_adjlist) != 0) {
        queue_m_destroy(&queue);
        printf("%s\n", "bfs() function fail , call graph_adjlist() fail");
        return  -1;
    }
    if (queue_enqueue(&queue, crl_adjlist) != 0) {
        queue_m_destroy(&queue);
        printf("%s\n", "bfs() function fail, call queue_enqueue() fail");
        return -1;
    }

    //开始广度路径搜素
    while (queue_size(&queue) > 0) {
        //从队列中取出一个节点, 遍历这个结点的邻接表链表数据,
        adjList  = queue_peek(&queue); //从头部取出元素
        list_resetIterator((List *)(&(adjList->adjacent)));        //初始化遍历
        while (list_hasNext((List *)(&(adjList->adjacent)))) {     //循环
            list_moveToNext((List *)(&(adjList->adjacent)));          //移动
            list_iterator((List *)(&(adjList->adjacent)), (void **)(&adj_vertex));   //获取遍历的元素
            //从图中找到这个元素对应的结点
            if (graph_adjlist(graph, adj_vertex, &crl_adjlist) != 0) {
                queue_m_destroy(&queue);
                printf("%s\n", "bfs() function fail, call graph_adjlist() fail, from graph  do not find the node which data in the queue");
                return -1;
            }
            clr_vertex = crl_adjlist->vertex;  //获取这个结点的数据

            //将白色节点数据状态颜色置为灰色,访问层级+1,并且将该结点加入到队列中
            if (clr_vertex->color == white) {
                clr_vertex->color = gray;
                clr_vertex->hops = ((BfsVertex *)adjList->vertex)->hops + 1;

                if(queue_enqueue(&queue, crl_adjlist) != 0) {
                    queue_m_destroy(&queue);
                    printf("%s\n", "bfs() function fail, call queue_enqueue() fail, add new node to queue fail");
                    return -1;
                }
            }
        }

        //遍历完成之后,从队列中取出一个结点,将其颜色置为黑色,在队列不为空时,进入下次循环
        if(queue_dequeue(&queue, (void **)(&adjList)) == 0) {
            ((BfsVertex *)(adjList->vertex))->color = black;
        } else {
            queue_m_destroy(&queue);
            printf("%s\n", "bfs() function fail, call queue_dequeue() fail");
            return -1;
        }
    }

    //搜索完成之后,队列为空,可以销毁队列
    queue_m_destroy(&queue);
    //对返回结构的List进行初始化
    //对图进行遍历,找到图中节点数据的hops字段不是-1的数据,
    list_resetIterator(&(graph->adjlists));
    while (list_hasNext(&(graph->adjlists))) {
        list_moveToNext(&(graph->adjlists));
        list_iterator(&(graph->adjlists), (void **)(&crl_adjlist));
        clr_vertex = (BfsVertex *)crl_adjlist->vertex;
        if (clr_vertex->hops != -1) {
            //将这些数据加入到返回结果的list集合中
            if(list_ins_next(hops, list_tail(hops), clr_vertex) != 0) {
                list_destroy(hops);
                printf("%s\n", "bfs() function fail, call list_ins_next() fail, insert the data to the hops list fail");
                return -1;
            }
        }
    }

    return 0;
}