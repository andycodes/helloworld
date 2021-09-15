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
给你一个链表的头节点 head，请你编写代码，反复删去链表
中由 总和 值为 0 的连续节点组成的序列，直到不存在这样
的序列为止。
删除完毕后，请你返回最终结果链表的头节点。
你可以返回任何满足题目要求的答案。
（注意，下面示例中的所有序列，都是对 ListNode 对象序列化
的表示。）
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

/*
160. 相交链表
编写一个程序，找到两个单链表相交的起始节点。

分别为链表A和链表B设置指针A和指针B，然后开始遍历链表，如果遍历完当前链表，则将指针指向另外一个链表的头部继续遍历，直至两个指针相遇。最终两个指针分别走过的路径为：指针A :a+c+b指针B :b+c+a明显 a+c+b = b+c+a,因而如果两个链表相交，则指针A和指针B必定在相交结点相遇。作者：belinda链接：https://leetcode-cn.com/problems/intersection-of-two-linked-lists/solution/jiao-ni-yong-lang-man-de-fang-shi-zhao-dao-liang-2/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
如果两个链表不相交，A B就在null相遇
*/
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
	if (headA == NULL || headB == NULL)
		return NULL;

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

/*
445. 两数相加 II
给你两个 非空 链表来代表两个非负整数。数字最高位位于链
表开始位置。它们的每个节点只存储一位数字。将这两数相
加会返回一个新的链表。
你可以假设除了数字 0 之外，这两个数字都不会以零开头。
进阶：
如果输入链表不能修改该如何处理？换句话说，你不能对列表
中的节点进行翻转。
示例：
输入：(7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 8 -> 0 -> 7
*/
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
	int astack[1024];
	int atop = -1;

	int bstack[1024];
	int btop = -1;

	struct ListNode* iter = l1;
	while(iter != NULL) {
		astack[++atop] = iter->val;
		iter = iter->next;
	}

	iter = l2;
	while(iter != NULL) {
		bstack[++btop] = iter->val;
		iter = iter->next;
	}

	struct ListNode* dummy = (struct ListNode*)calloc(1, sizeof(struct ListNode));

	int plus = 0;
	while(atop > -1 || btop > -1) {
		int a = 0;
		if (atop > -1) {
			a = astack[atop--];
		}

		int b = 0;
		if (btop > -1) {
			b = bstack[btop--];
		}

		int sum = a + b + plus;
		plus = sum / 10;
		sum = sum % 10;

		struct ListNode* newNode =  (struct ListNode*)calloc(1, sizeof(struct ListNode));
		newNode->val = sum;
		newNode->next = dummy->next;
		dummy->next = newNode;
	}

	if (plus != 0) {
		struct ListNode* newNode =  (struct ListNode*)calloc(1, sizeof(struct ListNode));
		newNode->val = plus;
		newNode->next = dummy->next;
		dummy->next = newNode;
	}

	return dummy->next;
}


