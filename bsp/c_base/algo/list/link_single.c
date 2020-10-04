/*

哨兵节点head--->node1-->node2--->NULL

链表遍历方式
while (entry != NULL) {
	do
	entry = entry->next;
}

for (struct ListNode * p = head; p != NULL; p = p->next) {
        // 访问 p.val
}

void traverse(struct ListNode * head)
{
    // 访问 head.val
    traverse(head->next)
}

快慢指针:
环路问题
对称问题
到达中间位置

删除动作:搞一个dummy节点
*/

struct ListNode {
     int val;
    struct ListNode *next;
};

struct ListNode* slink_init(void)
{
	/*哨兵节点: head  has no usr data */
	struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
	head->next = NULL;
	return head;
}

int slink_isEmpty(struct ListNode *head)
{
	if (head == NULL)
		return 1;

	return head->next == NULL ? 1:0;
}

void slink_first_push(struct ListNode *head, int val)
{
	struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
	newNode->val = val;
	newNode->next = head->next;
	head->next = newNode;
}

int slink_first_top(struct ListNode * head)
{
	if (slink_isEmpty(head))
		return -1;

	struct ListNode * entry = head->next;
	return entry->val;
}

int slink_first_pop(struct ListNode * head)
{
	int ret = 0;
	if (slink_isEmpty(head))
		return -1;

	struct ListNode *entry = head;
	struct ListNode *del = entry->next;
	ret = del->val;
	entry->next = entry->next->next;
	free(del);
	del = NULL;
	return ret;
}

void slink_last_push(struct ListNode* head, int val)
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

int slink_last_top(struct ListNode * head)
{
	struct ListNode * entry = head;
	while(entry->next != NULL) {
		entry = entry->next;
	}

	return entry->val;
}

int  slink_last_pop(struct ListNode * head)
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

/*
新建链表,头节点插入法
新建一个头结点，遍历原链表，把每个节点用头结点插入
到新建链表中。最后，新建的链表就是反转后的链表。
*/
struct ListNode *slink_reverse(struct ListNode * head)
{
	struct ListNode * dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
	struct ListNode * pCur = head;

	while (pCur != NULL) {
		struct ListNode * pNex = pCur->next;

		pCur->next = dummy->next;
		dummy->next = pCur;
		pCur = pNex;
	}

	return dummy->next;
}

struct ListNode *slink_reverse(struct ListNode * head)
{
        if(head == NULL || head.next == NULL){
            return head;
        }

	struct ListNode *prep, *nextp;
	prep = nextp = NULL;
	while(head != NULL){
		nextp = head->next;
		head->next = prep;
		prep = head;
		head = nextp;
	}
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
链表中解决带间距的问题，首先想到的也是很常用的就是
双指针。
让两个指针间隔 n+1个节点后两者同时后移，当跑得快的指
针到达尾部时，跑的慢的指针的下一个节点刚好就是要被
删除的节点，至此，问题迎刃而解。
然后注意边界问题，当待删除的元素刚好是第一个元素时
需要特殊处理。
最后是参数合法，当 head == NULL 或 n 超出了链表长度需要特
殊处理
*/
struct ListNode* removeNthFromEnd(struct ListNode* head, int n)
{
	struct ListNode* dummy = calloc(1, sizeof(struct ListNode));
	dummy->next = head;
	struct ListNode*fast = dummy;
	struct ListNode*slow = dummy;
	for(int i = 0; i <= n; i++) {
		fast = fast->next;
	}

	while(fast != NULL) {
		fast = fast->next;
		slow = slow->next;
	}

