/*集合覆盖问题实现*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "set_cover.h"
#include "../list/list.h"
#include "../set/set.h"
#include "../../test/set_cover_test/set_cover_test.h"

/**
 * @param members:
 * @param subsets:
 * @param covering:
 */
int kset_cover(Set *members, Set *subsets, Set *covering){
    Set intersection;
    KSet *subset;

    KSet *max_member;
    KSet *member;


    int max_size;

    set_init(covering, subsets->match, NULL);
    set_init(&intersection, members->match, NULL);

    while(set_size(members) > 0 && set_size(subsets)>0){
        max_size = 0;
        set_resetIterator(subsets);

        while(set_hasNext(subsets)){
            set_moveToNext(subsets);
            set_iterator(subsets, (void **)(&member));

            if(set_m_intersection(&intersection, &(member->pSet),members) != 0){
                return -1;
            }
            if(set_size(&intersection) > max_size){
                max_member = member;
                max_size = set_size(&intersection);
            }
            set_destroy(&intersection);
        }
        if(max_size == 0){
            return 1;
        }

        subset = max_member;

        if(set_insert(covering, subset) != 0){
            return -1;
        }


        Set *s = &(max_member->pSet);
        set_resetIterator(s);
        while(set_hasNext(s)){
            set_moveToNext(s);
            Skill * data;
            set_iterator(s, (void **)&data);
            set_remove(members, (void **)&data);
        }

        if(set_remove(subsets, (void **)&subset) != 0){
            return -1;
        }
    }

    if(set_size(members) > 0){
        return -1;
    }

    return 0;
}



KSet * kset_get_init(char *key, Set *s){
    KSet *ks = (KSet *)malloc(sizeof(KSet));
    ks->key = (void *)key;
    ks->pSet = *s;
    return ks;
}

int kset_match(KSet *kset1, KSet *kset2){
    if(kset1 == NULL || kset2 == NULL){
        return 0;
    }
    return strcmp((char *)kset1->key, (char *)kset2->key) == 0 ? 1 : 0;
}

void kset_destroy(KSet *kset){
    if(kset != NULL){
        if(kset->key != NULL){
            free(kset->key);
        }
        free(kset);
    }
}
