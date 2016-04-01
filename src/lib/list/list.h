#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
//
//#include <stdlib.h>

/*单链表结构*/

typedef struct ListElmt_{
    void *data;
    struct ListElmt_ *next;
}ListElmt;

typedef struct List_{
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    ListElmt *head;
    ListElmt *tail;
    ListElmt *current;
}List;

/*单链表结构的接口函数*/

void list_init(List *list, void (*destroy)(void *data));
void list_destroy(List *list);
int list_ins_next(List *list, ListElmt *elmt, const void *data);
int list_rem_next(List *list, ListElmt *elmt, void **data);

#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)

#define list_is_head(list, elmt) ((list)->head == (elmt) ? 1:0)
#define list_is_tail(elmt) ((elmt)->next == NULL ?1:0)

#define list_data(elmt) ((elmt)->data)
#define list_next(elmt) ((elmt)->next)


/*遍历Set集合用到的几个函数*/

/*判断指示器是否有下一个元素*/
int list_hasNext(List *plist);

/*移动指示器到下一个位置*/
void list_moveToNext(List *plist);

/*获取指示器位置处的data数据*/
void list_iterator(List *plist, void **data);
/*重置指示器*/
void list_resetIterator(List *plist);

#endif // LIST_H_INCLUDED
