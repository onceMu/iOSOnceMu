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

struct Node * findMiddleOfLinkList(struct Node *node);
struct Node * reverseLinkListNode(struct Node *node);

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
        //按照位与
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

//合并两个有序的链表  递归
struct Node *mergeTwoLink(struct Node *a,struct Node *b) {
    struct Node *result = NULL;
    if (a == NULL) {
        return (b);
    }else if (b == NULL) {
        return (a);
    }
    if (a -> data <= b ->data) {
        result = a;
        result ->next = mergeTwoLink(a->next, b);
    }else {
        result = b;
        result ->next = mergeTwoLink(a, b->next);
    }
    return (result);
};

////合并两个有序链表
//struct Node *mergeTowLinkSecond(struct Node *a, struct Node *b) {
//    struct Node *result = NULL;
//    struct Node **lastRef = &result;
//    while (1) {
//        if (a == NULL) {
//            *lastRef = b;
//            break;
//        }else if (b == NULL) {
//            *lastRef = a;
//            break;
//        }
//        if (a ->data <= b ->data) {
//            MoveNode(lastRef, &a);
//        }else {
//            MoveNode(lastRef, &b);
//        }
//        lastRef = &((*lastRef) ->next);
//    }
//    return  (result);
//}
//
////移动
//void MoveNode(struct Node **destRef,struct Node ** sourceRef) {
//    struct Node *temp = *sourceRef;
//    assert(temp != NULL);
//    *sourceRef = temp ->next;
//    temp ->next = *destRef;
//    *destRef = temp;
//}




///**
// * Definition for singly-linked list.
// * struct ListNode {
// *     int val;
// *     struct ListNode *next;
// * };
// */
//struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
//    struct ListNode *result = NULL;
//    if(l1 == NULL) {
//        return (l2);
//    }else if(l2 == NULL) {
//        return (l1);
//    }
//    if (l1 -> val <= l2 ->val) {
//        result = l1;
//        result ->next = mergeTwoLists(l1 ->next,l2);
//    }else {
//        result = l2;
//        result ->next = mergeTwoLists(l1,l2 ->next);
//    }
//    return (result);
//}


//删除有序链表中的重复节点
void removeDuplicates(struct Node *head) {
    struct Node *current = head;
    struct Node *next_next;
    if (current == NULL) {
        return;
    }
    while (current -> next != NULL) {
        if (current -> data == current ->next->data) {
            next_next = current ->next ->next;
            free(current ->next);
        }else {
            current = current ->next;
        }
    }
}

//删除有序链表中的重复节点
struct Node * removeDuplicatesNode(struct Node *head) {
    struct Node *current = head;
    struct Node *pre;
    while (current != NULL && current ->next != NULL) {
        if (current ->data == current ->next ->data) {
            pre = current ->next ->next;
            free(current ->next);
            current ->next = pre;
        }
        current = current ->next;
    }
    return head;
}



//判断链表是否有环
bool hasCycle(struct Node *head) {
    struct Node *fast = head;
    struct Node *solw = head;
    if(head == NULL) {
        return false;
    }
    if(head ->next == NULL) {
        return false;
    }
    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast ->next ->next;
        solw = solw ->next;
        if (fast == solw) {
            return true;
        }
    }
    return false;
}


//判断两个链表是否相交，并且指出第一个交点
struct Node *getIntersectionNode(struct Node *headA,struct Node *headB) {
    if (headA == NULL || headB == NULL) {
        return NULL;//有空链表，肯定不相交
    }
    struct Node *temp1 = headA;
    struct Node *temp2 = headB;
    int len1 = 0;
    int len2 = 0;
    int diff = 0;
    //先找出尾节
    while (temp1 ->next != NULL) {
        temp1 = temp1 ->next;
        len1 ++;
    }
    while (temp2 ->next != NULL) {
        temp2 = temp2 ->next;
        len2 ++;
    }
    if (temp1 != temp2) {
        return NULL;
    }
    //如果尾节点相同，则证明相交
    diff = abs(len1 - len2);
    if (len1 > len2) {
        temp1 = headA;
        temp2 = headB;
    }else {
        temp1 = headB;
        temp2 = headA;
    }
    //找出两个链表的差值，找到差值开始的节点
    for (int i = 0; i<diff; i++) {
        temp1 = temp1 ->next;
    }
    while (temp1 != temp2) {
        temp1 = temp1 ->next;
        temp2 = temp2 ->next;
    }
    return  temp1;
}

