// 使用 优先级队列 实现包裹分拣
// Created by wangxn on 2016/4/6.
//

#include "../lib/bitree/pqueue.h"
#include "test.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * 包裹的一个结构体
 */
typedef struct Parcel_ {
    int _id;
    int priority;
    char addr[64];
} Parcel;

/**
 * 新生成一个包裹,并赋值初始化
 */
static Parcel *parcel_get_init(int id, int priority, char *addr) {
    Parcel *p = malloc(sizeof(Parcel));
    if (p == NULL) {
        printf("%s\n", "parcel_get_init() fail, malloc memory err");
        return NULL;
    }

    p->_id = id;
    p->priority = priority;
    sprintf(p->addr, addr);

    return p;
}

/**
 * 销毁一个包裹数据
 */
static void parcel_destroy(Parcel *parcel) {
    if (parcel == NULL) {
        return;
    }

    free(parcel);
}

/**
 * 比较2个包裹的优先级
 */
static int parcel_compare(Parcel *p1, Parcel *p2) {
    return p1->priority - p2->priority;
}

void parcel_print(Parcel *parcel) {
    printf("[id=%d,priority=%d,addr=%s]\n", parcel->_id, parcel->priority, parcel->addr);
}


/**
 * 从 优先级队列中获取 一个优先级最高的一个包裹
 * 获取到的包裹数据让parcel指向
 * 返回0表示包裹获取成功
 */
int get_parcel(PQueue *parcels, Parcel *parcel) {
    if (pqueue_size(parcels) == 0) {
        printf("%s\n", "parcels size is zero, get_parcel() do nothing");
        return -1;
    }

    Parcel *data;
    if (pqueue_extract(parcels, (void **) (&data)) != 0) {
        printf("%s\n", "get_parcel() fail, call pqueue_extract() fail");
        return -1;
    }

    memcpy(parcel, data, sizeof(Parcel));
    free(data);
    return 0;
}

/**
 * 将一个新包裹插入到 优先级队列,
 * 优先级队列中的数据是传递给函数的一个内存复制,
 * 原来的数据需要手动free
 * 返回0,表示插入成功
 */
int put_parcel(PQueue *parcels, const Parcel *parcel) {
    Parcel *data;
    data = (Parcel *) malloc(sizeof(Parcel));
    if (data == NULL) {
        printf("%s\n", "put_parcel() fail, call malloc fail");
        return -1;
    }

    memcpy(data, parcel, sizeof(Parcel));

    if (pqueue_insert(parcels, data) != 0) {
        return -1;
    }

    return 0;
}

void test_parcel() {
    Parcel ps[] = {
            *parcel_get_init(1, 1, "no 1, street queen.2 NewYork"),
            *parcel_get_init(2, 2, "no 2, street queen.2 NewYork"),
            *parcel_get_init(3, 3, "no 3, street queen.2 NewYork"),
            *parcel_get_init(4, 4, "no 4, street queen.2 NewYork"),
            *parcel_get_init(5, 5, "no 5, street queen.2 NewYork"),
            *parcel_get_init(6, 6, "no 6, street queen.2 NewYork"),
            *parcel_get_init(7, 7, "no 7, street queen.2 NewYork"),
            *parcel_get_init(8, 8, "no 8, street queen.2 NewYork")
    };

    PQueue pQueue;
    pqueue_init(&pQueue, (void *) parcel_compare, (void *) parcel_destroy);

    int i;
    for (i = 0; i < 8; ++i) {
        put_parcel(&pQueue, &ps[i]);
    }

    printf("%s%d\n", "pqueue 's size is :", pqueue_size(&pQueue));

    Parcel *p;
    get_parcel(&pQueue, p);
    printf("%s\n", "get the top priority parcel");
    parcel_print(p);
    get_parcel(&pQueue, p);
    printf("%s\n", "get the top priority parcel");
    parcel_print(p);

    printf("%s%d\n", "pqueue 's size is : ", pqueue_size(&pQueue));

    printf("%s\n", "============== release data begin ===============");
    pqueue_destroy(&pQueue);
    printf("%s\n", "============== release data end ===============");
    return;
}



