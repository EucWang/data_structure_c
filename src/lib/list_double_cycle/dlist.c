/*双向链表抽象数据类型的实现*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "dlist.h"

// __declspec(dllexport)
void dlist_init(DList *list, void (*destroy)(void *data)){
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
    return;
}

// __declspec(dllexport)
void dlist_destroy(DList *list){
    void *data;
    while(dlist_remove(list, dlist_tail(list), &data) == 0 &&
          list->destroy != NULL){
        list->destroy(data);
    }

    memset(list, 0 , sizeof(DList));
    return;
}

/**
* @param  list
* @param  elmt  when elmt == NULL and list's size more than 0 ,return -1
* @param  data
* return malloc err ,then return -2
*/
// __declspec(dllexport)
int dlist_ins_next(DList *list, DListElmt *elmt, const void *data){
    DListElmt *new_elmt = NULL;
    if(elmt == NULL && dlist_size(list) != 0){
        return -1;
    }

    new_elmt = (DListElmt *)malloc(sizeof(DListElmt));
    if(new_elmt == NULL){
        return -2;
    }

    new_elmt->data = (void *)data;

    if(dlist_size(list) == 0){   //when list's size == 0
        list->head = new_elmt;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_elmt;
    }else{                                // when list's size > 0
        new_elmt->next = elmt->next;
        new_elmt->prev = elmt;

        if(elmt->next == NULL){
            list->tail = new_elmt;
        }else{
            elmt->next->prev = new_elmt;
        }

        elmt->next = new_elmt;
    }

    list->size++;
    return 0;
}

// __declspec(dllexport)
int dlist_ins_prev(DList *list, DListElmt *elmt, const void *data){
    DListElmt *new_elmt = NULL;

    if(elmt == NULL && dlist_size(list) != 0){
        return -1;
    }

    new_elmt = (DListElmt *)malloc(sizeof(DListElmt));
    if(new_elmt == NULL){
        return -2;
    }

    new_elmt->data = (void *)data;

    if(dlist_size(list) == 0){
        list->head = new_elmt;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_elmt;
    }else{
        new_elmt->next = elmt;
        new_elmt->prev =elmt->prev;

        if(elmt->prev == NULL){
            list->head = new_elmt;
        }else{
            elmt->prev->next = new_elmt;
        }

        elmt->prev = new_elmt;
    }

    list->size++;
    return 0;
}

// __declspec(dllexport)
int dlist_remove(DList *list, DListElmt *elmt, void **data){
    if(elmt == NULL && dlist_size(list) == 0){
        return -1;
    }

    *data = elmt->data;

    if(elmt == list->head){ // elmt is the head element
        list->head = elmt->next;
        if(list->head == NULL){
            list->tail = NULL;
        }else{
            elmt->next->prev = NULL;
        }
    }else{
        elmt->prev->next = elmt->next;
        if(elmt->next == NULL){
            list->tail = elmt->prev;
            list->tail->next = NULL;
        }else{
            elmt->next->prev = elmt->prev;
        }
    }
    free(elmt);
    list->size--;
    return 0;
}
