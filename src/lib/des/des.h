//
// Created by wangxn on 2016/3/14.
//

#ifndef C_WORKSPACE_DES_H
#define C_WORKSPACE_DES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>

/**
 * 加密函数
 */
int desEnc(unsigned char * pInData, int nInDataLen, unsigned char * pOutData, int * pOutDataLen);

/**
 * 解密函数
 */
int desDec(unsigned char * pInData, int nInDataLen, unsigned char * pOutData, int *POutDataLen);

#ifdef __cplusplus
};
#endif


#endif //C_WORKSPACE_DES_H
