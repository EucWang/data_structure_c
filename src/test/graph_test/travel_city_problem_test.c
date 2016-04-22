//
// Created by wangxn on 2016/4/22.
//

#include "../../lib/graph/graph_algorithm.h"
#include "../student/student.h"
#include "../test.h"
#include <stdio.h>

void travel_city_problem_test() {
    List tour;
    Student s[] = {
            *studn_get_init(1, "a", 0, 22, 11),
            *studn_get_init(2, "b", 0, 22, 11),
            *studn_get_init(3, "c", 0, 22, 11),
            *studn_get_init(4, "d", 0, 22, 11),
            *studn_get_init(5, "e", 0, 22, 11),
            *studn_get_init(6, "f", 0, 22, 11),
            *studn_get_init(7, "g", 0, 22, 11),
    };

    TspVertex *a = travel_city_problem_vertex_get_init(&s[0], 2.0, 1.0, (int (*)(const void *, const void *)) studn_match, NULL);
    TspVertex *b = travel_city_problem_vertex_get_init(&s[1], 5.0, 2.0, (int (*)(const void *, const void *)) studn_match, NULL);
    TspVertex *c = travel_city_problem_vertex_get_init(&s[2], 1.0, 3.0, (int (*)(const void *, const void *)) studn_match, NULL);
    TspVertex *d = travel_city_problem_vertex_get_init(&s[3], 4.0, 3.0, (int (*)(const void *, const void *)) studn_match, NULL);
    TspVertex *e = travel_city_problem_vertex_get_init(&s[4], 6.0, 3.0, (int (*)(const void *, const void *)) studn_match, NULL);
    TspVertex *f = travel_city_problem_vertex_get_init(&s[5], 2.0, 4.0, (int (*)(const void *, const void *)) studn_match, NULL);
    TspVertex *g = travel_city_problem_vertex_get_init(&s[6], 5.0, 5.0, (int (*)(const void *, const void *)) studn_match, NULL);

    list_init(&tour, NULL);
    list_ins_next(&tour, list_tail(&tour), a);
    list_ins_next(&tour, list_tail(&tour), b);
    list_ins_next(&tour, list_tail(&tour), c);
    list_ins_next(&tour, list_tail(&tour), d);
    list_ins_next(&tour, list_tail(&tour), e);
    list_ins_next(&tour, list_tail(&tour), f);
    list_ins_next(&tour, list_tail(&tour), g);

    List retVal;
    list_init(&retVal, NULL);
    tsp(&tour, a, &retVal, (int (*)(const void *, const void *)) studn_match);

    list_resetIterator(&retVal);
    TspVertex *tmp;
    Student *student;
    printf("%s\n", "the travel point : ");
    while (list_hasNext(&retVal)) {
        list_moveToNext(&retVal);
        list_iterator(&retVal, (void **) &tmp);
        student = (Student *) tmp->data;
        printf("%s,", student->name);
    }
}

