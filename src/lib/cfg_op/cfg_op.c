//
// Created by wangxn on 2016/3/11.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "../str_tool/str_tool.h"

char * trim(char * str);

int getCfgItem(char * pFileName/*in*/, char * pKey/*in*/, char * pValue/*out*/, int * pValueLen/*out*/);
int writeCfgItem(char * pFileName/*in*/, char * pItemName/*in*/, char * pItemValue/*in*/, int itemValueLen/*in*/);
int delCfgItem(char * pFileName/*in*/, char * pItemName/*in*/);
bool isFileOverSize(FILE *pf, int size);

#define LineMaxLen 2048
#define KeyMaxLen 64

/**
 * 实现流程:
 *  打开文件
 *  按照行的方式 循环读取文件内容
 *  解析每一行,若匹配key关键字, 再进行value值的提取
 *  提取value值需要去掉前后空格, 一级指针的典型应用
 */
int getCfgItem(char * pFileName/*in*/, char * pKey/*in*/, char * pValue/*out*/, int * pValueLen/*out*/){
    int rv = 0;

    FILE * fp = NULL;
    char lineBuf[LineMaxLen] = {0};
    char * pTmp = NULL, * pBegin = NULL, * pEnd = NULL;

    if (pFileName == NULL || pKey == NULL || pValue == NULL || pValueLen == NULL){
        rv = -1;
        printf("getCfgItem() error, param err\n");
        goto End;
    }

    fp = fopen(pFileName, "r");

    if (fp == NULL){
        rv = -2;
        printf("getCfgItem() error,fopen() error.\n");
        goto End;
    }

    //按行读取
    while(!feof(fp)){
        memset(lineBuf, 0 , sizeof(lineBuf));  //清空缓存中的内容
        pTmp = fgets(lineBuf, LineMaxLen, fp);  //一行一行的读取

        if (pTmp == NULL){
            break;
        }

        //返回字符在字符数组中第一次出现的地址,没找到返回的0
        pTmp = strchr(lineBuf, '=');
        if (pTmp == NULL){
            continue;
        }

        //在第一个形参指定的字符数组中寻找第二个形参指定的字符数组出现的地址返回
        char * hasKey = strstr(lineBuf, pKey);
        if (hasKey == NULL || (pTmp - hasKey) < 0){
            continue;
        }

        pTmp = pTmp + 1; //获得value 对应的字符开始的地址

        char * pValueTmp = trim(pTmp);
        *pValueLen = strlen(pValueTmp);
        strcpy(pValue, pValueTmp);
        free(pValueTmp);

//        while(1){              //获取value的起点
////            if (*pTmp == ' '){
//            if (0 != isspace(*pTmp)){
//                pTmp ++;
//            } else{
//                pBegin = pTmp;
//                if (*pBegin == '\n'){
//                    printf("config item %s do not have matched value.\n", pKey);
//                    goto End;
//                }
//                break;
//            }
//        }
//
//        //获取value的结束点
//        while(1){
//            if (*pTmp == ' ' || *pTmp == '\n') {
//                break;
//            }else{
//                pTmp ++;
//            }
//        }
//        pEnd = pTmp;
//
//        //赋值
//        *pValueLen = pEnd - pBegin;
//        memcpy(pValue, pBegin, pEnd - pBegin);
        break;
    }

    End:
        if (fp != NULL){
            fclose(fp);
        }
    return  rv;
}

/**
 *  删除某一个由pItemName指定的item项
 */
int delCfgItem(char * pFileName/*in*/, char * pItemName/*in*/){
    int rv = 0;
    int iTag = 0;
    long length = 0L;

    FILE * fp = NULL;

    char *pTmp = NULL, *pBegin = NULL, *pEnd = NULL;

    char filebuf[1024 * 16] = {0};
    char lineBuf[LineMaxLen];

    if (pFileName == NULL || pItemName == NULL){
        rv = -1;
        printf("delCfgItem() error. param error.\n");
        goto End;
    }

    fp = fopen(pFileName, "r");  //可读, 并且可以在文件尾部追加内容
    if (fp == NULL){
        rv = -3;
        printf("delCfgItem() error.  create file or open file err.\n");
        goto End;
    }

    if(isFileOverSize(fp, 1024*16)){
        rv = -4;
        goto End;
    }

    //按行读取
    while (!feof(fp)){
        memset(lineBuf, 0 , sizeof(lineBuf));  //清空buf
        pTmp = fgets(lineBuf, LineMaxLen, fp);  //读一行
        if (pTmp == NULL){
            break;
        }

        pTmp = strstr(lineBuf, pItemName);  //key关键字是否在本行
        if (pTmp == NULL){             //不在
            strcat(filebuf, lineBuf);
            continue;
        }else{                         //在
            iTag = 1;            //表示存在key
        }
    }

    if (0 == iTag){  //不存在key
        rv = -2;
        printf("delCfgItem() error.  no item in file.\n");
        goto End;
    }else{           //存在
        if (fp != NULL){
            fclose(fp);
            fp = NULL;  //避免野指针
        }

        fp = fopen(pFileName, "w+");   //重新打开文件

        if (fp == NULL){
            rv = -4;
            printf("fopen() error.\n");
            goto End;
        }

        fputs(filebuf, fp);  //将缓存的文件的新的内容写入到文件中
    }

    End:
    if(fp != NULL){
        fclose(fp);
    }
    return rv;
}

