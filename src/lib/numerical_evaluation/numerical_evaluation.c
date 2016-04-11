//
// Created by wangxn on 2016/4/11.
//

#include <stdlib.h>
#include <string.h>
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
 *
 */
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
    if ((talbe = malloc(sizeof(double) * n)) == NULL) {
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
    for (k = 1; l < n; ++k) {
        for (i = 0; i < n - k; ++i) {
            j = i + k;
            table[i] = (table[i + 1] - table[i]) / (x[j] - x[i]);
        }
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
