//
// Created by wangxn on 2016/4/1.
//

#include "../student/student.h"
#include "../../lib/hash_table_open_addressed/open_addr_hash_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int test_open_addressed_hash_table() {
    Student *s1 = studn_get_init(1, "zhangfei", 1, 34, 22);
    Student *s2 = studn_get_init(2, "guanyu", 1, 35, 22);
    Student *s3 = studn_get_init(3, "zhaoyun", 1, 32, 22);
    Student *s4 = studn_get_init(4, "weiyan", 1, 30, 22);
    Student *s5 = studn_get_init(5, "machao", 1, 31, 22);
    Student *s6 = studn_get_init(6, "liubei", 1, 40, 22);
    printf("end get students\n");

    OPEN_ADDR_HTABLE open_addr_htable;
    printf("start init\n");
    oa_htable_init(&open_addr_htable, 10,
                   (void *)studn_hash,
                   (void *)studn_hash2,
                   (void *)studn_match,
                   (void *)studn_destroy);
    printf("end init\n");
    oa_htable_insert(&open_addr_htable, s1);
    oa_htable_insert(&open_addr_htable, s2);
    oa_htable_insert(&open_addr_htable, s3);
    oa_htable_insert(&open_addr_htable, s4);
    oa_htable_insert(&open_addr_htable, s5);
    oa_htable_insert(&open_addr_htable, s6);
    printf("end insert to the hash table\n");

    printf("hash table size :%d\n", oa_htable_size(&open_addr_htable));
    int i = oa_htable_lookup(&open_addr_htable, (void **)(&s1));
    printf("lookup s1 : %s\n", (i == 0 ?"true":"false"));

    oa_htable_remove(&open_addr_htable, (void **)&s2);
    printf("after del one element, hash table size :%d\n", oa_htable_size(&open_addr_htable));
    getchar();

    oa_htable_destroy(&open_addr_htable);
    free(s1);
    free(s2);
    free(s3);
    free(s4);
    free(s5);
    free(s6);
    return 0;
}