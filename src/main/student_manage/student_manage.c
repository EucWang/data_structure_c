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
    List list;   //定义一个列表
    list_init(&list, NULL);   //初始化列表
    while (1) {                //定义一个循环,在循环中显示菜单,获取用户输入
        show_menu();
        get_select(&list);
    }
}

/**
 * 显示菜单
 */
void show_menu(){
    printf("Please enter your choose:\n");
    printf("1) add student\n");
    printf("2) delete student\n");
    printf("3) update student\n");
    printf("4) query student\n");
    printf("5) exit\n");
}

/**
 * 根据用户的输入内容进行不同的操作
 * @param list  列表
 */
void get_select(List *list){
    char input='\0';
    while (input != '1' && input != '2' && input != '3' && input != '4' && input != '5') {
        scanf("%c", &input);
    }
    switch (input) {
        case '1':
        printf("select insert student\n");
        insert(list);                          //选择菜单1,进行插入操作
        break;
        case '2':
        printf("select delete student\n");
        delete(list);                           //菜单2,进行删除操作
        break;
        case '3':
        printf("select update student\n");
        update(list);                         //更新操作
        break;
        case '4':
        printf("select query student\n");
        query(list);                          //查询操作
        break;
        case '5':
        printf("select exit program\n");
        exit(0);                                //退出程序
        break;
    }
}

/**
 * 让用户输入学生信息,然后将数据插入到列表中
 * @param list 列表
 */
void insert(List *list){
    int id;
    char name[255];
    char gender;
    int age;

    printf("Please enter sutdent's number:");
    scanf("%d", &id);
    printf("Please enter sutdent's name:");
    scanf("%s", name);
    printf("please enter student's gender(M/F):");
    scanf("%c", &gender);
    scanf("%c", &gender);
    printf("please enter student's age:");
    scanf("%d",&age);

    if ('0' == gender || 'M' == gender){
        gender = 'm';
    } else{
        gender = 'f';
    }
    if (age <= 0 || age >= 200){
        age = 0;
    }

    Student *s = studn_get_init(id, name,gender, age, 0);  //创建一个学生对象
    //list_ins_next(list, list_tail(list), s);               //将学生对象插入到列表中
	list_add(list, s);
    printf("add student success.\n");
}

/**
 * 从列表中删除一个学生信息
 * @param list  列表
 */
void delete(List *list){
    query(list);    //遍历列表,显示所有学生信息

    printf("please enter the number of student which one you want to delete\n");
    int number;
    scanf("%d", &number);

    Student *item;
    ListElmt *previous = list_head(list);  //将上一个元素指向列表头部
    ListElmt *current = list_head(list);   //将当前元素指向列表头部
    int flag = 0;

    int size = list_size(list);            //获取列表元素数量
    printf("list size = %d\n", size);

    if (size > 0) {
        while(current != NULL){
            item = list_data(current);      //获取当前元素中的数据,这个数据就是Student
            if(item->_id == number){        //将Student的id和用户输入的id比对, 相同
                flag = 1;
                if(current != previous){                        //这种情况表示移除的不是头部元素
                    list_rem_next(list, previous, (void **)item);
                }else {
                    list_rem_next(list, NULL, (void **)item);
                }
                break;
            } else {
                previous = current;                //上一个item指向当前元素
                current = list_next(current);     //遍历当前元素指向下一个元素
            }
        }
    }
    
    if (flag) {
        printf("delete from list success\n");
        studn_destroy(item);                      //将需要删除的学生对象的资源释放
        printf("delete student success\n");
    }else {
        printf("delete from list fail\n");
    }
}

/**
 * 更新列表中的某个学生的数据
 * @param list
 */
void update(List *list){
    query(list);       //输出学生列表中的所有数据到控制台显示

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

                char name[255];
                char gender;
                int age;
                printf("Please enter sutdent's name:");
                scanf("%s", name);
                printf("please enter student's gender(M/F):");
                scanf("%c", &gender);
                printf("please enter student's age:");
                scanf("%d",&age);

                if ('f' == gender || 'F' == gender){
                    gender = 'f';
                } else{
                    gender = 'm';
                }
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

/**
 * 查询列表中的所有学生信息并输出到控制台显示
 * @param list
 */
void query(List *list){
    int size = list_size(list);   //获取列表中元素数量

    printf("list size = %d\n", size);
    if (size > 0) {
        int i;
        list_resetIterator(list);     //初始化列表迭代器, 将列表指针移动到列表第一个元素之前
        Student *item;                //定义一个temp学生
        while(list_hasNext(list)){               //判断是否有一个学生
            list_moveToNext(list);                //移动列表指针到下一个元素
            list_iterator(list, (void **)(&item));      //获取下一个元素并赋值给temp学生
            studn_print(item);                       //控制台输出学生信息
        }
    }
}
