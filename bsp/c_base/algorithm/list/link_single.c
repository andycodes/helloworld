/*
���������ܣ�
������Ժͷ����Ա����ṹ��

void traverse(ListNode head) {
    for (ListNode p = head; p != null; p = p.next) {
        // ���� p.val
    }
}

void traverse(ListNode head) {
    // ���� head.val
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
    MyLinkedList *temp = obj;//��tempָ������ָ��ͷ���
    //ֻҪtempָ��ָ��Ľ���next����Null����ִ�������䡣
    while (temp->next) {
        temp=temp->next;
        printf("%d",temp->val);
    }
    printf("\n");
}


/*
��������������ϲ�Ϊһ���µ������������ء�
��������ͨ��ƴ�Ӹ�����������������нڵ���ɵġ�

ʾ����

���룺1->2->4, 1->3->4
�����1->1->2->3->4->4
*/

/*
���� 1���ݹ�
�뷨

���ǿ������µݹ�ض���������������� merge ���������Ա߽���������������ȣ���

\left\{ \begin{array}{ll} list1[0] + merge(list1[1:], list2) & list1[0] < list2[0] \\ list2[0] + merge(list1, list2[1:]) & otherwise \end{array} \right.
{
list1[0]+merge(list1[1:],list2)
list2[0]+merge(list1,list2[1:])
?

list1[0]<list2[0]
otherwise
?


Ҳ����˵����������ͷ����С��һ����
ʣ��Ԫ�ص� merge ��������ϲ���

�㷨
����ֱ�ӽ����ϵݹ���̽�ģ��
���ȿ��Ǳ߽������
����ģ���� l1 ���� l2 һ��ʼ���� null ��
��ôû���κβ�����Ҫ�ϲ���
��������ֻ��Ҫ���طǿ�����
��������Ҫ�ж� l1 �� l2 ��һ����ͷԪ�ظ�С��
Ȼ��ݹ�ؾ�����һ����ӵ�������ֵ��
������������ǿյģ���ô������ֹ��
���Եݹ��������һ������ֹ��

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
����һ�������ж��������Ƿ��л���

Ϊ�˱�ʾ���������еĻ���
����ʹ������ pos ����ʾ����β���ӵ���
���е�λ�ã������� 0 ��ʼ����
��� pos �� -1�����ڸ�������û�л���
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
    temp=temp->next;//tampָ����Ԫ���
    //tempָ��ɾ�����
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
    MyLinkedList* temp=obj;//������ʱ���temp
    //�����ҵ�Ҫ����λ�õ���һ�����
    for (int i=1; i<index; i++) {
        if (temp==NULL) {
            printf("����λ����Ч\n");
            return;
        }
        temp=temp->next;
    }
    //����������c
    MyLinkedList* c=(MyLinkedList*)malloc(sizeof(MyLinkedList));
    c->val=val;
    //�������в�����
    c->next=temp->next;
    temp->next=c;
    return ;
}


//����ɾ���ڵ�Ϊβ�ڵ�
void link_single_del_node(MyLinkedList* head,MyLinkedList*p_cur_node)
{
    if(p_cur_node != NULL)
    {
        if(p_cur_node->next != NULL)
        {//������ɾ���ڵ�Ϊβ�ڵ�
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
    //��������ɾ��������һ�����
    for (int i=1; i<index; i++) {
        temp=temp->next;
    }
    MyLinkedList* del=temp->next;//��������һ��ָ��ָ��ɾ����㣬�Է���ʧ
    temp->next=temp->next->next;//ɾ��ĳ�����ķ������Ǹ���ǰһ������ָ����
    free(del);//�ֶ��ͷŸý�㣬��ֹ�ڴ�й©
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
       //ɾ��ֵ��ͬ��ͷ���󣬿����µ�ͷ���Ҳֵ��ȣ���ѭ�����
        while(head!=NULL&&head->val==val){
            head=head->next;
        }
        if(head==NULL)
            return head;
        struct ListNode *prev=head;
        //ȷ����ǰ�����н��
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
���ж�һ�������Ƿ�Ϊ��������

ʾ�� 1:

����: 1->2
���: false
ʾ�� 2:

����: 1->2->2->1
���: true
*/
bool isPalindrome(struct ListNode* head){
    // ����������ų�
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

    // ����ָ���ҵ�β�����в�λ��
/*
���ǿ���ָ��һ����ָ��ÿ���������������ƣ�
��ָ��ÿ����һ���������ƣ���������ָ���ߵ�β��ʱ��
��ָ��պ��ߵ��в�
*/
    while(fastp && fastp->next != NULL){
        fastp = fastp->next->next;
        slowp = slowp->next;
    }

//�������ǿ��Է�ת�в�֮ǰ�������Ա��ں����Ƚϡ�
    // ��ת�в�ǰ��������
    struct ListNode *prep, *nextp;
    prep = nextp = NULL;
    while(head != slowp){
        nextp = head->next;
        head->next = prep;
        prep = head;
        head = nextp;
    }

    // ��������Ϊ�������������м���
    if(fastp != NULL && fastp->next == NULL)
        slowp = slowp->next;

    // ����ƥ��Ƚ�
    while(prep != NULL){
        if(prep->val != slowp->val)
            return false;
        prep = prep->next;
        slowp = slowp->next;
    }
    return true;
}


/*
����һ����������ɾ�������ظ���Ԫ�أ�ʹ��ÿ��Ԫ��ֻ����һ�Ρ�

ʾ�� 1:

����: 1->1->2
���: 1->2
ʾ�� 2:

����: 1->1->2->3->3
���: 1->2->3

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

//��дһ�������ҵ������������ཻ����ʼ�ڵ㡣
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    if (headA == NULL || headB == NULL) return NULL;
    struct ListNode *pA = headA, *pB = headB;
    while (pA != pB) {
        pA = pA == NULL ? headB : pA->next;
        pB = pB == NULL ? headA : pB->next;
    }
    return pA;
}


//�ݹ�ʵ��
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


//β�ݹ�ʵ��
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

//����ʵ��
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
��������?�ǿ� ������������ʾ�����Ǹ������������У����Ǹ��Ե�λ���ǰ���?����?�ķ�ʽ�洢�ģ��������ǵ�ÿ���ڵ�ֻ�ܴ洢?һλ?���֡�

��������ǽ��������������������᷵��һ���µ���������ʾ���ǵĺ͡�

�����Լ���������� 0 ֮�⣬���������������� 0?��ͷ��

ʾ����

���룺(2 -> 4 -> 3) + (5 -> 6 -> 4)
�����7 -> 0 -> 8
ԭ��342 + 465 = 807
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
148. ��������
�� O(n log n) ʱ�临�ӶȺͳ������ռ临�Ӷ��£��������������

ʾ�� 1:

����: 4->2->1->3
���: 1->2->3->4
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