//判断两个链表是否有环,并且给出第一个相交的节点
struct Node *getIntersectionCycleNode (struct Node *headA,struct Node *headB) {
    if (headA == NULL || headB == NULL) {
        return  NULL;
    }
    struct Node *temp = headA;
    //找到a的尾节点
    while(temp ->next != NULL) {
        temp = temp ->next;
    }
    //将a的尾节点指向b
    temp ->next = headB;
    
    struct Node *fast = temp;
    struct Node *solw = temp;
    while (fast -> next != NULL && fast ->next ->next != NULL) {
        fast = fast ->next ->next;
        solw = solw ->next;
        if (fast == solw) {
            break;
        }
    }
    if (fast != solw) {
        return NULL;
    }
    while (temp != solw) {
        temp = temp ->next;
        solw = solw ->next;
    }
    return temp;
}


struct Node *mergeSortedList(struct Node *headA,struct Node *headB) {
    if (headA == NULL) {
        return headB;
    }else if (headB == NULL) {
        return headA;
    }
    struct Node *result = NULL;
    if (headA ->data > headB ->data) {
        result = headB;
        result ->next = mergeSortedList(headA, headB ->next);
    }else {
        result = headA;
        result ->next = mergeSortedList(headA ->next, headB);
    }
    return result;
}

//删除链表中所有值为给定值的节点
struct Node *deleteSpecialData(struct Node *head,int val) {
    if (head == NULL) {
        return head;
    }
    struct Node *dummy=(struct Node *)malloc(sizeof(struct Node));
    dummy ->next = head;
    struct Node *pre = dummy;
    struct Node *temp = head;
    while (temp) {
        if (temp ->data == val) {
            pre ->next = temp ->next;
        }else {
            pre = temp;
        }
        temp = temp ->next;
    }
    return dummy ->next;
}

struct Node *reverseSpecialPosition(struct Node *head,int m,int n) {

    //计算出Node 长度
    if (head == NULL) {
        return head;
    }
    struct Node *temp = NULL;
    struct Node *currentM = head;
    //第一次遍历，找到 第M个节点
    for (int i = 0; i<m-1; i++) {
        temp = currentM;
        currentM = currentM ->next;
    }
    struct Node *end = currentM;
    struct Node *preM = currentM;
    //从第M个节点的下一个节点开始
    currentM = currentM ->next;
    for (int i = m+1; i<=n; i++) {
        struct Node *currentNext = currentM -> next;
        currentM ->next = preM;
        preM = currentM;
        currentM = currentNext;
    }
    //交换位置后，M节点的下一个节点是N 节点的next
    //在上一个循环中，currentM 指向的是 N节点的next节点
    //将M 节点指向 N的next节点
    end ->next = currentM;
    //现在将N节点指向
    if (temp) {
        temp ->next = preM;
    }else {
        head = preM;
    }
    
    return head;
    
}



// leetcode 237 问题
// 代码已经提交leetcode
// Delete Node in a Linked List，删除链表中的节点
void deleteNode (struct Node *node) {
    //分成两部分
    //1.删除节点的值
    //2.改变节点的next指针
    node ->data = node ->next ->data;
    node ->next = node ->next ->next;
}

// leetcode 234 问题
// 判断链表是否是回文链表
bool checkListNodeIsPalinrome(struct Node *node) {
    if (node == NULL) {
        return false;
    }
    struct Node *middleNode;
    struct Node *leftNode;
    struct Node *rightNode;
    leftNode = node;
    middleNode = findMiddleOfLinkList(node);
    rightNode = reverseLinkListNode(middleNode);
    while (leftNode && rightNode) {
        if (leftNode ->data != rightNode ->data) {
            return false;
        }
        leftNode = leftNode ->next;
        rightNode = rightNode ->next;
    }
    return true;
}

//找到链表的中间节点
//已经提交leetcode
//快慢指针、当快指针指向尾节点的时候，慢指针刚好指向中间节点
struct Node * findMiddleOfLinkList(struct Node *node) {
    if (node == NULL) {
        return  NULL;
    }
    struct Node *fast = node;
    struct Node *solw = node;
    while (fast && fast ->next) {
        fast = fast ->next ->next;
        solw = solw ->next;
    }
    return solw;
}

struct Node * reverseLinkListNode(struct Node *node) {
    if (node == NULL || node ->next == NULL) {
        return node;
    }
    struct Node *temp;
    struct Node *p,*q;
    p = node;
    q = node;
    while (q) {
        temp = q ->next;
        q ->next = p;
        p = q;
        q = temp;
    }
    node ->next = NULL;
    node = p;
    return node;
}

