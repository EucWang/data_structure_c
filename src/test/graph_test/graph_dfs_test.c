//
// Created by wangxn on 2016/4/8.
//

#include "../../lib/graph/graph_dfs.h"
#include "../course/course.h"
#include "../test.h"
#include <stdio.h>
/**
 * 深度优先测试
 *
 *
 *
 */
void graph_dfs_test(){
    Course s[] = {
            *course_get_init(11, "cs100"),
            *course_get_init(15, "cs200"),
            *course_get_init(16, "cs300"),
            *course_get_init(17, "ma100"),
            *course_get_init(18, "ma200"),
            *course_get_init(19, "ma300"),
            *course_get_init(20, "cs150")
    };

    DfsVertex b[] = {
            *dfs_vertex_get_init((void *)(&s[0]), (void *)course_match, (void *)course_destroy),
            *dfs_vertex_get_init((void *)(&s[1]), (void *)course_match, (void *)course_destroy),
            *dfs_vertex_get_init((void *)(&s[2]), (void *)course_match, (void *)course_destroy),
            *dfs_vertex_get_init((void *)(&s[3]), (void *)course_match, (void *)course_destroy),
            *dfs_vertex_get_init((void *)(&s[4]), (void *)course_match, (void *)course_destroy),
            *dfs_vertex_get_init((void *)(&s[5]), (void *)course_match, (void *)course_destroy),
            *dfs_vertex_get_init((void *)(&s[6]), (void *)course_match, (void *)course_destroy)
    };

    Graph graph;
    graph_init(&graph, (void *) dfs_vertex_match, NULL);
    int i;
    for (i = 0; i < 7; ++i) {
        graph_ins_vertex(&graph, &b[i]);
    }
    printf("%s\n", "insert vertex success");

    graph_ins_edge(&graph, &b[0], &b[1]);
    graph_ins_edge(&graph, &b[1], &b[2]);
    graph_ins_edge(&graph, &b[2], &b[5]);
    graph_ins_edge(&graph, &b[3], &b[2]);
    graph_ins_edge(&graph, &b[3], &b[4]);
    graph_ins_edge(&graph, &b[4], &b[5]);

    printf("%s\n", "insert edge success");

    printf("%s\n", "show all data in the graph");
    printf("%s\n", "=========================================");
    List list = (&graph)->adjlists;
    AdjList *adjList;

    list_resetIterator(&list);
    while (list_hasNext(&list)) {
        list_moveToNext(&list);
        list_iterator(&list, (void **) (&adjList));
        Course *course = (Course *)(((DfsVertex *) ((adjList->vertex)))->data);
        course_print(course);

        Set set = adjList->adjacent;
        DfsVertex *b_;
        list_resetIterator(&set);
        while (list_hasNext(&set)) {
            list_moveToNext(&set);
            list_iterator(&set, (void **) (&b_));
            printf("->\t");
            course_print((Course *)(b_->data));
        }
    }
    printf("%s\n", "=========================================");

    List ordered;
    graph_dfs(&graph, &ordered);
    printf("%s\n", "dfs success");

    DfsVertex *bfsVertex;
    list_resetIterator(&ordered);
    while (list_hasNext(&ordered)) {
        list_moveToNext(&ordered);
        list_iterator(&ordered, (void **) (&bfsVertex));
        course_print((Course *) bfsVertex->data);
    }


    printf("%s\n", "============== release data begin ===============");
    graph_destroy(&graph);
//    list_destroy(&list2);
    printf("%s\n", "============== release data end ===============");
}