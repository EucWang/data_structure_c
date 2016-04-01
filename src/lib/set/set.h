#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED

#include <stdlib.h>
#include "../list/list.h"

/*基于链表实现Set集合*/

typedef List Set;

/*公共接口*/

/*初始化集合*/
void set_init(Set *pSet, int (*match)(const void *key1, const void *key2),
              void (*destroy)(void *data));

/*销毁集合*/
#define set_destroy list_destroy

/*销毁集合,但是不销毁集合中的数据*/
void set_light_destroy(Set *pSet);

/*插入数据*/
int set_insert(Set *pSet, const void *data);

/*删除数据*/
int set_remove(Set *pSet, void **data);

/*获取2个集合的并集*/
int set_m_union(Set *setu, const Set *set1, const Set *set2);

/*获取2个集合的交集*/
int set_m_intersection(Set *seti, const Set *set1, const Set *set2);

/*获取2个集合的差集*/
int set_m_difference(Set *setd, const Set *set1, const Set *set2);
/*判断一个元素是否在集合中*/
int set_is_member(const Set *pSet, const void *data);

/*判断集合set1是否是集合set2的子集*/
int set_is_subset(const Set *set1, const Set *set2);

/*判断2个集合是否相等*/
int set_is_equal(const Set *set1, const Set *set2);

/*计算集合的成员个数*/
#define set_size(set) ((set)->size)

/*遍历Set集合用到的几个函数*/

/*判断指示器是否有下一个元素*/
int set_hasNext(Set *pSet);

/*移动指示器到下一个位置*/
void set_moveToNext(Set *pSet);

/*获取指示器位置处的data数据*/
void set_iterator(Set *pSet, void **data);
/*重置指示器*/
void set_resetIterator(Set *pSet);

#endif // SET_H_INCLUDED
