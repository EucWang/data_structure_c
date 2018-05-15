//
// Created by wangxn on 2018/5/14.
//

#ifndef DATA_STRUCTURE_C_LISTNODE_H
#define DATA_STRUCTURE_C_LISTNODE_H

typedef struct ListNode_ {
    int val;
    struct ListNode_* next;
}ListNode;

ListNode* create_node(int val);

void add_to_simple_list(ListNode* head, ListNode* addItem);

void del_simple_list(ListNode* node);

void print_simple_list(ListNode* head);

ListNode* removeNthFromEnd(ListNode* head, int n);

ListNode* reverseList(ListNode* head);

#endif //DATA_STRUCTURE_C_LISTNODE_H
