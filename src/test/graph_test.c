//
// Created by wangxn on 2016/4/7.
//

#include <stdio.h>
#include "../lib/graph/graph.h"
#include "./student/student.h"
#include "test.h"

void graph_test() {
    Graph graph;

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

    graph_init(&graph, (void *) studn_match, NULL);
    printf("%s\n", "graph init success");
    int i;
    for (i = 0; i < 8; ++i) {
        graph_ins_vertex(&graph, s + i);
    }
    printf("%s%d\n", "the graph vertex is :", graph_vcount(&graph));

    graph_ins_edge(&graph, s, s + 1);
    graph_ins_edge(&graph, s, s + 2);
    graph_ins_edge(&graph, s, s + 3);
    graph_ins_edge(&graph, s, s + 4);
    graph_ins_edge(&graph, s, s + 5);
    graph_ins_edge(&graph, s, s + 6);

    printf("%s%d\n", "the graph edge is :", graph_ecount(&graph));


    Student *tmp;
    tmp = &(s[0]);
    if(graph_rem_vertex(&graph, (void **)(&tmp)) == 0) {
        printf("%s\n", "remove vertex the first one , success");
    }else {
        printf("%s\n", "remove vertex the first one , fail");
    }

    tmp = &(s[7]);
    if(graph_rem_vertex(&graph, (void **)(&tmp)) == 0) {
        printf("%s\n", "remove vertex the last one , success");
    }else {
        printf("%s\n", "remove vertex the last one , fail");
    }
    printf("%s\n", "after remove vertex, the size");
    printf("%s%d\n", "the graph vertex is :", graph_vcount(&graph));

    printf("%s\n", "show all data in the graph");
    printf("%s\n", "=========================================");
    List list = (&graph)->adjlists;
    AdjList *adjList;
    list_resetIterator(&list);
    while (list_hasNext(&list)) {
        list_moveToNext(&list);
        list_iterator(&list, (void **) (&adjList));
        studn_print((Student *) ((adjList->vertex)));

        Set set = adjList->adjacent;
        Student *student_;
        list_resetIterator(&set);
        while (list_hasNext(&set)) {
            list_moveToNext(&set);
            list_iterator(&set, (void **) (&student_));
            printf("->\t");
            studn_print(student_);
        }
    }
    printf("%s\n", "=========================================");


    Student *pStudent = studn_get_init(14, "liucuihua", 0, 22, 11);
    Student *pStudent_ = studn_get_init(20, "liucuihua", 0, 22, 11);
    void **p;
    p = (void **)&pStudent_;
    if(graph_rem_edge(&graph, pStudent, p) == 0) {
        printf("%s\n", "remove edge the last one , success");
    } else {
        printf("%s\n", "remove edge the last one , fail");
    }
    printf("%s\n", "after remove edge, the size");
    printf("%s%d\n", "the graph edge is :", graph_ecount(&graph));


    AdjList *ss;
    if(graph_adjlist(&graph, s, &ss) == 0) {
        printf("%s\n", "get graph the first ele 's adjacency set");
        printf("%s\n", "=========================================");
        Student *student;
        list_resetIterator(&(ss->adjacent));
        while (list_hasNext(&(ss->adjacent))) {
            list_moveToNext(&(ss->adjacent));
            list_iterator(&(ss->adjacent), (void **)(&student));
            studn_print(student);
        }
        printf("%s\n", "=========================================");
    }

    printf("%s\n", "============== release data begin ===============");
    graph_destroy(&graph);
    printf("%s\n", "============== release data end ===============");
}