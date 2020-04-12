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

//#include "../../flag_type.h"
#include "flag_type.h"


typedef  struct ListNode {
      int val;
      struct ListNode *next;
}SLINKLIST;

/*
  	head|first node|.........|tail|
 idx:        |      0      |.........|n -1   |

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


void  slink_insert_before_idx(struct ListNode * head,int idx,int val)
{
	if(idx < 0){
		slink_push_first(head, val);
		return;
	}

	struct ListNode * entry = head;
	//首先找到要插入位置的上一个结点
	for (int i = 0; i < idx - 1; i++) {
		if (entry == NULL) {
			printf("%s err\n", __func__);
			return;
		}

		entry = entry->next;
	}

	struct ListNode * newNode =(struct ListNode *)malloc(sizeof(struct ListNode));
	newNode->val = val;
	newNode->next = entry->next;
	entry->next = newNode;
}


int slink_get_val_by_idx(struct ListNode * head, int idx)
{
    int i = 0;
    struct ListNode * entry = head;

    while(entry->next != NULL) {
        if(i++ == idx) {
            return entry->next->val;
        }
        entry = entry->next;
    }

    return -1;
}


void slink_amend_val(struct ListNode * head, int idx, int newVal)
{
    int i = 0;
    struct ListNode * entry = head;

    while(entry->next != NULL) {
        if(i++ == idx) {
		entry->next->val = newVal;
            return ;
        }
        entry = entry->next;
    }
}


int slink_get_idx_by_val(struct ListNode *head, int val)
{
    struct ListNode *entry = head;
    int i = 1;
    while (entry->next != NULL) {
        entry = entry->next;
        if (entry->val == val) {
            return i;
        }

        i++;
    }

    return -1;
}


//考虑删除节点为尾节点
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
			struct ListNode * del = entry->next;//单独设置一个指针指向被删除结点，以防丢失
			entry->next = entry->next->next;
			free(del);
			break;
		}
		entry = entry->next;
	}
}


void slink_del_by_value(struct ListNode* head, int val)
{
/*
删除值相同的头结点后，
可能新的头结点也值相等，用循环解决
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
        //确保当前结点后还有结点
        while(entry->next != NULL) {
            if(entry->next->val == val) {
                entry->next = entry->next->next;
            } else {
                entry=entry->next;
            }
        }
        return head;
}

/*
19. 删除链表的倒数第N个节点
难度中等780
给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
示例：
给定一个链表: 1->2->3->4->5, 和 n = 2.

当删除了倒数第二个节点后，链表变为 1->2->3->5.
说明：
给定的 n 保证是有效的。
进阶：
你能尝试使用一趟扫描实现吗？
*/
/*
链表中解决带间距的问题，首先想到的也是很常用的就是双指针。
让两个指针间隔 n+1个节点后两者同时后移，当跑得快的指针到达尾部时，跑的慢的指针的下一个节点刚好就是要被删除的节点，至此，问题迎刃而解。
然后注意边界问题，当待删除的元素刚好是第一个元素时需要特殊处理。
最后是参数合法，当 head == NULL 或 n 超出了链表长度需要特殊处理



*/
struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
	struct ListNode* dummy = calloc(1, sizeof(struct ListNode));
	dummy->next = head;
	struct ListNode*first = dummy;
	struct ListNode*second = dummy;
	for(int i = 1; i <= n+1;i++) {
		first = first->next;
	}

	while(first != NULL) {
		first = first->next;
		second = second->next;
	}

	second->next = second->next->next;
	return dummy->next;
}


void slink_display(struct ListNode *head)
{
	struct ListNode *entry = head;
	int id = 0;
	while (entry->next != NULL) {
		entry = entry->next;
		printf("[%d-%d]",id++, entry->val);
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
148. 排序链表
在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。

示例 1:

输入: 4->2->1->3
输出: 1->2->3->4
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
面试题 02.02. 返回倒数第 k 个节点
实现一种算法，找出单向链表中倒数第
k 个节点。返回该节点的值。
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
	slink_push_first(head, 1);
	slink_push_last(head, 3);
	slink_display(head);
	slink_insert_before_idx(head, 2, 2);
	slink_display(head);
	printf("slink_get_val_by_idx: %d\n", slink_get_val_by_idx(head, 2));
	slink_amend_val(head, 2, 5);
	printf("slink_get_val_by_idx: %d\n", slink_get_val_by_idx(head, 2));
	printf("slink_get_idx_by_val: %d\n", slink_get_idx_by_val(head, 5));
	slink_del_by_idx(head, 1);
	slink_display(head);
	return 0;

	slink_insert_before_idx(head,1,2);
	int ret = slink_get_val_by_idx(head,1);
	printf("%d\n",ret);
	slink_del_by_idx(head,1);
	ret = slink_get_val_by_idx(head,1);
	printf("%d\n",ret);
}

