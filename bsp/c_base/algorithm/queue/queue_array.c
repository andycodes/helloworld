#include <stdio.h>
#include <malloc.h>

struct queue_load{
	int data;
};

struct queue_blk{
	int count;
	int size;
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
	queue->size = sz;

	return queue;
}


void destroy_array_queue(struct queue_blk * queue)
{
	if (queue) {
		free((void*)queue);
		queue = NULL;
	}
}


struct queue_load  front(struct queue_blk * queue)
{
	return  queue->load[0];
}


struct queue_load  back(struct queue_blk * queue)
{
	return  queue->load[queue->count - 1];
}

/*
	load[0|1|2|3|4]  <--push
*/
void push(struct queue_blk * queue,struct queue_load load)
{
	queue->load[queue->count++] = load;
	if (queue->count > queue->size) {
		printf("[%s] push count[%d] too big\n", __func__, queue->count);
		queue->count = queue->count % queue->size;
		return;
	}
}


// 返回并删除“队列开头元素”
struct queue_load pop(struct queue_blk * queue)
{
	int i = 0;

	struct queue_load head = queue->load[0];

	queue->count--;
	while (i++<queue->count)
		queue->load[i-1] = queue->load[i];

	return head;
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


int is_full(struct queue_blk * queue)
{
	return queue->count >= queue->size;
}


#define for_queue_entry(queue) \
for(int i = 0; i < size(queue); i++)


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

	// 将“队列开头的元素”赋值给tmp，并删除“该元素”
	load2 = pop(q_test1);
	printf("load2 10 =%d\n", load2.data);

	// 只将“队列开头的元素”赋值给tmp，不删除该元素.
	load3 = front(q_test1);
	printf("load3 20=%d\n", load3.data);

	load1.data = 40;
	push(q_test1,load1);

	// 打印队列
	printf("is_empty() false =%d\n", is_empty(q_test1));
	printf("size() 3 =%d\n", size(q_test1));

	while (!is_empty(q_test1)) {
		struct queue_load tmp_load;

		tmp_load = pop(q_test1);
		printf("20 30 40  ==%d\n", tmp_load.data);
	}

	// 销毁队列
	destroy_array_queue(q_test1);
}