/**
 * 实现流程:
 *      循环读取每一行, 检查key配置项是否存在,若存在,则修改对应的value值
 *      若不存在, 在文件末尾,添加"key = value"
 *      难点: 如何修改文件流中的值
 */
int writeCfgItem(char * pFileName/*in*/, char * pItemName/*in*/, char * pItemValue/*in*/, int itemValueLen/*in*/){
    int rv = 0;
    int iTag = 0;
    long length = 0L;

    FILE * fp = NULL;

    char *pTmp = NULL, *pBegin = NULL, *pEnd = NULL;

    char filebuf[1024 * 16] = {0};
    char lineBuf[LineMaxLen];

    if (pFileName == NULL || pItemName == NULL || pItemValue == NULL){
        rv = -1;
        printf("writeCfgItem() error. param error.\n");
        goto End;
    }

    fp = fopen(pFileName, "r+");  //可读, 并且可以在文件尾部追加内容
    if (fp == NULL){
        printf("writeCfgItem() error. many be no file.\n");  //
    }

    if (fp == NULL){
        fp = fopen(pFileName, "w+");  //尝试创建文件
        if (fp == NULL){
            rv = -3;
            printf("writeCfgItem() error.  create file or open file err.\n");
            goto End;
        }
    }

    if(isFileOverSize(fp, 1024*16)){
        rv = -4;
        goto End;
    }

    //按行读取
    while (!feof(fp)){
        memset(lineBuf, 0 , sizeof(lineBuf));  //清空buf
        pTmp = fgets(lineBuf, LineMaxLen, fp);  //读一行
        if (pTmp == NULL){
            break;
        }

//        //返回字符在字符数组中第一次出现的地址,没找到返回的0
//        pTmp = strchr(lineBuf, '=');
//        if (pTmp == NULL){
//            continue;
//        }
//
//        //在第一个形参指定的字符数组中寻找第二个形参指定的字符数组出现的地址返回
//        char * hasKey = strstr(lineBuf, pKey);

        pTmp = strstr(lineBuf, pItemName);  //key关键字是否在本行
        if (pTmp == NULL){             //不在
            strcat(filebuf, lineBuf);
            continue;
        }else{                         //在
            sprintf(lineBuf, "%s = %s\n", pItemName, pItemValue);  //将需要写入到文件中的键值对放入到lineBuf中
            strcat(filebuf, lineBuf);
            iTag = 1;            //表示存在key
        }
    }

    if (0 == iTag){  //不存在key
        fprintf(fp, "%s = %s\n", pItemName, pItemValue);  //向文件尾部追加字符串
    }else{           //存在
        if (fp != NULL){
            fclose(fp);
            fp = NULL;  //避免野指针
        }

        fp = fopen(pFileName, "w+");   //重新打开文件

        if (fp == NULL){
            rv = -4;
            printf("fopen() error.\n");
            goto End;
        }

        fputs(filebuf, fp);  //将缓存的文件的新的内容写入到文件中
    }

    End:
        if(fp != NULL){
            fclose(fp);
        }
        return rv;
}

bool isFileOverSize(FILE *pf, int size) {
    fseek(pf, 0L, SEEK_END);   //将文件指针移动到文件结束的地方
    int length = ftell(pf);        //获取文件指针相对于文件起始位置的相对偏差,就是文件的长度

    fseek(pf,0L, SEEK_SET);  //将文件指针移动到文件开始的地方

    if (length > size){
        printf("file's size over 16k, nonsupport.\n");
        return true;
    }
    return false;
}