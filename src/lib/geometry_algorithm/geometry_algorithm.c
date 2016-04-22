//
// Created by wangxn on 2016/4/22.
//
#include "geometry_algorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * Point结构体的内存分配以及初始化
 */
Point * point_get_init(double x, double y, double z) {
    Point *retVal = (Point *) malloc(sizeof(Point));
    if (retVal == NULL) {
        return NULL;
    }

    retVal->x = x;
    retVal->y = y;
    retVal->z = z;
    return retVal;

}

/**
 * Point结构体的销毁
 */
void point_destroy(Point *p) {
    if (p == NULL) {
        return;
    }
    free(p);
}


/**
 * SPoint结构体的内存分配以及初始化
 */
SPoint *spoint_get_init(double rho, double theta, double phi) {
    SPoint *retVal = (SPoint *) malloc(sizeof(SPoint));
    if (retVal == NULL) {
        return NULL;
    }

    retVal->rho = rho;
    retVal->theta = theta;
    retVal->phi = phi;
    return retVal;
}

/**
 * SPoint结构体的销毁
 */
void spoint_destroy(SPoint *p) {
    if (p == NULL) {
        return;
    }
    free(p);
}


/**
 * 获得目标点相对于线段(由target_p1,和target_p2组成的)的方位,
 * 如果返回1 ,表示test_p3相对于从p1到p2线段的顺时针方向
 * 如果返回-1,表示在逆时针方向
 * 如果返回0,表示p3在p1的延长线上,此时称点p3与p1 共线
 */
static int get_direction(Point *target_p1, Point *target_p2, Point *test_p3) {
    int retVal;

    int test = (test_p3->x - target_p1->x)*(target_p2->y - target_p1->y) - (test_p3->y - target_p1->y)*(target_p2->x - target_p1->x);

    if (test < 0) {
        retVal = -1;
    } else if (test > 0) {
        retVal = 1;
    } else {
        retVal = 0;
    }
    return retVal;
}

/**
 *    1. 执行一次快速剔除检测(quick rejection test)
 *              针对每条线段建立一个边框,这个边界框是一个包围该线段的最小矩形,
 *              对于端点P1 = (x1,y1)和P2(x2,y2)所组成的线段,
 *              其边框左下角顶点的坐标为 (min(x1,x2), min(y1,y2)),  右上角的坐标(max(x1,x2), max(y1,y2))
 *              P3, p4组成的线段的最小矩形的生成同上
 *              执行如下判断,都成功,则两条线段的边框相交
 *              max(x1, x2) >= min(x3,x4)
 *              max(x3, x4) >= min(x1,x2)
 *              max(y1, y2) >= min(y3,y4)
 *              max(y3, y4) >= min(y1,y2)
 *      2. 上一步骤成功,接着执行一次跨越检测(straddle test)
 *              需要比较P3相对与P2的方位,以及P4相对于P2的方位
 *              要判断P3相对与从P2到P2的方位,只需要看如下公式:
 *              z1 = (x3 - x1)(y2 - y1) - (y3 - y1)(x2 - x1)
 *              如果z1为正,P3相对与P2就是顺时针的;为负,则是逆时针的;等于0,则P3位于P1的延长线上,此时称点P3与P1共线
 *              判断P4相对于从P2到P1的方位,如下公式
 *              z2 = (x4 - x1)(y2 - y1) - (y4 - y1)(x2 - x1)
 *              如果z1和z2的符号不同,或者其中一个等于0,那么这两条线段是互相跨越的.
 *              由于前面已经知道边框是相交的,那么这两条线段也是相交的
 *      3. 两步骤都成功,则两条线段才会相交
 *
 *  P1和P2指定一条线段,
 *  P3和P4指定一条线段
 *  这是只处理二维空间中标识的点,所以Point.z设置为0
 *  这个函数只适用于二维空间
 *
 *  返回0 ,表示不是
 *  返回1, 表示是相交的两个线段
 */
int lint(Point *p1, Point *p2, Point *p3, Point *p4) {
    int s1, s2, s3, s4;

    int flag = 0;
    //快速剔除检测
    flag += (MAX(p1->x, p2->x) >= MIN(p3->x, p4->x) ? 1 : 0);
    flag += (MAX(p3->x, p4->x) >= MIN(p1->x, p2->x) ? 1 : 0);
    flag += (MAX(p1->y, p2->y) >= MIN(p3->y, p4->y) ? 1 : 0);
    flag += (MAX(p3->y, p4->y) >= MIN(p1->y, p2->y) ? 1 : 0);
    if (flag < 4) {
        return 0;
    }

    //跨境检测

    //p3,p4两点相对于从p1到p2的线段的方位
    s1 = get_direction(p1, p2, p3);
    s2 = get_direction(p1, p2, p4);

    //p1,p2两点相对于从p3到p4的线段的方位
    s3 = get_direction(p3, p4, p1);
    s4 = get_direction(p3, p4, p2);

    if ((s1 * s2 <= 0) && (s3 * s4 <= 0)) {
        return 1;
    }

    return 0;
}
