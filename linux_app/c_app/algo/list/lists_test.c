/*
141. ��������
����һ�������ж��������Ƿ��л���
����������Ƿ���ڻ�·��һ��������������ָ�뷨��
����������ָ������ͬʱ������
��ָ��ÿ�ƶ�һ����ָ���ƶ�������
������ڻ�·�������վ���������
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
������ 02.08. ��·���
�Ѷ��е�11
����һ���л�����ʵ��һ���㷨���ػ�·�Ŀ�ͷ�ڵ㡣
�л�����Ķ��壺��������ĳ���ڵ��nextԪ��ָ������ǰ
����ֹ��Ľڵ㣬�������������ڻ�·��

ʾ�� 1��
���룺head = [3,2,0,-4], pos = 1
�����tail connects to node index 1
���ͣ���������һ��������β�����ӵ��ڶ����ڵ㡣
*/

/*
����˼·��
�����û�л���ʹ�ÿ���ָ��slow��fast��һ������������
��λ�ã����ҵ���֮��slow��head������fast�������������
һ�ζ���һ�����ٴ�����Ϊ������ڵ�
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
234. ��������
���ж�һ�������Ƿ�Ϊ��������
ʾ�� 1:
����: 1->2
���: false
ʾ�� 2:
����: 1->2->2->1
���: true
*/
bool isPalindrome(struct ListNode* head)
{
	// ����������ų�
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

	//�������ǿ��Է�ת�в�֮ǰ�������Ա��ں����Ƚϡ�
	// ��ת�в�ǰ��������
	struct ListNode *prep, *nextp;
	prep = nextp = NULL;
	while(head != slow){
		nextp = head->next;
		head->next = prep;
		prep = head;
		head = nextp;
	}

	// ��������Ϊ�������������м���
	if(fast != NULL && fast->next == NULL)
		slow = slow->next;

	// ����ƥ��Ƚ�
	while(prep != NULL) {
		if(prep->val != slow->val)
			return false;
		prep = prep->next;
		slow = slow->next;
	}
	return true;
}

/*
83. ɾ�����������е��ظ�Ԫ��
����һ����������ɾ�������ظ���Ԫ�أ�
ʹ��ÿ��Ԫ��ֻ����һ�Ρ�
ʾ�� 1:
����: 1->1->2
���: 1->2
ʾ�� 2:
����: 1->1->2->3->3
���: 1->2->3
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
82. ɾ�����������е��ظ�Ԫ�� II
����һ����������ɾ�����к����ظ����ֵĽڵ㣬
ֻ����ԭʼ������ û���ظ����� �����֡�
ʾ�� 1:
����: 1->2->3->3->4->4->5
���: 1->2->5
ʾ�� 2:
����: 1->1->1->2->3
���: 2->3
*/
/*
����ָ��
1.����dummy�ڵ��Ա�ɾ��ͷ�ڵ��ظ�Ԫ��
2.��slow��һ�νڵ�Ϊ�ظ��ڵ�ʱ��������ʱ�ڵ�fast��ǰ̽·��
���ߵ��ظ��ڵ����һ���ڵ�ʱ����slow->next = fast->next��
*/
struct ListNode* deleteDuplicates(struct ListNode* head)
{
//����1->1->3->3->4
	struct ListNode dummy;
	struct ListNode* slow = &dummy;
	slow->next = head;

	while(slow->next && slow->next->next) {// 1->1��������
		if (slow->next->val == slow->next->next->val) {
			struct ListNode * fast = slow->next;
			while(fast && fast->next && fast->val == fast->next->val) {//������
				fast = fast->next;
			}

			slow->next = fast->next;//����ǰ���ظ��ڵ㣬ֱ��3->3-4
		} else
			slow = slow->next;
	}

	return dummy.next;
}


