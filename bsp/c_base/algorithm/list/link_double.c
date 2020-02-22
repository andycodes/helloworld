#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct ListNode {
	struct ListNode *prev;
	struct ListNode *next;
	int val;
	int *p;
};

typedef  struct DoubleLink {
	int  cnt;
	int  size;
	struct ListNode *head;
}DOUBLELIST;


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


struct DoubleLink * dlink_init(int size)
{
	struct DoubleLink * dlink = (struct DoubleLink *)malloc(sizeof(struct DoubleLink));
	dlink->head = dlink_new_node(-1);
	dlink->cnt = 0;
	dlink->size = size;
	return dlink;
}


// 将“value”插入到index位置。成功，返回0；否则，返回-1。
int dlink_insert(struct DoubleLink *obj, int index, int value)
{
	// 插入表头
	if (index==0)
		return dlink_insert_first(value);

	// 获取要插入的位置对应的节点
	node *pindex=get_node(index);
	if (!pindex)
		return -1;

	// 创建“节点”
	node *pnode=create_node(value);
	if (!pnode)
		return -1;

	pnode->prev = pindex->prev;
	pnode->next = pindex;
	pindex->prev->next = pnode;
	pindex->prev = pnode;
	// 节点个数+1
	obj->cnt++;

	return 0;
}


// 将“value”插入到表头位置
void dlink_push_head(struct DoubleLink *obj, int value)
{
	if(obj->cnt >= obj->size)
		return;

	struct ListNode *head = obj->head;
	struct ListNode *newNode = dlink_new_node(value);
	if (newNode == NULL)
		return;

	newNode->prev = head;
	newNode->next = head->next;
	head->next->prev = newNode;
	head->next = newNode;
}


void dlink_push_last(struct DoubleLink* obj, int value)
{
	if(obj->cnt  >= obj->size)
		return;
	struct ListNode *head = obj->head;
	struct ListNode *newNode = dlink_new_node(value);
	if (newNode == NULL)
		return;

	newNode->next = head;
	newNode->prev = head->prev;
	head->prev->next = newNode;
	head->prev = newNode;
	obj->cnt++;
}

// 获取“双向链表中第index位置的节点”
struct ListNode *dlink_get_node(struct DoubleLink* obj, int index)
{
	struct ListNode *head = obj->head;
	if (index < 0 || index >= obj->size) {
		printf("%s failed! the index in out of bound!\n", __func__);
		return NULL;
	}

	// 正向查找
	if (index <= (obj->size/2)) {
		int i=0;
		node *pnode = head->next;
		while ((i++) < index)
			pnode = pnode->next;

//		printf("%s %d i=%d, pnode->value=%d\n",
//				__func__, __LINE__, i, pnode->value);
		return pnode;
	}

	// 反向查找
	int j=0;
	int rindex = obj->size - index - 1;
	node *rnode = head->prev;
	while ((j++) < rindex)
		rnode = rnode->prev;

//	printf("%s %d j=%d, rnode->value=%d\n",
//			__func__, __LINE__, j, rnode->value);
	return rnode;
}


// 获取“双向链表中第index位置的元素的值”。成功，返回节点值；否则，返回-1。
int dlink_get_value(struct DoubleLink* obj, int index)
{
	node *pindex = dlink_get_node(obj, index);
	if (!pindex)
	{
		printf("%s failed!\n", __func__);
		return -1;
	}

	return pindex->value;

}


int dlink_get_first(struct DoubleLink* obj)
{
	return dlink_get_value(0);
}


int dlink_get_last(struct DoubleLink* obj)
{
	return dlink_get_value(obj->cnt -1);
}


void dlink_delete(struct DoubleLink* obj, int index)
{
	struct ListNode *head = obj->head;
	struct ListNode *entry = dlink_get_node(head, index);
	if (entry == NULL) {
		printf("%s failed! the index in out of bound!\n", __func__);
		return;
	}

	entry->next->prev = entry->prev;
	entry->prev->next = entry->next;
	free(entry);
	obj->cnt--;
}


void dlink_del_first(struct DoubleLink* obj)
{
	dlink_delete(obj->head, 0);
}


bool dlink_del_last(struct DoubleLink* obj)
{
    return dlink_delete(obj->head, obj->cnt -1);
}


int dlink_destroy(struct DoubleLink* obj)
{
	struct ListNode *head = obj->head;
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
	free(obj)
	obj = NULL;
	return 0;
}


bool dlink_empty(struct DoubleLink* obj)
{
    return obj->cnt == 0;
}


bool dlink_full(struct DoubleLink* obj)
{
    return obj->cnt == obj->size;
}

int dlink_size(struct DoubleLink* obj)
{
	return obj->cnt;
}


// 打印“双向链表”
void dlink_print(struct DoubleLink* obj)
{
	if (obj->cnt==0 || (!obj))
	{
		printf("stack is Empty\n");
		return ;
	}

	struct ListNode *head = obj->head;

	printf("stack size()=%d\n", obj->cnt);
	node *pnode=head->next;
	while(pnode != head)
	{
		printf("%d\n", pnode->value);
		pnode = pnode->next;
	}
}

