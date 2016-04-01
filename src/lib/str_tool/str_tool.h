//
// Created by wangxn on 2016/3/11.
//

#ifndef C_WORKSPACE_MYSTRING_OP_H
#define C_WORKSPACE_MYSTRING_OP_H

#ifdef _cplusplus
extern "C"{
#endif

char * trim(char * str);


char ** splitString(char * str/*in*/, const char tag/*in*/, int * returnSize/*out*/);

#ifdef _cplusplus
}
#endif

#endif