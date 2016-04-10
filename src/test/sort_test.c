/*
 * sort_insert_sort_test.c
 *
 *  Created on: 2016年4月9日
 *      Author: wangxinnian
 */


#include "student/student.h"
#include <stdio.h>

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

void sort_quick_sort_test(){
    Student s[] = {
    	    *studn_get_init(20, "liucuihua", 0, 22, 11),
    	    *studn_get_init(14, "liucuihua", 0, 22, 11),
            *studn_get_init(16, "liucuihua", 0, 22, 11),

            *studn_get_init(15, "liucuihua", 0, 22, 11),
            *studn_get_init(18, "liucuihua", 0, 22, 11),
            *studn_get_init(17, "liucuihua", 0, 22, 11),

			*studn_get_init(21, "liucuihua", 0, 22, 11),
            *studn_get_init(74, "liucuihua", 0, 22, 11),
            *studn_get_init(64, "liucuihua", 0, 22, 11),

			*studn_get_init(54, "liucuihua", 0, 22, 11),
            *studn_get_init(44, "liucuihua", 0, 22, 11),
            *studn_get_init(34, "liucuihua", 0, 22, 11),

			*studn_get_init(13, "liucuihua", 0, 22, 11),
            *studn_get_init(12, "liucuihua", 0, 22, 11),
            *studn_get_init(11, "liucuihua", 0, 22, 11),

			*studn_get_init(10, "liucuihua", 0, 22, 11),
            *studn_get_init(9, "liucuihua", 0, 22, 11),
            *studn_get_init(8, "liucuihua", 0, 22, 11),

			*studn_get_init(7, "liucuihua", 0, 22, 11),
            *studn_get_init(6, "liucuihua", 0, 22, 11),
            *studn_get_init(5, "liucuihua", 0, 22, 11),

			*studn_get_init(4, "liucuihua", 0, 22, 11),
            *studn_get_init(3, "liucuihua", 0, 22, 11),
            *studn_get_init(91, "liucuihua", 0, 22, 11),

			*studn_get_init(81, "liucuihua", 0, 22, 11),
            *studn_get_init(71, "liucuihua", 0, 22, 11),
            *studn_get_init(61, "liucuihua", 0, 22, 11),

			*studn_get_init(51, "liucuihua", 0, 22, 11),
            *studn_get_init(41, "liucuihua", 0, 22, 11),
            *studn_get_init(25, "liucuihua", 0, 22, 11),

			*studn_get_init(24, "liucuihua", 0, 22, 11),
            *studn_get_init(23, "liucuihua", 0, 22, 11),
            *studn_get_init(22, "liucuihua", 0, 22, 11),

			*studn_get_init(31, "liucuihua", 0, 22, 11),
            *studn_get_init(1, "liucuihua", 0, 22, 11),
            *studn_get_init(2, "liucuihua", 0, 22, 11),

			*studn_get_init(212, "liucuihua", 0, 22, 11),
            *studn_get_init(271, "liucuihua", 0, 22, 11),
            *studn_get_init(19, "liucuihua", 0, 22, 11)
    };

    printf("%s\n", "get array success");

    quick_sort(s, 39, sizeof(Student), 0, 38, (void *)studn_compare);

    int i;
    for(i = 0; i<39; i++){
    	studn_print(s + i);
    }
}
