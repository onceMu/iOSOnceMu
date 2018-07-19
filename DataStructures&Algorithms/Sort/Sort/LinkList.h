//
//  LinkList.h
//  Sort
//
//  Created by le on 2018/7/11.
//  Copyright © 2018年 le. All rights reserved.
//

#ifndef LinkList_h
#define LinkList_h

#include <stdio.h>
#include <stdlib.h>

#endif /* LinkList_h */


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
    printf("呵呵呵\n");
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

//对于给定的链表，指定data 为key，删除最后一个出现的指定key,如果没有包含key，返回invalid data，
//要求O(n)
//如1 ->3 ->4 ->5 -> 6 ->7 ->8 ->9 ->3 ->1 -> null
//删除3 1 ->3 ->4 ->5 -> 6 ->7 ->8 ->9  ->1 -> null
//思路
void deleteLastKey(struct Node *head,int key) {
    struct Node *temp = head;
    struct Node *ptr = NULL;
    //从头开始遍历链表，如果key存在，则将temp 赋值给 ptr
    while (temp) {
        if (temp -> data == key) {
            //ptr 会指向最后一个 == key 的节点
            ptr = temp;
        }
        temp = temp -> next;
    }
    //如果ptr 不为空并且 ptr的下一个节点也不为空，即ptr 不是最后一个节点
    if (ptr != NULL && ptr ->next != NULL) {
        temp = head;
        while (temp -> next != ptr) {
            temp = temp -> next;
        }
        temp -> next = NULL;
    }
    if (ptr != NULL && ptr == NULL) {
        ptr -> data = ptr ->next ->data;
        temp = ptr ->next;
        ptr ->next = ptr ->next ->next;
        free(temp);
    }
}

void displyDeletedList(struct Node *head) {
    struct Node* temp = head;
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    while (temp != NULL) {
        printf("%d --> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

//删除链表给定位置的节点
void deletePositionNode(struct Node *head,int position) {
    if (head == NULL) {
        return;
    }
    struct Node *temp = head;
    if (position == 0) {
        head = temp ->next;
        free(temp);
        return;
    }
    for (int i =0; i<position -1; i++) {
        temp = temp ->next;
    }
    //如果越界
    if (temp == NULL || temp -> next == NULL) {
        return;
    }
    struct Node *next = temp ->next->next;
    free(temp ->next);
    temp ->next = next;
}

//翻转链表
//1->2->3->4-5->NULL
//5->4->3->2->1->NULL
void reverseLinkList(struct Node **head) {
    struct Node *pre = NULL;
    struct Node *current = *head;
    struct Node *next = NULL;
    
    while (current != NULL) {
        next = current -> next;
        current ->next = pre;
        pre = current;
        current = next;
    }
    *head = pre;
}

//旋转链表
//给定一个链表，10->20->30->40->50->60 给定一个k ==4，将链表旋转成 50->60->10->20->30->40;
//思路:
//1.先找到k节点，然后将k+1节点变成头结点，将原来的尾节点的next 指向原来的头结点
void rotateLinkList(struct Node **head,int k) {
    if (k == 0) {
        return;
    }
    struct Node *temp = *head;
    int count = 1;
    //先找到当前 k节点
    while (count < k && temp != NULL) {
        temp = temp -> next;
        count ++;
    }
    printf("当前的%d ---",temp->data);
    // 如果k 节点是空的，则返回
    if (temp == NULL) {
        return;
    }
    //保存当前的k节点
    struct Node *kNode = temp;
    //继续循环，找到最后一个节点
    while (temp -> next != NULL) {
        temp = temp -> next;
    }
    //将最后一个节点指针指向头结点
    temp -> next = *head;
    *head = kNode -> next;
    kNode -> next = NULL;
}
