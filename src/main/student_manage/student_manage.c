#include "../../lib/list/list.h"
#include "../../test/student/student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void show_menu();
static void insert(List *list);
static void delete(List *list);
static void update(List *list);
static void query(List *list);
static void get_select(List *list);

/**
 * 学生成绩管理系统
 * @return
 */
int student_manage(void) {

    List *list;
    list_init(list, NULL);

    while (1) {
        show_menu();
        get_select(list);
    }
}

void show_menu(){
    printf("Please enter your choose:\n");
    printf("1) add student\n");
    printf("2) delete student\n");
    printf("3) update student\n");
    printf("4) query student\n");
    printf("5) exit\n");
}

void get_select(List *list){
    char input='\0';
    while (input != '1' && input != '2' && input != '3' && input != '4' && input != '5') {
        scanf("%c", &input);
    }
    switch (input) {
        case '1':
        printf("select insert student\n");
        insert(list);
        break;
        case '2':
        printf("select delete student\n");
        delete(list);
        break;
        case '3':
        printf("select update student\n");
        update(list);
        break;
        case '4':
        printf("select query student\n");
        query(list);
        break;
        case '5':
        printf("select exit program\n");
        exit(0);
        break;
    }
}

void insert(List *list){
    printf("Please enter sutdent's number:");

    int id;
    scanf("%d", &id);

//    char number[255];
//    scanf("%s", number);

    printf("Please enter sutdent's name:");
    char name[255];
    scanf("%s", name);

    printf("please enter student's gender(M/F):");
    char gender;
    scanf("%c", &gender);

    if ('0' == gender || "M" == gender){
        gender = 'm';
    } else{
        gender = 'f';
    }

    int age;
    scanf("%d",&age);
    if (age <= 0 || age >= 200){
        age = 0;
    }



//    Stu *s = create_student(number, name, score);
    Student *s = studn_get_init(id, name,gender, age, 0);
    list_ins_next(list, list_tail(list), s);
    printf("add student success.\n");
}

void delete(List *list){
    query(list);

    printf("please enter the number of student which one you want to delete\n");
//    char number[255];
    int number;
    scanf("%d", number);

    Student *item;
    ListElmt *previous = list_head(list);
    ListElmt *current = list_head(list);
    int flag = 0;

    int size = list_size(list);
    printf("list size = %d\n", size);

    if (size > 0) {
        while(current != NULL){
            item = list_data(current);

//            if(!strncasecmp(item->id, number, 255)){
            if(item->_id == number){
                flag = 1;
                if(current != previous){
                    list_rem_next(list, previous, (void **)item);
                }else {
                    list_rem_next(list, NULL, (void **)item);
                }
                break;
            } else {
                previous = current;
                current = list_next(current);
            }
        }
    }
    
    if (flag) {
        printf("delete from list success\n");
//        destroy_student(item);
        studn_destroy(item);
        printf("delete student success\n");
    }else {
        printf("delete from list fail\n");
    }
}

void update(List *list){
    query(list);

    printf("please enter the number of student which one you want to update\n");
    int id;
    scanf("%d", &id);

    Student *item;
    ListElmt *previous = list_head(list);
    ListElmt *current = list_head(list);
    int flag = 0;

    int size = list_size(list);
    printf("list size = %d\n", size);

    if (size > 0) {
        while(current != NULL){
            item = list_data(current);

            if(item->_id == id){
                flag = 1;

                printf("Please enter sutdent's name:");
                char name[255];
                scanf("%s", name);

                printf("please enter student's gender(M/F):");
                char gender;
                scanf("%c", &gender);

                if ('f' == gender || "F" == gender){
                    gender = 'f';
                } else{
                    gender = 'm';
                }

                int age;
                scanf("%d",&age);
                if (age <= 0 || age >= 200){
                    age = 0;
                }


                memcpy(item->name, name, 32);
                item->gender = gender;
                item->age = age;
                break;
            } else {
                previous = current;
                current = list_next(current);
            }
        }
    }

    if (flag) {
        printf("update student from list success\n");
    }else {
        printf("update student from list fail\n");
    }
}

void query(List *list){
    int size = list_size(list);

    printf("list size = %d\n", size);
    if (size > 0) {
        int i;
        list_resetIterator(list);
        Student *item;
        while(list_hasNext(list)){
            list_moveToNext(list);
            list_iterator(list, (void **)(&item));
//            printf_student(item);
            studn_print(item);
        }
    }
}
