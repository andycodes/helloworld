/*
链表遍历框架，
兼具线性和非线性遍历结构：

void traverse(ListNode head) {
    for (ListNode p = head; p != null; p = p.next) {
        // 访问 p.val
    }
}

void traverse(ListNode head) {
    // 访问 head.val
    traverse(head.next)
}

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../flag_type.h"

typedef  struct ListNode {
      int val;
      struct ListNode *next;
}MyLinkedList;


void display(MyLinkedList *pHead)
{
    while( pHead != NULL)
    {
        printf("%d ", pHead->val);
        pHead = pHead->next;
    }
    printf("\n");
}


void display2(MyLinkedList *obj){
    MyLinkedList *temp = obj;//将temp指针重新指向头结点
    //只要temp指针指向的结点的next不是Null，就执行输出语句。
    while (temp->next) {
        temp=temp->next;
        printf("%d",temp->val);
    }
    printf("\n");
}


/*
将两个有序链表合并为一个新的有序链表并返回。
新链表是通过拼接给定的两个链表的所有节点组成的。

示例：

输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4
*/

/*
方法 1：递归
想法

我们可以如下递归地定义在两个链表里的 merge 操作（忽略边界情况，比如空链表等）：

\left\{ \begin{array}{ll} list1[0] + merge(list1[1:], list2) & list1[0] < list2[0] \\ list2[0] + merge(list1, list2[1:]) & otherwise \end{array} \right.
{
list1[0]+merge(list1[1:],list2)
list2[0]+merge(list1,list2[1:])
?

list1[0]<list2[0]
otherwise
?


也就是说，两个链表头部较小的一个与
剩下元素的 merge 操作结果合并。

算法
我们直接将以上递归过程建模，
首先考虑边界情况。
特殊的，如果 l1 或者 l2 一开始就是 null ，
那么没有任何操作需要合并，
所以我们只需要返回非空链表。
否则，我们要判断 l1 和 l2 哪一个的头元素更小，
然后递归地决定下一个添加到结果里的值。
如果两个链表都是空的，那么过程终止，
所以递归过程最终一定会终止。

*/

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2)
{
        if (l1 == NULL) {
            return l2;
        }
        else if (l2 == NULL) {
            return l1;
        }
        else if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
}


