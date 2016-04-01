#ifndef DLIST_H_INCLUDED
#define DLIST_H_INCLUDED


/*双向链表抽象数据类型的头文件*/

#ifdef _cplusplus
extern "C"{
#endif

#include <stdlib.h>

/*define a structure for double-linked list elements*/

// __declspec(dllexport)
typedef struct DListElmt_{
    void *data;
    struct DListElmt_ *prev;
    struct DListElmt_ *next;
}DListElmt;

// __declspec(dllexport)
typedef struct  DList_{
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    DListElmt *head;
    DListElmt *tail;
}DList;

//pulbic interface
void dlist_init(DList *list, void (*destroy)(void *data));
void dlist_destroy(DList *list);

int dlist_ins_next(DList *list, DListElmt *elmt, const void *data);
int dlist_ins_prev(DList *list, DListElmt *elmt, const void *data);

int dlist_remove(DList *list, DListElmt *elmt, void **data);

#define dlist_size(list) ((list)->size)
#define dlist_head(list) ((list)->head)
#define dlist_tail(list) ((list)->tail)

#define dlist_is_head(elmt) ((elmt)->prev == NULL ? 1: 0)
#define dlist_is_tail(elmt)  ((elmt)->next == NULL ? 1: 0)

#define dlist_data(elmt) ((elmt)->data)
#define dlist_next(elmt) ((elmt)->next)
#define dlist_prev(elmt) ((elmt)->prev)

//pulbic interface

#ifdef _cplusplus
}
#endif


#endif // DLIST_H_INCLUDED
