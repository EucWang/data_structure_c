/*
 * sort_insert_sort_test.c
 *
 *  Created on: 2016年4月9日
 *      Author: wangxinnian
 */


#include "student/student.h"

void sort_insert_sort_test(){
    Student s[] = {
    	    *studn_get_init(20, "liucuihua", 0, 22, 11),
    	    *studn_get_init(14, "liucuihua", 0, 22, 11),
            *studn_get_init(16, "liucuihua", 0, 22, 11),
            *studn_get_init(15, "liucuihua", 0, 22, 11),
            *studn_get_init(18, "liucuihua", 0, 22, 11),
            *studn_get_init(17, "liucuihua", 0, 22, 11),
            *studn_get_init(21, "liucuihua", 0, 22, 11),
            *studn_get_init(19, "liucuihua", 0, 22, 11)
    };

    insert_sort(s, 8, sizeof(Student), (void *)studn_compare);

    int i;
    for(i = 0; i<8; i++){
    	studn_print(s + i);
    }
}
