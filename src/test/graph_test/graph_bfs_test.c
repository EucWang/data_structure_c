//
// Created by wangxn on 2016/4/8.
//

#include <stdio.h>
#include "../../lib/graph/graph.h"
#include "../../lib/graph/graph_bfs.h"
#include "../student/student.h"
#include "../test.h"

/**
 * 广度优先测试
 */
void graph_bfs_test() {
    Student s[] = {
            *studn_get_init(14, "liucuihua", 0, 22, 11),
            *studn_get_init(15, "liucuihua", 0, 22, 11),
            *studn_get_init(16, "liucuihua", 0, 22, 11),
            *studn_get_init(17, "liucuihua", 0, 22, 11),
            *studn_get_init(18, "liucuihua", 0, 22, 11),
            *studn_get_init(19, "liucuihua", 0, 22, 11),
            *studn_get_init(20, "liucuihua", 0, 22, 11),
            *studn_get_init(21, "liucuihua", 0, 22, 11)
    };

    BfsVertex b[] = {
            *bfs_vertex_get_init((void *)(&s[0]), (void *)studn_match, (void *)studn_destroy),
            *bfs_vertex_get_init((void *)(&s[1]), (void *)studn_match, (void *)studn_destroy),
            *bfs_vertex_get_init((void *)(&s[2]), (void *)studn_match, (void *)studn_destroy),
            *bfs_vertex_get_init((void *)(&s[3]), (void *)studn_match, (void *)studn_destroy),
            *bfs_vertex_get_init((void *)(&s[4]), (void *)studn_match, (void *)studn_destroy),
            *bfs_vertex_get_init((void *)(&s[5]), (void *)studn_match, (void *)studn_destroy),
            *bfs_vertex_get_init((void *)(&s[6]), (void *)studn_match, (void *)studn_destroy),
            *bfs_vertex_get_init((void *)(&s[7]), (void *)studn_match, (void *)studn_destroy)
    };

    Graph graph;
    graph_init(&graph, (void *) bfs_vertex_match, NULL);
    int i;
    for (i = 0; i < 8; ++i) {
        graph_ins_vertex(&graph, &b[i]);
    }
    printf("%s\n", "insert vertex success");

    graph_ins_edge(&graph, &b[0], &b[1]);
    graph_ins_edge(&graph, &b[0], &b[2]);

    graph_ins_edge(&graph, &b[1], &b[0]);
    graph_ins_edge(&graph, &b[1], &b[2]);
    graph_ins_edge(&graph, &b[1], &b[3]);

    graph_ins_edge(&graph, &b[2], &b[0]);
    graph_ins_edge(&graph, &b[2], &b[1]);
    graph_ins_edge(&graph, &b[2], &b[3]);

    graph_ins_edge(&graph, &b[3], &b[1]);
    graph_ins_edge(&graph, &b[3], &b[4]);

    graph_ins_edge(&graph, &b[4], &b[2]);
    graph_ins_edge(&graph, &b[4], &b[3]);
    graph_ins_edge(&graph, &b[4], &b[5]);

    graph_ins_edge(&graph, &b[5], &b[4]);

    printf("%s\n", "insert edge success");

    printf("%s\n", "show all data in the graph");
    printf("%s\n", "=========================================");
    List list = (&graph)->adjlists;
    AdjList *adjList;

    list_resetIterator(&list);
    while (list_hasNext(&list)) {
        list_moveToNext(&list);
        list_iterator(&list, (void **) (&adjList));
        Student *student = (Student *)(((BfsVertex *) ((adjList->vertex)))->data);
        studn_print(student);

        Set set = adjList->adjacent;
        BfsVertex *b_;
        list_resetIterator(&set);
        while (list_hasNext(&set)) {
            list_moveToNext(&set);
            list_iterator(&set, (void **) (&b_));
            printf("->\t");
            Student *student = (Student *)(b_->data);
            studn_print(student);
        }
    }
    printf("%s\n", "=========================================");

    List list2;
    list_init(&list2, NULL);
    graph_bfs(&graph, b, &list2);
    printf("%s\n", "bfs success");

    BfsVertex *bfsVertex;
    list_resetIterator(&list2);
    while (list_hasNext(&list2)) {
        list_moveToNext(&list2);
        list_iterator(&list2, (void **) (&bfsVertex));
        studn_print((Student *) bfsVertex->data);
    }


    printf("%s\n", "============== release data begin ===============");
    graph_destroy(&graph);
    list_destroy(&list2);
    printf("%s\n", "============== release data end ===============");
}