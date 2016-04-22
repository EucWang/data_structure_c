//
// Created by wangxn on 2016/4/22.
//
/**
 * 集合算法的3个比较简单的算法问题
 *
 * 1. 判断线段是否相交
 *          一个简单算法, 首先判断以两条线段为对角线的矩形是否相交,
 *          如果不相交,则两条线段也不相交.
 *          然后判断这两条线段是否互相跨越,
 *          如果两个检测结果都成立,那么说明这两条线段是相交的
 * 2. 凸包
 *          凸包是包含一个点集的最小凸多边形.
 *          如果一个多边形内任意两点之间的连线完全包含在该多边形内,则称这个多边形是凸多边形
 * 3. 球面弧长
 *          要计算出相同平面上从一个点到另一个点之间的弧线长度,这个平面由球心画的虚线到球面上弧线两个端点的虚线确定
 */
#ifndef DATA_STRUCTURE_C_GEOMETRY_ALGORITHM_H
#define DATA_STRUCTURE_C_GEOMETRY_ALGORITHM_H

#include "../list/list.h"

#ifdef  PI
#define PI 3.14159
#endif

/**
 * 取x,y中的最小值或者最大值
 */
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

/**
 * degress 角度 一圈最大360
 * radian 弧度  一圈最大2 * PI
 * 角度和弧度转换的2个函数
 */
#define DEG2RAD(deg)  (((deg) * 2.0 * PI) / 360.0)
#define RAD2DEG(rad) (((rad)*260.0)/(2.0 * PI))

/**
 * define a structure for points in rectilinear coordinates
 * 直角坐标系的点(三维坐标系)
 *
 */
typedef struct Point_ {
    double x, y, z;
}Point;

/**
 * define a structure for points in spherical coordinates
 * 球面坐标系的点
 * 经纬网是基于球面坐标系的.
 * 球面坐标系是以地球面上任一点为极点，用垂直圈和等高圈组成的球面坐标网。
 * 垂直圈是通过极点的大圆圈，等高圈是垂直于垂直圈的一组圆，其中有一个最大的为大圆圈，其余都是小圆圈。垂直圈即相当于地理坐标系的经线圈，等高圈即相当于地理坐标系的纬线圈。
 * 它也要求三个数值，其中两个是角度，第三个是距离。
 * 想象一条来自原点的射线(线段)，它的两个角度可以决定该射线的方向。
 */
typedef struct  SPoint_{
    double rho, theta, phi;
}SPoint;


/******************************************************************************************/
/**
 * Point结构体的内存分配以及初始化
 */
Point * point_get_init(double x, double y, double z);

/**
 * Point结构体的销毁
 */
void point_destroy(Point *p);
/******************************************************************************************/
/**
 * SPoint结构体的内存分配以及初始化
 */
SPoint *spoint_get_init(double rho, double theta, double phi);

/**
 * SPoint结构体的销毁
 */
void spoint_destroy(SPoint *p);

/******************************************************************************************/
/**
 * 测试线段是否相交
 *
 * 斜截式是直线的一种表示法,可以表示为 y = m * x + b
 * 对于一个有端点P1 = (x1, y1) 和端点 P2 = (x2, y2)的线段来说,斜率m, 以及与y轴的截距b的计算公式如下
 *  m  = (y2 - y1) / (x2 - x1)
 *  b = y1 - m * x1
 *  通过m和b的值,线段就可以通过端点P1和p2表示直线的斜截式
 *
 *  第一种判断两条线段是否相交的方法:
 *      确定两条直线的交点Pi = (xi, yi),
 *      在判断该交点Pi是否在两条线段上.在,则说明相交,
 *      首先用斜截式表示两个线段
 *      y1 = m1 * x1 + b1;
 *      y2 = m2 * x2 + b2;
 *      通过如下公式计算两个线段的交点:
 *      xi = (b2 - b1) / (m2 - m1);
 *      yi = m1 * x1 + b1
 *      这样就可以计算出xi,yi的值,需要避免当两条线的斜率相同时,则会出现除0错误
 *      这种方法也存在精度问题
 *  第二种方法:
 *      1. 执行一次快速剔除检测(quick rejection test)
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
 *
 */
int lint(Point *p1, Point *p2, Point *p3, Point *p4);

int cvxhull(const List *p, List *polygon);

void arclen(SPoint p1, SPoint p2, double *length);

#endif //DATA_STRUCTURE_C_GEOMETRY_ALGORITHM_H
