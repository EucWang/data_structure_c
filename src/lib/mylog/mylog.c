//
// Created by wangxn on 2016/3/15.
//


//错误级别
#include <sys/unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mylog.h"


//文件名
#define _DEBUG_FILE_ "test.log"
//最大字符长度
#define _MAX_STRING_LEN 10240


int LogLevel[5] = {
  IC_NO_LOG_LEVEL,
  IC_DEBUG_LEVEL,
  IC_INFO_LEVEL,
  IC_WARNING_LEVEL,
  IC_ERROR_LEVEL};

char LogLevelName[5][10] = {
        "NO_LOG", "DEBUG", "INFO", "WARNING", "ERROR"
};


static int error_GetCurTime(char * strTime){
    struct  tm * tmTime = NULL;
    size_t timeLen = 0;
    time_t tTime = 0;

    tTime = time(NULL);
    tmTime = localtime(&tTime);
    timeLen = strftime(strTime, 33, "%Y.%m.%d %H:%M:%S", tmTime);

    return timeLen;
}

static int error_OpenFile(int * pf){
    char fileName[1024];
    memset(fileName, 0 , sizeof(fileName));

#ifdef WIN32
    sprintf(fileName, "D:\\%s",_DEBUG_FILE_);
#else
//    sprintf(fileName, "$s/c_toy_log/%s", getenv("HOME"),_DEBUG_FILE_);
    sprintf(fileName, "D:\\%s",_DEBUG_FILE_);
#endif

    *pf = open(fileName, O_WRONLY|O_CREAT|O_APPEND, 0666);
    if(*pf < 0){
        return -1;
    }
    return 0;
}


static  void error_Core(const char * file, int line, int level, int status, const char * fmt, va_list args){
    char str[_MAX_STRING_LEN];
    int strLen = 0;
    char tmpStr[64];
    int tmpstrLen = 0;
    int pf = 0;

    //初始化内存
    memset(str, 0, _MAX_STRING_LEN);
    memset(tmpStr, 0, 64);

    //加入Log时间
    tmpstrLen = error_GetCurTime(tmpStr);
    sprintf(str, "[%s] ", tmpStr);
    strLen = tmpstrLen;

    //加入log等级
    tmpstrLen = sprintf(str + strLen, "[%s] ", LogLevelName[level]);
    strLen += tmpstrLen;

    //加入log状态
    if(status != 0){
        tmpstrLen = sprintf(str+ strLen , "[ERRNO is %d] ", status);
    }else{
        tmpstrLen = sprintf(str  + strLen, "[SUCCESS] ");
    }

    strLen += tmpstrLen;

    //加入log信息
    tmpstrLen  = vsprintf(str+strLen, fmt, args);
    strLen += tmpstrLen;

    //加入log发生文件
    tmpstrLen = sprintf(str + strLen, " [%s]", file);
    strLen += tmpstrLen;

    //加入log发生行数
    sprintf(str + strLen , " [%d]\r\n", line);
    strLen += tmpstrLen;

    //打开log文件
    if(error_OpenFile(&pf)){
        return;
    }

    write(pf, str, strLen);

    close(pf);
    return;
}

void _LOG(const char * file, int line, int level, int status, const char * fmt, ...){
    va_list args;  //可变参数?

    if (level == IC_NO_LOG_LEVEL){
        return;
    }

    va_start(args, fmt);
    error_Core(file, line, level, status, fmt, args);
    va_end(args);
}