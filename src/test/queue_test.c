//
// Created by wangxn on 2016/4/1.
//


#include "../lib/queue/queue.h"
#include "student/student.h"

int test_queue()
{
    Queue_my myQueue;
    queue_m_init(&myQueue, (void *)studn_destroy);

    queue_enqueue(&myQueue, studn_get_init(1,"zhangsan",1, 32, 9));
    queue_enqueue(&myQueue, studn_get_init(2,"lisi",1, 32, 8));
    queue_enqueue(&myQueue, studn_get_init(3,"wangdazhui",1, 32, 9));
    queue_enqueue(&myQueue, studn_get_init(4,"zhangquandan",1, 32, 10));
    queue_enqueue(&myQueue, studn_get_init(5,"zhangfei",1, 32, 9));
    queue_enqueue(&myQueue, studn_get_init(6,"liucuihua",0, 22, 11));

    while(queue_size(&myQueue)>0){
        Student *tmp;
        queue_dequeue(&myQueue, (void **)(&tmp));
        studn_print(tmp);
    }

    queue_m_destroy(&myQueue);
    return 0;
}
