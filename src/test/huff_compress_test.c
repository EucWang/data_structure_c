//
// Created by wangxn on 2016/4/13.
//

#include "../lib/comprass/compress.h"
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include <string.h>


void huff_compress_test(){
    FILE *file = NULL;
    file = fopen("D:/c_note.txt", "rb");
    if (file == NULL) {
        printf("open file err\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    printf("file 'size : %d\n", size);
    const unsigned char *buf = (unsigned char *)malloc(size * sizeof(unsigned char));
    fread((void *)buf, size, sizeof(unsigned char), file);

//    const unsigned char buf[] = "1aabbb";
//    const unsigned char buf[] = {
//            '1','a','a','b','b','b'
//    };

    unsigned char * tmp = NULL;
    unsigned char ** compressed = &tmp;
    int compressed_size = 0;
    if((compressed_size = huffman_compress(buf, compressed, size)) <= 0) {
        printf("%s\n", "compress fail");
        return;
    }

    printf("compressed content size : %d\n", compressed_size);

    FILE *file2 = NULL;
    file2 = fopen("D:/test.huf", "wb");
    if (file2 == NULL) {
        printf("%s\n", "write file open err");
        return;
    }

    fwrite((const void *)(*compressed), compressed_size, sizeof(unsigned char), file2);
    printf("%s\n", "write file end");

//    fclose(file);
    fclose(file2);

    return;
}

void huff_uncompress_test(){

    FILE *file = NULL;
    file = fopen("D:/test.huf", "rb");
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

    printf("%s\n", *original);

    FILE *file2 = NULL;
    file2 = fopen("D:/test2.txt", "wb");
    if (file2 == NULL) {
        printf("%s\n", "write file open err");
        return;
    }

    fwrite((const void *)(*original), size, sizeof(unsigned char), file2);
    printf("%s\n", "write file end");


    fclose(file2);
    return;
}