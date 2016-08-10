#include "student.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

int PJW_Hash(char* str, int len);

Student * studn_get_init(int id, char * name,char gender, int age, int school_class){
    Student *ps = (Student *)malloc(sizeof(Student));

    ps->_id = id;
    memcpy(ps->name, name, 32);
    ps->gender = gender;
    ps->age = age;
    ps->school_class = school_class;

    return ps;
}

int studn_hash(Student *s){
    int len  = 20 + 33 * sizeof(char);
    char *str = (char *)malloc(len);
    memset(str, 0, len);
    sprintf(str, "%d%s%c%d%d", s->_id, s->name, s->gender,s->age,s->school_class);
    int hash = 0;
    int i;
    for(i = 0; i<len; i++){
        hash = 31 * hash + str[i];
    }

//	return PJW_Hash(str, len);
}
int studn_hash2(Student *s){
    int len  = 20 + 33 * sizeof(char);
    char *str = (char *)malloc(len);
    memset(str, 0, len);
    sprintf(str, "%d%s%c%d%d", s->_id, s->name, s->gender,s->age,s->school_class);
    int hash = 0;
    int i;
    for(i = 0; i<len; i++){
        hash = 43 * hash + str[i];
    }

//	return PJW_Hash(str, len);
}

void studn_destroy(Student *s){
    if(s != NULL){
        free(s);
    }
    return;
}

int studn_match(Student *s1, Student *s2) {
    if (s1 != NULL && s2 != NULL) {
        if (s1->_id > 0 && s2->_id > 0) {
            return s1->_id == s2->_id ? 1 : 0;
        }
    }

    return -1;
}

int studn_compare(Student *s1, Student *s2){
    return s1->_id - s2->_id;
}



void studn_print(Student *s){
    printf("[id:%d,name:%s,gender:%s,age:%d,school_class:%d]\n",
           s->_id, s->name, (s->gender == 'f' ||s->gender == 'F') ?"female":"male",s->age,s->school_class);
}

int PJW_Hash(char* str, int len){
    const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
    const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
    const unsigned int HighBits          = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash              = 0;
    unsigned int test              = 0;
    unsigned int i                 = 0;
    for(i = 0; i < len; str++, i++){
        hash = (hash << OneEighth) + (*str);
        if((test = hash & HighBits)  != 0){
            hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }
    return hash;
}
