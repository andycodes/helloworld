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
	/*�ڱ��ڵ�: head  has no usr data */
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
	//�����ҵ�Ҫ����λ�õ���һ�����
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

//����ɾ���ڵ�Ϊβ�ڵ�
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
			struct ListNode * del = entry->next;//��������һ��ָ��ָ��ɾ����㣬�Է���ʧ
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
	int id = 0;
	while (entry->next != NULL) {
		entry = entry->next;
		printf("[%d-%d]",id++, entry->val);
	}
	printf("\n");
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
�����н�����������⣬�����뵽��Ҳ�Ǻܳ��õľ���˫ָ�롣
������ָ���� n+1���ڵ������ͬʱ���ƣ����ܵÿ��ָ�뵽��β��ʱ���ܵ�����ָ�����һ���ڵ�պþ���Ҫ��ɾ���Ľڵ㣬���ˣ�����ӭ�ж��⡣
Ȼ��ע��߽����⣬����ɾ����Ԫ�ظպ��ǵ�һ��Ԫ��ʱ��Ҫ���⴦��
����ǲ����Ϸ����� head == NULL �� n ��������������Ҫ���⴦��
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
������ 02.08. ��·���
�Ѷ��е�11
����һ���л�����ʵ��һ���㷨���ػ�·�Ŀ�ͷ�ڵ㡣
�л�����Ķ��壺��������ĳ���ڵ��nextԪ��ָ������ǰ����ֹ��Ľڵ㣬�������������ڻ�·��


ʾ�� 1��
���룺head = [3,2,0,-4], pos = 1
�����tail connects to node index 1
���ͣ���������һ��������β�����ӵ��ڶ����ڵ㡣

*/

/*
����˼·��

�����û�л���ʹ�ÿ���ָ��slow��fast��һ������������
��λ�ã����ҵ���֮��slow��head������fast�������������һ�ζ���һ�����ٴ�����Ϊ������ڵ�
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
����һ����������ɾ�������ظ���Ԫ�أ�
ʹ��ÿ��Ԫ��ֻ����һ�Ρ�

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
	struct ListNode dmy;
	struct ListNode* slow = &dmy;
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

	return dmy.next;
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


//�ݹ�ʵ��
struct ListNode * reverse(struct ListNode *pHead)
{
//��˼���������ֻ��һ���ڵ��ʱ��תҲ�����Լ���ֱ�ӷ��ؼ��ɡ�
	if (pHead == NULL || pHead->next == NULL) {
		return pHead;
	}

	struct ListNode *p = pHead->next;
	struct ListNode *pNewHead = reverse(p);
	p->next = pHead;
	pHead ->next = NULL;
	return pNewHead;
}


//β�ݹ�ʵ��
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
����ʵ��
�ڿ������㷨֮ǰ���б�Ҫ��Ū������ӷ�ת��ԭ���Լ���Ҫ��Щָ�롣�������ԣ���һ��������ͬ�����ɵ����� A �� B �� C����Ҫ��ת����е����ӳ�Ϊ A �� B �� C��

��������������ָ�룬һ��ָ���� A��һ��ָ���� B�� �ֱ��Ϊ prev �� cur���������������ָ��򵥵�ʵ�� A �� B ֮������ӷ�ת��


cur.next = prev
������Ψһ�������ǣ�û�а취������ȥ��������֮��������֮����޷��ٷ��ʵ���� C����ˣ�������Ҫ���������ָ�룬���ڰ�����ת���̵Ľ��С���ˣ����ǲ���������ķ�ת���������ǣ�


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
		slink_push_first(ret, sum);
	}

	if (plus != 0)
		slink_push_first(ret, plus);

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





