//
// Created by wangxn on 2016/4/1.
//


#include "../lib/stack/stack.h"
#include "student/student.h"

int test_stack()
{
    Stack myStack;
    stack_init(&myStack, (void *)studn_destroy);

    stack_push(&myStack, studn_get_init(1,"zhangsan",1, 32, 9));
    stack_push(&myStack, studn_get_init(2,"lisi",1, 32, 8));
    stack_push(&myStack, studn_get_init(3,"wangdazhui",1, 32, 9));
    stack_push(&myStack, studn_get_init(4,"zhangquandan",1, 32, 10));
    stack_push(&myStack, studn_get_init(5,"zhangfei",1, 32, 9));
    stack_push(&myStack, studn_get_init(6,"liucuihua",0, 22, 11));

//    ListElmt *elmt = myStack.head;
//    Student *s = (Student *)elmt->data;
//    while(s != NULL){
//        studn_print(s);
//        elmt = list_next(elmt);
//        s = (Student *)list_data(elmt);
//    }

    while(stack_size(&myStack)>0){
        Student *tmp;
        stack_pop(&myStack, (void **)(&tmp));
        studn_print(tmp);
    }

    list_destroy(&myStack);
    return 0;
}