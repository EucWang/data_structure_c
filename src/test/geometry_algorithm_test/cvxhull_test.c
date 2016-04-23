//
// Created by wangxn on 2016/4/24.
//

/**
 * 凸包测试
*/

#include "../../lib/geometry_algorithm/geometry_algorithm.h"
#include "../test.h"
#include <stdio.h>


void cvxhull_test(){

    Point *p1 = point_get_init (5.0, 1.0, 0.0);
    Point *p2 = point_get_init (0.0, -2.0, 0.0);
    Point *p3 = point_get_init (-2.0, -4.0, 0.0);
    Point *p4 = point_get_init (-2.0, -1.0, 0.0);
    Point *p5 = point_get_init (-3.0, 2.0, 0.0);
    Point *p6 = point_get_init (-3.0, 3.0, 0.0);
    Point *p7 = point_get_init (-4.0, -2.0, 0.0);
    Point *p8 = point_get_init (1.0, 2.0, 0.0);

    List points;
    list_init (&points, NULL);
    list_ins_next (&points, list_tail(&points), (void *)p1);
    list_ins_next (&points, list_tail(&points), (void *)p2);
    list_ins_next (&points, list_tail(&points), (void *)p3);
    list_ins_next (&points, list_tail(&points), (void *)p4);
    list_ins_next (&points, list_tail(&points), (void *)p5);
    list_ins_next (&points, list_tail(&points), (void *)p6);
    list_ins_next (&points, list_tail(&points), (void *)p7);
    list_ins_next (&points, list_tail(&points), (void *)p8);

    List polygon;
    cvxhull (&points, &polygon);
    printf("polygon size :%d\n", list_size(&polygon));
    list_resetIterator(&polygon);
    Point *tmp;
    while(list_hasNext(&polygon)) {
        list_moveToNext(&polygon);
        list_iterator (&polygon, (void **)(&tmp));
        printf("(%.2f, %.2f)\n",tmp->x, tmp->y);
    }
}
