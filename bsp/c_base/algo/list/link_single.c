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
	/*哨兵节点: head  has no usr data */
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
	struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
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

	while (entry != NULL) {
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

void  slink_insert_before_idx(struct ListNode * head, int idx, int val)
{
	if(idx < 0) {
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

	struct ListNode * newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
	newNode->val = val;
	newNode->next = entry->next;
	entry->next = newNode;//?
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
void (struct ListNode * head,struct ListNode *delNode)
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


struct ListNode* slink_del_by_value(struct ListNode* head, int val)
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
检测链表中是否存在环路有一个方法叫做快慢指针法，
即设置两个指针从起点同时出发，
慢指针每移动一步快指针移动两步，
如果存在环路则它们终究会相遇。
*/
bool hasCycle(struct ListNode *head)
{
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
面试题 02.08. 环路检测
难度中等11
给定一个有环链表，实现一个算法返回环路的开头节点。
有环链表的定义：在链表中某个节点的next元素指向在它前面出现过的节点，则表明该链表存在环路。


示例 1：
输入：head = [3,2,0,-4], pos = 1
输出：tail connects to node index 1
解释：链表中有一个环，其尾部连接到第二个节点。

*/

/*
整体思路：

检测有没有环，使用快慢指针slow和fast（一次走两步）；
找位置，当找到环之后，slow从head出发，fast从相遇点出发，一次都走一步，再次相遇为环的入口点
*/
struct ListNode *detectCycle(struct ListNode *head) {
	if (head == NULL || head->next == NULL) {
		return NULL;
	}

	struct ListNode *slow = head;
	struct ListNode *fast = head;
	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			break;
	}

	if (fast == NULL || fast->next == NULL)
		return NULL;

	slow = head;
	while(slow != fast) {
		slow = slow->next;
		fast = fast->next;
	}

	return slow;
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
给定一个排序链表，删除所有重复的元素，
使得每个元素只出现一次。

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
/*
82. 删除排序链表中的重复元素 II
给定一个排序链表，删除所有含有重复数字的节点，
只保留原始链表中 没有重复出现 的数字。
示例 1:
输入: 1->2->3->3->4->4->5
输出: 1->2->5
示例 2:
输入: 1->1->1->2->3
输出: 2->3
*/
/*
快慢指针
1.设置dummy节点以便删除头节点重复元素
2.当slow下一段节点为重复节点时，设置临时节点fast向前探路，
当走到重复节点最后一个节点时，让slow->next = fast->next。
*/
struct ListNode* deleteDuplicates(struct ListNode* head)
{
//假设1->1->3->3->4
	struct ListNode dmy;
	struct ListNode* slow = &dmy;
	slow->next = head;
	while(slow->next && slow->next->next) {// 1->1满足条件
		if (slow->next->val == slow->next->next->val) {
			struct ListNode * fast = slow->next;
			while(fast && fast->next && fast->val == fast->next->val) {//不满足
				fast = fast->next;
			}

			slow->next = fast->next;//跳过前面重复节点，直接3->3-4
		} else
			slow = slow->next;
	}

	return dmy.next;
}

/*
1171. 从链表中删去总和值为零的连续节点
给你一个链表的头节点 head，请你编写代码，反复删去链表中由 总和 值为 0 的连续节点组成的序列，直到不存在这样的序列为止。

删除完毕后，请你返回最终结果链表的头节点。



你可以返回任何满足题目要求的答案。

（注意，下面示例中的所有序列，都是对 ListNode 对象序列化的表示。）

示例 1：

输入：head = [1,2,-3,3,1]
输出：[3,1]
提示：答案 [1,2,1] 也是正确的。
*/
struct ListNode* removeZeroSumSublists(struct ListNode* head){
    struct ListNode* pre = (struct ListNode*)malloc(sizeof(struct ListNode));
    pre->val = 0;
    pre->next = head;
    struct ListNode* p = pre;
    while (p){
        int sum = 0;
        struct ListNode* q = p->next;
        while (q){
            sum += q->val;
            if (sum == 0){
                p->next = q->next;
            }
            q = q->next;
        }
        p = p->next;
    }
    return pre->next;
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
//意思是如果链表只有一个节点的时候反转也是它自己，直接返回即可。
	if (pHead == NULL || pHead->next == NULL) {
		return pHead;
	}

	struct ListNode *p = pHead->next;
	struct ListNode *pNewHead = reverse(p);
	p->next = pHead;
	pHead ->next = NULL;
	return pNewHead;
}


//尾递归实现
struct ListNode *do_reverse_tail(struct ListNode *pHead, struct ListNode *pNewHead)
{
	if(pHead == NULL)
		return pNewHead;

	struct ListNode *pNext = pHead->next;
	pHead->next = pNewHead;
	return do_reverse_tail(pNext, pHead);
}

struct ListNode * reverse_tail(struct ListNode *pHead)
{
    return do_reverse_tail(pHead, NULL);
}

/*
迭代实现
在看具体算法之前，有必要先弄清楚链接反转的原理以及需要哪些指针。举例而言，有一个三个不同结点组成的链表 A → B → C，需要反转结点中的链接成为 A ← B ← C。

假设我们有两个指针，一个指向结点 A，一个指向结点 B。 分别记为 prev 和 cur。则可以用这两个指针简单地实现 A 和 B 之间的链接反转：


cur.next = prev
这样做唯一的问题是，没有办法继续下去，换而言之，这样做之后就无法再访问到结点 C。因此，我们需要引入第三个指针，用于帮助反转过程的进行。因此，我们不采用上面的反转方法，而是：


third = cur.next
cur.next = prev
prev = cur
cur = third

*/
struct ListNode * reverse_it(struct ListNode *pHead)
{
	struct ListNode *pNewHead = NULL;
	struct ListNode *pPrev = NULL;
	struct ListNode *pCur = pHead;

	while(pCur != NULL) {
		struct ListNode *pTmp = pCur->next;
		if(pTmp == NULL) {
			pNewHead = pCur;
		}
		pCur->next = pPrev;
		pPrev = pCur;
		pCur = pTmp;
	}

	return pNewHead;
}

/*
92. 反转链表 II
反转从位置 m 到 n 的链表。请使用一趟扫描完成反转。

说明:
1 ≤ m ≤ n ≤ 链表长度。

示例:

输入: 1->2->3->4->5->NULL, m = 2, n = 4
输出: 1->4->3->2->5->NULL
*/
struct ListNode* reverseBetween(struct ListNode* head, int m, int n)
{
        // Empty list
        if (head == NULL) {
            return NULL;
        }

        // Move the two pointers until they reach the proper starting point
        // in the list.
        struct ListNode*cur = head;
	struct ListNode *prev = NULL;
        while (m > 1) {
            prev = cur;
            cur = cur->next;
            m--;
            n--;
        }

        // The two pointers that will fix the final connections.
        struct ListNode*con = prev;
	struct ListNode* tail = cur;

        // Iteratively reverse the nodes until n becomes 0.
        struct ListNode* third = NULL;
        while (n > 0) {
            third = cur->next;
            cur->next = prev;
            prev = cur;
            cur = third;
            n--;
        }

        // Adjust the final connections as explained in the algorithm
        if (con != NULL) {
            con->next = prev;
        } else {
            head = prev;
        }

        tail->next = cur;
        return head;
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
给出两个?非空 的链表用来表示两个非负的整数。
其中，它们各自的位数是按照?逆序?的方式存储的，
并且它们的每个节点只能存储?一位?数字。

如果，我们将这两个数相加起来，
则会返回一个新的链表来表示它们的和。

您可以假设除了数字 0 之外，这两个数都不会以 0?开头。

示例：

输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807
*/
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
	struct ListNode* p = l1;
	struct ListNode* q = l2;
	int plus = 0;

	struct ListNode* ret = slink_init();
	while(p != NULL || q != NULL) {
		int x = p != NULL ? p->val : 0;
		int y = q != NULL ? q->val : 0;
		int sum = plus + x + y;
		plus = sum / 10;
		slink_push_last(ret, sum % 10);
		if (p != NULL) p = p->next;
		if (q != NULL) q = q->next;
	}

	if (plus > 0)  {
		slink_push_last(ret, plus);
	}

	return ret->next;
}
/*
445. 两数相加 II
给你两个 非空 链表来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。

你可以假设除了数字 0 之外，这两个数字都不会以零开头。



进阶：

如果输入链表不能修改该如何处理？换句话说，你不能对列表中的节点进行翻转。



示例：

输入：(7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 8 -> 0 -> 7
*/
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
	struct List astack;
	stack_init(&astack);

	struct List bstack;
	stack_init(&bstack);

	struct ListNode* iter = l1;
	while(iter != NULL) {
		stack_push_key(&astack, iter->val);
		iter = iter->next;
	}

	iter = l2;
	while(iter != NULL) {
		stack_push_key(&bstack, iter->val);
		iter = iter->next;
	}

	struct ListNode* ret = slink_init();

	int plus = 0;
	while(!stack_empty(&astack) || !stack_empty(&bstack)) {
		int a = 0;
		if (!stack_empty(&astack)) {
			struct DataEntry *aentry = stack_pop_entry(&astack);
			a = aentry->key;
			free(aentry);
		}

		int b = 0;
		if (!stack_empty(&bstack)) {
			struct DataEntry *bentry = stack_pop_entry(&bstack);
			b = bentry->key;
			free(bentry);
		}

		int sum = a + b + plus;
		plus = sum / 10;
		sum = sum % 10;
		slink_push_first(ret, sum);
	}

	if (plus != 0)
		slink_push_first(ret, plus);

	return ret->next;
}


/*
148. 排序链表
在 O(n log n) 时间复杂度和常数级空间复杂度下，
对链表进行排序。

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
struct ListNode* sortList(struct ListNode* head)
{
    if(head==NULL||head->next==NULL)
		return head;
	struct ListNode*p=head;
	struct ListNode*q=head->next;
	while(q!=NULL&&q->next!=NULL){
		p=p->next;q=q->next->next;
	}
	q=p->next;
	p->next=NULL;
	return merge_sotrlist(sortList(head),sortList(q));
}
/*
147. 对链表进行插入排序
对链表进行插入排序。


插入排序的动画演示如上。从第一个元素开始，该链表可以被认为已经部分排序（用黑色表示）。
每次迭代时，从输入数据中移除一个元素（用红色表示），并原地将其插入到已排好序的链表中。



插入排序算法：

插入排序是迭代的，每次只移动一个元素，直到所有元素可以形成一个有序的输出列表。
每次迭代中，插入排序只从输入数据中移除一个待排序的元素，找到它在序列中适当的位置，并将其插入。
重复直到所有输入数据插入完为止。


示例 1：

输入: 4->2->1->3
输出: 1->2->3->4
示例 2：

输入: -1->5->3->4->0
输出: -1->0->3->4->5
*/
struct ListNode* insertionSortList(struct ListNode* head)
{
if(!head)
        return NULL;
struct ListNode * p,*q;
int temp;

for(p=head;p;p=p->next)
{
     for(q=p->next;q;q=q->next)
     {
        if(p->val>q->val)
        {
            temp=p->val;
            p->val=q->val;
            q->val=temp;
        }
     }

}
    return head;
}

struct ListNode* insertionSortList(struct ListNode* head)
{
     if(!head)
        return NULL;

struct ListNode *L,*p,*q;
L=(struct ListNode*)malloc(sizeof(struct ListNode));
L->next=head;

p=head->next;
head->next=NULL;
while(p)
{
     struct ListNode *curr=p->next;
     q=L;
     while(q->next&&q->next->val<=p->val)
         q=q->next;
     p->next=q->next;
     q->next=p;
     p=curr;
}
     return L->next;

}

/*
61. 旋转链表
难度中等271
给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。
示例 1:
输入: 1->2->3->4->5->NULL, k = 2
输出: 4->5->1->2->3->NULL
解释:
向右旋转 1 步: 5->1->2->3->4->NULL
向右旋转 2 步: 4->5->1->2->3->NULL
}
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* rotateRight(struct ListNode* head, int k)
{
    // base cases
    if (head == NULL) return NULL;
    if (head->next == NULL) return head;

    // close the linked list into the ring
    struct ListNode* old_tail = head;
    int n;
    for(n = 1; old_tail->next != NULL; n++)
      old_tail = old_tail->next;

    old_tail->next = head;

    // find new tail : (n - k % n - 1)th node
    // and new head : (n - k % n)th node
    struct ListNode* new_tail = head;
    for (int i = 0; i < n - k % n - 1; i++)
      new_tail = new_tail->next;

    struct ListNode* new_head = new_tail->next;

    // break the ring
    new_tail->next = NULL;

    return new_head;
}

/*
86. 分隔链表
给定一个链表和一个特定值 x，对链表进行分隔，使得所有小于 x 的节点都在大于或等于 x 的节点之前。

你应当保留两个分区中每个节点的初始相对位置。

示例:

输入: head = 1->4->3->2->5->2, x = 3
输出: 1->2->2->4->3->5
*/
struct ListNode* partition(struct ListNode* head, int x){
        // before and after are the two pointers used to create the two list
        // before_head and after_head are used to save the heads of the two lists.
        // All of these are initialized with the dummy nodes created.
        struct ListNode* before_head = (struct ListNode*)calloc(1, sizeof(struct ListNode));
        struct ListNode* before = before_head;
        struct ListNode* after_head = (struct ListNode*)calloc(1, sizeof(struct ListNode));
        struct ListNode* after = after_head;

        while (head != NULL) {

            // If the original list node is lesser than the given x,
            // assign it to the before list.
            if (head->val < x) {
                before->next = head;
                before = before->next;
            } else {
                // If the original list node is greater or equal to the given x,
                // assign it to the after list.
                after->next = head;
                after = after->next;
            }

            // move ahead in the original list
            head = head->next;
        }

        // Last node of "after" list would also be ending node of the reformed list
        after->next = NULL;

        // Once all the nodes are correctly assigned to the two lists,
        // combine them to form a single list which would be returned.
        before->next = after_head->next;

        return before_head->next;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* partition(struct ListNode* head, int x)
{
           struct ListNode* pre=head;
           struct ListNode* cur=head;
// cur走的比pre快， pre之前都小于x，pre到cur之间都是大于等于x的，当cur的值小于x时，于pre交换
            while(cur){
                if(cur->val<x){
                    int tmp=pre->val;
                    pre->val=cur->val;
                    cur->val=tmp;
                    pre=pre->next;
                }
                cur=cur->next;

            }
            return head;
}





