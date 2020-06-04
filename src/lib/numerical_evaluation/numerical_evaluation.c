//
// Created by wangxn on 2016/4/11.
//

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "numerical_evaluation.h"

/**
 * 多项式插值的接口定义
 * 如果差值操作成功,返回0,否则返回-1
 *
 * 求数学函数在某些特定点上的值
 * 由调用者在参数x处指定函数值已知的点集.
 * 每个已知点所对应的函数值都在fx中指定.
 * 对应值待求的点由参数z来指定,
 * 而z所对应的函数值将在pz中返回.
 * x和fx中的元素个数由参数n来表示.
 * z中待求点的个数(以及pz中的返回值个数)由参数m来表示.
 * 由调用者负责管理x,fx,z以及pz所关联的存储空间
 *
 * 多项式插值法主要基于对一系列期望点的插值多项式的确定.
 * 要得到这个多项式,首先必须通过计算差商来确定该多项式的系数
 *
 * 差商表中每一行的每一项都仅仅依赖于其前一行的计算结果.因此并不需要一次性保存所有的表项.
 * 所以,只为最占用空间的行分配存储空间即可,该行将有n个条目.
 * 接下来,用fx中的值来初始化差商表的第一行
 */
//差商的计算方法:
//      f[x0] = f(x0); //f(x)和x的值必须已知
//      f[x0,x1] = (f[x1] - f[x0]) / (x1 - x0)
//      f[x1, x2] = (f[x2] - f[x1]) / (x2 - x1)
//      ...
//      f[x0,x1,x2] = (f[x1,x2] - f[x0,x1]) / (x2 - x0)
//      f[x1,x2,x3] = (f[x2,x3] - f[x1,x2]) / (x3 - x1)
//      ...
//      f[x0,x1,x2,x3] = (f[x1,x2,x3] - f[x0,x1,x2]) / (x3 - x0)

//差值公式:
//      pn(z) = f[x0] +
//              f[x0,x1]*(z - x0) +
//              f[x0,x1,x2]*(z-x0)*(z-x1) +
//              ... +
//              f[x0,x1,,,xn]*(z-x0)*(z-x1)...*(z-x(n-1))
//
//计算出差商,x0~xn,f(0)~f(n) 的值已知,则可以计算出任意z的的pn(z)值,这个值就是f(z)的近似值
//所以,通过pn(z)可以计算出函数f(x)在x=z处的近似值
int interpol(const double *x/*int*/,
             const double *fx/*in*/,
             int n/*in*/,
             double *z/*in*/,
             double *pz/*out*/,
             int m/*in*/) {

    double term, *table, *coeff;
    int i, j, k;

    //allocate storage for the divided-difference table and coefficients
    //为差商表分配内存空间
    if ((table = malloc(sizeof(double) * n)) == NULL) {
        return -1;
    }


    if ((coeff = malloc(sizeof(double) * n)) == NULL) {
        free(table);
        return -1;
    }

    //initialize the coefficients
    memcpy(table, fx, sizeof(double) * n);

    //determine the coefficients of the interpolating polynomial
    coeff[0] = table[0];

    //k表示差商的参数的个数, k为1:则差商为f[x0];  k为2:则差商为f[x0,x1]; k为3:则差商为f[x0,x1,x2]
    for (k = 1; k < n; ++k) {
        for (i = 0; i < n - k; ++i) {
            j = i + k;
            table[i] = (table[i + 1] - table[i]) / (x[j] - x[i]);
        }
        //取差商表每一层的第一个元素的数值保留下来,作为差值公式的前缀参数
        coeff[k] = table[0];
    }
    free(table);

    for (k = 0; k < m; ++k) {
        pz[k] = coeff[0];
        for (j = 1; j < n; ++j) {
            term = coeff[j];
            for (i = 0; i < j; ++i) {
                term = term * (z[k] - x[i]);
            }
            pz[k] = pz[k] + term;
        }
    }
    free(coeff);
    return 0;
}



/**
 * 最小二乘估计
 * 采用最小二乘估计法来计算出函数
 ***    y(x) = b1 * x + b0    ***
 * 中的系数 b1 和 b0
 * 这样y(x)将是有参数x和y所指定的点集的最佳拟合线.
 *
 * 可能最小二乘估计法最重要的应用就是对两个变量之间的线性关系进行推导.
 * 这在两个变量具有统计关系时(不精确的关系)显得尤其有意义.
 *
 * 在二维坐标系中表示就是一条穿过很多点的最密集区域的直线
 *
 * * 求b1和b0的联立方程组:
 * b1 = (n*(x0*y0 + x1*y1 +...+ xi*yi) - (x1 + x2 +...+ xi)*(y0 + y1 +...+ yi)) / (n*(x0*x0 + x1*x1 +...+ xi*xi) - (x0 + x1 +...+ xi)(x0 + x1 +...+ xi))
 * b0 = ((y0 + y1 +...+ yi) - b1*(x0 + x1 +...+ xi)) / n
 *
 * @param x :  点集的横坐标由参数x所指定,
 * @param y :  纵坐标由y所指定.
 * @param n :  n代表点的个数
 * @param b1 : 返回值
 * @param b2 : 返回值
 *
 */
