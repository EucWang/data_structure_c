#ifndef CLIST_H_INCLUDED
#define CLIST_H_INCLUDED

#include <stdlib.h>

/*单向 循环链表 的 头文件*/


typedef struct CListElmt_{

    void *data;
    struct CListElmt_ *next;

}CListElmt;

typedef struct CList_{

    int size;
    int (*match)(const void *key1, const void *key2);
    CListElmt *head;
    void (*destroy)(void *data);
}CList;

/*public interface*/

void clist_init(CList *list, void (*destroy)(void *data));
void clist_destroy(CList *list);
int clist_ins_next(CList *list, CListElmt *elmt, const void *data);
int clist_rem_next(CList *list, CListElmt *elmt, void **data);

#define clist_size(list) ((list)->size)
#define clist_head(list) ((list)->head)
#define clist_data(elmt) ((elmt)->data)
#define clist_next(elmt) ((elmt)->next)
#define clist_is_head(list, elmt) ((elmt) == (list->head) ? 1 : 0)

#endif // CLIST_H_INCLUDED
