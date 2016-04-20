//
// Created by wangxn on 2016/4/7.
//

#include <stdio.h>
#include <string.h>
#include "graph.h"

/**
 * 图的初始化
 */
void graph_init(Graph *graph,
                int (*match)(const void *key1, const void *key2),
                void (*destroy)(void *data)){

    graph->vcount = 0;
    graph->ecount = 0;
    graph->match = match;
    graph->destroy = destroy;

    list_init(&(graph->adjlists), NULL);  //初始化链表

    return;
}

/**
 * 图的销毁
 */
void graph_destroy(Graph *graph){
    AdjList *adjList;
    //遍历链表,移除每一个节点数据
    while (list_size(&(graph->adjlists)) > 0) {
        //移除root元素,将adjList指向从链表中移除的元素节点
        if (list_rem_next(&(graph->adjlists), NULL, (void **) (&adjList)) == 0) {
            //销毁节点上的set集合,也就是该节点出度的边的集合
            set_destroy(&(adjList->adjacent));

            if (graph->destroy != NULL) {
                graph->destroy(adjList->vertex);  //销毁节点中保存的节点数据
                free(adjList);                   //释放内存空间
            }
        }
    }
    list_destroy(&(graph->adjlists));   //销毁节点链表
    memset(graph, 0, sizeof(Graph));
    return;
}

/**
 * 插入结点
 */
int graph_ins_vertex(Graph *graph, const void *data){
    int retval = 0;

    //首先确保插入的节点数据在结点链表中没有相同的
    AdjList *ele_data;
    list_resetIterator(&(graph->adjlists));  //重置遍历参数
    while (list_hasNext(&(graph->adjlists))) {   //判断是否有可以遍历的数据
        list_moveToNext(&(graph->adjlists));
        list_iterator(&(graph->adjlists),(void **)(&ele_data));   //获取遍历的数据
        if(graph->match != NULL && graph->match(ele_data->vertex, data)) {   //比较数据,如果相同,则不插入数据,
            printf("%s\n", "graph_ins_vertex() function fail, has same data in the graph, do nothing");
            return 1;
        }
    }

    //为节点分配内存, 设置初始化数据
    AdjList *adjList = (AdjList *)malloc(sizeof(AdjList));
    if (adjList == NULL) {
        printf("%s\n", "graph_ins_vertex() function fail, malloc call err");
        return -1;
    }

    adjList->vertex = (void *)data;
    set_init(&(adjList->adjacent), graph->match, NULL);

    //将新节点插入到节点链表的尾部
    retval = list_ins_next(&(graph->adjlists), list_tail(&(graph->adjlists)), adjList);
    if (retval != 0) {
        printf("%s\n", "graph_ins_vertex() function fail, call list_ins_next() fail");
        return retval;
    }

    //图字段vcount值更新
    graph->vcount++;
    return 0;
}

/**
 * 插入边
 */
int graph_ins_edge(Graph *graph, const void *data1, const void *data2){
    int retval = 0;
    //确保插入的边的两个节点都在图中的结点链表中
    AdjList *ele_data,  *data1_adjlist;
    void  * the_data = NULL;
    int flag1 = 0, flag2 = 0;
    list_resetIterator(&(graph->adjlists));  //重置遍历参数
    while (list_hasNext(&(graph->adjlists))) {   //判断是否有可以遍历的数据
        list_moveToNext(&(graph->adjlists));
        list_iterator(&(graph->adjlists),(void **)(&ele_data));   //获取遍历的数据
        the_data = ele_data->vertex;
        if(graph->match(the_data, data1)) {   //比较数据,如果相同,退出循环
            data1_adjlist = ele_data;
            flag1 ++;
        }
        if(graph->match(the_data, data2)) {   //比较数据,如果相同,退出循环
            flag2 ++;
        }
        if (flag1 == 1 && flag2 == 1) {
            break;
        }
    }

    if (flag1 != 1 || flag2 != 1) {
        printf("%s\n", "graph_ins_edge function() fail, the data1 or data2 not in the graph.");
        return -1;
    }

    //将data2插入到data1的结点中的set集合中,也就是data1的出度
    retval = set_insert(&(data1_adjlist->adjacent), data2);
    if (retval != 0) {
        printf("%s\n", "graph_ins_edge function() fail, to insert data2 to the set of data1's edges fail");
        return retval;
    }

    //图字段ecount值更改
    graph->ecount++;
    return 0;
}

/**
 * 移除结点, 只能删除孤立的节点, 即该节点没有出度到其他节点的边,其他节点也没有出度到该节点的边
 * 将一个AdjList结构体从邻接表结构链表中移除
 * 首先确保该顶点不存在于任何邻接表中,
 * 但顶点要存在与邻接表结构链表里,且该顶点的邻接表为空
 * 然后调用list_rem_next从邻接表链表中移除合适的AdjList结构体
 * 最后,更新vcount值
 *
 * 返回0 , 表示移除成功
 * 返回-1, 移除失败
 */