/*
147. 对链表进行插入排序
对链表进行插入排序。
插入排序的动画演示如上。从第一个元素开始，该链表可以
被认为已经部分排序（用黑色表示）。
每次迭代时，从输入数据中移除一个元素（用红色表示），
并原地将其插入到已排好序的链表中。
插入排序算法：
插入排序是迭代的，每次只移动一个元素，直到所有元素可
以形成一个有序的输出列表。
每次迭代中，插入排序只从输入数据中移除一个待排序的元
素，找到它在序列中适当的位置，并将其插入。
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

	struct ListNode *p,*q;
	int temp;

	for(p = head; p != NULL; p = p->next) {
		for(q = p->next; q != NULL; q = q->next) {
			if(p->val > q->val) {
				temp = p->val;
				p->val = q->val;
				q->val = temp;
			}
		}
	}

	return head;
}

/*
61. 旋转链表
难度中等271
给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，
其中 k 是非负数。
示例 1:
输入: 1->2->3->4->5->NULL, k = 2
输出: 4->5->1->2->3->NULL
解释:
向右旋转 1 步: 5->1->2->3->4->NULL
向右旋转 2 步: 4->5->1->2->3->NULL
}
*/
struct ListNode* rotateRight(struct ListNode* head, int k)
{
	// base cases
	if (head == NULL)
		return NULL;
	if (head->next == NULL)
		return head;

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
给定一个链表和一个特定值 x，对链表进行分隔，使得所有小
于 x 的节点都在大于或等于 x 的节点之前。
你应当保留两个分区中每个节点的初始相对位置。
示例:
输入: head = 1->4->3->2->5->2, x = 3
输出: 1->2->2->4->3->5
*/
struct ListNode* partition(struct ListNode* head, int x)
{
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

/*
23. 合并K个升序链表
给你一个链表数组，每个链表都已经按升序排列。
请你将所有链表合并到一个升序链表中，返回合并后的链
表。
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
struct  ListNode* mergeTwoLists(struct ListNode *a, struct ListNode *b)
{
	if ((!a) || (!b))
		return a ? a : b;

	struct ListNode head, *tail = &head, *aPtr = a, *bPtr = b;
	while (aPtr && bPtr) {
		if (aPtr->val < bPtr->val) {
			tail->next = aPtr;
			aPtr = aPtr->next;
		} else {
			tail->next = bPtr;
			bPtr = bPtr->next;
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

struct ListNode* merge(struct ListNode **lists, int l, int r)
{
	if (l == r)
		return lists[l];
	if (l > r)
		return NULL;

	int mid = (l + r) >> 1;
	return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
}



struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
	return merge(lists, 0, listsSize - 1);
}

/*
355. 设计推特
设计一个简化版的推特(Twitter)，可以让用户实现发送推文，
关注/取消关注其他用户，能够看见关注人（包括自己）的
最近十条推文。你的设计需要支持以下的几个功能：
postTweet(userId, tweetId): 创建一条新的推文
getNewsFeed(userId): 检索最近的十条推文。每个推文都必须是由
此用户关注的人或者是用户自己发出的。推文必须按照时
间顺序由最近的开始排序。
follow(followerId, followeeId): 关注一个用户
unfollow(followerId, followeeId): 取消关注一个用户
示例:
Twitter twitter = new Twitter();
// 用户1发送了一条新推文 (用户id = 1, 推文id = 5).
twitter.postTweet(1, 5);
// 用户1的获取推文应当返回一个列表，其中包含一个id为
5的推文.
twitter.getNewsFeed(1);
// 用户1关注了用户2.
twitter.follow(1, 2);
// 用户2发送了一个新推文 (推文id = 6).
twitter.postTweet(2, 6);
// 用户1的获取推文应当返回一个列表，其中包含两个推文，
id分别为 -> [6, 5].
// 推文id6应当在推文id5之前，因为它是在5之后发送的.
twitter.getNewsFeed(1);
// 用户1取消关注了用户2.
twitter.unfollow(1, 2);
// 用户1的获取推文应当返回一个列表，其中包含一个id为
5的推文.
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

Twitter* twitterCreate()
{
	Twitter* twitter = (Twitter*)malloc(sizeof(Twitter));
	twitter->user = (struct User*)calloc(MAX_SIZE, sizeof(struct User));
	twitter->tweet = (struct Tweet*)malloc(sizeof(struct Tweet));
	twitter->tweet->next = NULL;
	return twitter;
}

void twitterPostTweet(Twitter* obj, int userId, int tweetId)
{
	struct Tweet* tweet = (struct Tweet*)malloc(sizeof(struct Tweet));
	tweet->userId = userId;
	tweet->tweetId = tweetId;
	tweet->next = obj->tweet->next;  //头插法,保证最后发布的推文在最前面
	obj->tweet->next = tweet;
}

int* twitterGetNewsFeed(Twitter* obj, int userId, int* retSize)
{
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

void twitterFollow(Twitter* obj, int followerId, int followeeId)
{
	(obj->user + followerId)->followee[followeeId] = 1;
}

void twitterUnfollow(Twitter* obj, int followerId, int followeeId) {
  (obj->user + followerId)->followee[followeeId] = 0;
}

void twitterFree(Twitter* obj) {
	if (obj && obj->user) free(obj->user);
	if (obj && obj->tweet) free(obj->tweet);
	if (obj) free(obj);
}


/*
284. 顶端迭代器
给定一个迭代器类的接口，接口包含两个方法： next() 和 hasNext()。设计并实现一个支持 peek() 操作的顶端迭代器 -- 其本质就是把原本应由 next() 方法返回的元素 peek() 出来。

示例:

假设迭代器被初始化为列表 [1,2,3]。

调用 next() 返回 1，得到列表中的第一个元素。
现在调用 peek() 返回 2，下一个元素。在此之后调用 next() 仍然返回 2。
最后一次调用 next() 返回 3，末尾元素。在此之后调用 hasNext() 应该返回 false。
进阶：你将如何拓展你的设计？使之变得通用化，从而适应所有的类型，而不只是整数型？
*/

/*
 *	struct Iterator {
 *		// Returns true if the iteration has more elements.
 *		bool (*hasNext)();
 *
 * 		// Returns the next element in the iteration.
 *		int (*next)();
 *	};
 */

struct PeekingIterator {
    int peekVal;
    bool hasPeeked;
    struct Iterator* iterator;
};

struct PeekingIterator* Constructor(struct Iterator* iter) {
    struct PeekingIterator* piter = malloc(sizeof(struct PeekingIterator));
    piter->iterator = iter;
    piter->hasPeeked = false;
    return piter;
}

int peek(struct PeekingIterator* obj) {
    if (obj->hasPeeked == false) {
        obj->peekVal = obj->iterator->next();
        obj->hasPeeked = true;
    }
    return obj->peekVal;
}

int next(struct PeekingIterator* obj) {
    if (obj->hasPeeked == true) {
        obj->hasPeeked = false;
        return obj->peekVal;
    }
    return obj->iterator->next();
}

bool hasNext(struct PeekingIterator* obj) {
    if (obj->hasPeeked == true) {
        return true;
    }
    return obj->iterator->hasNext();
}

/**
 * Your PeekingIterator struct will be instantiated and called as such:
 * PeekingIterator* obj = peekingIteratorCreate(arr, arrSize);
 * int param_1 = peek(obj);
 * int param_2 = next(obj);
 * bool param_3 = hasNext(obj);
 * peekingIteratorFree(obj);
*/

