/*单项循环链表实现*/

#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "clist.h"

void clist_init(CList *list, void (*destroy)(void *data)){
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    return;
}

void clist_destroy(CList * list){
    void *data;
    while(clist_size(list) > 0){
        if(clist_rem_next(list, list->head, (void **)(&data)) == 0
           && list->destroy != NULL){
            list->destroy(data);
        }
    }
    memset(list, 0, sizeof(CList));
    return;
}

int clist_ins_next(CList *list, CListElmt *elmt, const void *data){
    CListElmt *new_elmt;
    new_elmt = (CListElmt *)malloc(sizeof(CListElmt));
    if(new_elmt == NULL){
        return -1;
    }
    new_elmt->data = (void *)data;
    if(clist_size(list) == 0){
        new_elmt->next = new_elmt;
        list->head = new_elmt;
    }else{
        new_elmt->next = elmt->next;
        elmt->next = new_elmt;
    }

    list->size++;
    return 0;
}

/**
* 将elmt的下一个元素移除, 被移除的元素的数据放入到data指向的空间
* @param *list
* @param *elmt
* @param **data
*/
int clist_rem_next(CList *list, CListElmt *elmt, void **data){
    if(clist_size(list) == 0){
        return -1;
    }

    CListElmt * old_elmt = elmt->next;
    *data = old_elmt->data;

    if(elmt->next == elmt){
        list->head = NULL;
    }else{
        elmt->next = elmt->next->next;  //从链表中移除下一个节点
        if(old_elmt == clist_head(list)){  //判断被移除的节点是否位于head位置,
            list->head = old_elmt->next;    //是,则将被移除的节点的下一个节点作为head元素
        }
    }

    free(old_elmt);
    list->size--;
    return 0;
}




