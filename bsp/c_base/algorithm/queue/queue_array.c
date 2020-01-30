#include <stdio.h>
#include <malloc.h>

/*array queue*/

struct aqueue_load{
	int data;
};

struct aqueue_blk{
	int count;
	int size;
	struct aqueue_load load[0];
};


struct aqueue_blk * aqueue_init(int sz)
{
	struct aqueue_blk * queue;

	queue = (struct aqueue_blk * )malloc(sizeof(struct aqueue_blk) + sz*sizeof(struct aqueue_load));
	if(queue == NULL) {
		printf(" malloc error!");
		return  NULL;
	}

	queue->count = 0;
	queue->size = sz;

	return queue;
}


void aqueue_exit(struct aqueue_blk * queue)
{
	if (queue != NULL) {
		free((void*)queue);
		queue = NULL;
	}
}


struct aqueue_load  front(struct aqueue_blk * queue)
{
	return  queue->load[0];
}


struct aqueue_load  back(struct aqueue_blk * queue)
{
	return  queue->load[queue->count - 1];
}

/*
	load[0|1|2|3|4]  <--push
*/
void aqueue_push(struct aqueue_blk * queue,
	struct aqueue_load load)
{
	queue->load[queue->count++] = load;
	if (queue->count > queue->size) {
		printf("[%s] push count[%d] too big\n", __func__, queue->count);
		queue->count = queue->count % queue->size;
		return;
	}
}


// 返回并删除“队列开头元素”
struct aqueue_load aqueue_pop(struct aqueue_blk * queue)
{
	int i = 0;

	struct aqueue_load head = queue->load[0];

	queue->count--;
	while (i++<queue->count)
		queue->load[i-1] = queue->load[i];

	return head;
}


// 返回“队列”的大小
int aqueue_size(struct aqueue_blk * queue)
{
	return queue->count;
}

// 返回“队列”是否为空
int aqueue_is_empty(struct aqueue_blk * queue)
{
	return queue->count==0;
}


int is_full(struct aqueue_blk * queue)
{
	return queue->count >= queue->size;
}


#define for_aqueue_entry(queue) \
for(int i = 0; i < aqueue_size(queue); i++)


void main()
{
	struct aqueue_blk *q_test1;

	q_test1 = aqueue_init(12);

	struct aqueue_load load1;
	struct aqueue_load load2;
	struct aqueue_load load3;

	load1.data = 10;
	aqueue_push(q_test1,load1);
	load1.data = 20;
	aqueue_push(q_test1,load1);
	load1.data = 30;
	aqueue_push(q_test1,load1);

	// 将“队列开头的元素”赋值给tmp，并删除“该元素”
	load2 = aqueue_pop(q_test1);
	printf("load2 10 =%d\n", load2.data);

	// 只将“队列开头的元素”赋值给tmp，不删除该元素.
	load3 = front(q_test1);
	printf("load3 20=%d\n", load3.data);

	load1.data = 40;
	aqueue_push(q_test1,load1);

	// 打印队列
	printf("is_empty() false =%d\n", aqueue_is_empty(q_test1));
	printf("aqueue_size() 3 =%d\n", aqueue_size(q_test1));

	while (!aqueue_is_empty(q_test1)) {
		struct aqueue_load tmp_load;

		tmp_load = aqueue_pop(q_test1);
		printf("20 30 40  ==%d\n", tmp_load.data);
	}

	// 销毁队列
	aqueue_exit(q_test1);
}

