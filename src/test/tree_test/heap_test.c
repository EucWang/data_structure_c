//
// Created by wangxn on 2016/4/6.
//

#include "../test.h"
#include "../../lib/bitree/heap.h"
#include ".././student/student.h"
#include <stdio.h>

void heap_test(){
    Heap heap;
    heap_init(&heap, (void *) studn_compare, (void *) studn_destroy);

    heap_insert(&heap, studn_get_init(1, "zhangsan", 1, 32, 9));
    heap_insert(&heap, studn_get_init(2, "lisi", 1, 32, 8));
    heap_insert(&heap, studn_get_init(3, "wangdazhui", 1, 32, 9));
    heap_insert(&heap, studn_get_init(4, "zhangquandan", 1, 32, 10));
    heap_insert(&heap, studn_get_init(5, "zhangfei", 1, 32, 9));
    heap_insert(&heap, studn_get_init(6, "liucuihua", 0, 22, 11));
    heap_insert(&heap, studn_get_init(7, "liucuihua", 0, 22, 11));
    heap_insert(&heap, studn_get_init(8, "liucuihua", 0, 22, 11));
    heap_insert(&heap, studn_get_init(9, "liucuihua", 0, 22, 11));
    heap_insert(&heap, studn_get_init(10, "liucuihua", 0, 22, 11));
    heap_insert(&heap, studn_get_init(11, "liucuihua", 0, 22, 11));
    heap_insert(&heap, studn_get_init(12, "liucuihua", 0, 22, 11));
    heap_insert(&heap, studn_get_init(13, "liucuihua", 0, 22, 11));
    heap_insert(&heap, studn_get_init(14, "liucuihua", 0, 22, 11));
    heap_insert(&heap, studn_get_init(15, "liucuihua", 0, 22, 11));
    heap_insert(&heap, studn_get_init(16, "liucuihua", 0, 22, 11));
    heap_insert(&heap, studn_get_init(17, "liucuihua", 0, 22, 11));
    heap_insert(&heap, studn_get_init(18, "liucuihua", 0, 22, 11));
    heap_insert(&heap, studn_get_init(19, "liucuihua", 0, 22, 11));
    heap_insert(&heap, studn_get_init(20, "liucuihua", 0, 22, 11));
    heap_insert(&heap, studn_get_init(21, "liucuihua", 0, 22, 11));

    printf("%s%d\n", " heap size :" , heap_size(&heap));

    Student **s;
    printf("%s\n", "获取顶部元素1");
    heap_extract(&heap, (void **)s);
    studn_print(*s);
    printf("%s\n", "获取顶部元素2");
    heap_extract(&heap, (void **)s);
    studn_print(*s);

    printf("%s\n", "============== release data begin ===============");
    heap_destroy(&heap);
    printf("%s\n", "============== release data end ===============");
    return;
}