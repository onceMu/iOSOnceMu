struct ListNode {
	int val;
	struct ListNode *next;
}

//1.倒置链表
struct ListNode *reverseListNode (struct ListNode *head) {
	struct ListNode *pre = NULL;
	struct ListNode *current = head;
	struct ListNode *temp = NULL;
	while (current != NULL) {
		temp = current ->next;
		current ->next = pre;
		pre = current;
		current = temp;
	}
	head = pre;
	return head;
}

//2.判断链表是否有环
bool checkLinkListIsCycle1 (struct ListNode *head) {
	if (head == NULL) {
		return false;
	}
	struct ListNode *fast = head;
	struct ListNode *solw = head;
	while (fast ->next != NULL  && fast ->next ->next != NULL) {
		solw = solw ->next;
		fast = fast ->next ->next;
		if (solw == fast) {
			return true;
		}
	}
	return false;
}
//3.判断链表是否是回文链表
//思路，将链表从中折断成两个链表。将第二个链表倒置，然后比较倒置之前的链表和原来的链表
bool checkLinkListIsPalindrome (struct ListNode *head) {
	if (head == NULL) {
		return true;
	}
	struct ListNode *fast = head;
	struct ListNode *solw = head;
	while (fast != NULL && fast ->next != NULL) {
		fast = fast ->next ->next;
		solw = solw ->next;
	}
	//找到中间节点
	struct ListNode *middle = solw;
	struct ListNode *revserseList = reverseListNode(middle);
	while (revserseList != NULL) {
		if(revserseList ->val != head ->val) {
			return false;
		}
		revserseList = revserseList ->next;
		head = head ->next;
	}
	return true;
}
//4.判断两个链表是否相交，如果相交
//思路1：分别计算出两个链表的长度，计算出两者的差值k，然后找出比较长的链表，让长链表先走k步，然后再顺序比较
struct ListNode * checkTwoLinkListIsIntersection (struct ListNode *headA, struct ListNode *headB) {
	if (headA == NULL || headB == NULL) {
		return NULL;
	}
	int lenghtA = 0;
	int lenghtB = 0;
	struct ListNode *preA = headA;
	struct ListNode *preB = headB;
	while (preA != NULL) {
		preA = preA ->next;
		lenghtA ++;
	}
	while (preB != NULL) {
		preB = preB ->next;
		lenghtB ++;
	}
	if (preA != preB) {
		return false;
	}
	int diff = 0;
	
	if (lenghtA > lenghtB)
	{
		diff = lenghtA - lenghtB;
		preA = headA;
		preB = headB;
	}else {
		diff = lenghtB - lenghtA;
		preA = headB;
		preB = headA;
	}
	for (int i = 0; i < diff; ++i)
	{
		preA = preA ->next;
	}
	while(preA != preB) {
		preA = preA ->next;
		preB = preB ->next;
	}
	return preA;
}

//思路2，不断的比较两个链表
struct ListNode *checkTwoLinkListIsIntersection2 (struct ListNode *headA,struct ListNode *headB) {
	if(headA == NULL || headB == NULL) {
		return NULL;
	}
	struct ListNode *preA = headA;
	struct ListNode *preB = headB;
	while (preA != preB) {
		preA = preA ? preA ->next : headB;
		preB = preB ? preB ->next : headA;
	}
	return preA;
}

//5.翻转链表
//思路：找到翻转之后的尾指针，然后从尾部指针分成两部分，将尾指针之后的节点翻转，然后跟尾部指针之前的节点拼成一个
struct ListNode *rotateLinkList (struct ListNode *head,int k) {
	if (head == NULL || k = 0) {
		return head;
	}	
	int length = 1;
	struct ListNode *temp = head;
	while (temp != NULL) {
		temp = temp ->next;
		length ++;
	}
	//形成环
	temp ->next = head;
	k = length - k % count;//旋转k次之后，最后的尾指针在head 中的节点位置
	for (int i = 0; i < k; i ++)
	{
		temp = temp ->next;
	}
	//尾指针的下一个节点就是旋转之后的头指针
	head = temp ->next;
	//将尾指针断开，打破换
	temp ->next = NULL;
	return head;
}

//6.删除有序链表的重复数字
//两个变种：1.保留重复数字 2.不保留重复数字
struct ListNode *removeMutableNumberKeep (struct ListNode *head) {
	if (head == NULL) {
		return head;
	}
    struct ListNode *node = head;
	while (node ->next != NULL) {
		if (node ->val == node ->next ->val) {
			node ->next = node ->next ->next;
		}else {
			node = node ->next;
		}
	}
	return head;
}

struct ListNode *removeMutableNumberDead (struct ListNode *head) {
	if (head == NULL) {
		return head;
	}
	struct ListNode *temp = (struct ListNode *)malloc(sizof(struct ListNode));
	temp ->next = head;
	head = temp;
	while (head ->next != NULL && head ->next ->next != NULL) {
		if (head ->val == head ->next ->val) {
			int val = head ->val;
			while (head ->next != NULL && head ->next ->val == val) {
				head ->next = head ->next ->next;
			}
			
		}else {
			head = head ->next;
		}
		return temp ->next;
	}
}
