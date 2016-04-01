//
// Created by wangxn on 2016/4/1.
//

#include <stdio.h>
#include "../lib/set/set.h"
#include "student/student.h"

int test_set(){
    Set set1;
    set_init(&set1, (void *)studn_match, (void *)studn_destroy);

    set_insert(&set1, studn_get_init(1,"zhangsan",1, 32, 9));
    set_insert(&set1, studn_get_init(2,"lisi",1, 32, 8));
    set_insert(&set1, studn_get_init(3,"wangdazhui",1, 32, 9));
    set_insert(&set1, studn_get_init(4,"zhangquandan",1, 32, 10));
    set_insert(&set1, studn_get_init(5,"zhangfei",1, 32, 9));
    set_insert(&set1, studn_get_init(6,"liucuihua",0, 22, 11));

    Set set2;
    set_init(&set2, (void *)studn_match, (void *)studn_destroy);

    set_insert(&set2, studn_get_init(1,"zhangsan",1, 32, 9));
    set_insert(&set2, studn_get_init(2,"libai",1, 32, 8));
    set_insert(&set2, studn_get_init(7,"wangzhaojun",1, 36, 199));
    set_insert(&set2, studn_get_init(8,"ZhangDaQian",1, 32, 18));
    set_insert(&set2, studn_get_init(9,"ZhangAiLing",0, 33, 19));
    set_insert(&set2, studn_get_init(10,"LiuCuiHong",0, 21, 11));

    Set su;
    set_m_union(&su, &set1, &set2);

    printf("the union of the two set:\n");
    set_resetIterator(&su);
    while(set_hasNext(&su)){
        set_moveToNext(&su);
        Student *data = NULL;
        set_iterator(&su, (void **)(&data));
        studn_print(data);
    }
    printf("************************************\n");

    Set sd;
    set_m_difference(&sd, &set1,&set2);

    printf("the difference of the two set:\n");
    set_resetIterator(&sd);
    while(set_hasNext(&sd)){
        set_moveToNext(&sd);
        Student *data = NULL;
        set_iterator(&sd, (void **)(&data));
        studn_print(data);
    }
    printf("************************************\n");

    Set si;
    set_m_intersection(&si, &set1,&set2);
    printf("the intersection of the two set:\n");
    set_resetIterator(&si);
    while(set_hasNext(&si)){
        set_moveToNext(&si);
        Student *data = NULL;
        set_iterator(&si, (void **)(&data));
        studn_print(data);
    }
    printf("************************************\n");

    printf("delete 4 data from set2,and then if it's set1's subset\n");
    Student *s1 = studn_get_init(7,"wangzhaojun",1, 36, 199);
    Student *s2 = studn_get_init(8,"ZhangDaQian",1, 32, 18);
    Student *s3 = studn_get_init(9,"ZhangAiLing",0, 33, 19);
    Student *s4 = studn_get_init(10,"LiuCuiHong",0, 21, 11);

    set_remove(&set2, (void **)(&s1));
    set_remove(&set2, (void **)(&s2));
    set_remove(&set2, (void **)(&s3));
    set_remove(&set2, (void **)(&s4));
    free(s1);
    free(s2);
    free(s3);
    free(s4);

    printf(set_is_subset(&set2, &set1)?"true":"false");

    set_destroy(&set1);
    set_destroy(&set2);
//    set_light_destroy(&su);
//    set_light_destroy(&sd);
//    set_light_destroy(&si);
    set_destroy(&su);
    set_destroy(&sd);
    set_destroy(&si);
    return 0;
}