/*
给定一个链表，判断链表中是否有环。

为了表示给定链表中的环，
我们使用整数 pos 来表示链表尾连接到链
表中的位置（索引从 0 开始）。
如果 pos 是 -1，则在该链表中没有环。
*/
bool hasCycle(struct ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return false;
    }
    struct ListNode *slow = head;
    struct ListNode *fast = head->next;
    while (slow != fast) {
        if (fast == NULL || fast->next == NULL) {
            return false;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    return true;
}


/** Initialize your data structure here. */
struct ListNode* slink_init() {
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next = NULL;
    return head;
}

/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
int link_single_get_val(MyLinkedList* obj, int index) {
    int i = 0;
    MyLinkedList* entry = obj;

    while(entry->next != NULL){
        if(i++ == index){
            return entry->next->val;
        }
        entry = entry->next;
    }
    return -1;
}


MyLinkedList*link_single_amend_value(MyLinkedList* obj,int index,int newElem){
    MyLinkedList* temp=obj;
    temp=temp->next;//tamp指向首元结点
    //temp指向被删除结点
    for (int i=1; i<index; i++) {
        temp=temp->next;
    }
    temp->val=newElem;
    return obj;
}


int link_single_get_index(MyLinkedList* obj,int val){
    MyLinkedList* t=obj;
    int i=1;
    while (t->next) {
        t=t->next;
        if (t->val==val) {
            return i;
        }
        i++;
    }
    return -1;
}


/** Add a node of value val before the first element of the linked list.
After the insertion, the new node will be the first node of the linked list. */
void link_single_push_new_head(MyLinkedList* obj, int val) {
	MyLinkedList* newNode = (MyLinkedList*)malloc(sizeof(MyLinkedList));
	newNode->val = val;
	newNode->next = obj->next;
	obj->next = newNode;
}


/** Append a node of value val to the last element of the linked list. */
void slink_push_tail(struct ListNode* obj, int val) {
    struct ListNode* tmp = obj;
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;

    while (tmp) {
        if (tmp->next == NULL) {
            tmp->next = newNode;
            return;
        }
        tmp = tmp->next;
    }
}


/** Add a node of value val before the index-th node in the linked list.
If index equals to the length of linked list,
the node will be appended to the end of linked list.
If index is greater than the length, the node will not be inserted. */
void link_single_insert_new_node_before_index
    (MyLinkedList* obj, int index, int val) {
    int i = 0;

    if(index < 0){
        link_single_push_new_head(obj,val);
        return;
    }

    MyLinkedList* newNode = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    newNode->val = val;

    MyLinkedList* entry = obj;
    while(entry !=  NULL){
            if(i++ == index){
                newNode->next = entry->next;//?
                entry->next = newNode;//?
                break;
            }
            entry = entry->next;
    }
}


void  link_single_insert_new_node_before_index_2
    (MyLinkedList* obj,int index,int val){
    MyLinkedList* temp=obj;//创建临时结点temp
    //首先找到要插入位置的上一个结点
    for (int i=1; i<index; i++) {
        if (temp==NULL) {
            printf("插入位置无效\n");
            return;
        }
        temp=temp->next;
    }
    //创建插入结点c
    MyLinkedList* c=(MyLinkedList*)malloc(sizeof(MyLinkedList));
    c->val=val;
    //向链表中插入结点
    c->next=temp->next;
    temp->next=c;
    return ;
}


//考虑删除节点为尾节点
void link_single_del_node(MyLinkedList* head,MyLinkedList*p_cur_node)
{
    if(p_cur_node != NULL)
    {
        if(p_cur_node->next != NULL)
        {//不考虑删除节点为尾节点
            MyLinkedList* pTemp = p_cur_node->next;
            p_cur_node->val = pTemp->val;
            p_cur_node->next = pTemp->next;
            free(pTemp);
        }
        else
        {
            MyLinkedList* temp = head;
            while(temp != NULL)
            {
                if(temp->next == p_cur_node)
                {
                    free(p_cur_node);
                    temp->next = NULL;
                }
                temp = temp->next;
            }
        }
    }
}


/** Delete the index-th node in the linked list, if the index is valid. */
void link_single_del_node_by_index(MyLinkedList* obj, int index) {
        int i = 0;
        MyLinkedList* list = obj;
        while(list->next != NULL){
            if(i++ == index){
                list->next = list->next->next;
                break;
            }
            list = list->next;
        }
}

void link_single_del_node_by_index_2(MyLinkedList* obj,int index){
    MyLinkedList* temp=obj;
    //遍历到被删除结点的上一个结点
    for (int i=1; i<index; i++) {
        temp=temp->next;
    }
    MyLinkedList* del=temp->next;//单独设置一个指针指向被删除结点，以防丢失
    temp->next=temp->next->next;//删除某个结点的方法就是更改前一个结点的指针域
    free(del);//手动释放该结点，防止内存泄漏
    return ;
}


void link_single_del_node_by_key(MyLinkedList*head,int key)
{
	MyLinkedList*node1=head;
	MyLinkedList*node2=NULL;
	if (head==NULL)
	{
		return;
	}
	else
	{
		if (node1->val==key)
		{
			head=head->next;
			free(node1);
			return;
		}
		else
		{
			while (node1!=NULL)
			{
				node2=node1;
				node2=node2->next;
				if (node2->val==key)
				{
					node1->next=node2->next;
					free(node2);
					break;
				}
				node1=node1->next;
			}
			return;
		}
    }
}


struct ListNode* link_single_del_node_by_key_2(struct ListNode* head, int val){
       //删除值相同的头结点后，可能新的头结点也值相等，用循环解决
        while(head!=NULL&&head->val==val){
            head=head->next;
        }
        if(head==NULL)
            return head;
        struct ListNode *prev=head;
        //确保当前结点后还有结点
        while(prev->next!=NULL){
            if(prev->next->val==val){
                prev->next=prev->next->next;
            }else{
                prev=prev->next;
            }
        }
        return head;

}



void myLinkedListFree(MyLinkedList* obj) {

}

/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * MyLinkedList* obj = slink_init();
 * int param_1 = link_single_get_val(obj, index);

 * link_single_push_new_head(obj, val);

 * slink_push_tail(obj, val);

 * link_single_insert_new_node_before_index(obj, index, val);

 * link_single_del_node_by_index(obj, index);

 * myLinkedListFree(obj);
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/*
请判断一个链表是否为回文链表。

示例 1:

输入: 1->2
输出: false
示例 2:

输入: 1->2->2->1
输出: true
*/
bool isPalindrome(struct ListNode* head){
    // 特殊情况的排除
    if(head == NULL || head->next == NULL)
        return true;
    if(head->next->next == NULL){
        if(head->val == head->next->val)
            return true;
        else
            return false;
    }

    struct ListNode *fastp, *slowp;
    fastp = head->next->next;
    slowp = head->next;

    // 快慢指针找到尾部及中部位置
/*
我们可以指定一个快指针每次以两个步长后移，
慢指针每次以一个步长后移，这样当快指针走到尾部时，
慢指针刚好走到中部
*/
    while(fastp && fastp->next != NULL){
        fastp = fastp->next->next;
        slowp = slowp->next;
    }

//而后我们可以翻转中部之前的链表，以便于后续比较。
    // 翻转中部前链表序列
    struct ListNode *prep, *nextp;
    prep = nextp = NULL;
    while(head != slowp){
        nextp = head->next;
        head->next = prep;
        prep = head;
        head = nextp;
    }

    // 若结点个数为奇数，则舍弃中间结点
    if(fastp != NULL && fastp->next == NULL)
        slowp = slowp->next;

    // 回文匹配比较
    while(prep != NULL){
        if(prep->val != slowp->val)
            return false;
        prep = prep->next;
        slowp = slowp->next;
    }
    return true;
}


/*
给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。

示例 1:

输入: 1->1->2
输出: 1->2
示例 2:

输入: 1->1->2->3->3
输出: 1->2->3

*/
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL && current->next != NULL) {
        if (current->next->val == current->val) {
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
    return head;
}

//编写一个程序，找到两个单链表相交的起始节点。
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    if (headA == NULL || headB == NULL) return NULL;
    struct ListNode *pA = headA, *pB = headB;
    while (pA != pB) {
        pA = pA == NULL ? headB : pA->next;
        pB = pB == NULL ? headA : pB->next;
    }
    return pA;
}


