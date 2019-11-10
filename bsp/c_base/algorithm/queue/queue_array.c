#include <stdio.h>
#include <malloc.h>

/**
 * C ����: ����ʵ�ֵĶ��У�ֻ�ܴ洢int���ݡ�
 *
 */


struct queue_blk{
	int count;
	int arr[0];
};

struct queue_blk * create_array_queue(int sz)
{
	struct queue_blk * queue;

	queue = (struct queue_blk * )malloc(sizeof(struct queue_blk) + sz*sizeof(int));
	if(queue == NULL) {
		printf(" malloc error!");
		return  NULL;
	}

	queue->count = 0;

	return queue;
}


void destroy_array_queue(struct queue_blk * queue)
{
	if (queue)
	{
		free((void*)queue);
		queue = NULL;
	}
}


void push(struct queue_blk * queue,int val)
{
	queue->arr[queue->count++] = val;
}


int front(struct queue_blk * queue)
{
	return queue->arr[0];
}


// ���ز�ɾ�������п�ͷԪ�ء�
int pop(struct queue_blk * queue)
{
	int i = 0;;
	int ret = queue->arr[0];

	queue->count--;
	while (i++<queue->count)
		queue->arr[i-1] = queue->arr[i];

	return ret;
}


// ���ء����С��Ĵ�С
int size(struct queue_blk * queue)
{
	return queue->count;
}

// ���ء����С��Ƿ�Ϊ��
int is_empty(struct queue_blk * queue)
{
	return queue->count==0;
}

void main()
{
	int tmp=0;
	struct queue_blk *q_test1;

	// ���������С�
	q_test1 = create_array_queue(12);

	// ��10, 20, 30 �������������
	push(q_test1,10);
	push(q_test1,20);
	push(q_test1,30);

	// �������п�ͷ��Ԫ�ء���ֵ��tmp����ɾ������Ԫ�ء�
	tmp = pop(q_test1);
	printf("tmp=%d\n", tmp);

	// ֻ�������п�ͷ��Ԫ�ء���ֵ��tmp����ɾ����Ԫ��.
	tmp = front(q_test1);
	printf("tmp=%d\n", tmp);

	push(q_test1,40);

	// ��ӡ����
	printf("is_empty()=%d\n", is_empty(q_test1));
	printf("size()=%d\n", size(q_test1));
	while (!is_empty(q_test1))
	{
		printf("%d\n", pop(q_test1));
	}

	// ���ٶ���
	destroy_array_queue(q_test1);
}