int graph_rem_vertex(Graph *graph, void **data){

    AdjList *adjList, *temp, *prev;
    ListElmt * prevElmt;
    int found = 0;

    //遍历图的所有节点,
    list_resetIterator(&(graph->adjlists));
    while (list_hasNext(&(graph->adjlists))) {
        list_moveToNext(&(graph->adjlists));
        list_iterator(&(graph->adjlists), (void **)(&adjList));

        //在每一个节点的邻接链表中查找data,如果存在任意一个,则退出,
        if(set_is_member(&(adjList->adjacent),*data)) {
            printf("%s\n", "graph_rem_vertex() function fail, the data already in other data's adjacency set");
            return -1;
        }

        //找到对应的节点
        if(graph->match(*data, adjList->vertex)) {
            temp = adjList;
            found = 1;
        }

        //保存对应的节点之前的一个节点
        if (!found) {
            prevElmt = (graph->adjlists).current;
//            prevElmt = adjList->adjacent.current;
//            prev = adjList;
        }
    }

    //如果没有在图中找到对应的节点, 退出
    if (!found) {
        printf("%s\n", "graph_rem_vertex() function fail, do not found the data in the graph");
        return -1;
    }

    //如果图中对应的节点的邻接链表有内容,则这个节点不能移除,退出
    if (set_size(&(temp->adjacent)) > 0) {
        printf("%s\n", "graph_rem_vertex() function fail, the data in graph has adjacency set, can not remove");
        return -1;
    }

    //从图中的邻接表链表中移除该data, 将移除的data数据传递给adjList
    if (list_rem_next(&(graph->adjlists), prevElmt, (void **)&adjList) != 0) {
        printf("%s\n", "graph_rem_vertex() function fail, call list_rem_next() fail");
        return -1;
    }

    *data = adjList->vertex;  //将图中节点中的数据传递给data
    free(adjList);            //释放节点的内存空间
    graph->vcount--;         //vcount字段值修改
    return 0;
}

/**
 * 移除边,只移除边
 * 将由data2所指定的顶点从data1所指定的顶点的邻接表中移除.
 * 首先确保data1在图中.
 * 然后调用set_remove来讲data2从data1所指定的顶点的邻接表中移除,
 * 然后更新ecount值
 *
 * 返回0,移除成功
 * 返回-1, 移除失败
 */
int graph_rem_edge(Graph *graph, void *data1, void **data2){
    void **adjList;
    //遍历图的所有节点
    list_resetIterator(&(graph->adjlists));
    int found = 0;
    while (list_hasNext(&(graph->adjlists))) {
        list_moveToNext(&(graph->adjlists));
        list_iterator(&(graph->adjlists), adjList);

        //找到data1所在的节点
        if(graph->match(data1, ((AdjList *)(*adjList))->vertex)){
            found = 1;
            break;
        }
    }

    if (found == 0 || adjList == NULL || *adjList == NULL) {
        printf("%s\n", "graph_rem_edge() function fail, do not found data1 in the graph");
        return -1;
    }

    //在data1 所在的节点的邻接表中移除data2数据
    if(set_remove(&(((AdjList *)(*adjList))->adjacent), data2) != 0) {
        printf("%s\n", "graph_rem_edge() function fail, call set_remove() fail");
        return  -1;
    }
    //修改ecount值
    graph->ecount--;
    return 0;
}

/**
 * 获取邻接表链表集合,返回一个AdjList结构体,
 * 其中包含指定顶点的邻接顶点集合
 * 为了实现这个操作,检索邻接表结构链表
 * 知道找到其中包含指定顶点的那个AdjList结构体
 */
int graph_adjlist(const Graph *graph/*in*/, const void *data/*in*/, AdjList **adjlist/*out*/){
    AdjList *tmp;
    int found  = 0;
    //遍历图的所有节点
    list_resetIterator((List *)(&(graph->adjlists)));
    while (list_hasNext((List *)(&(graph->adjlists)))) {
        list_moveToNext((List *)(&(graph->adjlists)));
        list_iterator((List *)(&(graph->adjlists)), (void **)(&tmp));

        //找到data所在的节点
        if(graph->match(data, tmp->vertex)){
            found = 1;
            break;
        }
    }

    if (tmp == NULL || found == 0) {
        printf("%s\n", "graph_rem_edge() function fail, do not found data1 in the graph");
        return -1;
    }

    *adjlist = tmp;
    return  0;
}

/**
 * 判断顶点data1是否与data2有邻接关系
 * 为了实现该操作,首先在邻接表链表结构中定位由data1所指定的顶点,
 * 然后调用set_is_member来判断data2是否在data1的邻接表中
 */
int graph_is_adjacent(const Graph *graph, const void *data1, const void *data2){
    AdjList *tmp;
    //遍历图的所有节点
    list_resetIterator((List *)(&(graph->adjlists)));
    while (list_hasNext((List *)(&(graph->adjlists)))) {
        list_moveToNext((List *)(&(graph->adjlists)));
        list_iterator((List *)(&(graph->adjlists)), (void **)(&tmp));

        //找到data所在的节点
        if(graph->match(data1, tmp->vertex)){
            break;
        }
    }

    if (tmp == NULL) {
        printf("%s\n", "graph_rem_edge() function fail, do not found data1 in the graph");
        return -1;
    }

    //判断data2是否在data1中的adjacency 的set集合中
    return  set_is_member(&(tmp->adjacent), data2);
}
