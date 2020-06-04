/*
 * sort.c
 *
 *  Created on: 2016年4月9日
 *      Author: wangxinnian
 */
#include <math.h>
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
int insert_sort(void *data, int size, int esize, int (*compare)(const void *key1, const void *key2)) {

    char *a = data;
    void *key;
    int i, j;

    //为key分配一个数组元素大小的空间
    if ((key = (char *) malloc(esize)) == NULL) {
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
        while (i >= 0 && compare(&a[i * esize], key) > 0) {
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
static int compare_int(const void *int1, const void *int2) {

    if (*(const int *) int1 > *(const int *) int2) {
        return 1;
    } else if (*(const int *) int1 > *(const int *) int2) {
        return -1;
    } else {
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
                     int (*compare)(const void *key1, const void *key2)/*比较函数*/) {

    char *a = (char *) data;
    void *pval;
    void *tmp;
    int r[3];

    if ((pval = malloc(sizeof(esize))) == NULL) {
        printf("%s\n", "static partition() fail, call malloc fail");
        return -1;
    }

    if ((tmp = malloc(sizeof(esize))) == NULL) {
        printf("%s\n", "static partition() fail, call malloc fail");
        free(pval);
        return -1;
    }

    //获取三个随机数值，放入到临时数组r中
    r[0] = (rand() % (k - i + 1)) + i;
    r[1] = (rand() % (k - i + 1)) + i;
    r[2] = (rand() % (k - i + 1)) + i;

    //对这3个随机数进行排序，
    insert_sort(r, 3, sizeof(int), compare_int);
    //获取的随机数的中间值作为数组中的索引值，这个值必然在i和k之间，将数组中的这个值复制给pval
    memcpy(pval, &a[r[1] * esize], esize);

    i--;
    k++;

    //在分的区块内遍历，交叉遍历
    //比较k索引处的值和分割值，大于的情况下k左移，直到不大于分割值为止
    //比较i索引处的值和分割值，小于的情况下i右移，直到不小于分割值为止
    //移动完成之后，如果i依然在k的右边，交换i和k索引处的值
    while (1) {
        do {
            k--;
        } while (compare(&a[k * esize], pval) > 0);

        do {
            i++;
        } while (compare(&a[i * esize], pval) < 0);

        if (i >= k) {
            break;
        } else {
            //交换i和k的值
            memcpy(tmp, &a[i * esize], esize);
            memcpy(&a[i * esize], &a[k * esize], esize);
            memcpy(&a[k * esize], tmp, esize);
        }
    }

    printf("%s\n", "partition success");

    free(pval);
//	free(tmp);//这里释放free时会导致堆栈垃圾
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
               int i,
               int k,
               int (*compare)(const void *key1, const void *key2)) {

    int j;

    while (i < k) {
        //对数组进行区块划分，并进行大体上的排序，获得分割值的索引值
        if ((j = partition(data, esize, i, k, compare)) < 0) {
            return -1;
        }

        //递归调用本函数，对区块右边进行排序
        if (quick_sort(data, size, esize, i, j, compare) < 0) {
            return -1;
        }

        //将起始值设置为分割值的索引值+1, 对区块的左边进行排序
        i = j + 1;
    }
    return 0;
}

static int merge(void *data,
                 int esize,
                 int i, int j, int k,
                 int (*compare)(const void *key1, const void *key2)) {
    char *a = data;
    char *m;
    int ipos, jpos, mpos;

    ipos = i;
    jpos = j + 1;
    mpos = 0;

    //为结果数组分配内存空间
    if((m = (char *)malloc(esize * ( (k - i) + 1))) == NULL) {
        printf("%s\n", "static merge() fail, call malloc fail");
        return -1;
    }

    //只要两个堆有一个没有遍历完,就继续遍历
    while (ipos <= j || jpos <= k) {
        //在第一个堆已经遍历完成的情况下,只要第二个堆没有遍历完,就将第二个堆中的所有元素复制到目标数组中
        if (ipos > j) {
            while (jpos <= k) {
                memcpy(&m[mpos * esize], &a[jpos * esize], esize);
                jpos++;
                mpos++;
            }
            continue;
        } else if (jpos > k) { //或者在第二个堆遍历完成,但是第一个堆还没有遍历完,将第一个堆的所有元素复制到目标数组中
            while (ipos <= j) {
                memcpy(&m[mpos * esize], &a[ipos * esize], esize);
                ipos++;
                mpos++;
            }
            continue;
        }

        //比较第一个堆和第二个堆中的指定索引处的值,小值复制到目标数组中
        //对应的索引移动位置
        if (compare(&a[ipos * esize], &a[jpos * esize]) < 0) {
            memcpy(&m[mpos * esize], &a[ipos * esize], esize);
            ipos++;
            mpos++;
        } else {
            memcpy(&m[mpos * esize], &a[jpos * esize], esize);
            jpos++;
            mpos++;
        }
    }

    //将结果数组复制到原来的数组中
    memcpy(&a[i * esize], m, esize * ((k - i) + 1));
    free(m);
    return 0;
}


/**
 * 归并排序
 * 在所有情况下都能达到快速排序的平均性能,但是需要额外的存储空间
 * 原理: 将数据集对半分堆,对每一堆再次对半分堆,重复过程直到每堆只有一个元素,
 *        然后将堆两两合并,合并的堆就可以是两个有序堆的合集,也是有序的.合并过程持续到完成
 * @param data : 数组
 * @param size : 数组大小
 * @param esize : 数组每个元素内存占空间大小
 * @param i :    索引开始,默认为0
 * @param k :    索引结束, 默认为 size - 1
 * @param compare :  比较函数
 *
 * 关键是如何将两个有序集合合并为一个有序集,这个有函数merge完成
 * 其将data中i到j之间的数据集与j+1到k之间的数据集合并成一个i到k的有序数据集
 */
int merge_sort(void *data,
               int size,
               int esize,
               int i,
               int k,
               int (*compare)(const void *key1, const void *key2)) {

    int j;
    if (i < k) {
        j = (int)((i + k - 1) / 2);

        if (merge_sort(data, size, esize, i, j, compare) < 0) {
            printf("%s\n", "recycle call merge_sort() fail");
            return -1;
        }

        if (merge_sort(data, size, esize, j + 1, k, compare) < 0) {
            printf("%s\n", "recycle call merge_sort() fail");
            return -1;
        }

        if (merge(data, esize, i, j, k, compare) < 0) {
            printf("%s\n", "merge_sort fail, call merge fail");
            return -1;
        }
    }
    return 0;
}



/**
 * 计数排序
 * 线性排序,速度快,非常稳定,稳定度排序能使具有相同数值的元素有相同的排序,就像他们在原始集合中表现出来的一样
 * 通过计算一个集合中元素出现的次数来确定集合如何排列
 * 计数排序不需要进行元素比较
 * 计数排序有一定的局限性:
 *      它只能用于整形或者那些可以用整形来表示的数据集合,这是因为计数排序利用一个数组的索引来记录元素出现的次数,
 *      比如,如果整数3出现过4次,那么4将存储到数组索引为3的位置上.
 *      同时,我们还需要知道集合中最大整数的值,以便于为数组分配足够的空间
 *
 * @param data : 整数的数组
 * @param size : data中元素的个数
 * @param k    : 为data中最大的整数+1
 */
int count_sort(int *data, int size, int k){
    int *counts;
    int *temp;
    int i, j;

    if ((counts = (int *) malloc(k * sizeof(int))) == NULL) {
        printf("%s\n", "count_sort fail, call malloc fail");
        return -1;
    }

    if ((temp = (int *) malloc(size * sizeof(int))) == NULL) {
        printf("%s\n", "count_sort fail, call malloc fail");
        return -1;
    }

    for (i = 0; i < k; ++i) {
        counts[i] = 0;
    }

    for (j = 0; j < size; ++j) {
        counts[data[j]] = counts[data[j]] + 1;
    }

    // adjust each count to reflect the counts before it.
    for (i = 1; i < k; ++i) {
        counts[i] = counts[i] + counts[i - 1];
    }

    //use teh counts to position each element where it belongs
    for (j = size - 1; j >= 0; --j) {
        temp[counts[data[j]] - 1] = data[j];
        counts[data[j]] = counts[data[j]] - 1;
    }

    //prepare to pass back the sorted data
    memcpy(data, temp, size * sizeof(int));

    free(counts);
    free(temp);
    return 0;
}



/**
 * 基数排序
 * 线性排序算法,
 * 将数据按位分开,并从数据的最低有效位到最高有效位进行比较,一次排序,从而得到有序数据集合
 * 基数排序会用到计数排序,因为对于基数排序,除了稳定性,他还是一种线性算法,切必须知道每一位可能的最大整数值
 *
 * 基数排序不局限于对整形数据进行排序,只要能把元素分割成整形数,就可以使用基数排序
 * 例如可以对一个以2的8次方为基数 字符串进行基数排序,或者对一个64位的整数按4位以2的16次方为基数的值进行排序
 * 具体选择什么值为基数取决于数据本身, 同时考虑空间限制,需要将pn + pk最小化
 * (其中p为每个元素的位数,n为元素的个数,k为基数). 一般使k小于等于n
 *
 * @param data:
 * @param size: data中整数的个数
 * @param p:    指定每个整数包含的位数,十进制的位数
 * @param k:    k指定基数, 一般使k小于等于size
 *
 */
int radix_sort(int *data, int size, int p, int k) {
    int *counts, *temp;
    int index, pval, i, j, n;

    //为counts分配内存空间,counts的数组大小由基数指定
    if((counts = (int *)malloc(k * sizeof(int))) == NULL) {
        return -1;
    }
    //分配一个和data同样大小的数组,作为数据的临时存放区
    if((temp = (int *)malloc(size * sizeof(int))) == NULL) {
        return -1;
    }

    //从低位到高位依次循环
    for (n = 0; n < p; ++n) {
        for (i = 0; i < k; ++i) { // 初始化counts数组
            counts[i] = 0;
        }

        //k的n次方的int数值
        pval = (int)pow((double)k, (double)n);

        //计数排序
        for (j = 0; j < size; ++j) {
            index = (int)(data[j]/pval) % k;
            counts[index] = counts[index] + 1;
        }

        for (i = 1; i < k; ++i) {
            counts[i] = counts[i] + counts[i - 1];
        }

        for (j = size - 1; j >= 0 ; --j) {
            index = (int)(data[j] / pval) % k;
            temp[counts[index] - 1] = data[j];
            counts[index] = counts[index] - 1;
        }

        memcpy(data, temp, size * sizeof(int));
    }

    free(counts);
    free(temp);
    return 0;
}



/**
 * 只能对有序数据集合进行操作.
 * 二分查找能够应用到任何类型的数据,只要这些数据只要能够排序
 * 相对于查找,维护一个有序数据集合的代价更高.
 * 此外,元素必须存储在连续的空间中.
 * 因此,当待搜索的集合是相对静态的数据集时, 此时使用二分查找法是最好的选择
 *
 * @param sorted: 排好序的数组
 * @param target: 数组中的目标元素
 * @param size:   数组大小
 * @param esize:  数组元素大小
 * @param compare: 数组元素比较函数
 * 成功,返回target的索引值,否则返回-1
 */
int bisearch(void *sorted,
             void *target,
             int size,
             int esize,
             int (*compare)(const void *key1, const void *key2)) {

    int left, middle, right;
    right = size - 1;

    while (left <= right) {
        middle = (left + right) / 2;

        switch (compare(((char *)sorted + (esize * middle)),target)) {
            case -1:
                left = middle + 1;
                break;
            case 1:
                right = middle - 1;
                break;
            case 0:
                return middle;
                break;
        }
    }
    return -1;
}