/*
1171. ��������ɾȥ�ܺ�ֵΪ��������ڵ�
����һ�������ͷ�ڵ� head�������д���룬����ɾȥ����
���� �ܺ� ֵΪ 0 �������ڵ���ɵ����У�ֱ������������
������Ϊֹ��
ɾ����Ϻ����㷵�����ս�������ͷ�ڵ㡣
����Է����κ�������ĿҪ��Ĵ𰸡�
��ע�⣬����ʾ���е��������У����Ƕ� ListNode �������л�
�ı�ʾ����
ʾ�� 1��
���룺head = [1,2,-3,3,1]
�����[3,1]
��ʾ���� [1,2,1] Ҳ����ȷ�ġ�
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
160. �ཻ����
��дһ�������ҵ������������ཻ����ʼ�ڵ㡣

�ֱ�Ϊ����A������B����ָ��A��ָ��B��Ȼ��ʼ����������������굱ǰ������ָ��ָ������һ�������ͷ������������ֱ������ָ����������������ָ��ֱ��߹���·��Ϊ��ָ��A :a+c+bָ��B :b+c+a���� a+c+b = b+c+a,���������������ཻ����ָ��A��ָ��B�ض����ཻ������������ߣ�belinda���ӣ�https://leetcode-cn.com/problems/intersection-of-two-linked-lists/solution/jiao-ni-yong-lang-man-de-fang-shi-zhao-dao-liang-2/��Դ�����ۣ�LeetCode������Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
������������ཻ��A B����null����
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
92. ��ת���� II
��ת��λ�� m �� n ��������ʹ��һ��ɨ����ɷ�ת��
˵��:
1 �� m �� n �� �����ȡ�
ʾ��:
����: 1->2->3->4->5->NULL, m = 2, n = 4
���: 1->4->3->2->5->NULL
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
445. ������� II
�������� �ǿ� ���������������Ǹ��������������λλ����
��ʼλ�á����ǵ�ÿ���ڵ�ֻ�洢һλ���֡�����������
�ӻ᷵��һ���µ�����
����Լ���������� 0 ֮�⣬���������ֶ��������㿪ͷ��
���ף�
��������������޸ĸ���δ������仰˵���㲻�ܶ��б�
�еĽڵ���з�ת��
ʾ����
���룺(7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
�����7 -> 8 -> 0 -> 7
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
147. ��������в�������
��������в�������
��������Ķ�����ʾ���ϡ��ӵ�һ��Ԫ�ؿ�ʼ�����������
����Ϊ�Ѿ����������ú�ɫ��ʾ����
ÿ�ε���ʱ���������������Ƴ�һ��Ԫ�أ��ú�ɫ��ʾ����
��ԭ�ؽ�����뵽���ź���������С�
���������㷨��
���������ǵ����ģ�ÿ��ֻ�ƶ�һ��Ԫ�أ�ֱ������Ԫ�ؿ�
���γ�һ�����������б�
ÿ�ε����У���������ֻ�������������Ƴ�һ���������Ԫ
�أ��ҵ������������ʵ���λ�ã���������롣
�ظ�ֱ�������������ݲ�����Ϊֹ��
ʾ�� 1��
����: 4->2->1->3
���: 1->2->3->4
ʾ�� 2��
����: -1->5->3->4->0
���: -1->0->3->4->5
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
61. ��ת����
�Ѷ��е�271
����һ��������ת����������ÿ���ڵ������ƶ� k ��λ�ã�
���� k �ǷǸ�����
ʾ�� 1:
����: 1->2->3->4->5->NULL, k = 2
���: 4->5->1->2->3->NULL
����:
������ת 1 ��: 5->1->2->3->4->NULL
������ת 2 ��: 4->5->1->2->3->NULL
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
86. �ָ�����
����һ�������һ���ض�ֵ x����������зָ���ʹ������С
�� x �Ľڵ㶼�ڴ��ڻ���� x �Ľڵ�֮ǰ��
��Ӧ����������������ÿ���ڵ�ĳ�ʼ���λ�á�
ʾ��:
����: head = 1->4->3->2->5->2, x = 3
���: 1->2->2->4->3->5
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
23. �ϲ�K����������
����һ���������飬ÿ�������Ѿ����������С�
���㽫��������ϲ���һ�����������У����غϲ������
��
ʾ�� 1��
���룺lists = [[1,4,5],[1,3,4],[2,6]]
�����[1,1,2,3,4,4,5,6]
���ͣ������������£�
[
  1->4->5,
  1->3->4,
  2->6
]
�����Ǻϲ���һ�����������еõ���
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
355. �������
���һ���򻯰������(Twitter)���������û�ʵ�ַ������ģ�
��ע/ȡ����ע�����û����ܹ�������ע�ˣ������Լ�����
���ʮ�����ġ���������Ҫ֧�����µļ������ܣ�
postTweet(userId, tweetId): ����һ���µ�����
getNewsFeed(userId): ���������ʮ�����ġ�ÿ�����Ķ���������
���û���ע���˻������û��Լ������ġ����ı��밴��ʱ
��˳��������Ŀ�ʼ����
follow(followerId, followeeId): ��עһ���û�
unfollow(followerId, followeeId): ȡ����עһ���û�
ʾ��:
Twitter twitter = new Twitter();
// �û�1������һ�������� (�û�id = 1, ����id = 5).
twitter.postTweet(1, 5);
// �û�1�Ļ�ȡ����Ӧ������һ���б����а���һ��idΪ
5������.
twitter.getNewsFeed(1);
// �û�1��ע���û�2.
twitter.follow(1, 2);
// �û�2������һ�������� (����id = 6).
twitter.postTweet(2, 6);
// �û�1�Ļ�ȡ����Ӧ������һ���б����а����������ģ�
id�ֱ�Ϊ -> [6, 5].
// ����id6Ӧ��������id5֮ǰ����Ϊ������5֮���͵�.
twitter.getNewsFeed(1);
// �û�1ȡ����ע���û�2.
twitter.unfollow(1, 2);
// �û�1�Ļ�ȡ����Ӧ������һ���б����а���һ��idΪ
5������.
// ��Ϊ�û�1�Ѿ����ٹ�ע�û�2.
twitter.getNewsFeed(1);
*/
#define MAX_SIZE 512

