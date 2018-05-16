//
// Created by wangxn on 2018/5/15.
//

#include "SimpleList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ListNode* create_node(int val) {
    ListNode* retVal = malloc(sizeof(ListNode));
    retVal->val = val;
    retVal->next = NULL;
}


/**
 * 获得链表元素个数
 * @param head 
 * @return 
 */
int size_list(ListNode *head) {
    int size = 0;
    ListNode* item;
    item = head;
    while (item != NULL) {
        item = item->next;
        size++;
    }
    return size;
}

/**
 * 获得索引index处的ListNode
 * @param head 
 * @param index 
 * @return 
 */
ListNode* index_list(ListNode* head, int index) {
    ListNode* item = head;
    ListNode* retVal = NULL;
    int i = 0;
    while (item != NULL) {
        if (index == i) {
            retVal = item;
            break;
        }

        item = item->next;
        i++;
        
    }

    return retVal;
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

/**
 * 合并两个有序链表
    将两个有序链表合并为一个新的有序链表并返回。
    新链表是通过拼接给定的两个链表的所有节点组成的。
 * @param l1
 * @param l2
 * @return
 */
ListNode* mergeTwoLists(ListNode *l1, ListNode *l2) {
    if (l1 == NULL && l2 == NULL) {
        return NULL;
    } else if (l1 == NULL) {
        return l2;
    } else if (l2 == NULL) {
        return l1;
    }

    ListNode* item1 = l1;
    ListNode* item2 = l2;
    ListNode* item = NULL;
    ListNode* newHead = NULL;

    if (l1->val >= l2->val) {
        item = l2;
        item2 = l2->next;
    } else{
        item = l1;
        item1 = l1->next;
    }

    newHead = item;

    while (true) {  //两个链表都遍历到了尾部
        if (item1 == NULL && item2 == NULL) {
            break;
        }else if (item1 == NULL && item2 != NULL) {
            item->next = item2;
            break;
        } else if (item2 == NULL && item1 != NULL) {
            item->next = item1;
            break;
        } else if(item1 != NULL && item2 != NULL){
                if (item1->val >= item2->val) {
                    item->next = item2;
                    item2 = item2->next;
                } else if (item1->val < item2->val) {
                    item->next = item1;
                    item1 = item1->next;
                }
                item = item->next;
        }
    }

    return newHead;
}


/**
 * 回文链表
    请判断一个链表是否为回文链表。
    示例 1:
        输入: 1->2
        输出: false
    示例 2:
        输入: 1->2->2->1
        输出: true
    进阶：
        你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？
 * @param head
 * @return
 */
bool isListPalindrome(ListNode* head){
    int size = size_list(head);
    if (size <= 1) {
        return true;
    }
    int half = size/2 + size%2;

    ListNode *pNode_ = index_list(head, half - 1);  //得到中间节点的前一个节点
    struct ListNode_ *node_ = pNode_->next;         //得到中间节点
    pNode_->next = NULL;                            //将List分成2个List

    node_ = reverseList(node_);                             //翻转第二个List


    ListNode* item1 = head;
    ListNode* item2 = node_;
    while (item2 != NULL) {
        if(item1->val == item2->val){
            item1 = item1->next;
            item2 = item2->next;
        } else{
            return false;
        }
    }
    return true;
}


/**
 * 环形链表
    给定一个链表，判断链表中是否有环。
    进阶：
        你能否不使用额外空间解决此题？
 * @param head
 * @return
 */
bool hasCycle(ListNode* head) {
    //第一种实现方式 ,
    /////////////////////////////////////////////
    if (head == NULL || head->next == NULL) {
        return false;
    }
//    int index = 0;
//    int i = 0;
//    ListNode* item = head;
//    ListNode* innerItem = head;
//    while (item != NULL) {
//        i = 0;
//        innerItem = head;
//        if (item->next != NULL) {
//            while (i < index) {
//                if (item->next != innerItem){
//                    innerItem = innerItem->next;
//                    i++;
//                } else {
//                    return true;
//                }
//            }
//        } else{
//            break;
//        }
//
//        item = item->next;
//        index++;
//    }
//    return false;
    //第二种实现方式, 优化的方式
    ////////////////////////////////////////////////////
    ListNode* fast = head;
    ListNode* slow = head;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
        if (slow == fast) {
            return true;
        }
    }

    return false;
}

