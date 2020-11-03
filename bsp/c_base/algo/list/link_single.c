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

struct ListNode *prev = head;//prevά��ǰָ��(ָ��ǰ��һ������)
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

