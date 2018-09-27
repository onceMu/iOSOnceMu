//
//  LinkList.c
//  Sort
//
//  Created by le on 2018/7/11.
//  Copyright © 2018年 le. All rights reserved.
//

#include "LinkList.h"
#include <stdio.h>
#include <stdlib.h>

//给定的链表，打印链表的中间节点
//压扁链表
//删除链表中和值为0的子节点，
//删除链表的中间节点
//删除有序链表中的重复的元素
//翻转链表
//删除链表中的环
//查找链表是否有环
//从链表的尾节点查找第N 个节点
//判断一个单链表是否是回文链表
//将链表每K 个节点翻转一次
//删除链表中第一个重复的节点
//删除链表
//判断两个链表是否相交，如果相交，则指出第一个交点




struct Node {
    int data;
    struct Node *next;
};

//链表中插入数据
void pushLinkList(struct Node ** head,int data){
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode -> data = data;
    newNode -> next = (*head);
    (*head) = newNode;
}

//打印链表
void printLinkList(struct Node *head) {
    while (head != NULL) {
        printf("%d ->",head->data);
        head = head ->next;
    }
}

//打印链表的中间节点
//算法思路，两个指针，一个一次走一步，一个一次走两步，当快的指针循环到尾部的时候，说明慢的指针刚好是处于中间节点
void printMiddleOfLinkList (struct Node *head) {
    struct Node *slow = head;
    struct Node *fast = head;
    if (head != NULL) {
        while (fast != NULL && fast->next != NULL) {
            fast = fast->next->next;
            slow = slow->next;
        }
        printf("%d", ((void)("The middle element is [%d]\n"),slow->data));
    }
}

//另外一种思路
void printMiddleLinkList(struct Node *head) {
    int count = 0;
    struct Node *mid = head;
    while (head != NULL) {
        if (count & 1) {
            mid = mid -> next;
        }
        ++count;
        head = head ->next;
    }
    if (mid != NULL) {
        printf("%d", ((void)("The middle element is [%d]\n"),mid->data));
    }
}


struct Node *mergeTwoSortedList (struct Node *l1,struct Node *l2) {
    if (l1 == NULL) {
        return *l2;
    }else if (l2 == NULL) {
        return *l1;
    }
    struct Node *result = NULL;
    if (l1 ->data <= l2 ->data) {
        result = l1;
        result -> next = mergeTwoSortedList(l1 ->next, l2);
    }else {
        result = l2;
        result -> next = mergeTwoSortedList(l1, l2 ->next);
    }
    return result;
}

//检查链表是否有环
bool checkNodeHasCycle (struct Node *head) {
    struct Node *slow = head;
    struct Node *fast = head;
    while (fast && fast ->next) {
        slow = slow ->next;
        fast = fast ->next ->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

struct Node *checkTwoNodeIntersection(struct Node *headA,struct Node *headB) {
    if (headA == NULL || headB == NULL) {
        return NULL;
    }
    struct Node *temp1 = headA;
    struct Node *temp2 = headB;
    int len1 = 0;
    int len2 = 0;
    int diff = 0;
    while (temp1 ->next != NULL) {
        temp1 = temp1 ->next;
        len1 ++;
    }
    while (temp2 ->next != NULL) {
        temp2 = temp2 ->next;
        len2 ++;
    }
    //如果两个链表的尾节点不是同一个节点，则说明不相交
    if (temp2 != temp1) {
        return NULL;
    }
    if (len1 > len2) {
        diff = len1 - len2;
        temp1 = headA;
        temp2 = headB;
    }else {
        diff = len2 - len1;
        temp1 = headB;
        temp2 = headA;
    }
    for (int i =0; i< diff; i++) {
        temp1 = temp1 ->next;
    }
    while (temp1 != temp2) {
        temp1 = temp1 ->next;
        temp2 = temp2 ->next;
    }
    return temp1;

}


//链表排序
//排序算法，

