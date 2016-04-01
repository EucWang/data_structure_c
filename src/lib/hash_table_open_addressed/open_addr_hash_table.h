//
// Created by wangxn on 2016/4/1.
// 开地址hash表, 使用双散列算法
//

#ifndef OPEN_ADDR_HASH_TABLE_OPEN_ADDR_HASH_TABLE_H
#define OPEN_ADDR_HASH_TABLE_OPEN_ADDR_HASH_TABLE_H

typedef struct open_addr_htable_{
    int positions;   //哈希表中可以分配的槽位数量, 容量

    /**
     * 指针vacated将被初始化来指向一个特殊的地址空间, 来指明这个特殊地址上曾经删除一个元素
     * 主要是用来辅助删除元素
     */
    void *vacated;

    int (*h1)(const void *key); //第一次计算hash值的方法,第一次散列
    int (*h2)(const void *key); //第二次计算hash值的方法,第二次散列

    int (*match)(const void *key1, const void *key2); //子元素比较的函数
    void (*destroy)(void *data);                      //子元素销毁的函数
    int size;       //表中现有元素的个数
    void **table;   //存储元素的数组
}OPEN_ADDR_HTABLE;

/**
 * hash表初始化
 */
int oa_htable_init(OPEN_ADDR_HTABLE *open_addr_htable,
                    int positions,
                    int (*h1)(const void *key),
                    int (*h2)(const void *key),
                    int (*match)(const void *key1, const void *key2),
                    void (*destroy)(void *data));

/**
 * hash表的销毁
 */
void oa_htable_destroy(OPEN_ADDR_HTABLE *open_addr_htable);

/**
 * hash表的数据插入
 */
int oa_htable_insert(OPEN_ADDR_HTABLE *open_addr_htable, const void *data);

/**
 * hash表的数据移除
 */
int oa_htable_remove(OPEN_ADDR_HTABLE *open_addr_htable, void **data);

/**
 * hash表的数据查找
 */
int oa_htable_lookup(const OPEN_ADDR_HTABLE *open_addr_htable, void **data);

/**
 * hash表中现有子元素的个数
 */
#define oa_htable_size(open_addr_htable) ((open_addr_htable)->size)

#endif //OPEN_ADDR_HASH_TABLE_OPEN_ADDR_HASH_TABLE_H
