
#include <stdio.h>
#include <malloc.h>

/**
 * C ����ʵ�ֵ�˫�������ܴ洢�������ݡ�
 *
 * @author skywang
 * @date 2013/11/07
 */
// ˫������ڵ�
typedef struct tag_node 
{
	struct tag_node *prev;
	struct tag_node *next;
	void* p;
}node;

// ��ͷ��ע�⣬��ͷ�����Ԫ��ֵ������
static node *phead=NULL;
// �ڵ������
static int  count=0;

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
int create_dlink()
{
	// ������ͷ
	phead = create_node(NULL);
	if (!phead)
		return -1;

	// ���á��ڵ������Ϊ0
	count = 0;

	return 0;
}

// ��˫�������Ƿ�Ϊ�ա�
int dlink_is_empty()
{
	return count == 0;
}

// ���ء�˫������Ĵ�С��
int dlink_size() {
	return count;
}

// ��ȡ��˫�������е�indexλ�õĽڵ㡱
static node* get_node(int index) 
{
	if (index<0 || index>=count)
	{
		printf("%s failed! index out of bound!\n", __func__);
		return NULL;
	}

	// �������
	if (index <= (count/2))
	{
		int i=0;
		node *pnode=phead->next;
		while ((i++) < index) 
			pnode = pnode->next;

		return pnode;
	}

	// �������
	int j=0;
	int rindex = count - index - 1;
	node *rnode=phead->prev;
	while ((j++) < rindex) 
		rnode = rnode->prev;

	return rnode;
}

// ��ȡ����һ���ڵ㡱
static node* get_first_node() 
{
	return get_node(0);
}

// ��ȡ�����һ���ڵ㡱
static node* get_last_node() 
{
	return get_node(count-1);
}

// ��ȡ��˫�������е�indexλ�õ�Ԫ�ء����ɹ������ؽڵ�ֵ�����򣬷���-1��
void* dlink_get(int index)
{
	node *pindex=get_node(index);
	if (!pindex) 
	{
		printf("%s failed!\n", __func__);
		return NULL;
	}

	return pindex->p;

}

// ��ȡ��˫�������е�1��Ԫ�ص�ֵ��
void* dlink_get_first()
{
	return dlink_get(0);
}

// ��ȡ��˫�����������1��Ԫ�ص�ֵ��
void* dlink_get_last()
{
	return dlink_get(count-1);
}

// ����pval�����뵽indexλ�á��ɹ�������0�����򣬷���-1��
int dlink_insert(int index, void* pval) 
{
	// �����ͷ
	if (index==0)
		return dlink_insert_first(pval);

	// ��ȡҪ�����λ�ö�Ӧ�Ľڵ�
	node *pindex=get_node(index);
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
	count++;

	return 0;
}

// ����pval�����뵽��ͷλ��
int dlink_insert_first(void *pval) 
{
	node *pnode=create_node(pval);
	if (!pnode)
		return -1;

	pnode->prev = phead;
	pnode->next = phead->next;
	phead->next->prev = pnode;
	phead->next = pnode;
	count++;
	return 0;
}

// ����pval�����뵽ĩβλ��
int dlink_append_last(void *pval) 
{
	node *pnode=create_node(pval);
	if (!pnode)
		return -1;
	
	pnode->next = phead;
	pnode->prev = phead->prev;
	phead->prev->next = pnode;
	phead->prev = pnode;
	count++;
	return 0;
}

// ɾ����˫��������indexλ�õĽڵ㡱���ɹ�������0�����򣬷���-1��
int dlink_delete(int index)
{
	node *pindex=get_node(index);
	if (!pindex) 
	{
		printf("%s failed! the index in out of bound!\n", __func__);
		return -1;
	}

	pindex->next->prev = pindex->prev;
	pindex->prev->next = pindex->next;
	free(pindex);
	count--;

	return 0;
}	

// ɾ����һ���ڵ�
int dlink_delete_first() 
{
	return dlink_delete(0);
}

// ɾ�����һ���ڵ�
int dlink_delete_last() 
{
	return dlink_delete(count-1);
}

// ������˫���������ɹ�������0�����򣬷���-1��
int destroy_dlink()
{
	if (!phead)
	{
		printf("%s failed! dlink is null!\n", __func__);
		return -1;
	}

	node *pnode=phead->next;
	node *ptmp=NULL;
	while(pnode != phead)
	{
		ptmp = pnode;
		pnode = pnode->next;
		free(ptmp);
	}

	free(phead);
	phead = NULL;
	count = 0;

	return 0;
}
