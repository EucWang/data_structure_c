//
// Created by wangxn on 2016/4/21.
//

#include "../lib/graph/graph_algorithm.h"
#include <stdio.h>
#include "test.h"
#include "student/student.h"


/**
 * 测试最短路径树
 */
void test_shortest_tree_from_graph() {
    Student s[] = {
            *studn_get_init(1, "a", 0, 22, 11),
            *studn_get_init(2, "b", 0, 22, 11),
            *studn_get_init(3, "c", 0, 22, 11),
            *studn_get_init(4, "d", 0, 22, 11),
            *studn_get_init(5, "e", 0, 22, 11),
            *studn_get_init(6, "f", 0, 22, 11),
    };

    PathVertex m[] = {
            /*0*/*path_vertex_get_init((void *)(&s[0]), 0, (int (*)(const void *, const void *))studn_match, NULL),
                 *path_vertex_get_init((void *)(&s[1]), 0, (int (*)(const void *, const void *))studn_match, NULL),
                 *path_vertex_get_init((void *)(&s[2]), 0, (int (*)(const void *, const void *))studn_match, NULL),
                 *path_vertex_get_init((void *)(&s[3]), 0, (int (*)(const void *, const void *))studn_match, NULL),
                 *path_vertex_get_init((void *)(&s[4]), 0, (int (*)(const void *, const void *))studn_match, NULL),
                 *path_vertex_get_init((void *)(&s[5]), 0, (int (*)(const void *, const void *))studn_match, NULL),

            /*a点延伸出去的边的连接节点*/
            /*6*/*path_vertex_get_init((void *)(&s[1]), 8, (int (*)(const void *, const void *))studn_match, NULL),
                 *path_vertex_get_init((void *)(&s[2]), 4, (int (*)(const void *, const void *))studn_match, NULL),

            /*b点延伸出去的边的连接节点*/
            /*8*/*path_vertex_get_init((void *)(&s[2]), 6, (int (*)(const void *, const void *))studn_match, NULL),
                 *path_vertex_get_init((void *)(&s[3]), 2, (int (*)(const void *, const void *))studn_match, NULL),
                 *path_vertex_get_init((void *)(&s[5]), 4, (int (*)(const void *, const void *))studn_match, NULL),

            /*c点延伸出去的边的连接节点*/
           /*11*/*path_vertex_get_init((void *)(&s[4]), 4, (int (*)(const void *, const void *))studn_match, NULL),
                 *path_vertex_get_init((void *)(&s[5]), 1, (int (*)(const void *, const void *))studn_match, NULL),

            /*e点延伸出去的边的连接节点*/
            /*13*/*path_vertex_get_init((void *)(&s[5]), 5, (int (*)(const void *, const void *))studn_match, NULL),

            /*f点延伸出去的边的连接节点*/
            /*14*/*path_vertex_get_init((void *)(&s[1]), 2, (int (*)(const void *, const void *))studn_match, NULL),
                 *path_vertex_get_init((void *)(&s[3]), 7, (int (*)(const void *, const void *))studn_match, NULL),
                 *path_vertex_get_init((void *)(&s[4]), 4, (int (*)(const void *, const void *))studn_match, NULL),
    };

    Graph graph;
    graph_init(&graph, (int (*)(const void *, const void *))path_vertex_match, NULL);
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

    graph_ins_edge(&graph, &m[2], &m[11]);
    graph_ins_edge(&graph, &m[2], &m[12]);

    graph_ins_edge(&graph, &m[4], &m[13]);

    graph_ins_edge(&graph, &m[5], &m[14]);
    graph_ins_edge(&graph, &m[5], &m[15]);
    graph_ins_edge(&graph, &m[5], &m[16]);

    List span;
    PathVertex *vertex = NULL;
    shortest(&graph, m, &span, (int (*)(const void *, const void *))path_vertex_match);
    list_resetIterator(&span);
    while (list_hasNext(&span)) {
        list_moveToNext(&span);
        list_iterator(&span, (void **)(&vertex));
        Student *s = (Student *)vertex->data;
        printf("d : %.0f", vertex->d);
        if (vertex->parent != NULL) {
            Student *sP = (Student *)(vertex->parent->data);
            printf(", parentid:%d, ",  sP->_id);
        }
        studn_print(s);
    }

    return;
}