	slow->next = slow->next->next;
	return dummy->next;
}

/*
141. 环形链表
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
	struct ListNode *fast = head;
	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			return true;
	}

	return false;
}

/*
面试题 02.08. 环路检测
难度中等11
给定一个有环链表，实现一个算法返回环路的开头节点。
有环链表的定义：在链表中某个节点的next元素指向在它前
面出现过的节点，则表明该链表存在环路。

示例 1：
输入：head = [3,2,0,-4], pos = 1
输出：tail connects to node index 1
解释：链表中有一个环，其尾部连接到第二个节点。
*/

/*
整体思路：
检测有没有环，使用快慢指针slow和fast（一次走两步）；
找位置，当找到环之后，slow从head出发，fast从相遇点出发，
一次都走一步，再次相遇为环的入口点
*/
struct ListNode *detectCycle(struct ListNode *head)
{
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
234. 回文链表
请判断一个链表是否为回文链表。
示例 1:
输入: 1->2
输出: false
示例 2:
输入: 1->2->2->1
输出: true
*/
bool isPalindrome(struct ListNode* head)
{
	// 特殊情况的排除
	if(head == NULL || head->next == NULL)
		return true;

	if(head->next->next == NULL){
		if(head->val == head->next->val)
			return true;
		else
			return false;
	}

	struct ListNode *fast, *slow;
	fast = head->next->next;
	slow = head->next;

	while(fast != NULL && fast->next != NULL){
		fast = fast->next->next;
		slow = slow->next;
	}

	//而后我们可以翻转中部之前的链表，以便于后续比较。
	// 翻转中部前链表序列
	struct ListNode *prep, *nextp;
	prep = nextp = NULL;
	while(head != slow){
		nextp = head->next;
		head->next = prep;
		prep = head;
		head = nextp;
	}

	// 若结点个数为奇数，则舍弃中间结点
	if(fast != NULL && fast->next == NULL)
		slow = slow->next;

	// 回文匹配比较
	while(prep != NULL) {
		if(prep->val != slow->val)
			return false;
		prep = prep->next;
		slow = slow->next;
	}
	return true;
}

/*
83. 删除排序链表中的重复元素
给定一个排序链表，删除所有重复的元素，
使得每个元素只出现一次。
示例 1:
输入: 1->1->2
输出: 1->2
示例 2:
输入: 1->1->2->3->3
输出: 1->2->3
*/
struct ListNode* deleteDuplicates(struct ListNode* head)
{
	struct ListNode* entry = head;
	while (entry != NULL && entry->next != NULL) {
		if (entry->next->val == entry->val) {
			entry->next = entry->next->next;
		} else {
			entry = entry->next;
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
	struct ListNode dummy;
	struct ListNode* slow = &dummy;
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

	return dummy.next;
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
		slink_last_push(ret, sum % 10);
		if (p != NULL) p = p->next;
		if (q != NULL) q = q->next;
	}

	if (plus > 0)  {
		slink_last_push(ret, plus);
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
		slink_first_push(ret, sum);
	}

	if (plus != 0)
		slink_first_push(ret, plus);

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

/*
146. LRU缓存机制
难度中等768
运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制。它应该支持以下操作： 获取数据 get 和 写入数据 put 。
获取数据 get(key) - 如果关键字 (key) 存在于缓存中，则获取关键字的值（总是正数），否则返回 -1。
写入数据 put(key, value) - 如果关键字已经存在，则变更其数据值；如果关键字不存在，则插入该组「关键字/值」。当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。

进阶:
你是否可以在 O(1) 时间复杂度内完成这两种操作？

示例:
LRUCache cache = new LRUCache( 2 /* 缓存容量 */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // 返回  1
cache.put(3, 3);    // 该操作会使得关键字 2 作废
cache.get(2);       // 返回 -1 (未找到)
cache.put(4, 4);    // 该操作会使得关键字 1 作废
cache.get(1);       // 返回 -1 (未找到)
cache.get(3);       // 返回  3
cache.get(4);       // 返回  4

*/


typedef struct {
	int capacity;
	struct List list;
	struct HashTable ht;
} LRUCache;


LRUCache* lRUCacheCreate(int capacity) {
	LRUCache *obj = (LRUCache *)calloc(1, sizeof(LRUCache));
	obj->capacity = capacity;
	ListInit(&obj->list);
	HashInit(&obj->ht, capacity, hashequal_int, hashcode_int);
	return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
/*
获取数据 get(key) - 如果关键字 (key) 存在于缓存中，
则获取关键字的值（总是正数），否则返回 -1。
*/
	int value = -1;
	struct DataEntry *find = hashFindKey(&obj->ht, key);
	if (find != NULL) {
		struct DataEntry *linkNode = NODE_ENTRY(find->link, struct DataEntry, node);
		value = linkNode->value;

		ListRemove(find->link);
		ListAddTail(&obj->list, find->link);
	}

	return value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
/*
写入数据 put(key, value) - 如果关键字已经存在，
则变更其数据值；
如果关键字不存在，
则插入该组「关键字/值」。当缓存容量达到上限时，
它应该在写入新数据之前删除最久未使用的数据值，
从而为新的数据值留出空间。
*/
struct DataEntry *find = hashFindKey(&obj->ht, key);
	if (find != NULL) {
		struct DataEntry *linkNode = NODE_ENTRY(find->link, struct DataEntry, node);
		linkNode->value = value;

		ListRemove(find->link);
		ListAddTail(&obj->list, find->link);

		return;
	}

	if (obj->capacity <= 0) {
		struct Node *node;
		node = obj->list.base.next;
		struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);

		struct DataEntry *del = hashFindKey(&obj->ht, entry->key);
		HashRemove(&del->node);

		ListRemoveHead(&obj->list);
		obj->capacity++;
	}

	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
	entry->key = key;
	entry->value = value;
	ListAddTail(&obj->list, &entry->node);

	struct DataEntry *hashentry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
	hashentry->key = key;
	hashentry->link = &entry->node;
	HashAdd(&obj->ht, &hashentry->node);

	obj->capacity--;
}

void lRUCacheFree(LRUCache* obj) {
	ListDeinit(&obj->list, node_free);
	HashDeinit(&obj->ht, node_free);
	free(obj);
}

/*
460. LFU缓存
难度困难238
请你为 最不经常使用（LFU）缓存算法设计并实现数据结构。它应该支持以下操作：get 和 put。
"	get(key) - 如果键存在于缓存中，则获取键的值（总是正数），否则返回 -1。
"	put(key, value) - 如果键已存在，则变更其值；如果键不存在，请插入键值对。当缓存达到其容量时，则应该在插入新项之前，使最不经常使用的项无效。在此问题中，当存在平局（即两个或更多个键具有相同使用频率）时，应该去除最久未使用的键。
「项的使用次数」就是自插入该项以来对其调用 get 和 put 函数的次数之和。使用次数会在对应项被移除后置为 0 。

进阶：
你是否可以在 O(1) 时间复杂度内执行两项操作？

示例：
LFUCache cache = new LFUCache( 2 /* capacity (缓存容量) */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // 返回 1
cache.put(3, 3);    // 去除 key 2
cache.get(2);       // 返回 -1 (未找到key 2)
cache.get(3);       // 返回 3
cache.put(4, 4);    // 去除 key 1
cache.get(1);       // 返回 -1 (未找到 key 1)
cache.get(3);       // 返回 3
cache.get(4);       // 返回 4
*/
struct DListNode {
  int key;                         //键
  int value;                       //值
  int freq;                        //访问频率
  struct DListNode *prior, *next;  //前驱，后继
};

typedef struct {
  struct DListNode* head;
  int capacity;
} LFUCache;

LFUCache* lFUCacheCreate(int capacity) {
  LFUCache* cache = (LFUCache*)malloc(sizeof(LFUCache));
  // 初始化设置头结点
  cache->capacity = capacity;
  cache->head = (struct DListNode*)malloc(sizeof(struct DListNode));
  cache->head->prior = NULL;
  cache->head->next = NULL;
  return cache;
}

// 结点提升，插入排序的感觉，相同频率的放在同频率的最前面
void lFUCaacheUp(LFUCache* obj, struct DListNode* p) {
  struct DListNode* q;
  p->freq++;
  if (p->next) {  //如果当前结点是最后一个结点，
    p->next->prior = p->prior;
    p->prior->next = p->next;  //将p结点从链表上摘下
  } else
    p->prior->next = NULL;
  q = p->prior;
  while (q != obj->head && q->freq <= p->freq)  //向前查找p结点的插入位置
    q = q->prior;
  p->next = q->next;  //将p结点插入，排在同频率的第一个
  if (q->next != NULL)
    q->next->prior = p;
  p->prior = q;
  q->next = p;
}

int lFUCacheGet(LFUCache* obj, int key) {
  int count = 0;
  struct DListNode *p = obj->head->next, *q;
  // 遍历链表，查找元素
  while (p && p->key != key && count < obj->capacity) {
    p = p->next;
    count++;
  }
  // 不存在返回 -1
  if (p == NULL || count == obj->capacity) return -1;
  // 存在：访问频率加一，按访问频率调整链表，返回值
  lFUCaacheUp(obj, p);
  return p->value;
}

void lFUCachePut(LFUCache* obj, int key, int value) {
  int count = 0;
  struct DListNode *p = obj->head, *q;
  // 先遍历链表找 key 是否存在
  while (p->next != NULL && p->next->key != key && count < obj->capacity) {
    p = p->next;
    count++;
  }
  // key已存在更新 结点，按访问频率调整链表
  if (p->next != NULL && p->next->key == key && count < obj->capacity) {  //key值已存在
    p->next->value = value;
    lFUCaacheUp(obj, p->next);
    return;
  }
  count = 0;
  p = obj->head;
  while (p->next != NULL && p->next->freq > 1 && count < obj->capacity) {
    p = p->next;
    count++;
  }
  if (count == obj->capacity) {  //到达表尾，直接覆盖尾结点
    p->key = key;
    p->value = value;
    p->freq = 1;
  } else {  //未到达表尾
    // 创建结点，存值
    struct DListNode* s = (struct DListNode*)malloc(sizeof(struct DListNode));
    s->key = key;
    s->value = value;
    s->freq = 1;
    // 插入
    s->next = p->next;
    s->prior = p;
    p->next = s;
    if (s->next)
      s->next->prior = s;
    else
      s->next = NULL;
  }
}

void lFUCacheFree(LFUCache* obj) {
  if (obj == NULL) return;
  struct DListNode* s;
  while (obj->head) {
    s = obj->head;
    obj->head = obj->head->next;
    free(s);
  }
  free(obj);
}

#define LEN 10001
typedef struct {
    int key;
    int value;
    int times;
} Nums;

typedef struct {
    Nums queue[LEN];
    int start;
    int end;
    int capacity;
} LFUCache;

int Compare(const void *a, const void *b)
{
    Nums *aa = (Nums *)a;
    Nums *bb = (Nums *)b;
    return aa->times - bb->times;
}

void Sort(Nums *nums, int start, int end, Nums n)
{
    for (int i = start; i < end - 1; i++) {
        if (nums[i].times >= nums[i + 1].times) {
            nums[i] = nums[i + 1];
            nums[i + 1] = n;
            continue;
        }
        break;
    }
}

LFUCache* lFUCacheCreate(int capacity) {
    LFUCache *catch = (LFUCache *)malloc(sizeof(LFUCache));
    catch->start = 0;
    catch->end = 0;
    catch->capacity = capacity;
    return catch;
}

int lFUCacheGet(LFUCache* obj, int key) {
    int value = -1;
    int start = obj->start;
    int end = obj->end;
    for (int i = start; i < end; i++) {
        if (obj->queue[i].key == key) {
            value = obj->queue[i].value;
            obj->queue[i].times++;
            Sort(obj->queue, i, obj->end, obj->queue[i]);
            break;
        }
    }
    return value;
}

void lFUCachePut(LFUCache* obj, int key, int value) {
    Nums n = {0};
    n.key = key;
    n.value = value;
    n.times = 1;
    if (lFUCacheGet(obj, key) == -1) {
        obj->queue[obj->end++] = n;
        if (obj->end - obj->start > obj->capacity) {
            obj->start++;
        }
        int len = obj->end - obj->start;
        qsort(obj->queue + obj->start, len, sizeof(Nums), Compare);
    } else {
        for (int i = obj->start; i < obj->end; i++) {
            if (obj->queue[i].key == key) {
                 obj->queue[i].value = value;
                obj->queue[i].times++;
                Sort(obj->queue, i, obj->end, obj->queue[i]);
                break;
            }
        }
    }
}

void lFUCacheFree(LFUCache* obj) {
    free(obj);
}

/**
 * Your LFUCache struct will be instantiated and called as such:
 * LFUCache* obj = lFUCacheCreate(capacity);
 * int param_1 = lFUCacheGet(obj, key);

 * lFUCachePut(obj, key, value);

 * lFUCacheFree(obj);
*/

/*
23. 合并K个升序链表
给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。



示例 1：

输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct  ListNode* mergeTwoLists(struct ListNode *a, struct ListNode *b) {
        if ((!a) || (!b)) return a ? a : b;
        struct ListNode head, *tail = &head, *aPtr = a, *bPtr = b;
        while (aPtr && bPtr) {
            if (aPtr->val < bPtr->val) {
                tail->next = aPtr; aPtr = aPtr->next;
            } else {
                tail->next = bPtr; bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr ? aPtr : bPtr);
        return head.next;
    }


struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
 	struct ListNode *ans = NULL;
        for (size_t i = 0; i < listsSize; ++i) {
            ans = mergeTwoLists(ans, lists[i]);
        }
        return ans;

}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct  ListNode* mergeTwoLists(struct ListNode *a, struct ListNode *b) {
        if ((!a) || (!b)) return a ? a : b;
        struct ListNode head, *tail = &head, *aPtr = a, *bPtr = b;
        while (aPtr && bPtr) {
            if (aPtr->val < bPtr->val) {
                tail->next = aPtr; aPtr = aPtr->next;
            } else {
                tail->next = bPtr; bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr ? aPtr : bPtr);
        return head.next;
    }

 struct ListNode* merge(struct ListNode **lists, int l, int r) {
        if (l == r) return lists[l];
        if (l > r) return NULL;
        int mid = (l + r) >> 1;
        return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
    }



struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
	return merge(lists, 0, listsSize - 1);
}




void swap(struct ListNode **tree, int i, int j) {
    struct ListNode *tmp = tree[i];
    tree[i] = tree[j];
    tree[j] = tmp;
}

void heapify(struct ListNode **tree, int n, int i) {
    /* 本函数从上到下依次将最大值下沉，即最小堆实现 */
    if (i >= n) return;  // 叶子节点超界
    int minIdx = i;  // 最小节点索引
    int left = 2 * i + 1, right = 2 * i + 2;  // 左右孩子节点索引
    if (left < n && tree[left]->val < tree[minIdx]->val) {
        minIdx = left;
    }
    if (right < n && tree[right]->val < tree[minIdx]->val) {
        minIdx = right;
    }
    if (minIdx != i) {
        /* 如果当前节点不是最小堆，交换然后依次递归下去构建最小堆 */
        swap(tree, i, minIdx);
        heapify(tree, n, minIdx);  // 注意传参是minIdx继续整理堆
    }
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
    // 1.特判空列表
    if (listsSize < 1 || lists == NULL) return NULL;  // [[]]不能判断
    // 2.构建最小堆实现
    struct ListNode **tree = (struct ListNode**)malloc(sizeof(struct ListNode*) * listsSize);
    for (int i = 0, j = listsSize, k = 0; i < j; i++) {
        if (!lists[i]) listsSize--;  // NULL
        else tree[k++] = lists[i];
    }
    if (listsSize <= 0) return NULL;
    int idx = ((listsSize - 1) - 1) / 2;  // 获取最后一个叶子节点下标
    for (; idx >= 0; idx--) heapify(tree, listsSize, idx);
    /* 3.堆进行维护，每次“替换”最小值
    * 如果空表，移到最后对剩下元素维护堆，直到最后堆的大小为0结束。
    */
    struct ListNode *dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *prev = dummy, *curr;
    while (listsSize > 0) {
        /* 每次从堆顶取最小元素的节点出来，然后构建链表后整理堆
        * 1.如果当前堆顶元素无后续节点，那么将其与最后idx交换，下次整理堆数量-1
        * 2.如果当前堆顶元素有后继节点，那么继续构建表后整理堆。
        * 整理堆永远是从0号位置开始，只是整理数量listsSize下降而已。
        */
        curr = tree[0];
        if (curr->next == NULL) {
            swap(tree, listsSize - 1, 0);  // 与最后一位交换
            listsSize--;  // 下次整理堆数量减少1
        } else tree[0] = tree[0]->next;
        prev->next = curr;
        prev = curr;
        heapify(tree, listsSize, 0);
    }
    return dummy->next;
}

/*
355. 设计推特
设计一个简化版的推特(Twitter)，可以让用户实现发送推文，关注/取消关注其他用户，能够看见关注人（包括自己）的最近十条推文。你的设计需要支持以下的几个功能：

postTweet(userId, tweetId): 创建一条新的推文
getNewsFeed(userId): 检索最近的十条推文。每个推文都必须是由此用户关注的人或者是用户自己发出的。推文必须按照时间顺序由最近的开始排序。
follow(followerId, followeeId): 关注一个用户
unfollow(followerId, followeeId): 取消关注一个用户
示例:

Twitter twitter = new Twitter();

// 用户1发送了一条新推文 (用户id = 1, 推文id = 5).
twitter.postTweet(1, 5);

// 用户1的获取推文应当返回一个列表，其中包含一个id为5的推文.
twitter.getNewsFeed(1);

// 用户1关注了用户2.
twitter.follow(1, 2);

// 用户2发送了一个新推文 (推文id = 6).
twitter.postTweet(2, 6);

// 用户1的获取推文应当返回一个列表，其中包含两个推文，id分别为 -> [6, 5].
// 推文id6应当在推文id5之前，因为它是在5之后发送的.
twitter.getNewsFeed(1);

// 用户1取消关注了用户2.
twitter.unfollow(1, 2);

// 用户1的获取推文应当返回一个列表，其中包含一个id为5的推文.
// 因为用户1已经不再关注用户2.
twitter.getNewsFeed(1);
*/
#define MAX_SIZE 512

struct User {
  int id;                  //用户id
  int followee[MAX_SIZE];  //用户关注的用户id  (基于数组的散列)
};

struct Tweet {
  int userId;   //用户id
  int tweetId;  //推特id
  struct Tweet* next;
};

typedef struct {
  struct User* user;
  struct Tweet* tweet;
} Twitter;

/** Initialize your data structure here. */
Twitter* twitterCreate() {
  Twitter* twitter = (Twitter*)malloc(sizeof(Twitter));
  twitter->user = (struct User*)calloc(MAX_SIZE, sizeof(struct User));
  twitter->tweet = (struct Tweet*)malloc(sizeof(struct Tweet));
  twitter->tweet->next = NULL;
  return twitter;
}

/** Compose a new tweet. */
void twitterPostTweet(Twitter* obj, int userId, int tweetId) {
  struct Tweet* tweet = (struct Tweet*)malloc(sizeof(struct Tweet));
  tweet->userId = userId;
  tweet->tweetId = tweetId;
  tweet->next = obj->tweet->next;  //头插法,保证最后发布的推文在最前面
  obj->tweet->next = tweet;
}

/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
int* twitterGetNewsFeed(Twitter* obj, int userId, int* retSize) {
  int* ret = (int*)calloc(10, sizeof(int));
  *retSize = 0;
  struct Tweet* tweet = obj->tweet->next;
  struct User* user = obj->user;
  while (tweet && *retSize < 10) {  //用户自己及用户关注的人的推文
    if (tweet->userId == userId || (user + userId)->followee[tweet->userId] == 1)
      ret[(*retSize)++] = tweet->tweetId;
    tweet = tweet->next;
  }
  return ret;
}

/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
void twitterFollow(Twitter* obj, int followerId, int followeeId) {
  (obj->user + followerId)->followee[followeeId] = 1;
}

/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
void twitterUnfollow(Twitter* obj, int followerId, int followeeId) {
  (obj->user + followerId)->followee[followeeId] = 0;
}

void twitterFree(Twitter* obj) {
  if (obj && obj->user) free(obj->user);
  if (obj && obj->tweet) free(obj->tweet);
  if (obj) free(obj);
}

/*
432. 全 O(1) 的数据结构
难度困难57
请你实现一个数据结构支持以下操作：
1.	Inc(key) - 插入一个新的值为 1 的 key。或者使一个存在的 key 增加一，保证 key 不为空字符串。
2.	Dec(key) - 如果这个 key 的值是 1，那么把他从数据结构中移除掉。否则使一个存在的 key 值减一。如果这个 key 不存在，这个函数不做任何事情。key 保证不为空字符串。
3.	GetMaxKey() - 返回 key 中值最大的任意一个。如果没有元素存在，返回一个空字符串"" 。
4.	GetMinKey() - 返回 key 中值最小的任意一个。如果没有元素存在，返回一个空字符串""。

*/

typedef struct date{
	int n;
	char* key;
	struct date* pre;
	struct date* next;
	UT_hash_handle hh;
} AllOne;
struct date* users = NULL;
/** Initialize your data structure here. */
AllOne* allOneCreate() {
	struct date* obj = (struct date*)malloc(sizeof(struct date));
	struct date* tail = (struct date*)malloc(sizeof(struct date));
	obj->n = 0;
	obj->pre = tail;
	obj->next = tail;
	tail->n = INT_MAX;
	tail->pre = obj;
	tail->next = obj;
	return obj;
}
/** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
void allOneInc(AllOne* obj, char * key) {
	struct date* node = NULL;
	HASH_FIND_STR(users, key, node);
	if (!node){
		node = (struct date*)malloc(sizeof(struct date));
		node->n = 1;
		node->key = key;
		node->pre = obj;
		node->next = obj->next;
		obj->next->pre = node;
		obj->next = node;
        HASH_ADD_STR(users, key, node);
	}
	else{
		node->n++;
		while (node->n > node->next->n){
			struct date* t = node->next;
            t->next->pre = node;
            node->pre->next = t;
			node->next = t->next;
			t->pre = node->pre;
			t->next = node;
			node->pre = t;
		}
	}
}
/** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
void allOneDec(AllOne* obj, char * key) {
	struct date* node = NULL;
	HASH_FIND_STR(users, key, node);
	if (node){
		if (node->n > 1){
			node->n--;
			while (node->n < node->pre->n){
				struct date* t = node->pre;
                t->pre->next = node;
                node->next->pre = t;
				node->pre = t->pre;
				t->pre = node;
				t->next = node->next;
				node->next = t;
			}
		}
		else{
			node->pre->next = node->next;
			node->next->pre = node->pre;
			HASH_DEL(users, node);
			free(node);
		}
	}
}
/** Returns one of the keys with maximal value. */
char * allOneGetMaxKey(AllOne* obj) {
	if (obj->pre->pre->n)
		return obj->pre->pre->key;
	return "";
}
/** Returns one of the keys with Minimal value. */
char * allOneGetMinKey(AllOne* obj) {
	if (obj->next->n < INT_MAX)
		return obj->next->key;
	return "";
}
void allOneFree(AllOne* obj) {
	struct date *current_user, *tmp;
	HASH_ITER(hh, users, current_user, tmp) {
		HASH_DEL(users, current_user);
		free(current_user);
	}
	struct date *t = obj->pre;
	free(t);
    free(obj);
	obj = NULL;
}

/**
 * Your AllOne struct will be instantiated and called as such:
 * AllOne* obj = allOneCreate();
 * allOneInc(obj, key);

 * allOneDec(obj, key);

 * char * param_3 = allOneGetMaxKey(obj);

 * char * param_4 = allOneGetMinKey(obj);

 * allOneFree(obj);
*/

/*
138. 复制带随机指针的链表
给定一个链表，每个节点包含一个额外增加的随机指针，该指针可以指向链表中的任何节点或空节点。

要求返回这个链表的 深拷贝。

我们用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：

val：一个表示 Node.val 的整数。
random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  NULL 。


示例 1：



输入：head = [[7,NULL],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,NULL],[13,0],[11,4],[10,2],[1,0]]
*/

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct TreeNode *next;
 *     struct TreeNode *random;
 * };
 */

typedef struct __hash_entry {
    void *key;
    void *data;
    UT_hash_handle hh;
}hash_entry_t;

hash_entry_t *htbl = NULL;

void delete_all_htbl(void)
{
    hash_entry_t *elem, *tmp;

    HASH_ITER(hh, htbl, elem, tmp) {
        HASH_DEL(htbl,elem);
        free(elem);
    }
}

struct Node* copyRandomList(struct Node* head)
{
    struct Node* phead = head;
    struct Node* new_head = NULL;
    struct Node* prev;

