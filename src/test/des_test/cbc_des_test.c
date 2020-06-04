//
// Created by wangxn on 2016/4/19.
//
#include <stdio.h>
#include <stdlib.h>
#include "../test.h"
#include "../../lib/encryption/cbc_des.h"
#include "../../lib/encryption/encrypt.h"
#include <string.h>

void cbc_des_test() {

    unsigned char sources[] = {
            '1','2','3','4','5','6','7','8',
            '9','0',
            '1','2','3','4','5','6','7','8','9','0',
            '1','2','3','4','5','6'
    };
    unsigned char key[] = {
            'a','b','c','d','e','f','g','h'
    };

    unsigned char target[26];

    cbc_des_encipher(sources, target,key, 26);

//    printf("target is :%s\n", target);

    unsigned char target2[26];

    cbc_des_decipher(target,target2, key, 26);

    int i;
    for (i = 0; i < 26; ++i) {
        printf("%c", sources[i]);
    }
    printf("\n");
    for (i = 0; i < 26; ++i) {
        printf("%c", target2[i]);
    }
}