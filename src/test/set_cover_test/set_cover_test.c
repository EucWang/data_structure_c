#include "../../lib/list/list.h"
#include "../../lib/set/set.h"
#include "../../lib/set_cover/set_cover.h"
#include "set_cover_test.h"
#include <stdio.h>
#include <stdlib.h>

Skill * skill_get_init(int id, char * name, char * skill_detail){
    Skill *s = (Skill *)malloc(sizeof(Skill));
    if(s != NULL){
        s->_id = id;
        if(name != NULL){
            sprintf(s->name, name);
        }else{
            memset(s->name, 0 ,sizeof(char) * 32);
        }

        if(name != NULL){
            sprintf(s->skill_detail, skill_detail);
        }else{
            memset(s->skill_detail, 0 ,sizeof(char) * 32);
        }

        return s;
    }
    return NULL;
}

void skill_destroy(Skill *s){
    if(s != NULL){
        free(s);
    }
}

int skill_match(Skill *s1, Skill *s2){
    if(s1 == NULL || s2 == NULL){
        return -1;
    }

    if(s1->_id == s2->_id){
        return 1;
    }

    return 0;
}





