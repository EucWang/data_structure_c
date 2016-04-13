//
// Created by wangxn on 2016/4/13.
//

#include "../lib/comprass/compress.h"
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include <string.h>


void huff_compress_test(){

//    FILE *file = NULL;
//    file = fopen("D:/test.txt", "r");
//    if (file == NULL) {
//        printf("open file err\n");
//        return;
//    }
//
//    fseek(file, 0, SEEK_END);
//    long size = ftell(file);
//    fseek(file, 0, SEEK_SET);
//
//    const unsigned char *buf = (unsigned char *)malloc(size * sizeof(unsigned char));
//
//    fread((void *)buf, size, sizeof(unsigned char), file);

    const unsigned char buf[] = "1aabbbccccdddddeeeeee";
    size_t i = sizeof(buf);
    printf("%s%d\n", "the char arr ' size is ", i);
    
//    printf("%s\n", "read to buf end");

    unsigned char * tmp = NULL;
    unsigned char ** compressed = &tmp;
    if(huffman_compress(buf, compressed, i) <= 0) {
        printf("%s\n", "compress fail");
        return;
    }

    FILE *file2 = NULL;
    file2 = fopen("D:/test.huf", "w");
    if (file2 == NULL) {
        printf("%s\n", "write file open err");
        return;
    }

    fwrite((const void *)(*compressed), i, sizeof(unsigned char), file2);
    printf("%s\n", "write file end");

//    fclose(file);
    fclose(file2);

    return;
}

void huff_uncompress_test(){

    FILE *file = NULL;
    file = fopen("D:/test.huf", "r");
    if (file == NULL) {
        printf("open file err\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buf = (unsigned char *)malloc(size * sizeof(unsigned char));
    memset(buf, 0, size * sizeof(unsigned char));

    fread((void *)buf, size, sizeof(unsigned char), file);
    fclose(file);

    printf("%s\n", "read to buf end");

    unsigned char * tmp = NULL;
    unsigned char ** original = &tmp;
    if((size = huffman_uncompress(buf, original)) <= 0) {
        printf("%s\n", "uncompress fail");
        return;
    }

    FILE *file2 = NULL;
    file2 = fopen("D:/test2.txt", "w");
    if (file2 == NULL) {
        printf("%s\n", "write file open err");
        return;
    }

    fwrite((const void *)(*original), size, sizeof(unsigned char), file2);
    printf("%s\n", "write file end");


    fclose(file2);
    return;
}