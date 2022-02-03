/*

哨兵节点head--->node1-->node2--->NULL

链表遍历方式
while (entry != NULL) {
	do {...}
	entry = entry->next;
}

for (struct ListNode * p = head; p != NULL; p = p->next) {
        do {...}
}

void traverse(struct ListNode * head)
{
    do {...}
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
struct ListNode* lists_init(void)
{
	struct ListNode* head = (struct ListNode*)calloc(1, sizeof(struct ListNode));
	head->next = NULL;
	return head;
}

int lists_isEmpty(struct ListNode *head)
{
	return head == NULL || head->next == NULL;
}

void lists_head_push(struct ListNode *head, int val)
{
	struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
	newNode->val = val;

	newNode->next = head->next;
	head->next = newNode;
}

int lists_head_top(struct ListNode * head)
{
	if (lists_isEmpty(head))
		return -1;

	return head->next->val;
}

int lists_head_pop(struct ListNode * head)
{
	int ret = 0;
	if (lists_isEmpty(head))
		return -1;

	struct ListNode *del = head->next;
	int pop = del->val;

	head->next = head->next->next;

	free(del);
	del = NULL;

	return pop;
}

struct ListNode *tail = head; //tail维护前指针(指向前面一个对象)
void lists_tail_push(int val)
{
	struct ListNode *node = malloc(sizeof(struct ListNode));
	node->val = val;
	node->next = NULL;

	tail->next = node;
	tail = tail->next;
}

struct ListNode *lists_reverse(struct ListNode * head)
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
148. 排序链表-归并排序
*/
struct ListNode* merge_sotrlist(struct ListNode* p,struct ListNode* q)
{
	struct ListNode head;
	struct ListNode *entry = &head;

	while(p != NULL && q != NULL) {
		if(p->val <= q->val){
			entry->next = p;
			entry = p;
			p = p->next;
		}else{
			entry->next = q;
			entry = q;
			q = q->next;
		}
	}

	entry->next = (p == NULL) ? q : p;
	return head.next;
}

struct ListNode* sortList(struct ListNode* head)
{
	if(head==NULL||head->next==NULL)
		return head;

	struct ListNode* slow = head;
	struct ListNode* fast = head->next;
	while(fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}

	struct ListNode*  l2 = slow->next;
	slow->next = NULL;

	return merge_sotrlist(sortList(head),sortList(l2));
}

/*删除当前节点
狸猫换太子
将next复制到当前节点
再将next删除掉*/
void deleteNode(struct ListNode* node)
{
    struct ListNode *del = node->next;
    *node = *del;
    free(del);
}


/*
19. 删除链表的倒数第N个节点
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

