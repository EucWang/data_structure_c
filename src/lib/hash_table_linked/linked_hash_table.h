/*
 * linked_hash_table.h
 *
 *  Created on: 2016年3月31日
 *      Author: wangxn
 */

#ifndef LINKED_HASH_TABLE_H_INCLUDED
#define LINKED_HASH_TABLE_H_INCLUDED

#include "../list/list.h"

/**
 * 链式哈希表结构
 */
typedef struct linked_hash_table_{
	/**
	 * 桶的个数
	 */
	int buckets;

	/**
	 * 进入到hash表中的子元素的3个函数
	 */
	int (*h)(const void *key);
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);

	/*
	 * 目前集合中元素的个数
	 * */
	int size;

	/**
	 * 存储桶的链表
	 */
	List *table;
}Linked_Hash_Table;

/*public interface*/

/**
 * @func 对链式哈希表进行初始化, 只有进过初始化的表才能进行其他操作
 * @param lhtable: 需要被初始化的哈希表
 * @param buckers: 初始的大小
 * @param h:       hash函数
 * @param match:   比较函数
 * @param destroy: 元素的自毁函数
 */
int linked_hash_table_init(Linked_Hash_Table * lhtable,
							int buckers,
							int (*h)(const void *key),
							int (*match)(const void *key1, const void *key2),
							void (*destroy)(void *data));

/**
 * @function 主要功能是剔除每个桶中的元素,释放有初始化分配的内存空间,
 * 					如果destroy不为空的话,释放每一个元素的空间
 * @param lhtable: 被销毁的表
 */
void linked_hash_table_destroy(Linked_Hash_Table *lhtable);

/**
 * @function :插入数据,在函数内部,
 * 		首先调用linked_hash_table_lookup()查看是有已经在集合中存在相同的元素,
 * 		没有,将新元素的键散列,然后将新元素插入到哈希表中
 * @param lhtable:
 * @param data:
 */
int linked_hash_table_insert(Linked_Hash_Table *lhtable, const void *data);

/**
 * @function : 散列元素的键,查找与元素相匹配的桶,然后调用list_rem_next删除元素
 */
int linked_hash_table_remove(Linked_Hash_Table *lhtable, void **data);

/**
 * @function : 查找元素,并获取指向删除元素的指针
 */
int linked_hash_table_lookup(const Linked_Hash_Table *lhtable, void **data);

/**
 * @function : 获取哈希表的元素的个数
 */
#define linked_hash_table_size(lhtable) ((lhtable)->size)

#endif

