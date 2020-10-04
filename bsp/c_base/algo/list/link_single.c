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


