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
//




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

