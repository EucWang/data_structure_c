//
// Created by wangxn on 2016/4/1.
// 开地址hash表的实现类, 使用双散列算法
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "open_addr_hash_table.h"


static char vacated;

/**
 * hash表初始化
 */
int oa_htable_init(OPEN_ADDR_HTABLE *open_addr_htable,
                   int positions,
                   int (*h1)(const void *key),
                   int (*h2)(const void *key),
                   int (*match)(const void *key1, const void *key2),
                   void (*destroy)(void *data)) {

    int i;

    open_addr_htable->table = (void **) malloc(positions * sizeof(void *));
    if (open_addr_htable->table == NULL) {
        printf("oa_htable_init() malloc memory err");
        return -1;
    }

    open_addr_htable->positions = positions;

    for (i = 0; i < open_addr_htable->positions; ++i) {
        open_addr_htable->table[i] = NULL;
    }

    open_addr_htable->vacated = &vacated;

    open_addr_htable->h1 = h1;
    open_addr_htable->h2 = h2;
    open_addr_htable->match = match;
    open_addr_htable->destroy = destroy;

    open_addr_htable->size = 0;

    return 0;
}

/**
 * hash表的销毁
 */
void oa_htable_destroy(OPEN_ADDR_HTABLE *open_addr_htable) {

    int i;
    if (open_addr_htable->destroy != NULL) {
        for (i = 0; i < open_addr_htable->positions; i++) {
            if (open_addr_htable->table[i] != NULL &&
                open_addr_htable->table[i] != open_addr_htable->vacated) {
                open_addr_htable->destroy(open_addr_htable->table[i]);
            }
        }
    }

    free(open_addr_htable->table);

    memset(open_addr_htable, 0, sizeof(OPEN_ADDR_HTABLE));

    return;
}

/**
 * hash表的数据插入
 */
int oa_htable_insert(OPEN_ADDR_HTABLE *open_addr_htable, const void *data) {

    void *tmp;
    int position;
    int i;


    if (open_addr_htable->size == open_addr_htable->positions) {
        printf("oa_htable_insert() table is full, insert fail\n");
        return -1;
    }

    tmp = (void *) data;

    if (oa_htable_lookup(open_addr_htable, &tmp) == 0) {
        printf("oa_htable_insert() already has the data , insert fail\n");
        return 1;
    }

    //尝试positions次插入数据,每次计算的都是2次散列计算的值模于positions,得到一个索引值就是存储的位置
    for (i = 0; i < open_addr_htable->positions; i++) {
        position = (open_addr_htable->h1(data) + (i * open_addr_htable->h2(data))) % open_addr_htable->positions;

        if (open_addr_htable->table[position] == NULL ||
            open_addr_htable->table[position] == open_addr_htable->vacated) {
            open_addr_htable->table[position] = (void *) data;
            open_addr_htable->size++;
            return 0;
        }
    }

    printf("oa_htable_insert() insert fail!\n");
    return -1;
}

/**
 * hash表的数据移除
 */
int oa_htable_remove(OPEN_ADDR_HTABLE *open_addr_htable, void **data) {

    int position;
    int i;

    //尝试positions次插入数据,每次计算的都是2次散列计算的值模于positions,得到一个索引值就是存储的位置
    for (i = 0; i < open_addr_htable->positions; i++) {
        position = (open_addr_htable->h1(data) + (i * open_addr_htable->h2(data))) % open_addr_htable->positions;

        if (open_addr_htable->table[position] == NULL) {
            printf("%s\n", "oa_htable_remove() no the data in table, remove fail");
            return -1;
        } else if (open_addr_htable->table[position] == open_addr_htable->vacated) {
            continue;
        } else if (open_addr_htable->match(open_addr_htable->table[position], *data)) {
            *data = open_addr_htable->table[position];
            open_addr_htable->table[position] = open_addr_htable->vacated;
            open_addr_htable->size--;
            return 0;
        }
    }
    printf("%s\n", "oa_htable_remove() remove fail!");
    return -1;
}

/**
 * hash表的数据查找
 */
int oa_htable_lookup(const OPEN_ADDR_HTABLE *open_addr_htable, void **data) {

    int position;
    int i;

    for (i = 0; i < open_addr_htable->positions; ++i) {
        position = (open_addr_htable->h1(data) + (i * open_addr_htable->h2(data))) % open_addr_htable->positions;

        if (open_addr_htable->table[position] == NULL) {
            printf("%s\n", "oa_htable_lookup() no the data in table, lookup no data");
            return -1;
        } else if (open_addr_htable->match(open_addr_htable->table[position], *data)) {
            *data = open_addr_htable->table[position];
            return 0;
        }
    }

    printf("%s\n", "oa_htable_lookup() lookup no data.");
    return -1;
}
