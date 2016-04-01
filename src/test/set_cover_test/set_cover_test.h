#ifndef SET_COVER_TEST_H_INCLUDED
#define SET_COVER_TEST_H_INCLUDED

typedef struct Skill_{
    int _id;
    char name[32];
    char skill_detail[32];
}Skill;

Skill * skill_get_init(int id, char * name, char * skill_detail);

void skill_destroy(Skill *s);

int skill_match(Skill *s1, Skill *s2);

#endif // SET_COVER_TEST_H_INCLUDED
