//
// Created by wangxn on 2016/3/11.
//

#ifndef C_WORKSPACE_CFG_OP_H
#define C_WORKSPACE_CFG_OP_H

#ifdef _cplusplus
extern "C"{
#endif

int getCfgItem(char * pFileName, char * pKey, char * pValue, int * pValueLen);

int writeCfgItem(char * pFile, char * pItemName, char * pItemValue, int itemValueLen);
int delCfgItem(char * pFileName/*in*/, char * pItemName/*in*/);
#ifdef _cplusplus
}
#endif

#endif //C_WORKSPACE_CFG_OP_H
