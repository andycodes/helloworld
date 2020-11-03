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

/*
res[*returnSize] = calloc(1, sizeof(struct ListNode));
res[*returnSize]->val = pop->val;
res[*returnSize]->next = NULL;
prev = res[*returnSize];
*/
struct ListNode* slink_init(void)
{
	struct ListNode* head = (struct ListNode*)calloc(1, sizeof(struct ListNode));
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

struct ListNode *prev = head;//prev维护前指针(指向前面一个对象)
void slink_last_push(int val)
{
	struct ListNode *node = malloc(sizeof(struct ListNode));
	node->val = val;
	node->next = NULL;

	prev->next = node;
	prev = prev->next;
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

	struct ListNode *prev = NULL,
	struct ListNode *pnext = NULL;

	while(head != NULL){
		pnext = head->next;
		head->next = prev;
		prev = head;
		head = pnext;
	}

	return head;
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