void lsqe(const double *x/*in*/,
          const double *y/*in*/,
          int n/*in*/,
          double *b1/*out*/,
          double *b0/*out*/){

    double sumx, sumy, sumx2, sumxy;
    int i;

    sumx = 0.0;
    sumy = 0.0;
    sumx2 = 0.0;
    sumxy = 0.0;

    for (i = 0; i < n; ++i) {
        sumx = sumx + x[i];
        sumy = sumy + y[i];
        sumx2 = sumx2 + pow(x[i], 2.0);
        sumxy = sumxy + (x[i] * y[i]);
    }

    *b1 = (sumxy - ((sumx * sumy)/(double)n)) / (sumx2 - (pow(sumx, 2.0)/(double)n));
    *b0 = (sumy - ((*b1)*sumx))/(double)n;
    return;
}



/**
 *** 方程求解 ***
 *
 *  对形如f(x)=0的方程式进行求解
 *
 *  科学计算中最基本的一类问题就是对形如f(x)=0的方程式进行求解.通常称为求方程式的根,或找出f(x)的零点,这里只处理实根,不考虑虚根
 *  这里侧重于求解当f(x)是一个多项式时的实根.
 *
 *  牛顿迭代法是近似解法中最好的方法之一.
 *  牛顿迭代法通过一系列迭代操作使得到的结果不断逼近方程的实根.
 *  首先选择一个初始值 x=x0, 使得该初始值接近实根的值
 *  迭代计算公式, 直到x(i+1)达到一个满意的近似结果为止
 *      x(i+1) = xi - f(xi)/f`(xi)
 *  f(x)是要求解的多项式方程,而f`(x)是f(x)的导数
 *
 ***  多项式求导  ***
 *  函数求导是微积分的基础,
 *  要计算出多项式的求导结果,只需要对多项式的每一项套用如下两个公式:
 *     (d/dx)k = 0;
 *     (d/dx)kx(r次方) = krx((r-1)次方)
 *  k为常数, r是有理数, x未知数. (d/dx)表示求导,这里的x是多项式中的变量.
 *  对于多项式中的每一常数项,套用第一个公式,否则,就用第二个公式.
 *
 ***  高阶求导 ***
 *  f(x)的2阶求导可以记为f``(x),它是f`(x)的求导结果
 *
 *** 斜率(1阶)  凹凸性(2阶) ***
 * f(x)在点x=x0处的1阶导数表示函数f(x)在点x0处的斜率,一阶导数决定函数f(x)是递增还是递减
 * 求导结果的大小表示f(x)递增或者递减的速率
 * 负表示递减,正表示递增
 *
 * f(x)在点x=x0处的二阶导数表示函数在该点处的凹凸性,二阶导数值表明函数图像的凹凸程度
 * 凹凸性发生改变的位置,比如曲线上凸和下凹部的分界点,也成为拐点,拐点必然是2阶导函数与x轴的交点.
 * 负表示凸的,正表示凹的
 *
 ***  为牛顿迭代法确定迭代初始值  ***
 *  为x0 确定一个区间[a,b],满足条件:
 *      f(a),f(b)的符号不同,
 *      f`(x)的符号不会改变
 *      f``(x)的符号不会改变
 *  满足这些条件,那么在这个区间内有且只有一个根存在
 *
 *******************************************************************
 * 如果找到了根,返回0,否则返回-1
 *
 * 采用牛顿迭代法根据给定的初始值来计算方程f的根.
 *
 * @param f : 函数f
 * @param g : 函数f的导数g
 * @param x : 初始值由x[0]指定.
 * @param n : 迭代的最大次数
 * @param delta: 表示逐次逼近的差值,用该值来确定何时应该结束迭代
 *
 * 函数返回后,迭代过程中计算出的近似值都保存在数组x中,此时n代表数组x中的元素个数.
 * 由调用者负责管理同x相关联的存储空间
 *
 * use Newton's method to find a root of f.
 */
int root(double (*f)(double x)/*in*/,
         double (*g)(double x)/*in*/,
         double *x/*in,out*/,
         int *n/*in*/,
         double delta/*in*/) {

    int satisfied;
    int i;
    i = 0;
    satisfied = 0;

    while (!satisfied && i + 1 < *n) {
        x[i + 1] = x[i] - ((f(x[i]))/(g(x[i])));

        if (fabs(x[i + 1] - x[i]) < delta) {
            satisfied = 1;
        }

        i++;
    }

    if (i == 0) {
        *n = 1;
    }

    if (satisfied) {
        return 0;
    } else {
        return -1;
    }

}