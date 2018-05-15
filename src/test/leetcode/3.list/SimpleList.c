//
// Created by wangxn on 2018/5/15.
//

#include "SimpleList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

ListNode* create_node(int val) {
    ListNode* retVal = malloc(sizeof(ListNode));
    retVal->val = val;
    retVal->next = NULL;
}

/**
 * 添加到尾部
 * @param head
 * @param item
 */
void add_to_simple_list(ListNode* head, ListNode* addItem) {
    if (head == NULL || addItem == NULL) {
        return;
    }

    ListNode* item = head;  //遍历到最后一个元素,item指向最后一个元素
    while (item != NULL) {
        ListNode* tmp = item->next;
        if (tmp == NULL){
            break;
        }else{
            item = tmp;
        }
    }

    item->next = addItem;
}


void print_simple_list(ListNode* head) {
    if (head == NULL) {
        return;
    }

    ListNode* item = head;
    printf("\n[");
    while (item != NULL) {
        printf("%d ", item->val);

        if (item == NULL) {
            break;
        }
        item = item->next;
    }
    printf("]\n");
}

/**
 * 删除链表的结点
     请编写一个函数，
     使其可以删除某个链表中给定的（非末尾的）节点，
     您将只被给予要求被删除的节点。
 * @param node
 */
void del_simple_list(ListNode* node) {
    node->val = node->next->val;
    node->next = node->next->next;
}

/**
 * 删除链表的倒数第N个节点
    给定一个链表，
    删除链表的倒数第 n 个节点，
    并且返回链表的头结点。
 * @param head
 * @param n
 * @return
 */
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* item = head;
    int size = 0;
    while (item != NULL) {
        size++;
        item = item->next;
    }
//    printf("\nsize is %d\n", size);
    if (n > size || n<=0) {
        printf("erro params:n :%d, size is:%d\n", n, size);
        return head;
    }

    if(size <= 1) {
        free(head);
        return NULL;
    }

    item = head;
    int i = 0;
    while (item != NULL) {
        if (n != 1 && i == size  - n) {
            break;
        } else if(n == 1 && i == size - 2){
            break;
        }
        item = item->next;
        i++;
    }
    if (n == 1) {
        item->next = NULL;  // 删除到时第一个,就是删除最后一个, 拿到倒数第二个元素,next置空
    } else{
        item->val = item->next->val;
        item->next = item->next->next;
    }
    if (i == 0) {  //首元素
        head = item;
    }
    return head;
}

ListNode* reverseListNode(ListNode* pre, ListNode* next){
    struct ListNode_ *node_ = next->next;
    next->next = pre;

    ListNode* retVal = NULL;
    if (node_ != NULL) {
        retVal = reverseListNode(next, node_);
    } else {
        retVal = next;
    }

    return retVal;
}

/**
 * 反转链表
    反转一个单链表。

    示例:

        输入: 1->2->3->4->5->NULL
        输出: 5->4->3->2->1->NULL
    进阶:
        你可以迭代或递归地反转链表。你能否用两种方法解决这道题？
 * @param head
 * @return
 */
ListNode* reverseList(ListNode* head) {

    if (head == NULL) {  //空链表
        return NULL;
    }

    if (head->next == NULL) {  //只有一个元素的链表
        return head;
    }

    struct ListNode_ *node_ = head->next;

    head->next = NULL;

    return reverseListNode(head, node_);
}

/**
 * 翻转链表 第二种实现, 用遍历实现
 * @param head
 * @return
 */
ListNode* reverseList2(ListNode* head) {

    if (head == NULL) {  //空链表
        return NULL;
    }

    if (head->next == NULL) {  //只有一个元素的链表
        return head;
    }

    ListNode* item = head;
    ListNode* pre = head;
    ListNode* tmp;

    while (item != NULL) {
        if (item == head) {
            item = head->next;

            head->next = NULL;
        } else {
            tmp = item->next;  //next  下一个位置
            if (tmp != NULL) {
                item->next = pre;
                pre = item;
                item = tmp;
            } else {
                item->next = pre;
                break;
            }
        }
    }

    return item;
}