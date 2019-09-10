#include "list.h"

#define QUEUE_HEAD(name) LIST_HEAD(name)


typedef struct  {
	struct list_head queue;
	int data;
} Q_NODE_TYPE;

typedef struct list_head struct queue_head;

static QUEUE_HEAD(queue1);

static inline void queue_push(struct queue_head *new, struct queue_head *head)
{
    list_add_tail(new,head);
}

#define queue_front(ptr) list_first_entry(ptr, Q_NODE_TYPE, queue)


int main(int argc, char *argv[])
{
    Q_NODE_TYPE  node1;
    node1 = (Q_NODE_TYPE *)malloc(sizeof(Q_NODE_TYPE));
    node1->data = 1;
    queue_push(&node1->queue,&queue1);

    node1 = queue_front(&queue1);
}

