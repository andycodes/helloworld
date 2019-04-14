
#include <stdio.h>
#include <malloc.h>

#include "double_link.h"

/**
 * C 语言实现的双向链表，能存储任意数据。
 *
 */


// 新建“节点”。成功，返回节点指针；否则，返回NULL。
static node* create_node(void *pval)
{
	node *pnode=NULL;
	pnode = (node *)malloc(sizeof(node));
	if (!pnode)
	{
		printf("create node error!\n");
		return NULL;
	}
	// 默认的，pnode的前一节点和后一节点都指向它自身
	pnode->prev = pnode->next = pnode;
	// 节点的值为pval
	pnode->p = pval;

	return pnode;
}

// 新建“双向链表”。成功，返回0；否则，返回-1。
ListHead_t* create_dlink()
{
	ListHead_t* plist_head;

	plist_head = (ListHead_t *)malloc(sizeof(ListHead_t));
	if (NULL == plist_head){
		printf("create ListHead_t error!\n");
		return NULL;
	}

	// 创建表头
	plist_head->phead = create_node(NULL);
	if (!plist_head->phead)
		return NULL;

	// 设置“节点个数”为0
	plist_head->count = 0;

	return plist_head;
}

// “双向链表是否为空”
int dlink_is_empty(ListHead_t* plist_head)
{
	return plist_head->count == 0;
}

// 返回“双向链表的大小”
int dlink_size(ListHead_t* plist_head) {
	return plist_head->count;
}

// 获取“双向链表中第index位置的节点”
static node* get_node(ListHead_t* plist_head,int index)
{
	if (index<0 || index>=plist_head->count)
	{
		printf("%s failed! index out of bound!\n", __func__);
		return NULL;
	}

	// 正向查找
	if (index <= (plist_head->count/2))
	{
		int i=0;
		node *pnode=plist_head->phead->next;
		while ((i++) < index)
			pnode = pnode->next;

		return pnode;
	}

	// 反向查找
	int j=0;
	int rindex = plist_head->count - index - 1;
	node *rnode=plist_head->phead->prev;
	while ((j++) < rindex)
		rnode = rnode->prev;

	return rnode;
}

// 获取“第一个节点”
static node* get_first_node(ListHead_t* plist_head)
{
	return get_node(plist_head,0);
}

// 获取“最后一个节点”
static node* get_last_node(ListHead_t* plist_head)
{
	return get_node(plist_head,plist_head->count-1);
}

// 获取“双向链表中第index位置的元素”。成功，返回节点值；否则，返回-1。
void* dlink_get(ListHead_t* plist_head, int index)
{
	node *pindex=get_node(plist_head,index);
	if (!pindex)
	{
		printf("%s failed!\n", __func__);
		return NULL;
	}

	return pindex->p;

}

// 获取“双向链表中第1个元素的值”
void* dlink_get_first(ListHead_t* plist_head)
{
	return dlink_get(plist_head,0);
}

// 获取“双向链表中最后1个元素的值”
void* dlink_get_last(ListHead_t* plist_head)
{
	return dlink_get(plist_head, plist_head->count-1);
}

// 将“pval”插入到index位置。成功，返回0；否则，返回-1。
int dlink_insert(ListHead_t* plist_head, int index, void* pval)
{
	// 插入表头
	if (index==0)
		return dlink_insert_first(plist_head,pval);

	// 获取要插入的位置对应的节点
	node *pindex=get_node(plist_head,index);
	if (!pindex)
		return -1;

	// 创建“节点”
	node *pnode=create_node(pval);
	if (!pnode)
		return -1;

	pnode->prev = pindex->prev;
	pnode->next = pindex;
	pindex->prev->next = pnode;
	pindex->prev = pnode;
	// 节点个数+1
	plist_head->count++;

	return 0;
}

// 将“pval”插入到表头位置
int dlink_insert_first(ListHead_t* plist_head,void *pval)
{
	node *pnode=create_node(pval);
	if (!pnode)
		return -1;

	pnode->prev = plist_head->phead;
	pnode->next = plist_head->phead->next;
	plist_head->phead->next->prev = pnode;
	plist_head->phead->next = pnode;
	plist_head->count++;
	return 0;
}

// 将“pval”插入到末尾位置
int dlink_append_last(ListHead_t* plist_head, void *pval)
{
	node *pnode=create_node(pval);
	if (!pnode)
		return -1;

	pnode->next = plist_head->phead;
	pnode->prev = plist_head->phead->prev;
	plist_head->phead->prev->next = pnode;
	plist_head->phead->prev = pnode;
	plist_head->count++;
	return 0;
}

// 删除“双向链表中index位置的节点”。成功，返回0；否则，返回-1。
int dlink_delete(ListHead_t* plist_head, int index)
{
	node *pindex=get_node(plist_head,index);
	if (!pindex)
	{
		printf("%s failed! the index in out of bound!\n", __func__);
		return -1;
	}

	pindex->next->prev = pindex->prev;
	pindex->prev->next = pindex->next;
	free(pindex);
	plist_head->count--;

	return 0;
}

// 删除第一个节点
int dlink_delete_first(ListHead_t* plist_head)
{
	return dlink_delete(plist_head,0);
}

// 删除组后一个节点
int dlink_delete_last(ListHead_t* plist_head)
{
	return dlink_delete(plist_head,plist_head->count-1);
}

// 撤销“双向链表”。成功，返回0；否则，返回-1。
int destroy_dlink(ListHead_t* plist_head)
{
	if (!plist_head->phead)
	{
		printf("%s failed! dlink is null!\n", __func__);
		return -1;
	}

	node *pnode=plist_head->phead->next;
	node *ptmp=NULL;
	while(pnode != plist_head->phead)
	{
		ptmp = pnode;
		pnode = pnode->next;
		free(ptmp);
	}

	free(plist_head->phead);
	plist_head->phead = NULL;
	plist_head->count = 0;

	return 0;
}
