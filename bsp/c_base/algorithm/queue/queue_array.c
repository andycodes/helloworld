#include <stdio.h>
#include <malloc.h>

/**
 * C 语言: 数组实现的队列，只能存储int数据。
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


// 返回并删除“队列开头元素”
int pop(struct queue_blk * queue)
{
	int i = 0;;
	int ret = queue->arr[0];

	queue->count--;
	while (i++<queue->count)
		queue->arr[i-1] = queue->arr[i];

	return ret;
}


// 返回“队列”的大小
int size(struct queue_blk * queue)
{
	return queue->count;
}

// 返回“队列”是否为空
int is_empty(struct queue_blk * queue)
{
	return queue->count==0;
}

void main()
{
	int tmp=0;
	struct queue_blk *q_test1;

	// 创建“队列”
	q_test1 = create_array_queue(12);

	// 将10, 20, 30 依次推入队列中
	push(q_test1,10);
	push(q_test1,20);
	push(q_test1,30);

	// 将“队列开头的元素”赋值给tmp，并删除“该元素”
	tmp = pop(q_test1);
	printf("tmp=%d\n", tmp);

	// 只将“队列开头的元素”赋值给tmp，不删除该元素.
	tmp = front(q_test1);
	printf("tmp=%d\n", tmp);

	push(q_test1,40);

	// 打印队列
	printf("is_empty()=%d\n", is_empty(q_test1));
	printf("size()=%d\n", size(q_test1));
	while (!is_empty(q_test1))
	{
		printf("%d\n", pop(q_test1));
	}

	// 销毁队列
	destroy_array_queue(q_test1);
}