//递归实现
struct ListNode * reverse(struct ListNode *pHead)
{
    if (pHead == NULL || pHead->next == NULL)
    {
        return pHead;
    }
    struct ListNode *p = pHead->next;
    struct ListNode *pNewHead =  reverse(p);
    p->next = pHead;
    pHead ->next = NULL;
    return pNewHead;
}


//尾递归实现
struct ListNode * do_reverse_tail(struct ListNode *pHead, struct ListNode *pNewHead)
{
    if(pHead == NULL)
    {
        return pNewHead;
    }
    else
    {
        struct ListNode *pNext = pHead->next;
        pHead->next = pNewHead;
        return do_reverse_tail(pNext, pHead);
    }
}

struct ListNode * reverse_tail(struct ListNode *pHead)
{
    return do_reverse_tail(pHead, NULL);
}

//迭代实现
struct ListNode * reverse_it(struct ListNode *pHead)
{
    struct ListNode *pNewHead = NULL;
    struct ListNode *pPrev = NULL;
    struct ListNode *pCur = pHead;
    while(pCur != NULL)
    {
        struct ListNode *pTmp = pCur->next;
        if(pTmp == NULL)
        {
            pNewHead = pCur;
        }
        pCur->next = pPrev;
        pPrev = pCur;
        pCur = pTmp;
    }

    return pNewHead;
}


struct ListNode* middleNode(struct ListNode* head){
        struct ListNode* slow = head;
        struct ListNode* fast = head;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
}


/*
给出两个?非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照?逆序?的方式存储的，并且它们的每个节点只能存储?一位?数字。

如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

您可以假设除了数字 0 之外，这两个数都不会以 0?开头。

示例：

输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807
*/
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* res = slink_init();
    struct ListNode* p = l1;
    struct ListNode* q = l2;
    int carry = 0;
    while (p != NULL || q != NULL) {
        int x = (p != NULL) ? p->val : 0;
        int y = (q != NULL) ? q->val : 0;
        int sum = carry + x + y;
        carry = sum / 10;
        slink_push_tail(res, sum % 10);
        if (p != NULL) p = p->next;
        if (q != NULL) q = q->next;
    }

    if (carry > 0) {
        slink_push_tail(res, carry);
    }

    return res->next;
}


/*
148. 排序链表
在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。

示例 1:

输入: 4->2->1->3
输出: 1->2->3->4
*/
struct ListNode* merge_sotrlist(struct ListNode* p,struct ListNode* q){
	struct ListNode *head=(struct ListNode*)malloc(sizeof(struct ListNode));
	struct ListNode *temp=head;
	while(p!=NULL&&q!=NULL){
		if(p->val<=q->val){
			temp->next=p;
			temp=p;
			p=p->next;
		}else{
			temp->next=q;
			temp=q;
			q=q->next;
		}
	}
    temp->next=(p==NULL)?q:p;
	return head->next;
}
struct ListNode* sortList(struct ListNode* head){
    if(head==NULL||head->next==NULL)return head;
	struct ListNode*p=head;struct ListNode*q=head->next;
	while(q!=NULL&&q->next!=NULL){
		p=p->next;q=q->next->next;
	}
	q=p->next;
	p->next=NULL;
	return merge_sotrlist(sortList(head),sortList(q));
}


int main()
{
    MyLinkedList* obj = slink_init();

    link_single_push_new_head(obj,1);
    slink_push_tail(obj,3);
    link_single_insert_new_node_before_index(obj,1,2);
    int ret = link_single_get_val(obj,1);
    printf("%d\n",ret);
    link_single_del_node_by_index(obj,1);
    ret = link_single_get_val(obj,1);
    printf("%d\n",ret);
}

