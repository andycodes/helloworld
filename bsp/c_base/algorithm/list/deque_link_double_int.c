#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef  struct ListNode {
	struct ListNode *prev;
	struct ListNode *next;
	int val;
}DLINKLIST;


// 新建“节点”。成功，返回节点指针；否则，返回NULL。
struct ListNode* dlink_new_node(int value)
{
	struct ListNode *newNode = NULL;
	newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
	if (newNode == NULL) {
		printf("create node error!\n");
		return NULL;
	}

	// 默认的，newNode的前一节点和后一节点都指向它自身
	newNode->prev = newNode->next = newNode;
	// 节点的值为value
	newNode->value = value;

	return newNode;
}


// 将“value”插入到表头位置
void dlink_push_head(struct ListNode *head, int value)
{
	struct ListNode *newNode = dlink_new_node(value);
	if (newNode == NULL)
		return;

	newNode->prev = head;
	newNode->next = head->next;
	head->next->prev = newNode;
	head->next = newNode;
}


void dlink_push_last(struct ListNode * head, int value)
{
	struct ListNode *newNode = dlink_new_node(value);
	if (newNode == NULL)
		return;

	newNode->next = head;
	newNode->prev = head->prev;
	head->prev->next = newNode;
	head->prev = newNode;
}


void dlink_delete(struct ListNode* head, int index)
{
	struct ListNode *entry = get_node(head, index);
	if (entry == NULL) {
		printf("%s failed! the index in out of bound!\n", __func__);
		return;
	}

	entry->next->prev = entry->prev;
	entry->prev->next = entry->next;
	free(entry);
}


int dlink_destroy(struct ListNode* head)
{
	if (!head)
	{
		printf("%s failed! dlink is null!\n", __func__);
		return -1;
	}

	struct ListNode *entry=head->next;
	struct ListNode *ptmp=NULL;
	while(entry != head)
	{
		ptmp = entry;
		entry = entry->next;
		free(ptmp);
	}

	free(head);
	head = NULL;

	return 0;
}


/////////////////////////////////////////////////////////////

typedef  struct CircDeque {
	int  cnt;
	int  size;
	struct ListNode *head;
}CDEQUE;


/** Initialize your data structure here. Set the size of the deque to be size. */
struct CircDeque * CircDequeInit(int size)
{
	struct CircDeque * cdeque = (struct CircDeque *)malloc(sizeof(struct CircDeque));
	cdeque->head = dlink_new_node(-1);
	cdeque->cnt = 0;
	cdeque->size = size;
	return cdeque;
}


void CircDequePushHead(struct CircDeque *obj, int value)
{
    if(obj->cnt >= obj->size)
        return;

    dlink_insert_first(obj->head, value);
}


void CircDequePushLast(struct CircDeque* obj, int value)
{
    if(obj->cnt  >= obj->size)
        return;

	dlink_push_last(obj->head, value);
}


bool CircDequeDelFront(struct CircDeque* obj)
{
    return dlink_delete(obj->head, 0);
}

bool CircDequeDelLast(struct CircDeque* obj)
{
    return dlink_delete(obj->head, obj->cnt -1);
}


int CircDequeGetFront(struct CircDeque* obj)
{
    struct ListNode* entry = get_node(obj->head, 0);

    if (entry != NULL)
        return entry->value;
    else
        return -1;
}


int CircDequeGetLast(struct CircDeque* obj)
{
    struct ListNode* entry = get_node(obj->head, obj->cnt-1);

    if (entry->cnt)
        return entry->value;
    else
        return -1;
}


bool CircDequeisEmpty(struct CircDeque* obj)
{
    return obj->cnt == 0;
}


bool CircDequeisFull(struct CircDeque* obj)
{
    return obj->cnt == obj->size;
}


