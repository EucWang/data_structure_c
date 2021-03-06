/*
 * linked_hash_.c
 *
 *  Created on: 2016年3月31日
 *      Author: wangxn
 */


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include  "linked_hash_set.h"


/**
 * @func 对链式哈希表进行初始化, 只有进过初始化的表才能进行其他操作
 * @param lhset: 需要被初始化的哈希表
 * @param buckers: 初始的大小
 * @param h:       hash函数
 * @param match:   比较函数
 * @param destroy: 元素的自毁函数
 */
int linked_hash_set_init(Linked_Hash_Set * lhset,
							int buckets,
							int (*h)(const void *key),
							int (*match)(const void *key1, const void *key2),
							void (*destroy)(void *data)){
	if(lhset == NULL){
		printf("linked_hash_set_init() err args:buckets=%d, smaller than zero\n", buckets);
		return -1;
	}

	if(buckets <= 0){
		printf("linked_hash_set_init() err args:buckets=%d, smaller than zero\n", buckets);
		return -1;
	}

	int i;

	lhset->table = (List *)malloc(buckets * sizeof(List)); //分配多个链表空间
	if(lhset->table == NULL) {
		printf("linked_hash_set_init() err malloc null\n");
		return -2;
	}

	for (i = 0 ; i < lhset->buckets; i++){
		list_init(&lhset->table[i], destroy); //多个链表初始化
	}

	lhset->buckets = buckets;
	lhset->h  = h;
	lhset->match = match;
	lhset->destroy = destroy;
	lhset->size = 0;

	return 0;
}

/**
 * @function 主要功能是剔除每个桶中的元素,释放有初始化分配的内存空间,
 * 					如果destroy不为空的话,释放每一个元素的空间
 * @param lhset: 被销毁的表
 */
void linked_hash_set_destroy(Linked_Hash_Set *lhset){
	int i;
	for(i = 0 ; i < lhset->buckets; i++){
		list_destroy(&lhset->table[i]);
	}

	free(lhset->table);

	memset(lhset, 0 ,sizeof(Linked_Hash_Set));

	return ;
}

/**
 * @function :插入数据,在函数内部,
 * 		首先调用linked_hash_set_lookup()查看是有已经在集合中存在相同的元素,
 * 		没有,将新元素的键散列,然后将新元素插入到哈希表中
 * @param lhset:
 * @param data:
 */
int linked_hash_set_insert(Linked_Hash_Set *lhset, const void *data){
	void *tmp;
	int bucket, retval;

	//如果在hash表中已经存在,则不需要任何处理
	tmp = (void *)data;
	if(linked_hash_set_lookup(lhset,&tmp) == 0){
		return 1;
	}

	/*hash the key*/
	bucket = lhset->h(data) % lhset->buckets;

	// retval = list_ins_next(&(lhset->table[bucket]), NULL, data);
	retval = list_add(&(lhset->table[bucket]), tmp);
	if(retval == 0){
		lhset->size++;
	}

	return retval;
}

/**
 * @function : 散列元素的键,查找与元素相匹配的桶,然后调用list_rem_next删除元素
 */
int linked_hash_set_remove(Linked_Hash_Set *lhset, void **data){
	ListElmt *elmt, *prev;
	prev = NULL;
	int bucket = lhset->h(*data) % lhset->buckets;

	List *theList = &(lhset->table[bucket]);
	for(elmt = list_head(theList); elmt != NULL ; elmt = list_next(elmt)){
		if(lhset->match(*data, list_data(elmt))){
			//找到了这个元素
			if(list_rem_next(theList, prev, data) == 0){
				lhset->size--;
				return 0;
			}else{
				printf("linked_hash_set_remove() : list_rem_next() err\n");
				return -1;
			}
		}
		prev = elmt;
	}

	printf("linked_hash_set_remove()  donot find the data\n");
	return -1;
}

/**
 * @function : 查找元素,并获取指向删除元素的指针
 */
int linked_hash_set_lookup(const Linked_Hash_Set *lhset, void **data){

	ListElmt * elmt;
	int bucket;

	/*hash the key*/
	bucket = lhset->h(*data) % lhset->buckets;

	List *theList = &(lhset->table[bucket]);
	for(elmt = list_head(theList); elmt != NULL ; elmt = list_next(elmt)){
		if(lhset->match(*data, list_data(elmt))){
			 *data = list_data(elmt);
			 return 0;
		}
	}

	// printf("linked_hash_set_lookup() donot find the data\n");
	return -1;
}

void linked_hash_set_map(Linked_Hash_Set * lhset, int (*visit)(const void *value)) {
    int list_size = lhset->buckets;
    for (int i = 0; i < list_size; i++) {
        List *list = &(lhset->table[i]);
        ListElmt *elmt;
        for (elmt = list_head(list); elmt != NULL; elmt = list_next(elmt)) {
            visit(elmt->data);
        }
    }
}