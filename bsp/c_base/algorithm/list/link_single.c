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
}SLINKLIST;

/*
  	head|first node|.........|tail|
 idx:    0  |      1      |.........|n   |

*/

struct ListNode* slink_init(void)
{
	/*head  has no usr data*/
	struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
	head->next = NULL;
	return head;
}


int slink_empty(struct ListNode *head)
{
	return head->next == NULL ? 1:0;
}


void slink_push_first(struct ListNode *head, int val)
{
	struct ListNode * newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
	newNode->val = val;
	newNode->next = head->next;
	head->next = newNode;
}


int slink_get_first(struct ListNode * head)
{
	if (head == NULL || head->next == NULL)
		return -1;

	struct ListNode * entry = head->next;
	return entry->val;
}


int slink_pop_first(struct ListNode * head)
{
	int ret = 0;
	if (head == NULL || head->next == NULL) {
		printf("%s err\n", __func__);
		return -1;
	}

	struct ListNode * entry = head;
	struct ListNode * del = entry->next;
	ret = del->val;
	entry->next = entry->next->next;
	free(del);
	del = NULL;
	return ret;
}


void slink_push_last(struct ListNode* head, int val)
{
    struct ListNode* entry = head;
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;

    while (entry) {
        if (entry->next == NULL) {
            entry->next = newNode;
            return;
        }
        entry = entry->next;
    }
}


int slink_get_last(struct ListNode * head)
{
    struct ListNode * entry = head;
    while(entry->next != NULL) {
        entry = entry->next;
    }

    return entry->val;
}


int  slink_pop_last(struct ListNode * head)
{
	struct ListNode * entry = head;
	while(entry->next != NULL) {
		if(entry->next->next == NULL) {
			struct ListNode * del = entry->next;
			int ret = del->val;
			entry->next = entry->next->next;
			free(del);
			del = NULL;
			return ret;
		}
		entry = entry->next;
	}

	return -1;
}


/** Add a node of value val before the idx-th node in the linked list.
If idx equals to the length of linked list,
the node will be appended to the end of linked list.
If idx is greater than the length, the node will not be inserted. */
void slink_insert_before_idx(struct ListNode *head, int idx, int val)
{
    int i = 0;

    if(idx < 0){
        slink_push_first(head, val);
        return;
    }

    struct ListNode * newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    newNode->val = val;

    struct ListNode * entry = head;
    while(entry !=  NULL) {
            if(i++ == idx){
                newNode->next = entry->next;
                entry->next = newNode;
                break;
            }
            entry = entry->next;
    }
}

void  slink_insert_before_idx2(struct ListNode * head,int idx,int val)
{
	if(idx < 0){
		slink_push_first(head, val);
		return;
	}

	struct ListNode * entry = head;//������ʱ���entry
	//�����ҵ�Ҫ����λ�õ���һ�����
	for (int i = 0; i < idx - 1; i++) {
		if (entry==NULL) {
			printf("%s err\n", __func__);
			return;
		}
		entry = entry->next;
	}
	//����������c
	struct ListNode * newNode =(struct ListNode *)malloc(sizeof(struct ListNode));
	newNode->val = val;
	//�������в�����
	newNode->next = entry->next;
	entry->next = newNode;
}


int slink_get_val_by_idx(struct ListNode * head, int idx)
{
    int i = 0;
    struct ListNode * entry = head;

    while(entry->next != NULL) {
        if(i++ == idx){
            return entry->next->val;
        }
        entry = entry->next;
    }

    return -1;
}


void slink_amend_val(struct ListNode * head, int idx, int newVal)
{
	struct ListNode * entry = head;
	entry = entry->next;//tampָ����Ԫ���
	for (int i = 1; i< idx; i++) {
		entry = entry->next;
	}
	entry->val = newVal;
}


int slink_get_idx_by_val(struct ListNode *head, int val)
{
    struct ListNode *t=head;
    int i = 1;
    while (t->next != NULL) {
        t = t->next;
        if (t->val==val) {
            return i;
        }
        i++;
    }
    return -1;
}


