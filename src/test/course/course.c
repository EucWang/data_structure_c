//
// Created by wangxn on 2016/4/8.
//

#include "course.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Course课程结构体的内存申请以及数据初始化
 */
Course *course_get_init(int id, char *name) {
    Course *c = (Course *) malloc(sizeof(Course));
    if (c == NULL) {
        printf("%s\n", "course_get_init() fail, malloc fail");
        return NULL;
    }

    c->_id = id;
    if (name != NULL) {
        sprintf(c->name, "%s", name);
    }
    return c;
}

/**
 * Course的匹配校验
 */
int course_match(Course *c1, Course *c2) {
    if (c1 == NULL || c2 == NULL) {
        return -1;
    }

    return c1->_id == c2->_id ? 1 : 0;
}

/**
 * Course的内存销毁
 */
void course_destroy(Course *c) {
    if (c != NULL) {
        return;
    }
    free(c);
}

void course_print(Course *c) {
    if (c == NULL) {
        return;
    }
    printf("[%d,%s]\n", c->_id, c->name);
}