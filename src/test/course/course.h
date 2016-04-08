//
// Created by wangxn on 2016/4/8.
//

#ifndef DATA_STRUCTURE_C_COURSE_H
#define DATA_STRUCTURE_C_COURSE_H

/**
 * 课程的结构
 */
typedef struct  Course_{
    int _id;
    char name[32];
}Course;

/**
 * Course课程结构体的内存申请以及数据初始化
 */
Course * course_get_init(int id, char *name);

/**
 * Course的匹配校验
 */
int course_match(Course *c1, Course *c2);

/**
 * Course的内存销毁
 */
void course_destroy(Course *c);

void course_print(Course *c);

#endif //DATA_STRUCTURE_C_COURSE_H
