
#ifndef _DOUBLE_LINK_H
#define _DOUBLE_LINK_H

// 双向链表节点
typedef struct tag_node
{
	struct tag_node *prev;
	struct tag_node *next;
	void* p;
}node;

typedef struct list_head_t
{
	node 	*phead;/*表头。注意，表头不存放元素值！！！*/
	int	count;/*节点个数。*/
}ListHead_t;

// 新建“双向链表”。成功，返回表头；否则，返回NULL
extern ListHead_t* create_dlink();
// 撤销“双向链表”。成功，返回0；否则，返回-1
extern int destroy_dlink(ListHead_t* plist_head);

// “双向链表是否为空”。为空的话返回1；否则，返回0。
extern int dlink_is_empty(ListHead_t* plist_head);
// 返回“双向链表的大小”
extern int dlink_size(ListHead_t* plist_head);

// 获取“双向链表中第index位置的元素”。成功，返回节点指针；否则，返回NULL。
extern void* dlink_get(ListHead_t* plist_head,int index);
// 获取“双向链表中第1个元素”。成功，返回节点指针；否则，返回NULL。
extern void* dlink_get_first(ListHead_t* plist_head);
// 获取“双向链表中最后1个元素”。成功，返回节点指针；否则，返回NULL。
extern void* dlink_get_last(ListHead_t* plist_head);

// 将“value”插入到index位置。成功，返回0；否则，返回-1。
extern int dlink_insert(ListHead_t* plist_head,int index, void *pval);
// 将“value”插入到表头位置。成功，返回0；否则，返回-1。
extern int dlink_insert_first(ListHead_t* plist_head,void *pval);
// 将“value”插入到末尾位置。成功，返回0；否则，返回-1。
extern int dlink_append_last(ListHead_t* plist_head,void *pval);

// 删除“双向链表中index位置的节点”。成功，返回0；否则，返回-1
extern int dlink_delete(ListHead_t* plist_head,int index);
// 删除第一个节点。成功，返回0；否则，返回-1
extern int dlink_delete_first(ListHead_t* plist_head);
// 删除组后一个节点。成功，返回0；否则，返回-1
extern int dlink_delete_last(ListHead_t* plist_head);

#endif