    if (!head)
        return NULL;

    while (phead != NULL) {
        hash_entry_t *elem;
        struct Node *node;
        HASH_FIND_PTR(htbl, &phead, elem);
        if (elem) {
            node = (struct Node*)elem->data;
        } else {
            node = malloc(sizeof(struct Node));
            node->val = phead->val;
            elem = malloc(sizeof(hash_entry_t));
            elem->key = (void *)phead;
            elem->data = (void *)node;
            HASH_ADD_PTR(htbl, key, elem);
        }
        if (phead->random) {
            hash_entry_t *h;
            HASH_FIND_PTR(htbl, &phead->random, h);
            if (h) {
                node->random = (struct Node*)h->data;
            } else {
                struct Node* r_node = malloc(sizeof(struct Node));
                r_node->val = phead->random->val;
                node->random = r_node;
                h = malloc(sizeof(hash_entry_t));
                h->key = (void *)phead->random;
                h->data = (void *)r_node;
                HASH_ADD_PTR(htbl, key, h);
            }
        } else {
            node->random = NULL;
        }

        if (new_head == NULL) {
            new_head = node;
            prev = new_head;
        } else {
            prev->next = node;
            prev = node;
        }
        phead = phead->next;
    }

    prev->next = NULL;
    delete_all_htbl();

    return new_head;
}