//����ɾ���ڵ�Ϊβ�ڵ�
void slink_del_by_node(struct ListNode * head,struct ListNode *delNode)
{
	if (delNode == NULL)
		return;

	if(delNode->next != NULL) {
		struct ListNode * pTemp = delNode->next;
		delNode->val = pTemp->val;
		delNode->next = pTemp->next;
		free(pTemp);
	} else {//last node
		struct ListNode * entry = head;
		while(entry != NULL) {
			if(entry->next == delNode) {
				free(delNode);
				entry->next = NULL;
			}
			entry = entry->next;
		}
	}
}


/** Delete the idx-th node in the linked list, if the idx is valid. */
void slink_del_by_idx(struct ListNode * head, int idx)
{
	int i = 0;
	struct ListNode * entry = head;
	while(entry->next != NULL) {
		if(i++ == idx) {
			struct ListNode * del = entry->next;//��������һ��ָ��ָ��ɾ����㣬�Է���ʧ
			entry->next = entry->next->next;
			free(del);
			break;
		}
		entry = entry->next;
	}
}


void slink_del_by_idx2(struct ListNode * head, int idx)
{
	struct ListNode *entry = head;
	//��������ɾ��������һ�����
	for (int i = 0; i< idx - 1; i++) {
		entry = entry->next;
	}
	struct ListNode * del = entry->next;//��������һ��ָ��ָ��ɾ����㣬�Է���ʧ
	entry->next = entry->next->next;//ɾ��ĳ�����ķ������Ǹ���ǰһ������ָ����
	free(del);//�ֶ��ͷŸý�㣬��ֹ�ڴ�й©
	return ;
}


void slink_del_by_value(struct ListNode *head, int value)
{
	struct ListNode *node1 = head;
	struct ListNode *node2 = NULL;

	if (head == NULL)
		return;

	if (node1->val == value) {
		head = head->next;
		free(node1);
		return;
	}

	while (node1 != NULL) {
		node2 = node1->next;
		if (node2->val == value) {
			node1->next = node2->next;
			free(node2);
			break;
		}
		node1 = node1->next;
	}
}


void slink_del_by_value2(struct ListNode* head, int val)
{
/*
ɾ��ֵ��ͬ��ͷ����
�����µ�ͷ���Ҳֵ��ȣ���ѭ�����
*/
	struct ListNode* entry;
	while(head != NULL && head->val == val) {
		entry = head;
		head = head->next;
		free(entry);
        }

	if(head == NULL)
		return;

	entry = head;
        //ȷ����ǰ�����н��
        while(entry->next != NULL) {
            if(entry->next->val == val) {
                entry->next = entry->next->next;
            } else {
                entry=entry->next;
            }
        }
        return head;
}


void slink_display(struct ListNode *head)
{
    struct ListNode *entry = head;
    while (entry->next != NULL) {
        entry = entry->next;
        printf("%d ",entry->val);
    }
    printf("\n");
}

void slink_display2(struct ListNode *pHead)
{
    while( pHead != NULL)
    {
        printf("%d ", pHead->val);
        pHead = pHead->next;
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
        slink_push_last(res, sum % 10);
        if (p != NULL) p = p->next;
        if (q != NULL) q = q->next;
    }

    if (carry > 0) {
        slink_push_last(res, carry);
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
	struct ListNode *entry=head;
	while(p!=NULL&&q!=NULL){
		if(p->val<=q->val){
			entry->next=p;
			entry=p;
			p=p->next;
		}else{
			entry->next=q;
			entry=q;
			q=q->next;
		}
	}
    entry->next=(p==NULL)?q:p;
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

/*
������ 02.02. ���ص����� k ���ڵ�
ʵ��һ���㷨���ҳ����������е�����
k ���ڵ㡣���ظýڵ��ֵ��
*/
int kthToLast(struct ListNode* head, int k){
	struct ListNode*  fast = head;
	struct ListNode*  slow = head;

	while(k--) {
		fast = fast->next;
	}

	while(fast != NULL) {
		fast = fast->next;
		slow = slow->next;
	}

	return slow->val;
}

int main()
{
    struct ListNode * head = slink_init();

    slink_push_first(head,1);
    slink_push_last(head,3);
    slink_insert_before_idx(head,1,2);
    int ret = slink_get_val_by_idx(head,1);
    printf("%d\n",ret);
    slink_del_by_idx(head,1);
    ret = slink_get_val_by_idx(head,1);
    printf("%d\n",ret);
}

