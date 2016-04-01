//
// Created by wangxn on 2016/3/11.
//

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "str_tool.h"


/**
 * 将str字符串去掉头部和尾部的空格,在字符串中间的空格保留
 * 返回一个去掉空格的字符串
 */
char * trim(char * str){
    int len = strlen(str);                                      //判断字符串的长度
    char * retVal = (char *)malloc((len+1) * sizeof(char));     //分配一个和字符串str相同大小的空间
    memset(retVal,0,(len+1) * sizeof(char));                    //清空这个内存空间的内容
    int i,j,k;
    int flagLeft = 0;                       //左标记
    int flagRight =0;                       //右标记
    for (i = 0, j = 0; i < len; ++i) {      //遍历字符串
        if(0 == isspace(*(str + i))){             //如果指向的字符不是空字符
            (*(retVal + j)) = (*(str + i));       //将字符复制到新分配的内存空间中
            j++;                                  //新内存空间的指针后移
        } else{                            //是空字符
            flagLeft = 0;
            flagRight = 0;
            k = i -1;
            while (k >=0){                           //以当前字符为原点,向左遍历, 判断是否有不是空字符的情况
                if(0 == isspace(*(str + k))){
                    flagLeft = 1;                   //有不是空字符的情况
                    break;
                }
                k--;
            }
            k = i+1;
            while (k < len){                        //以当前字符为原点,向右遍历,判断是否有不是空字符的情况
                if(0 == isspace(*(str + k))){
                    flagRight = 1;                //有不是空字符的情况
                    break;
                }
                k++;
            }
            if (flagLeft && flagRight){               //以当前字符为原点,向左和向右都有不是空字符的情况,表示当前空字符位于字符串中间,保留这个空字符
                (*(retVal + j)) = (*(str + i));
                j++;
            }
        }
    }
    return retVal;
}


/**
 * 用tag分割字符串str,
 * returnSize 是分割之后的获取的字符串数量
 * 返回 分割之后的多个字符串组成的数组
 */
char ** splitString(char * str/*in*/, const char tag/*in*/, int * returnSize/*out*/){
    if (str == NULL){
        return NULL;
    }

    int length = strlen(str);
    char * point;
    point = str;        //一个指向str的指针
    int size = 1;       //分割之后的字符串数量
    int i = 0;          //标识point指针在str中的遍历的偏移量
    while (point){
        if (*point == '\0'){
            break;
        }
        if (tag == *point){                   //str中有标识的tag字符时
            if (i != 0 && i != length - 1){
                size++;                       //分割之后的字符串数量自加一
            }
        }
        i++;
        point++;    //point指针遍历str
    }

    *returnSize = size;   //为返回值赋值

    char ** retVal = (char **)malloc(size * sizeof(char *));    //分配一个二维字符数组的堆内存空间
    i = 0;
    int index = 1;
    *retVal = point = strdup(str);  //分配一个和str大小相同的堆内存空间,同时将str的内容复制到这篇内存中,将首地址返回,
    char ** ctlRetVal = retVal;     //另外分配一个二级指针指向同一片内存空间
    while (point){
        if (*point == '\0'){  //到达结尾处,跳出循环
            break;
        }

        if (tag == *point){  //指针指向分割点
            *point = '\0';             //将分割字符设置为'\0',作为分段标记
            ctlRetVal++;
            *ctlRetVal = point + 1;   //将下一个指针位置传递给  待返回字符串指针数组
        }
        point++;
    }
    return retVal;
}