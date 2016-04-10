/*
 * sort.c
 *
 *  Created on: 2016年4月9日
 *      Author: wangxinnian
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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

/**
 * 比较2个整数integer型数据的值
 */
static int compare_int(const void * int1, const void * int2){

	if(*(const int *)int1 > *(const int *)int2){
		return 1;
	}else if(*(const int *)int1 > *(const int *)int2) {
		return -1;
	}else{
		return 0;
	}
}

/**
 * 随机选择三个元素,然后选择三个元素中的中间值.
 * 这个中间值就是作为快速排序的分割值
 * 然后对区块进行交叉遍历，所有分割值左边的都小于分割值，所有分割值右边的都大于分割值
 * 返回分割值的索引值
 */
static int partition(void *data,  /*数组数据*/
		int esize,   /*单个数组元素内存空间大小*/
		int i,  /*起始索引*/
		int k,   /*结束索引*/
		int (*compare)(const void *key1, const void *key2)/*比较函数*/){

	char *a = (char *)data;
	void *pval, *temp;
	int r[3];

	if((pval = malloc(sizeof(esize))) == NULL){
		printf("%s\n", "static partition() fail, call malloc fail");
		return -1;
	}

	if((temp = malloc(sizeof(esize))) == NULL){
		printf("%s\n", "static partition() fail, call malloc fail");
		return -1;
	}

	//获取三个随机数值，放入到临时数组r中
	r[0] = (rand() % (k - i + 1)) + i;
	r[1] = (rand() % (k - i + 1)) + i;
	r[2] = (rand() % (k - i + 1)) + i;

	//对这3个随机数进行排序，
	insert_sort(r, 3, sizeof(int), compare_int);
	//获取的随机数的中间值作为数组中的索引值，这个值必然在i和k之间，将数组中的这个值复制给pval
	memcpy(pval, &a[r[1]*esize], esize);

	i--;
	k++;

	//在分的区块内遍历，交叉遍历
	//比较k索引处的值和分割值，大于的情况下k左移，直到不大于分割值为止
	//比较i索引处的值和分割值，小于的情况下i右移，直到不小于分割值为止
	//移动完成之后，如果i依然在k的右边，交换i和k索引处的值
	while(1){
		do{
			k--;
		}while(compare(&a[k*esize], pval) > 0);

		do{
			i++;
		}while(compare(&a[i*esize], pval) < 0);

		if( i >= k){
			break;
		}else{
			//交换i和k的值
			memcpy(temp, &a[i*esize],esize);
			memcpy(&a[i*esize], &a[k*esize],esize);
			memcpy(&a[k*esize],temp,esize);
		}
	}

	printf("%s\n", "partition success");

	printf("%s\n", "begin free temp memory");
	free(pval);
	free(temp);
	printf("%s\n", "end free temp memory");

	return k;
}



/**
 * 快速排序
 *
 *  在处理到大型数据集时,快速排序是一个比较好的选择
 *  快速排序是一种分治排序算法
 *      分:  设定一个分割值并将数据分为两部分
 *      治:  分别在两部分用递归的方式继续使用快速排序法
 *      合:  对分割部分排序直至完成
 *
 *  快速排序的效率,关键取决于如何选择分割值
 *
 *  选择分割值的一种行之有效的方法是通过随机选择法来选取.
 *  同时,还可以改进这种随机选择方法,方法是首先随机选择三个元素,然后选择三个元素中的中间值.
 *  这就是所谓的中位数方法, 可以保证平均情况下的性能.
 *  由于这种分割方法依赖随机数的统计特性,所以快速排序是随机算法的一个好例子
 *
 * 操作方式:
 *      通过函数partition来分割data中处于i和k之间的元素(i<k)
 *
 *      首先选取一个分割值,一旦选定分割值,就将k往data的左边移动,直到找到一个小于或者等于分割值的元素.
 *      这个元素属于左边分区.
 *      然后,将i往右边移动,直到找到一个大于或等于分割值的元素
 *      这个元素属于右边分区.
 *      一旦找到的两个元素处于错误的位置,就交换他们的位置
 *      重复这个过程,直到i和k重合
 *
 *      递归:
 *      初始时,i为0, k为size-1.
 *
 * @param: data  数组
 * @param: size  数组中的元素个数
 * @param: esize 每个元素的大小
 * @param: i     i和k定义当前进行排序的两个部分,其值分别初始化为0 和size-1
 * @param: k
 * @param: compare
 * 当qksort返回时,data包含已经排序的元素
 */
int quick_sort(void *data,
		int size,
		int esize,
		int i ,
		int k,
		int (*compare)(const void *key1, const void *key2)){

	int j;

	while(i<k){
		//对数组进行区块划分，并进行大体上的排序，获得分割值的索引值
		if((j = partition(data, esize, i, k , compare)) < 0){
			return -1;
		}

		//递归调用本函数，对区块右边进行排序
		if(quick_sort(data,size, esize, i, j, compare) < 0){
			return -1;
		}

		//将起始值设置为分割值的索引值+1, 对区块的左边进行排序
		i = j + 1;
	}
	return 0;
}

