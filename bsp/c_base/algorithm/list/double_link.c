
#include <stdio.h>
#include <malloc.h>

#include "double_link.h"

/**
 * C ����ʵ�ֵ�˫�������ܴ洢�������ݡ�
 *
 */


// �½����ڵ㡱���ɹ������ؽڵ�ָ�룻���򣬷���NULL��
static node* create_node(void *pval)
{
	node *pnode=NULL;
	pnode = (node *)malloc(sizeof(node));
	if (!pnode)
	{
		printf("create node error!\n");
		return NULL;
	}
	// Ĭ�ϵģ�pnode��ǰһ�ڵ�ͺ�һ�ڵ㶼ָ��������
	pnode->prev = pnode->next = pnode;
	// �ڵ��ֵΪpval
	pnode->p = pval;

	return pnode;
}

// �½���˫���������ɹ�������0�����򣬷���-1��
ListHead_t* create_dlink()
{
	ListHead_t* plist_head;

	plist_head = (ListHead_t *)malloc(sizeof(ListHead_t));
	if (NULL == plist_head){
		printf("create ListHead_t error!\n");
		return NULL;
	}

	// ������ͷ
	plist_head->phead = create_node(NULL);
	if (!plist_head->phead)
		return NULL;

	// ���á��ڵ������Ϊ0
	plist_head->count = 0;

	return plist_head;
}

// ��˫�������Ƿ�Ϊ�ա�
int dlink_is_empty(ListHead_t* plist_head)
{
	return plist_head->count == 0;
}

// ���ء�˫������Ĵ�С��
int dlink_size(ListHead_t* plist_head) {
	return plist_head->count;
}

// ��ȡ��˫�������е�indexλ�õĽڵ㡱
static node* get_node(ListHead_t* plist_head,int index)
{
	if (index<0 || index>=plist_head->count)
	{
		printf("%s failed! index out of bound!\n", __func__);
		return NULL;
	}

	// �������
	if (index <= (plist_head->count/2))
	{
		int i=0;
		node *pnode=plist_head->phead->next;
		while ((i++) < index)
			pnode = pnode->next;

		return pnode;
	}

	// �������
	int j=0;
	int rindex = plist_head->count - index - 1;
	node *rnode=plist_head->phead->prev;
	while ((j++) < rindex)
		rnode = rnode->prev;

	return rnode;
}

// ��ȡ����һ���ڵ㡱
static node* get_first_node(ListHead_t* plist_head)
{
	return get_node(plist_head,0);
}

// ��ȡ�����һ���ڵ㡱
static node* get_last_node(ListHead_t* plist_head)
{
	return get_node(plist_head,plist_head->count-1);
}

// ��ȡ��˫�������е�indexλ�õ�Ԫ�ء����ɹ������ؽڵ�ֵ�����򣬷���-1��
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

// ��ȡ��˫�������е�1��Ԫ�ص�ֵ��
void* dlink_get_first(ListHead_t* plist_head)
{
	return dlink_get(plist_head,0);
}

// ��ȡ��˫�����������1��Ԫ�ص�ֵ��
void* dlink_get_last(ListHead_t* plist_head)
{
	return dlink_get(plist_head, plist_head->count-1);
}

// ����pval�����뵽indexλ�á��ɹ�������0�����򣬷���-1��
int dlink_insert(ListHead_t* plist_head, int index, void* pval)
{
	// �����ͷ
	if (index==0)
		return dlink_insert_first(plist_head,pval);

	// ��ȡҪ�����λ�ö�Ӧ�Ľڵ�
	node *pindex=get_node(plist_head,index);
	if (!pindex)
		return -1;

	// �������ڵ㡱
	node *pnode=create_node(pval);
	if (!pnode)
		return -1;

	pnode->prev = pindex->prev;
	pnode->next = pindex;
	pindex->prev->next = pnode;
	pindex->prev = pnode;
	// �ڵ����+1
	plist_head->count++;

	return 0;
}

// ����pval�����뵽��ͷλ��
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

// ����pval�����뵽ĩβλ��
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

// ɾ����˫��������indexλ�õĽڵ㡱���ɹ�������0�����򣬷���-1��
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

// ɾ����һ���ڵ�
int dlink_delete_first(ListHead_t* plist_head)
{
	return dlink_delete(plist_head,0);
}

// ɾ�����һ���ڵ�
int dlink_delete_last(ListHead_t* plist_head)
{
	return dlink_delete(plist_head,plist_head->count-1);
}

// ������˫���������ɹ�������0�����򣬷���-1��
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
