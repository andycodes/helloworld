/*

�ڱ��ڵ�head--->node1-->node2--->NULL

���������ʽ
while (entry != NULL) {
	do
	entry = entry->next;
}

for (struct ListNode * p = head; p != NULL; p = p->next) {
        // ���� p.val
}

void traverse(struct ListNode * head)
{
    // ���� head.val
    traverse(head->next)
}

����ָ��:
��·����
�Գ�����
�����м�λ��

ɾ������:��һ��dummy�ڵ�
*/

struct ListNode {
     int val;
    struct ListNode *next;
};

struct ListNode* slink_init(void)
{
	/*�ڱ��ڵ�: head  has no usr data */
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
�½�����,ͷ�ڵ���뷨
�½�һ��ͷ��㣬����ԭ������ÿ���ڵ���ͷ������
���½������С�����½���������Ƿ�ת�������
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
19. ɾ������ĵ�����N���ڵ�
�Ѷ��е�780
����һ������ɾ������ĵ����� n ���ڵ㣬���ҷ��������ͷ��㡣
ʾ����
����һ������: 1->2->3->4->5, �� n = 2.

��ɾ���˵����ڶ����ڵ�������Ϊ 1->2->3->5.
˵����
������ n ��֤����Ч�ġ�
���ף�
���ܳ���ʹ��һ��ɨ��ʵ����
*/
/*
�����н�����������⣬�����뵽��Ҳ�Ǻܳ��õľ���
˫ָ�롣
������ָ���� n+1���ڵ������ͬʱ���ƣ����ܵÿ��ָ
�뵽��β��ʱ���ܵ�����ָ�����һ���ڵ�պþ���Ҫ��
ɾ���Ľڵ㣬���ˣ�����ӭ�ж��⡣
Ȼ��ע��߽����⣬����ɾ����Ԫ�ظպ��ǵ�һ��Ԫ��ʱ
��Ҫ���⴦��
����ǲ����Ϸ����� head == NULL �� n ��������������Ҫ��
�⴦��
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
����һ�������ͷ�ڵ� head�������д���룬����ɾȥ�������� �ܺ� ֵΪ 0 �������ڵ���ɵ����У�ֱ������������������Ϊֹ��

ɾ����Ϻ����㷵�����ս�������ͷ�ڵ㡣



����Է����κ�������ĿҪ��Ĵ𰸡�

��ע�⣬����ʾ���е��������У����Ƕ� ListNode �������л��ı�ʾ����

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
��������?�ǿ� ������������ʾ�����Ǹ���������
���У����Ǹ��Ե�λ���ǰ���?����?�ķ�ʽ�洢�ģ�
�������ǵ�ÿ���ڵ�ֻ�ܴ洢?һλ?���֡�

��������ǽ������������������
��᷵��һ���µ���������ʾ���ǵĺ͡�

�����Լ���������� 0 ֮�⣬���������������� 0?��ͷ��

ʾ����

���룺(2 -> 4 -> 3) + (5 -> 6 -> 4)
�����7 -> 0 -> 8
ԭ��342 + 465 = 807
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
445. ������� II
�������� �ǿ� ���������������Ǹ��������������λλ������ʼλ�á����ǵ�ÿ���ڵ�ֻ�洢һλ���֡�����������ӻ᷵��һ���µ�����

����Լ���������� 0 ֮�⣬���������ֶ��������㿪ͷ��



���ף�

��������������޸ĸ���δ������仰˵���㲻�ܶ��б��еĽڵ���з�ת��



ʾ����

���룺(7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
�����7 -> 8 -> 0 -> 7
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
148. ��������
�� O(n log n) ʱ�临�ӶȺͳ������ռ临�Ӷ��£�
�������������

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
147. ��������в�������
��������в�������


��������Ķ�����ʾ���ϡ��ӵ�һ��Ԫ�ؿ�ʼ����������Ա���Ϊ�Ѿ����������ú�ɫ��ʾ����
ÿ�ε���ʱ���������������Ƴ�һ��Ԫ�أ��ú�ɫ��ʾ������ԭ�ؽ�����뵽���ź���������С�



���������㷨��

���������ǵ����ģ�ÿ��ֻ�ƶ�һ��Ԫ�أ�ֱ������Ԫ�ؿ����γ�һ�����������б�
ÿ�ε����У���������ֻ�������������Ƴ�һ���������Ԫ�أ��ҵ������������ʵ���λ�ã���������롣
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
61. ��ת����
�Ѷ��е�271
����һ��������ת����������ÿ���ڵ������ƶ� k ��λ�ã����� k �ǷǸ�����
ʾ�� 1:
����: 1->2->3->4->5->NULL, k = 2
���: 4->5->1->2->3->NULL
����:
������ת 1 ��: 5->1->2->3->4->NULL
������ת 2 ��: 4->5->1->2->3->NULL
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
86. �ָ�����
����һ�������һ���ض�ֵ x����������зָ���ʹ������С�� x �Ľڵ㶼�ڴ��ڻ���� x �Ľڵ�֮ǰ��

��Ӧ����������������ÿ���ڵ�ĳ�ʼ���λ�á�

ʾ��:

����: head = 1->4->3->2->5->2, x = 3
���: 1->2->2->4->3->5
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
// cur�ߵı�pre�죬 pre֮ǰ��С��x��pre��cur֮�䶼�Ǵ��ڵ���x�ģ���cur��ֵС��xʱ����pre����
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
146. LRU�������
�Ѷ��е�768
�����������յ����ݽṹ����ƺ�ʵ��һ��  LRU (�������ʹ��) ������ơ���Ӧ��֧�����²����� ��ȡ���� get �� д������ put ��
��ȡ���� get(key) - ����ؼ��� (key) �����ڻ����У����ȡ�ؼ��ֵ�ֵ�����������������򷵻� -1��
д������ put(key, value) - ����ؼ����Ѿ����ڣ�����������ֵ������ؼ��ֲ����ڣ��������顸�ؼ���/ֵ���������������ﵽ����ʱ����Ӧ����д��������֮ǰɾ�����δʹ�õ�����ֵ���Ӷ�Ϊ�µ�����ֵ�����ռ䡣

����:
���Ƿ������ O(1) ʱ�临�Ӷ�����������ֲ�����

ʾ��:
LRUCache cache = new LRUCache( 2 /* �������� */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // ����  1
cache.put(3, 3);    // �ò�����ʹ�ùؼ��� 2 ����
cache.get(2);       // ���� -1 (δ�ҵ�)
cache.put(4, 4);    // �ò�����ʹ�ùؼ��� 1 ����
cache.get(1);       // ���� -1 (δ�ҵ�)
cache.get(3);       // ����  3
cache.get(4);       // ����  4

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
��ȡ���� get(key) - ����ؼ��� (key) �����ڻ����У�
���ȡ�ؼ��ֵ�ֵ�����������������򷵻� -1��
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
д������ put(key, value) - ����ؼ����Ѿ����ڣ�
����������ֵ��
����ؼ��ֲ����ڣ�
�������顸�ؼ���/ֵ���������������ﵽ����ʱ��
��Ӧ����д��������֮ǰɾ�����δʹ�õ�����ֵ��
�Ӷ�Ϊ�µ�����ֵ�����ռ䡣
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
460. LFU����
�Ѷ�����238
����Ϊ �����ʹ�ã�LFU�������㷨��Ʋ�ʵ�����ݽṹ����Ӧ��֧�����²�����get �� put��
"	get(key) - ����������ڻ����У����ȡ����ֵ�����������������򷵻� -1��
"	put(key, value) - ������Ѵ��ڣ�������ֵ������������ڣ�������ֵ�ԡ�������ﵽ������ʱ����Ӧ���ڲ�������֮ǰ��ʹ�����ʹ�õ�����Ч���ڴ������У�������ƽ�֣���������������������ͬʹ��Ƶ�ʣ�ʱ��Ӧ��ȥ�����δʹ�õļ���
�����ʹ�ô����������Բ����������������� get �� put �����Ĵ���֮�͡�ʹ�ô������ڶ�Ӧ��Ƴ�����Ϊ 0 ��

���ף�
���Ƿ������ O(1) ʱ�临�Ӷ���ִ�����������

ʾ����
LFUCache cache = new LFUCache( 2 /* capacity (��������) */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // ���� 1
cache.put(3, 3);    // ȥ�� key 2
cache.get(2);       // ���� -1 (δ�ҵ�key 2)
cache.get(3);       // ���� 3
cache.put(4, 4);    // ȥ�� key 1
cache.get(1);       // ���� -1 (δ�ҵ� key 1)
cache.get(3);       // ���� 3
cache.get(4);       // ���� 4
*/
struct DListNode {
  int key;                         //��
  int value;                       //ֵ
  int freq;                        //����Ƶ��
  struct DListNode *prior, *next;  //ǰ�������
};

typedef struct {
  struct DListNode* head;
  int capacity;
} LFUCache;

LFUCache* lFUCacheCreate(int capacity) {
  LFUCache* cache = (LFUCache*)malloc(sizeof(LFUCache));
  // ��ʼ������ͷ���
  cache->capacity = capacity;
  cache->head = (struct DListNode*)malloc(sizeof(struct DListNode));
  cache->head->prior = NULL;
  cache->head->next = NULL;
  return cache;
}

// �����������������ĸо�����ͬƵ�ʵķ���ͬƵ�ʵ���ǰ��
void lFUCaacheUp(LFUCache* obj, struct DListNode* p) {
  struct DListNode* q;
  p->freq++;
  if (p->next) {  //�����ǰ��������һ����㣬
    p->next->prior = p->prior;
    p->prior->next = p->next;  //��p����������ժ��
  } else
    p->prior->next = NULL;
  q = p->prior;
  while (q != obj->head && q->freq <= p->freq)  //��ǰ����p���Ĳ���λ��
    q = q->prior;
  p->next = q->next;  //��p�����룬����ͬƵ�ʵĵ�һ��
  if (q->next != NULL)
    q->next->prior = p;
  p->prior = q;
  q->next = p;
}

int lFUCacheGet(LFUCache* obj, int key) {
  int count = 0;
  struct DListNode *p = obj->head->next, *q;
  // ������������Ԫ��
  while (p && p->key != key && count < obj->capacity) {
    p = p->next;
    count++;
  }
  // �����ڷ��� -1
  if (p == NULL || count == obj->capacity) return -1;
  // ���ڣ�����Ƶ�ʼ�һ��������Ƶ�ʵ�����������ֵ
  lFUCaacheUp(obj, p);
  return p->value;
}

void lFUCachePut(LFUCache* obj, int key, int value) {
  int count = 0;
  struct DListNode *p = obj->head, *q;
  // �ȱ��������� key �Ƿ����
  while (p->next != NULL && p->next->key != key && count < obj->capacity) {
    p = p->next;
    count++;
  }
  // key�Ѵ��ڸ��� ��㣬������Ƶ�ʵ�������
  if (p->next != NULL && p->next->key == key && count < obj->capacity) {  //keyֵ�Ѵ���
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
  if (count == obj->capacity) {  //�����β��ֱ�Ӹ���β���
    p->key = key;
    p->value = value;
    p->freq = 1;
  } else {  //δ�����β
    // ������㣬��ֵ
    struct DListNode* s = (struct DListNode*)malloc(sizeof(struct DListNode));
    s->key = key;
    s->value = value;
    s->freq = 1;
    // ����
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
23. �ϲ�K����������
����һ���������飬ÿ�������Ѿ����������С�

���㽫��������ϲ���һ�����������У����غϲ��������



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
    /* ���������ϵ������ν����ֵ�³�������С��ʵ�� */
    if (i >= n) return;  // Ҷ�ӽڵ㳬��
    int minIdx = i;  // ��С�ڵ�����
    int left = 2 * i + 1, right = 2 * i + 2;  // ���Һ��ӽڵ�����
    if (left < n && tree[left]->val < tree[minIdx]->val) {
        minIdx = left;
    }
    if (right < n && tree[right]->val < tree[minIdx]->val) {
        minIdx = right;
    }
    if (minIdx != i) {
        /* �����ǰ�ڵ㲻����С�ѣ�����Ȼ�����εݹ���ȥ������С�� */
        swap(tree, i, minIdx);
        heapify(tree, n, minIdx);  // ע�⴫����minIdx���������
    }
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
    // 1.���п��б�
    if (listsSize < 1 || lists == NULL) return NULL;  // [[]]�����ж�
    // 2.������С��ʵ��
    struct ListNode **tree = (struct ListNode**)malloc(sizeof(struct ListNode*) * listsSize);
    for (int i = 0, j = listsSize, k = 0; i < j; i++) {
        if (!lists[i]) listsSize--;  // NULL
        else tree[k++] = lists[i];
    }
    if (listsSize <= 0) return NULL;
    int idx = ((listsSize - 1) - 1) / 2;  // ��ȡ���һ��Ҷ�ӽڵ��±�
    for (; idx >= 0; idx--) heapify(tree, listsSize, idx);
    /* 3.�ѽ���ά����ÿ�Ρ��滻����Сֵ
    * ����ձ��Ƶ�����ʣ��Ԫ��ά���ѣ�ֱ�����ѵĴ�СΪ0������
    */
    struct ListNode *dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *prev = dummy, *curr;
    while (listsSize > 0) {
        /* ÿ�δӶѶ�ȡ��СԪ�صĽڵ������Ȼ�󹹽�����������
        * 1.�����ǰ�Ѷ�Ԫ���޺����ڵ㣬��ô���������idx�������´����������-1
        * 2.�����ǰ�Ѷ�Ԫ���к�̽ڵ㣬��ô���������������ѡ�
        * �������Զ�Ǵ�0��λ�ÿ�ʼ��ֻ����������listsSize�½����ѡ�
        */
        curr = tree[0];
        if (curr->next == NULL) {
            swap(tree, listsSize - 1, 0);  // �����һλ����
            listsSize--;  // �´��������������1
        } else tree[0] = tree[0]->next;
        prev->next = curr;
        prev = curr;
        heapify(tree, listsSize, 0);
    }
    return dummy->next;
}

/*
355. �������
���һ���򻯰������(Twitter)���������û�ʵ�ַ������ģ���ע/ȡ����ע�����û����ܹ�������ע�ˣ������Լ��������ʮ�����ġ���������Ҫ֧�����µļ������ܣ�

postTweet(userId, tweetId): ����һ���µ�����
getNewsFeed(userId): ���������ʮ�����ġ�ÿ�����Ķ��������ɴ��û���ע���˻������û��Լ������ġ����ı��밴��ʱ��˳��������Ŀ�ʼ����
follow(followerId, followeeId): ��עһ���û�
unfollow(followerId, followeeId): ȡ����עһ���û�
ʾ��:

Twitter twitter = new Twitter();

// �û�1������һ�������� (�û�id = 1, ����id = 5).
twitter.postTweet(1, 5);

// �û�1�Ļ�ȡ����Ӧ������һ���б����а���һ��idΪ5������.
twitter.getNewsFeed(1);

// �û�1��ע���û�2.
twitter.follow(1, 2);

// �û�2������һ�������� (����id = 6).
twitter.postTweet(2, 6);

// �û�1�Ļ�ȡ����Ӧ������һ���б����а����������ģ�id�ֱ�Ϊ -> [6, 5].
// ����id6Ӧ��������id5֮ǰ����Ϊ������5֮���͵�.
twitter.getNewsFeed(1);

// �û�1ȡ����ע���û�2.
twitter.unfollow(1, 2);

// �û�1�Ļ�ȡ����Ӧ������һ���б����а���һ��idΪ5������.
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
  tweet->next = obj->tweet->next;  //ͷ�巨,��֤��󷢲�����������ǰ��
  obj->tweet->next = tweet;
}

/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
int* twitterGetNewsFeed(Twitter* obj, int userId, int* retSize) {
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
432. ȫ O(1) �����ݽṹ
�Ѷ�����57
����ʵ��һ�����ݽṹ֧�����²�����
1.	Inc(key) - ����һ���µ�ֵΪ 1 �� key������ʹһ�����ڵ� key ����һ����֤ key ��Ϊ���ַ�����
2.	Dec(key) - ������ key ��ֵ�� 1����ô���������ݽṹ���Ƴ���������ʹһ�����ڵ� key ֵ��һ�������� key �����ڣ�������������κ����顣key ��֤��Ϊ���ַ�����
3.	GetMaxKey() - ���� key ��ֵ��������һ�������û��Ԫ�ش��ڣ�����һ�����ַ���"" ��
4.	GetMinKey() - ���� key ��ֵ��С������һ�������û��Ԫ�ش��ڣ�����һ�����ַ���""��

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
138. ���ƴ����ָ�������
����һ������ÿ���ڵ����һ���������ӵ����ָ�룬��ָ�����ָ�������е��κνڵ��սڵ㡣

Ҫ�󷵻��������� �����

������һ���� n ���ڵ���ɵ���������ʾ����/����е�����ÿ���ڵ���һ�� [val, random_index] ��ʾ��

val��һ����ʾ Node.val ��������
random_index�����ָ��ָ��Ľڵ���������Χ�� 0 �� n-1���������ָ���κνڵ㣬��Ϊ  NULL ��


ʾ�� 1��



���룺head = [[7,NULL],[13,0],[11,4],[10,2],[1,0]]
�����[[7,NULL],[13,0],[11,4],[10,2],[1,0]]
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

