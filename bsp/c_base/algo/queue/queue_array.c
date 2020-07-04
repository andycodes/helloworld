#include <stdio.h>
#include <malloc.h>

/*array queue*/

struct aqueue_load{
	int val;
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

int  aqueue_get_first_val(struct aqueue_blk * queue)
{
	return  queue->load[0].val;
}


int aqueue_get_last_val(struct aqueue_blk * queue)
{
	return  queue->load[queue->count - 1].val;
}


void aqueue_push_last_val(struct aqueue_blk * queue, int value)
{
	struct aqueue_load load;
	load.val = value;
	queue->load[queue->count++] = load;
	if (queue->count > queue->size) {
		printf("[%s] push count[%d] too big\n", __func__, queue->count);
		queue->count = queue->count % queue->size;
		return;
	}
}


int aqueue_pop_first_val(struct aqueue_blk * queue)
{
	int i = 0;

	struct aqueue_load head = queue->load[0];

	queue->count--;
	while (i++<queue->count)
		queue->load[i-1] = queue->load[i];

	return head.val;
}


struct aqueue_load  aqueue_get_first(struct aqueue_blk * queue)
{
	return  queue->load[0];
}


struct aqueue_load  aqueue_get_last(struct aqueue_blk * queue)
{
	return  queue->load[queue->count - 1];
}


/*
	load[0|1|2|3|4]  <--push
*/
void aqueue_push_last(struct aqueue_blk * queue,
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
struct aqueue_load aqueue_pop_first(struct aqueue_blk * queue)
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
int aqueue_empty(struct aqueue_blk * queue)
{
	return queue->count==0;
}


int is_full(struct aqueue_blk * queue)
{
	return queue->count >= queue->size;
}


#define for_aqueue_entry(queue) \
for(int i = 0; i < aqueue_size(queue); i++)

