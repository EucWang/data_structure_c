//
// Created by wangxn on 2016/4/1.
//
#include <stdio.h>
#include <stdlib.h>
#include  "../student/student.h"
#include "../../lib/hash_table_linked/linked_hash_table.h"
#include "../test.h"

int test_linked_hash_table(void) {
    int arr_length = 6;

    Student *s1 = studn_get_init(1, "zhangfei", 1, 34, 22);
    Student *s2 = studn_get_init(2, "guanyu", 1, 35, 22);
    Student *s3 = studn_get_init(3, "zhaoyun", 1, 32, 22);
    Student *s4 = studn_get_init(4, "weiyan", 1, 30, 22);
    Student *s5 = studn_get_init(5, "machao", 1, 31, 22);
    Student *s6 = studn_get_init(6, "liubei", 1, 40, 22);

    Student ** ss = {&s1, &s2, &s3, &s4, &s5, &s6};

    printf("end get students\n");

    Linked_Hash_Table lhtable;
    printf("start init\n");
    linked_hash_table_init(&lhtable, 10,
                           (void *)studn_hash, (void *)studn_match, NULL
                        //    (void *)studn_destroy
                           );
    printf("end init\n");
    for (size_t i = 0; i < arr_length; i++) {
        linked_hash_table_insert(&lhtable, *(ss + i));
    } 

    printf("hash table size :%d\n", linked_hash_table_size(&lhtable));
    for (size_t i = 0; i < arr_length; i++) {
        int isIn  = linked_hash_table_lookup(&lhtable, (void **)(ss + i));
        printf("lookup %ld : %s\n", i, (isIn == 0 ?"true":"false"));
    }
    

    linked_hash_table_remove(&lhtable, (void **)&s2);
    printf("after del one element, hash table size :%d\n", linked_hash_table_size(&lhtable));
    for (size_t i = 0; i < arr_length; i++) {
        void * item = *(ss + i);
        int isIn  = linked_hash_table_lookup(&lhtable, &item);
        printf("lookup %ld : %s\n", i, (isIn == 0 ?"true":"false"));
    }

    linked_hash_table_remove(&lhtable, (void **)&s6);
    printf("after del one element, hash table size :%d\n", linked_hash_table_size(&lhtable));
    for (size_t i = 0; i < arr_length; i++) {
        void * item = *(ss + i);
        int isIn  = linked_hash_table_lookup(&lhtable, &item);
        printf("lookup %ld : %s\n", i, (isIn == 0 ?"true":"false"));
    }

    linked_hash_table_map(&lhtable, studn_print);

//    getchar();

    linked_hash_table_destroy(&lhtable);
    for (size_t i = 0; i < arr_length; i++){
        free(*(ss + i));
    }
    
    return 0;
}
