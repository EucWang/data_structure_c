/*
 * sort.c
 *
 *  Created on: 2016年4月9日
 *      Author: wangxinnian
 */

#include <string.h>
#include <stdlib.h>
#include "sort.h"

/**
 * 插入排序
 * 基本原理: 就是每次从没有排序的数据集中取出一个元素,插入已经排好序的数据集中
 *
 * 虽然实现插入排序用到连续的存储空间,但是他也可以用链表来实现,并且效率不差(并不是所有的排序都可以使用链表来实现)
 *
 * 操作方式:
 *      使用一个嵌套循环.
 *          外部循环使用标号j来控制元素,使元素从无序数据集中插入有序数据集中.
 *          由于待插入的元素总是会被插入有序数据集的右边,
 *          因此也可以认为j是data中分隔有序元素集合和无序元素集合的界线
 *          对于每个处于位置j的元素,都会使用变量i来向后查找元素将要放置的位置.
 *          当向后查找数据时,每个处于位置i的元素都要向后移动一位,以保证预留出足够的空间来插入新元素.
 *          一旦到达无序数据集的尾部,data就是一个有序数据集了
 *
 *  @param: data  连续的存储空间
 *  @param: size  空间的数据数量
 *  @param: esize 单个数据占据内存的空间大小
 *  @param: compare
 */
int insert_sort(void *data, int size, int esize, int (*compare)(const void *key1, const void *key2)){

	char *a = data;
	void *key;
	int i, j;

	//为key分配一个数组元素大小的空间
	if ((key = (char *)malloc(esize)) == NULL) {
		printf("%s\n", "issort() fail , call malloc fail");
		return -1;
	}

	//从第二个数组元素开始遍历
	for (j = 1; j < size; j++) {
		//将数组元素数值复制给key指向的空间
		memcpy(key, &a[j * esize], esize);

		i = j - 1;  //i是j左边的一个元素

		// 从j左边的第一个位置开始向数组起始位置处遍历
		//i位置的元素都和key进行比较，如果i位置的元素大于key的值，则将i位置元素的数值复制给i+1位置,这个过程会覆盖掉原来j 的数值
		while (i >= 0 && compare(&a[i * esize],  key) > 0) {
			memcpy(&a[(i + 1) * esize], &a[i * esize], esize);
			i--;
		}

		//循环完之后i的数值为0,将原来j位置的数值覆盖掉移动停止的位置的元素
		memcpy(&a[(i + 1) * esize], key, esize);
	}

	free(key);
	return 0;
}
