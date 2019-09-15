#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef int bool;
#define true 1
#define false 0

/////////////////////////////////////////////

typedef struct  tag_node{
	struct tag_node *prev;
	struct tag_node *next;
	int value;
} MyCircularDeque;

static int  count=0;
static int  g_k=0;


// 新建“节点”。成功，返回节点指针；否则，返回NULL。
static MyCircularDeque* create_node(int value)
{
	MyCircularDeque *pnode=NULL;
	pnode = (MyCircularDeque *)malloc(sizeof(MyCircularDeque));
	if (!pnode)
	{
		printf("create node error!\n");
		return NULL;
	}
	// 默认的，pnode的前一节点和后一节点都指向它自身
	pnode->prev = pnode->next = pnode;
	// 节点的值为value
	pnode->value = value;

	return pnode;
}



/** Initialize your data structure here. Set the size of the deque to be k. */

MyCircularDeque* myCircularDequeCreate(int k) {
	// 创建表头
	MyCircularDeque * phead = create_node(-1);
	if (!phead)
		return 0;

	// 设置“节点个数”为0
	count = 0;
       g_k = k;

	return phead;
}

// 将“value”插入到表头位置
bool dlink_insert_first(MyCircularDeque *phead,int value)
{
	MyCircularDeque *pnode=create_node(value);
	if (!pnode)
		return false;

	pnode->prev = phead;
	pnode->next = phead->next;
	phead->next->prev = pnode;
	phead->next = pnode;
	count++;
	return true;
}


/** Adds an item at the front of Deque. Return true if the operation is successful. */
bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {
    if(count >=g_k)
        return false;

    return  dlink_insert_first(obj,value);
}


// 将“value”插入到末尾位置
bool dlink_append_last(MyCircularDeque * phead,int value)
{
	MyCircularDeque *pnode=create_node(value);
	if (!pnode)
		return false;

	pnode->next = phead;
	pnode->prev = phead->prev;
	phead->prev->next = pnode;
	phead->prev = pnode;
	count++;
	return true;
}


/** Adds an item at the rear of Deque. Return true if the operation is successful. */
bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {
    if(count >=g_k)
        return false;

    return  dlink_append_last(obj,value);
}


// 获取“双向链表中第index位置的节点”
static MyCircularDeque* get_node(MyCircularDeque* phead, int index)
{
	if (index<0 || index>=count)
	{
		printf("%s failed! the index in out of bound!\n", __func__);
		return NULL;
	}

	// 正向查找
	if (index <= (count/2))
	{
		int i=0;
		MyCircularDeque *pnode=phead->next;
		while ((i++) < index)
			pnode = pnode->next;

//		printf("%s %d i=%d, pnode->value=%d\n",
//				__func__, __LINE__, i, pnode->value);
		return pnode;
	}

	// 反向查找
	int j=0;
	int rindex = count - index - 1;
	MyCircularDeque *rnode=phead->prev;
	while ((j++) < rindex)
		rnode = rnode->prev;

//	printf("%s %d j=%d, rnode->value=%d\n",
//			__func__, __LINE__, j, rnode->value);
	return rnode;
}



// 删除“双向链表中index位置的节点”。成功，返回0；否则，返回-1。
int dlink_delete(MyCircularDeque* phead,int index)
{
	MyCircularDeque *pindex=get_node(phead,index);
	if (!pindex)
	{
		printf("%s failed! the index in out of bound!\n", __func__);
		return false;
	}

	pindex->next->prev = pindex->prev;
	pindex->prev->next = pindex->next;
	free(pindex);
	count--;

	return true;
}


/** Deletes an item from the front of Deque. Return true if the operation is successful. */
bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
    return dlink_delete(obj, 0);
}

/** Deletes an item from the rear of Deque. Return true if the operation is successful. */
bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
    return dlink_delete(obj,count-1);
}

/** Get the front item from the deque. */
int myCircularDequeGetFront(MyCircularDeque* obj) {
    MyCircularDeque* pnode = get_node(obj,0);

    if (count)
        return pnode->value;
    else
        return -1;
}

/** Get the last item from the deque. */
int myCircularDequeGetRear(MyCircularDeque* obj) {
    MyCircularDeque* pnode = get_node(obj,count-1);

    if (count)
        return pnode->value;
    else
        return -1;
}

/** Checks whether the circular deque is empty or not. */
bool myCircularDequeIsEmpty(MyCircularDeque* obj) {
    return count == 0;
}

/** Checks whether the circular deque is full or not. */
bool myCircularDequeIsFull(MyCircularDeque* obj) {
    return count == g_k;
}

// 撤销“双向链表”。成功，返回0；否则，返回-1。
int destroy_dlink(MyCircularDeque* phead)
{
	if (!phead)
	{
		printf("%s failed! dlink is null!\n", __func__);
		return -1;
	}

	MyCircularDeque *pnode=phead->next;
	MyCircularDeque *ptmp=NULL;
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


void myCircularDequeFree(MyCircularDeque* obj) {
        (void)destroy_dlink(obj);
}

/**
 * Your MyCircularDeque struct will be instantiated and called as such:
 * MyCircularDeque* obj = myCircularDequeCreate(k);
 * bool param_1 = myCircularDequeInsertFront(obj, value);

 * bool param_2 = myCircularDequeInsertLast(obj, value);

 * bool param_3 = myCircularDequeDeleteFront(obj);

 * bool param_4 = myCircularDequeDeleteLast(obj);

 * int param_5 = myCircularDequeGetFront(obj);

 * int param_6 = myCircularDequeGetRear(obj);

 * bool param_7 = myCircularDequeIsEmpty(obj);

 * bool param_8 = myCircularDequeIsFull(obj);

 * myCircularDequeFree(obj);
*/


