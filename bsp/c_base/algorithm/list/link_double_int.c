
#include <stdio.h>
#include <malloc.h>

/**
 * c����ʵ�ֵ�˫������
 */
// ˫������ڵ�
typedef struct tag_node
{
	struct tag_node *prev;
	struct tag_node *next;
	int value;
}node;

// ��ͷ��ע�⣬��ͷ�����Ԫ��ֵ������
static node *phead=NULL;
// �ڵ������
static int  count=0;

// �½����ڵ㡱���ɹ������ؽڵ�ָ�룻���򣬷���NULL��
static node* create_node(int value)
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
	// �ڵ��ֵΪvalue
	pnode->value = value;

	return pnode;
}

// �½���˫���������ɹ�������0�����򣬷���-1��
int create_dlink()
{
	// ������ͷ
	phead = create_node(-1);
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
		printf("%s failed! the index in out of bound!\n", __func__);
		return NULL;
	}

	// �������
	if (index <= (count/2))
	{
		int i=0;
		node *pnode=phead->next;
		while ((i++) < index)
			pnode = pnode->next;

//		printf("%s %d i=%d, pnode->value=%d\n",
//				__func__, __LINE__, i, pnode->value);
		return pnode;
	}

	// �������
	int j=0;
	int rindex = count - index - 1;
	node *rnode=phead->prev;
	while ((j++) < rindex)
		rnode = rnode->prev;

//	printf("%s %d j=%d, rnode->value=%d\n",
//			__func__, __LINE__, j, rnode->value);
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

// ��ȡ��˫�������е�indexλ�õ�Ԫ�ص�ֵ�����ɹ������ؽڵ�ֵ�����򣬷���-1��
int dlink_get(int index)
{
	node *pindex=get_node(index);
	if (!pindex)
	{
		printf("%s failed!\n", __func__);
		return -1;
	}

	return pindex->value;

}

// ��ȡ��˫�������е�1��Ԫ�ص�ֵ��
int dlink_get_first()
{
	return dlink_get(0);
}

// ��ȡ��˫�����������1��Ԫ�ص�ֵ��
int dlink_get_last()
{
	return dlink_get(count-1);
}

// ����value�����뵽indexλ�á��ɹ�������0�����򣬷���-1��
int dlink_insert(int index, int value)
{
	// �����ͷ
	if (index==0)
		return dlink_insert_first(value);

	// ��ȡҪ�����λ�ö�Ӧ�Ľڵ�
	node *pindex=get_node(index);
	if (!pindex)
		return -1;

	// �������ڵ㡱
	node *pnode=create_node(value);
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

// ����value�����뵽��ͷλ��
int dlink_insert_first(int value)
{
	node *pnode=create_node(value);
	if (!pnode)
		return -1;

	pnode->prev = phead;
	pnode->next = phead->next;
	phead->next->prev = pnode;
	phead->next = pnode;
	count++;
	return 0;
}

// ����value�����뵽ĩβλ��
int dlink_append_last(int value)
{
	node *pnode=create_node(value);
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

// ��ӡ��˫������
void print_dlink()
{
	if (count==0 || (!phead))
	{
		printf("stack is Empty\n");
		return ;
	}

	printf("stack size()=%d\n", count);
	node *pnode=phead->next;
	while(pnode != phead)
	{
		printf("%d\n", pnode->value);
		pnode = pnode->next;
	}
}
