#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED


typedef struct Student_{
    int _id;
    char name[32];
    char gender;
    int age;
    int school_class;
}Student;

/*构建Student结构体的内存空间, 初始化Student结构体的每一项成员变量*/
Student * studn_get_init(int id, char * name,char gender, int age, int school_class);

/*销毁Student结构体*/
void studn_destroy(Student *s);

/*判断2个Student是否相等, 相等返回1, 否则返回2*/
int studn_match(Student *s1, Student *s2);

/*控制台打印输出Student的中的每一个成员变量值*/
void studn_print(Student *s);



int studn_hash(Student *s);

int studn_hash2(Student *s);

#endif // STUDENT_H_INCLUDED
