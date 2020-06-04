//
// Created by wangxn on 2018/5/15.
//

#include <stdio.h>
#include "testSimpleList.h"

void testMerge2(){
    //第一个链表
    ListNode* node = create_node(2);
    printf("the first list :\n");
    print_simple_list(node);

    //第二个链表
    ListNode* node2 = create_node(1);
    printf("the second list :\n");
    print_simple_list(node2);

    //合并之后的第三个链表
    ListNode* node3 = mergeTwoLists(node, node2);
    printf("the merged list:\n");
    print_simple_list(node3);
}


void testMerge() {
    //第一个链表
    ListNode* node = create_node(1);
    ListNode* node_1 = create_node(2);
    ListNode* node_3 = create_node(4);
    add_to_simple_list(node, node_1);
    add_to_simple_list(node, node_3);
    printf("the first list :\n");
    print_simple_list(node);

    //第二个链表
    ListNode* node2 = create_node(1);
    ListNode* node2_1 = create_node(3);
    ListNode* node2_2 = create_node(4);
    add_to_simple_list(node2, node2_1);
    add_to_simple_list(node2, node2_2);
    printf("the second list :\n");
    print_simple_list(node2);

    //合并之后的第三个链表
    ListNode* node3 = mergeTwoLists(node, node2);
    printf("the merged list:\n");
    print_simple_list(node3);
}



void testDel(){

    ListNode* node = create_node(1);
    ListNode* node1 = create_node(2);
    ListNode* node2 = create_node(3);
    ListNode* node3 = create_node(4);

    add_to_simple_list(node, node1);
    add_to_simple_list(node, node2);
    add_to_simple_list(node, node3);

    print_simple_list(node);

    del_simple_list(node2);
    print_simple_list(node);

}

void testReverse(){
    ListNode* node = create_node(1);
    ListNode* node1 = create_node(2);
    ListNode* node2 = create_node(3);
    ListNode* node3 = create_node(4);

    add_to_simple_list(node, node1);
    add_to_simple_list(node, node2);
    add_to_simple_list(node, node3);

    print_simple_list(node);

    ListNode* nodeNew = reverseList(node);
    print_simple_list(nodeNew);

}

void testRemoveFromEnd(){
    ListNode* node = create_node(1);
    ListNode* node1 = create_node(2);
    ListNode* node2 = create_node(3);
    ListNode* node3 = create_node(4);

    add_to_simple_list(node, node1);
    add_to_simple_list(node, node2);
    add_to_simple_list(node, node3);

    print_simple_list(node);

    ListNode* nodeNew = reverseList(node);
    print_simple_list(nodeNew);
}

void testPalindrome(){
    //测试1
    ListNode* node11 = create_node(1);
    ListNode* node12 = create_node(2);
    ListNode* node13 = create_node(3);
    ListNode* node14 = create_node(4);
    add_to_simple_list(node11, node12);
    add_to_simple_list(node11, node13);
    add_to_simple_list(node11, node14);

    print_simple_list(node11);
    bool retVal = isListPalindrome(node11);
    printf("list is palindrome or not ? %d", retVal);
    //测试2
    ListNode* node21 = create_node(1);
    ListNode* node22 = create_node(2);
    ListNode* node23 = create_node(2);
    ListNode* node24 = create_node(1);
    add_to_simple_list(node21, node22);
    add_to_simple_list(node21, node23);
    add_to_simple_list(node21, node24);

    print_simple_list(node21);
    bool retVal2 = isListPalindrome(node21);
    printf("list is palindrome or not ? %d", retVal2);
    //测试3
    ListNode* node31 = create_node(1);
//    ListNode* node32 = create_node(2);
    ListNode* node33 = create_node(2);
    ListNode* node34 = create_node(1);
//    add_to_simple_list(node31, node32);
    add_to_simple_list(node31, node33);
    add_to_simple_list(node31, node34);

    print_simple_list(node31);
    bool retVal3 = isListPalindrome(node31);
    printf("list is palindrome or not ? %d", retVal3);
}

void testHasCycle() {

    ListNode* node11 = create_node(1);
    ListNode* node12 = create_node(2);
    ListNode* node13 = create_node(3);
    ListNode* node14 = create_node(4);
    add_to_simple_list(node11, node12);
    add_to_simple_list(node11, node13);
    add_to_simple_list(node11, node14);
    print_simple_list(node11);

    bool retVal = hasCycle(node11);
    printf("list has cycle or not ? %d", retVal);

    ListNode* node21 = create_node(1);
    ListNode* node22 = create_node(2);
    ListNode* node23 = create_node(3);
    ListNode* node24 = create_node(4);
    add_to_simple_list(node21, node22);
    add_to_simple_list(node21, node23);
    add_to_simple_list(node21, node24);
    print_simple_list(node21);
    node24->next = node21;

    bool retVal2 = hasCycle(node21);
    printf("list has cycle or not ? %d", retVal2);
}

void testSimpleListAdd(){

//    testDel();
//    testRemoveFromEnd();
//    testReverse();
//    testMerge();
//    testMerge2();
//    testPalindrome();
    testHasCycle();
}
