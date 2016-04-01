//
// Created by wangxn on 2016/4/1.
//

#include <stdio.h>
#include "set_cover_test/set_cover_test.h"
#include "../lib/set/set.h"
#include "../lib/set_cover/set_cover.h"

int test_set_conver(){
    Skill skill_arr[12] = {
            *skill_get_init(0, "a_da_peng_zhan_chi", "level3"),
            *skill_get_init(1, "b_hen_sao_qian_jun", "level2"),
            *skill_get_init(2, "c_tie_sha_zhang", "level1"),

            *skill_get_init(3, "d_zong_yun_ti", "level5"),
            *skill_get_init(4, "e_da_gou_gun", "level4"),
            *skill_get_init(5, "f_bing_bu_qing_yun", "level3"),

            *skill_get_init(6, "g_po_fu_chen_zhou", "level2"),
            *skill_get_init(7, "h_ti_hu_guan_ding", "level1"),
            *skill_get_init(8, "i_lu_ye_gui_gen", "level3"),

            *skill_get_init(9, "j_tai_zu_chang_quan", "level4"),
            *skill_get_init(10, "k_tai_ji_quan", "level5"),
            *skill_get_init(11, "l_bai_qing_xi", "level1"),
    };

    Set members;
    set_init(&members, (void *)skill_match, NULL);
    int i;
    for(i = 0; i<12; i++){
        set_insert(&members, &skill_arr[i]);
    }

    printf("#######177###########\n");
    /***************************************/
    Set set1;
    set_init(&set1, (void *)skill_match, NULL);
    for(i = 0; i<4; i++){
        set_insert(&set1, &skill_arr[i]);
    }
    KSet *kset1 = kset_get_init("athlete1",&set1);
//    set_destroy(&set1);
    /*******************187********************/
    Set set2;
    set_init(&set2, (void *)skill_match, NULL);
    for(i = 4; i<9; i++){
        set_insert(&set2, &skill_arr[i]);
    }
    KSet *kset2 = kset_get_init("athlete2",&set2);
//    set_destroy(&set2);
    /********************195*******************/
    Set set3;
    set_init(&set3, (void *)skill_match, NULL);
    for(i = 9; i<12; i++){
        set_insert(&set3, &skill_arr[i]);
    }
    KSet *kset3 = kset_get_init("athlete3",&set3);
//    set_destroy(&set3);
    /***************************************/
    Set set4;
    set_init(&set4, (void *)skill_match, NULL);
    set_insert(&set4, &skill_arr[0]);
    set_insert(&set4, &skill_arr[4]);
    KSet *kset4 = kset_get_init("athlete4",&set4);
//    set_destroy(&set4);
    /***************************************/
    Set set5;
    set_init(&set5, (void *)skill_match, NULL);
    set_insert(&set5, &skill_arr[1]);
    set_insert(&set5, &skill_arr[5]);
    set_insert(&set5, &skill_arr[6]);
    KSet *kset5 = kset_get_init("athlete5",&set5);
//    set_destroy(&set5);
    /***************************************/
    Set set6;
    set_init(&set6, (void *)skill_match, NULL);
    set_insert(&set6, &skill_arr[1]);
    set_insert(&set6, &skill_arr[5]);
    set_insert(&set6, &skill_arr[6]);
    KSet *kset6 = kset_get_init("athlete6",&set6);
//    set_destroy(&set6);
    /***************************************/
    Set set7;
    set_init(&set7, (void *)skill_match, NULL);
    set_insert(&set7, &skill_arr[11]);
    KSet *kset7 = kset_get_init("athlete7",&set7);
//    set_destroy(&set7);
    /***************************************/

    printf("##########234########\n");
    Set athletes;
    set_init(&athletes, (void *)kset_match, NULL);
    set_insert(&athletes, kset1);
    set_insert(&athletes, kset2);
    set_insert(&athletes, kset3);
    set_insert(&athletes, kset4);
    set_insert(&athletes, kset5);
    set_insert(&athletes, kset6);
    set_insert(&athletes, kset7);

    printf("########245##########\n");
    Set covering;
    set_init(&covering, (void *)kset_match, NULL);
    printf("########248##########\n");
    kset_cover(&members, &athletes, &covering);

    printf("########250##########\n");
    printf("choose out athletes:\n");

    set_resetIterator(&covering);
    while(set_hasNext(&covering)){
        KSet *data;
        set_moveToNext(&covering);
        set_iterator(&covering, (void **)&data);
        printf("%s\n", (char *)data->key);
    }
    printf("##################\n");
    return 0;
}