// leetcode 19 给定n，从链表尾节点开始删除第n个节点
//思路1 leetcode 提交成功
//1.找到链表长度t
//2.遍历t-n之前的节点
//3.删除第t-n节点的next节点
struct Node *deleteNthListNode2 (struct Node *head,int n) {
    if (head == NULL) {
        return head;
    }
    int count = 1;
    struct Node *temp = head;
    while (temp ->next != NULL) {
        temp = temp ->next;
        count ++;
    }
    if (n >= count) {
        return head ->next;
    }
    temp = head;
    for (int i = 0; i< count -n -1; i++) {
        temp = temp ->next;
    }
    temp ->next = temp ->next ->next;
    return head;
}



//思路2 leetcode 提交成功
//快慢指针
//快指针先跑N步，如果快指针为NULLz，则直接返回head ->next
//然后将快慢指针一起开始跑，一直跑到快指针指向空
//
struct Node *deleteNthListNode (struct Node *head,int n) {
    if (head == NULL) {
        return head;
    }
    struct Node *fast = head;
    struct Node *slow = head;
    for (int i = 0; i<n ; i++) {
        fast = fast ->next;
        if (fast == NULL) {
            return head ->next;
        }
    }
    while (fast ->next != NULL) {
        fast = fast ->next;
        slow = slow ->next;
    }
    slow ->next = slow ->next ->next;
    return head;
}


//leetcode 61 roate list
//思路
//1.找出链表的长度以及尾指针
//2.将链表变成环
//3.找出打破环的节点
//4.将打破环的节点的next 指向NULL
struct Node * rotateRight(struct Node *head,int k) {
    if (k ==0 || head == NULL) {
        return head;
    }
    int count = 1;
    struct Node *temp = head;
    //找出链表长度以及链表的尾指针
    while (temp ->next != NULL) {
        temp = temp ->next;
        count ++;
    }
    //将链表尾指针指向头指针，这样链表就是环
    temp ->next = head;
    
    k = count - k % count;
    for (int i = 0; i< k; i++) {
        temp = temp ->next;
    }
    head = temp ->next;
    temp ->next = NULL;
    return head;
}


//leetcode sortList O(NlgN);
//要求平均算法时间复杂度是 O(NlgN);
//能使用的排序算法快排、堆排序、归并排序
//递归的思想 leetcode一直提交不成功
struct Node *mergeTwoList(struct Node *l1,struct Node *l2) {
    if (l1 == NULL) {
        return l2;
    }
    if (l2 == NULL) {
        return l1;
    }
    struct Node *result = NULL;
    if (l1-> data <= l2 ->data) {
        result = l1;
        result ->next = mergeTwoList(l1->next, l2);
    }else {
        result = l2;
        result ->next = mergeTwoList(l1, l2->next);
    }
    return result;
}

struct Node *sortList(struct Node *head) {
    if (head == NULL) {
        return head;
    }
    struct Node *fast = head;
    struct Node *slow = head;
    struct Node *pre = NULL;
    //切成两个链表
    while (fast != NULL && fast ->next != NULL) {
        pre = slow;
        fast = fast ->next ->next;
        slow = slow ->next;
    }
    pre ->next = NULL;
    struct Node *l1 = sortList(head);
    struct Node *l2 = sortList(slow);
    return mergeTwoList(l1, l2);
}



//相加两个链表
//struct Node *addTwoList(struct Node *l1, struct Node *l2) {
//    if (l1 == NULL) {
//        return l2;
//    }
//    if (l2 == NULL) {
//        return l1;
//    }
//    int a = 0;
//    struct Node *head = (struct Node *)malloc(sizeof(struct Node));
//    while ( l1 || l2) {
//        int v1 = (l1 ? l1 ->data : 0);
//        int v2 = (l2 ? l2 ->data : 0);
//        int temp = v1 +v2 + a;
//        if (temp >= 10) {
//            a = temp - 10;
//            temp = temp - 10;
//        }else {
//            a = 0;
//        }
//
//    }
//}

//if (head == NULL) {
//    return head;
//}
//int count = 1;
//struct ListNode *temp = head;
//while (temp ->next != NULL) {
//    temp = temp ->next;
//    count ++;
//}
//if (n >= count) {
//    return head ->next;
//}
//temp = head;
//for (int i = 0; i< count -n - 1; i++) {
//    temp = temp ->next;
//}
//temp ->next = temp ->next ->next;
//return head;
//struct ListNode *pre = NULL;
//struct ListNode *current = head;
//struct ListNode *next = NULL;
//while (current != NULL) {
//    next = current ->next;
//    current ->next = pre;
//    pre = current;
//    current = next;
//}
//head = pre;
//return head;

//检查链表是否是回文链表
int checkLinkListIsPalindromeList(struct Node *head) {
    if (head == NULL) {
        return -1;
    }
    return 1;
    
}
