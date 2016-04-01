//
// Created by wangxn on 2016/4/1.
//


#include <stdio.h>
#include <stdlib.h>
#include  "./student/student.h"
#include "../lib/hash_table_linked/linked_hash_table.h"

int test_linked_hash_table(void) {
    Student *s1 = studn_get_init(1, "zhangfei", 1, 34, 22);
    Student *s2 = studn_get_init(2, "guanyu", 1, 35, 22);
    Student *s3 = studn_get_init(3, "zhaoyun", 1, 32, 22);
    Student *s4 = studn_get_init(4, "weiyan", 1, 30, 22);
    Student *s5 = studn_get_init(5, "machao", 1, 31, 22);
    Student *s6 = studn_get_init(6, "liubei", 1, 40, 22);
    printf("end get students\n");

    Linked_Hash_Table lhtable;
    printf("start init\n");
    linked_hash_table_init(&lhtable, 10,
                           (void *)studn_hash, (void *)studn_match, (void *)studn_destroy);
    printf("end init\n");
    linked_hash_table_insert(&lhtable, s1);
    linked_hash_table_insert(&lhtable, s2);
    linked_hash_table_insert(&lhtable, s3);
    linked_hash_table_insert(&lhtable, s4);
    linked_hash_table_insert(&lhtable, s5);
    linked_hash_table_insert(&lhtable, s6);
    printf("end insert to the hash table\n");

    printf("hash table size :%d\n", linked_hash_table_size(&lhtable));
    int i = linked_hash_table_lookup(&lhtable, (void **)(&s1));
    printf("lookup s1 : %s\n", (i == 0 ?"true":"false"));


    linked_hash_table_remove(&lhtable, (void **)&s2);
    printf("after del one element, hash table size :%d\n", linked_hash_table_size(&lhtable));
    getchar();

    linked_hash_table_destroy(&lhtable);
    free(s1);
    free(s2);
    free(s3);
    free(s4);
    free(s5);
    free(s6);
    return 0;
}
