//
// Created by wangxn on 2016/4/20.
//

#include "../../lib/graph/graph_algorithm.h"
#include <stdio.h>
#include "../test.h"
#include "../student/student.h"


/**
 * 测试最小生成树
 */
void test_mini_span_tree_from_graph() {
    Student s[] = {
            *studn_get_init(1, "a", 0, 22, 11),
            *studn_get_init(2, "b", 0, 22, 11),
            *studn_get_init(3, "c", 0, 22, 11),
            *studn_get_init(4, "d", 0, 22, 11),
            *studn_get_init(5, "e", 0, 22, 11),
            *studn_get_init(6, "f", 0, 22, 11),
    };

    int * func_match = (int (*)(const void *, const void *))studn_match;

    MstVertex m[] = {
            /*0*/*mst_vertex_get_init((void *)(&s[0]), 0, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[1]), 0, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[2]), 0, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[3]), 0, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[4]), 0, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[5]), 0, func_match, NULL),
            
            /*a点延伸出去的边的连接节点*/
            /*6*/*mst_vertex_get_init((void *)(&s[1]), 7, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[2]), 4, func_match, NULL),
            
            /*b点延伸出去的边的连接节点*/
            /*8*/*mst_vertex_get_init((void *)(&s[0]), 7, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[2]), 6, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[3]), 2, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[5]), 4, func_match, NULL),
            
            /*c点延伸出去的边的连接节点*/
            /*12*/*mst_vertex_get_init((void *)(&s[0]), 4, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[1]), 6, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[4]), 9, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[5]), 8, func_match, NULL),
            
            /*d点延伸出去的边的连接节点*/
            /*16*/*mst_vertex_get_init((void *)(&s[1]), 2, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[5]), 7, func_match, NULL),
            
            
            /*e点延伸出去的边的连接节点*/
            /*18*/*mst_vertex_get_init((void *)(&s[2]), 9, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[5]), 1, func_match, NULL),
            
            /*f点延伸出去的边的连接节点*/
            /*20*/*mst_vertex_get_init((void *)(&s[1]), 4, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[2]), 8, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[3]), 7, func_match, NULL),
            *mst_vertex_get_init((void *)(&s[4]), 1, func_match, NULL),
    };

    Graph graph;
    int * default_mst_match =  (int (*)(const void *, const void *))mst_vertex_match;
    graph_init(&graph, default_mst_match, NULL);
    int i;
    //插入所有的节点
    for (i = 0; i < 6; ++i) {
        graph_ins_vertex(&graph, &m[i]);
    }
    printf("%s\n", "insert vertex success");

    //插入所有的边
    graph_ins_edge(&graph, &m[0], &m[6]);
    graph_ins_edge(&graph, &m[0], &m[7]);

    graph_ins_edge(&graph, &m[1], &m[8]);
    graph_ins_edge(&graph, &m[1], &m[9]);
    graph_ins_edge(&graph, &m[1], &m[10]);
    graph_ins_edge(&graph, &m[1], &m[11]);

    graph_ins_edge(&graph, &m[2], &m[12]);
    graph_ins_edge(&graph, &m[2], &m[13]);
    graph_ins_edge(&graph, &m[2], &m[14]);
    graph_ins_edge(&graph, &m[2], &m[15]);

    graph_ins_edge(&graph, &m[3], &m[16]);
    graph_ins_edge(&graph, &m[3], &m[17]);

    graph_ins_edge(&graph, &m[4], &m[18]);
    graph_ins_edge(&graph, &m[4], &m[19]);

    graph_ins_edge(&graph, &m[5], &m[20]);
    graph_ins_edge(&graph, &m[5], &m[21]);
    graph_ins_edge(&graph, &m[5], &m[22]);
    graph_ins_edge(&graph, &m[5], &m[23]);

    List span;
    mst(&graph, m, &span, (int (*)(const void *, const void *))mst_vertex_match);
    list_resetIterator(&span);
    while (list_hasNext(&span)) {
        list_moveToNext(&span);
        MstVertex *vertex = NULL;
        list_iterator(&span, (void **)(&vertex));
        Student *s = (Student *)vertex->data;
        printf("key : %.0f", vertex->key);
        if (vertex->parent != NULL) {
            Student *sP = (Student *)(vertex->parent->data);
            printf(", parentid:%d, ",  sP->_id);
        }
        studn_print(s);
    }

    return;
}