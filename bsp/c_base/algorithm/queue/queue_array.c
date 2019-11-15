#include <stdio.h>
#include <malloc.h>

struct queue_load{
	int data;
};

struct queue_blk{
	int count;
	struct queue_load load[0];
};

struct queue_blk * create_array_queue(int sz)
{
	struct queue_blk * queue;

	queue = (struct queue_blk * )malloc(sizeof(struct queue_blk) + sz*sizeof(struct queue_load));
	if(queue == NULL) {
		printf(" malloc error!");
		return  NULL;
	}

	queue->count = 0;

	return queue;
}


void destroy_array_queue(struct queue_blk * queue)
{
	if (queue) {
		free((void*)queue);
		queue = NULL;
	}
}


void push(struct queue_blk * queue,struct queue_load load)
{
	queue->load[queue->count++] = load;
}


struct queue_load  front(struct queue_blk * queue)
{
	return  queue->load[0];
}


// ���ز�ɾ�������п�ͷԪ�ء�
struct queue_load pop(struct queue_blk * queue)
{
	int i = 0;

	struct queue_load head = queue->load[0];

	queue->count--;
	while (i++<queue->count)
		queue->load[i-1] = queue->load[i];

	return head;
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
	struct queue_blk *q_test1;

	q_test1 = create_array_queue(12);

	struct queue_load load1;
	struct queue_load load2;
	struct queue_load load3;

	load1.data = 10;
	push(q_test1,load1);
	load1.data = 20;
	push(q_test1,load1);
	load1.data = 30;
	push(q_test1,load1);

	// �������п�ͷ��Ԫ�ء���ֵ��tmp����ɾ������Ԫ�ء�
	load2 = pop(q_test1);
	printf("tmp=%d\n", load2.data);

	// ֻ�������п�ͷ��Ԫ�ء���ֵ��tmp����ɾ����Ԫ��.
	load3 = front(q_test1);
	printf("tmp=%d\n", load3.data);

	load1.data = 40;
	push(q_test1,load1);

	// ��ӡ����
	printf("is_empty()=%d\n", is_empty(q_test1));
	printf("size()=%d\n", size(q_test1));

	while (!is_empty(q_test1)) {
		struct queue_load tmp_load;

		tmp_load = pop(q_test1);
		printf("%d\n", tmp_load.data);
	}

	// ���ٶ���
	destroy_array_queue(q_test1);
}

