//
// Created by wangxn on 2016/4/22.
//

/**
 * 线段相交测试
*/

#include "../../lib/geometry_algorithm/geometry_algorithm.h"
#include "../test.h"
#include <stdio.h>

static  void test1();
static  void test2();

void line_intersect_test() {
//    test1();
    test2();
}

void test1() {
    Point *p1 = point_get_init(-2.0, -4.0, 0);
    Point *p2 = point_get_init(4.0, 2.0, 0);

    Point *p3 = point_get_init(-1.0, 3.0, 0);
    Point *p4 = point_get_init(2.0, -1.0, 0);

    int retVal = lint(p1, p2, p3, p4);

    printf("%s\n", ((retVal == 1) ? "two lines intersect" : "two lines not intersect"));

    point_destroy(p1);
    point_destroy(p2);
    point_destroy(p3);
    point_destroy(p4);


}
void test2() {
    Point *p1 = point_get_init(-4.0, -2.0, 0);
    Point *p2 = point_get_init(1.0, 2.0, 0);

    Point *p3 = point_get_init(2.4, -2.0, 0);
    Point *p4 = point_get_init(4.0, 2.5, 0);

    int retVal = lint(p1, p2, p3, p4);

    printf("%s\n", ((retVal == 1) ? "two lines intersect" : "two lines not intersect"));

    point_destroy(p1);
    point_destroy(p2);
    point_destroy(p3);
    point_destroy(p4);
}