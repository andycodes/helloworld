/*

�ڱ��ڵ�head--->node1-->node2--->NULL

���������ʽ
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

struct ListNode *tail = head; //tailά��ǰָ��(ָ��ǰ��һ������)
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
148. ��������-�鲢����
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

/*ɾ����ǰ�ڵ�
��è��̫��
��next���Ƶ���ǰ�ڵ�
�ٽ�nextɾ����*/
void deleteNode(struct ListNode* node)
{
    struct ListNode *del = node->next;
    *node = *del;
    free(del);
}


/*
19. ɾ������ĵ�����N���ڵ�
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

