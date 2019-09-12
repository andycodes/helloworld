
#ifndef _DOUBLE_LINK_H
#define _DOUBLE_LINK_H

// ˫������ڵ�
typedef struct tag_node
{
	struct tag_node *prev;
	struct tag_node *next;
	void* p;
}node;

typedef struct list_head_t
{
	node 	*phead;/*��ͷ��ע�⣬��ͷ�����Ԫ��ֵ������*/
	int	count;/*�ڵ������*/
}ListHead_t;

// �½���˫���������ɹ������ر�ͷ�����򣬷���NULL
extern ListHead_t* create_dlink();
// ������˫���������ɹ�������0�����򣬷���-1
extern int destroy_dlink(ListHead_t* plist_head);

// ��˫�������Ƿ�Ϊ�ա���Ϊ�յĻ�����1�����򣬷���0��
extern int dlink_is_empty(ListHead_t* plist_head);
// ���ء�˫������Ĵ�С��
extern int dlink_size(ListHead_t* plist_head);

// ��ȡ��˫�������е�indexλ�õ�Ԫ�ء����ɹ������ؽڵ�ָ�룻���򣬷���NULL��
extern void* dlink_get(ListHead_t* plist_head,int index);
// ��ȡ��˫�������е�1��Ԫ�ء����ɹ������ؽڵ�ָ�룻���򣬷���NULL��
extern void* dlink_get_first(ListHead_t* plist_head);
// ��ȡ��˫�����������1��Ԫ�ء����ɹ������ؽڵ�ָ�룻���򣬷���NULL��
extern void* dlink_get_last(ListHead_t* plist_head);

// ����value�����뵽indexλ�á��ɹ�������0�����򣬷���-1��
extern int dlink_insert(ListHead_t* plist_head,int index, void *pval);
// ����value�����뵽��ͷλ�á��ɹ�������0�����򣬷���-1��
extern int dlink_insert_first(ListHead_t* plist_head,void *pval);
// ����value�����뵽ĩβλ�á��ɹ�������0�����򣬷���-1��
extern int dlink_append_last(ListHead_t* plist_head,void *pval);

// ɾ����˫��������indexλ�õĽڵ㡱���ɹ�������0�����򣬷���-1
extern int dlink_delete(ListHead_t* plist_head,int index);
// ɾ����һ���ڵ㡣�ɹ�������0�����򣬷���-1
extern int dlink_delete_first(ListHead_t* plist_head);
// ɾ�����һ���ڵ㡣�ɹ�������0�����򣬷���-1
extern int dlink_delete_last(ListHead_t* plist_head);

#endif

