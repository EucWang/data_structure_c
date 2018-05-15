//
// Created by wangxn on 2018/5/15.
//

#include "testSimpleList.h"


void testSimpleListAdd(){

    ListNode* node = create_node(1);
    ListNode* node1 = create_node(2);
    ListNode* node2 = create_node(3);
    ListNode* node3 = create_node(4);

    add_to_simple_list(node, node1);
    add_to_simple_list(node, node2);
    add_to_simple_list(node, node3);

    print_simple_list(node);


//    del_simple_list(&node2);

//    removeNthFromEnd(head, 1);
    ListNode* nodeNew = reverseList(node);
    print_simple_list(nodeNew);
}