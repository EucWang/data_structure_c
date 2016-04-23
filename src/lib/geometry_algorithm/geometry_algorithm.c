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
 * @brief get_distance 二维情况下，计算两个点之间的距离
 * @param p1
 * @param p2
 * @return 返回2个点的距离
 */
static int get_distance(Point *p1, Point *p2){
    return sqrt(pow(p1->x - p2->x, 2.0) + pow(p1->y - p2->y, 2.0));
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



/**
 * @brief cvxhull 该函数计算出由P所指定的点集合的凸包。P
 *                  中的每一个元素都必须是Point类型的。
 *                  由于cvxhull函数只适用于2维空间，这里忽略掉Point结构中的z坐标值
 * @param p   点集合，Point是List中元素的类型，
 * @param polygon 得到的凸包的返回的点集合，polygon中的点其实都在p集合中，必须保证在访问polygon时，p集合中的点的内存空间是有效的
 * @return 如果计算出凸包，返回0,否则返回-1
 */
int cvxhull(const List *points, List *polygon) {

    Point *low, *p0, *pc, *pi;
    List * p = (List *)points;

    //首先找到y轴最低的点，
    low = (Point *)(list_head(p)->data);
    list_resetIterator(p);
    while (list_hasNext(p)) {
        list_moveToNext(p);
        list_iterator (p, (void **)(&pi));
        //如果是y轴相同，取x轴的值最低的点
        if (pi->y < low->y) {
            //保存这个点的指针
            low = pi;
        } else {
            if (pi->y == low->y && pi->x < low->x) {
                low = pi;
            }
        }
    }

    //初始化polygon的List集合
    list_init (polygon, NULL);

    //设置po的值是最低的那个点
    p0 = low;
    //设置count为0
    int count = 0;
    int direction = 0;
    double distance1, distance2;
    //开始循环
    do {

        //将p0加入到polygon集合中
        if (list_ins_next (polygon, list_tail(polygon), p0) != 0) {
            list_destroy(polygon);
            return -1;
        }

        //开始遍历p点集合中的每一个元素
        //目的是为了获得pc点，这个点的特点是：从P
        //集合中任意拿出一个点，没有其他点会位于从P0点到pc点的线段的顺时针方向
        //这个pc点就是下一个p0点，就是放入到polygon中的下一个点
        list_resetIterator(p);
        while(list_hasNext(p)) {
            list_moveToNext(p);
            list_iterator (p, (void **)(&pi));

            //如果当前元素和P0相同，跳过本轮循环
            if (pi == p0){
                continue;
            }

            //将count++
            count++;

            //如果count==1,保存当前点为pc，然后跳过本轮循环
            if (count == 1) {
                pc = pi;
                continue;
            }

            //调用计算公式，计算当前点相对于从pc点到p0点的线段的相对方位。
            direction = get_direction (p0, pc, pi);
            //如果当前pi点位于p0到pc线段的顺时针方向，则将pi保存为新的pc点
            if (direction > 0) {
                //>0表示顺时针方向，则将当前的点保存为pc点
                pc = pi;
            }else if(direction == 0) {
                //如果==0,表示在同一线段上，
                //计算当前点pi到p0的距离
                //计算pc点到p0的距离
                distance1 = get_distance (pi, p0);
                distance2 = get_distance (pc, p0);
                //如果pi到p0的距离比pc点到p0的距离远，则将pi保存为pc点
                if (distance1 > distance2) {
                    pc = pi;
                }
            }
        }

        //遍历结束
        //将获得的pc点设置为p0点
        p0 = pc;
    //在p0不是那个最低点时，继续外层循环
    }while(p0 != low);
    return 0;
}

