#include <stdlib.h>
#include <string.h>
#include "../list/list.h"
#include "set.h"

/*初始化集合*/
void set_init(Set *pSet, int (*match)(const void *key1, const void *key2),
              void (*destroy)(void *data)){
    list_init(pSet,destroy);
    pSet->match = match;
    return;
}

/*销毁集合,但是不销毁集合中的数据, 这个函数作废,不需要了*/
void set_light_destroy(Set *pSet){
    void *data;
    while(list_size(pSet) > 0 && list_rem_next(pSet, NULL, (void **)(&data)) == 0){
    }
    memset(pSet, 0 , sizeof(List));
}

/*插入数据*/
int set_insert(Set *pSet, const void *data){
    if(set_is_member(pSet, data)){
        return 1;
    }
    return list_ins_next(pSet, list_tail(pSet), data);
}


/*删除数据*/
int set_remove(Set *pSet, void **data){
    //遍历集合,如果有相同的元素,则跳出遍历
    ListElmt *member= NULL, *prev=NULL;
    for(member = list_head(pSet); member != NULL; member = list_next(member)){
        if(pSet->match(*data, list_data(member))){
            break;
        }
        prev = member;
    }

    //没有更多的集合元素了
    if(member == NULL){
        return -1;
    }

    return list_rem_next(pSet, prev, data);
}


/**********************************************/

/*判断指示器是否有下一个元素*/
int set_hasNext(Set *pSet){
    if(pSet->current == NULL){
        if(pSet->head == NULL){
            return 0;
        }else{

            return 1;
        }
    }else{
        if(pSet->current->next == NULL){
            return 0;
        }else{
            return 1;
        }
    }
}

/*移动指示器到下一个位置*/
void set_moveToNext(Set *pSet){
    if(pSet->current == NULL){
        pSet->current = pSet->head;
    }else{
        pSet->current = pSet->current->next;
    }
}

/*获取指示器位置处的data数据*/
void set_iterator(Set *pSet, void **data){
        *data = pSet->current->data;
}
/*重置指示器*/
void set_resetIterator(Set *pSet){
    pSet->current = NULL;
}
/**********************************************/

/*获取2个集合的并集, 新生成的集合中的元素依然是原来2个集合中的元素,并不生成新的元素的拷贝*/
int set_m_union(Set *setu, const Set *set1, const Set *set2){
    set_init(setu, set1->match, NULL);

    ListElmt *member;
    void *data;
    //遍历set1集合,将其所有数据元素全部插入到setu集合中
    for(member = set1->head; member != NULL; member = list_next(member)){
        data = list_data(member);
        if(list_ins_next(setu, list_tail(setu), data) != 0){
            set_destroy(setu);
            return -1;
        }
    }

    for(member = set2->head; member != NULL; member = list_next(member)){
        data = list_data(member);
        if(set_is_member(set1, data)){
            continue;
        }else if(list_ins_next(setu, list_tail(setu), data) != 0){
            set_destroy(setu);
            return -1;
        }
    }
    return 0;
}


/*获取2个集合的交集,新生成的集合中的元素依然是原来2个集合中的元素,并不生成新的元素的拷贝*/
int set_m_intersection(Set *seti, const Set *set1, const Set *set2){
    set_init(seti, set1->match, NULL);

//    ListElmt *member;
//    void *data;
//    for(member = set1->head; member != NULL; member = list_next(member)){
//        data = list_data(member);
//        if(set_is_member(set2, data)){
//            if(list_ins_next(seti, list_tail(seti), data) != 0) {
//                set_destroy(seti);
//                return -1;
//            }
//        }
//    }
    set_resetIterator((Set *)set1);
    while(set_hasNext((Set *)set1)){
        void *data;
        set_moveToNext((Set *)set1);
        set_iterator((Set *)set1, &data);
        if(set_is_member((Set *)set2, data)){
            if(list_ins_next(seti, list_tail(seti), data) != 0){
                set_destroy(seti);
                return -1;
            }
        }
    }

    return 0;
}

/*获取2个集合的差集,新生成的集合中的元素依然是原来2个集合中的元素,并不生成新的元素的拷贝*/
int set_m_difference(Set *setd, const Set *set1, const Set *set2){
    set_init(setd, set1->match, NULL);

    ListElmt *member;
    void *data;
    for(member = set1->head; member != NULL; member = list_next(member)){
        data = list_data(member);
        if(!set_is_member(set2, data)){
            if(list_ins_next(setd, list_tail(setd), data) != 0) {
                set_destroy(setd);
                return -1;
            }
        }
    }
    return 0;
}

/*判断一个元素是否在集合中*/
int set_is_member(const Set *pSet, const void *data){
    ListElmt *member;
    void * member_data = NULL;
    for(member = pSet->head; member != NULL; member = list_next(member)){
        member_data = list_data(member);
        if(pSet->match(member_data, data)){
            return 1;
        }
    }
    return 0;
}

/*判断集合set1是否是集合set2的子集*/
int set_is_subset(const Set *set1, const Set *set2){
    if(set_size(set1) > set_size(set2))  {
        return 0;
    }

    ListElmt *member;
    void * member_data = NULL;
    for(member = set1->head; member != NULL; member = list_next(member)){
        member_data = list_data(member);
        if(!set_is_member(set2, member_data)){
            return 0;
        }
    }
    return 1;
}

/*判断2个集合是否相等*/
int set_is_equal(const Set *set1, const Set *set2){
     if(set_size(set1) != set_size(set2))  {
        return 0;
    }
    return set_is_subset(set1, set2);
}
