//
// Created by wangxn on 2016/3/15.
//

#ifndef C_WORKSPACE_MYLOG_H
#define C_WORKSPACE_MYLOG_H


extern  int LogLevel[5];

/*
 * const char * file : 文件名称
 * int line : 文件行号
 * int level : 错误级别
 *          0 : 没有日志
 *          1 : debug
 *          2 : info
 *          3 : warning
 *          4 : error
 * int status : 错误码
 * const char * fmt : 可变参数
 * */
void _LOG(const char * file, int line, int level, int status, const char * fmt, ...);

#endif //C_WORKSPACE_MYLOG_H
