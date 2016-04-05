//
// Created by wangxn on 2016/4/1.
//
#include <stdio.h>
#include "../lib/bitree/bitree.h"
#include "student/student.h"
#include "test.h"
#include "../lib/bitree/bitree_traverse.h"

void bitree_test(){
    BiTree bitree;
    bitree_init(&bitree, NULL, (void *)studn_destroy);


    bitree_ins_left(&bitree, NULL, (void *)studn_get_init(1,"zhangsan",1, 32, 9));
    bitree_ins_left(&bitree, bitree_root(&bitree), studn_get_init(2,"lisi",1, 32, 8));
    bitree_ins_right(&bitree,bitree_root(&bitree), studn_get_init(4,"zhangquandan",1, 32, 10));
    bitree_ins_left(&bitree, bitree_root(&bitree)->left, studn_get_init(3,"wangdazhui",1, 32, 9));
    bitree_ins_left(&bitree, bitree_root(&bitree)->left->left, studn_get_init(5,"zhangfei",1, 32, 9));
    bitree_ins_right(&bitree, bitree_root(&bitree)->left->left->left,studn_get_init(6,"liucuihua",0, 22, 11));



    printf("%s%d\n", "bitree size :", bitree_size(&bitree));

    bitree_rem_left(&bitree, bitree_root(&bitree)->left->left);

    printf("%s%d\n", "after remove a node , bitree size :", bitree_size(&bitree));


    BiTree bitree2;
    bitree_init(&bitree2, NULL, (void *)studn_destroy);


    bitree_ins_left(&bitree2, NULL, (void *)studn_get_init(7,"zhangsan",1, 32, 9));
    bitree_ins_left(&bitree2, bitree_root(&bitree2), studn_get_init(8,"lisi",1, 32, 8));
    bitree_ins_right(&bitree2,bitree_root(&bitree2), studn_get_init(9,"zhangquandan",1, 32, 10));
    bitree_ins_left(&bitree2, bitree_root(&bitree2)->left, studn_get_init(10,"wangdazhui",1, 32, 9));
    bitree_ins_left(&bitree2, bitree_root(&bitree2)->left->left, studn_get_init(11,"zhangfei",1, 32, 9));
    bitree_ins_right(&bitree2, bitree_root(&bitree2)->left->left->left,studn_get_init(12,"liucuihua",0, 22, 11));

    printf("%s%d\n", "bitree2 size :", bitree_size(&bitree2));

    BiTree merge;
    bitree_merge(&merge, &bitree, &bitree2,studn_get_init(13,"liucuihua",0, 22, 11));
    printf("%s%d\n", "merge bitree size :", bitree_size(&merge));


    List mlist;
    list_init(&mlist, NULL);
    preorder(merge.root, &mlist);
    printf("%s%d\n", "merge and the order list size:", mlist.size);
    printf("%s\n", "preorder() merge bitree, and then show all elements:");
    list_resetIterator(&mlist);
    while(list_hasNext(&mlist)){
    	list_moveToNext(&mlist);
    	Student * data;
    	list_iterator(&mlist, (void **)&data);
    	studn_print(data);
    }

    bitree_destroy(&bitree);
    bitree_destroy(&bitree2);
    bitree_destroy(&merge);
    return;
}



void bitree_test2(){
    BiTree bitree;
    bitree_init(&bitree, (void *)studn_compare, (void *)studn_destroy);

    bitree_ins(&bitree, studn_get_init(4,"zhangquandan",1, 32, 10));
    bitree_ins(&bitree, studn_get_init(3,"wangdazhui",1, 32, 9));
    bitree_ins(&bitree, studn_get_init(1,"zhangsan",1, 32, 9));
    bitree_ins(&bitree, studn_get_init(2,"lisi",1, 32, 8));
    bitree_ins(&bitree, studn_get_init(5,"zhangfei",1, 32, 9));
    bitree_ins(&bitree, studn_get_init(6,"liucuihua",0, 22, 11));

    printf("%s%d\n", "bitree size :", bitree_size(&bitree));
    bitree_rem_left(&bitree, bitree_root(&bitree)->left);
    printf("%s%d\n", "after remove a node , bitree size :", bitree_size(&bitree));

    bitree_destroy(&bitree);
    return;
}