struct User {
	int id;                  //�û�id
	int followee[MAX_SIZE];  //�û���ע���û�id  (���������ɢ��)
};

struct Tweet {
	int userId;   //�û�id
	int tweetId;  //����id
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
	tweet->next = obj->tweet->next;  //ͷ�巨,��֤��󷢲�����������ǰ��
	obj->tweet->next = tweet;
}

int* twitterGetNewsFeed(Twitter* obj, int userId, int* retSize)
{
	int* ret = (int*)calloc(10, sizeof(int));
	*retSize = 0;

	struct Tweet* tweet = obj->tweet->next;
	struct User* user = obj->user;

	while (tweet && *retSize < 10) {  //�û��Լ����û���ע���˵�����
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
284. ���˵�����
����һ����������Ľӿڣ��ӿڰ������������� next() �� hasNext()����Ʋ�ʵ��һ��֧�� peek() �����Ķ��˵����� -- �䱾�ʾ��ǰ�ԭ��Ӧ�� next() �������ص�Ԫ�� peek() ������

ʾ��:

�������������ʼ��Ϊ�б� [1,2,3]��

���� next() ���� 1���õ��б��еĵ�һ��Ԫ�ء�
���ڵ��� peek() ���� 2����һ��Ԫ�ء��ڴ�֮����� next() ��Ȼ���� 2��
���һ�ε��� next() ���� 3��ĩβԪ�ء��ڴ�֮����� hasNext() Ӧ�÷��� false��
���ף��㽫�����չ�����ƣ�ʹ֮���ͨ�û����Ӷ���Ӧ���е����ͣ�����ֻ�������ͣ�
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

