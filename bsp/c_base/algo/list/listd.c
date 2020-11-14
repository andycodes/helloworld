struct ListNode {
	struct ListNode *prev;
	struct ListNode *next;
	int val;
};

struct ListNode* listd_new_node(int value)
{
	struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
	if (node == NULL) {
		return NULL;
	}

	node->value = value;
	node->prev = node->next = node;
	return node;
}

void listd_head_push(struct ListNode *head, int value)
{
	struct ListNode *node = listd_new_node(value);
	if (node == NULL)
		return;

	node->prev = head;
	node->next = head->next;
	head->next->prev = node;
	head->next = node;
}

void listd_tail_push(struct ListNode* head, int value)
{
	struct ListNode *node = listd_new_node(value);
	if (node == NULL)
		return;

	node->next = head;
	node->prev = head->prev;
	head->prev->next = node;
	head->prev = node;
}

void listd_del(struct ListNode* head, struct ListNode* del)
{
	del->next->prev = del->prev;
	del->prev->next = del->next;
	free(del);
	del = NULL;
}

void listd_destroy(struct ListNode* head)
{
	struct ListNode *entry=head->next;
	struct ListNode *del=NULL;
	while(entry != head)
	{
		del = entry;
		entry = entry->next;
		free(del);
	}

	free(head);
	head = NULL;
}
