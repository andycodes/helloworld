#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"

#define QUEUE_HEAD(name) LIST_HEAD(name)


typedef struct  {
	struct list_head queue;
	int data;
} Q_ENTRY_TYPE;

#define queue_head list_head

static QUEUE_HEAD(queue1);

static inline void queue_push(struct queue_head *new, struct queue_head *head)
{
    list_add_tail(new,head);
}

#define queue_front(ptr_queue) list_first_entry(ptr_queue, Q_ENTRY_TYPE, queue)


static inline void queue_pop(struct queue_head *head)
{
        Q_ENTRY_TYPE  *entry1;

         entry1 = queue_front(head);

         list_del(&entry1->queue);
}


static inline int queue_size(struct queue_head *head)
{
    Q_ENTRY_TYPE  *pos;
    int cnt = 0;

    list_for_each_entry(pos,head,queue)cnt++;

    return cnt;
}

#define queue_is_empty(queue_head)   list_empty(queue_head)


int main(int argc, char *argv[])
{
    Q_ENTRY_TYPE  *entry1;
    entry1 = (Q_ENTRY_TYPE *)malloc(sizeof(Q_ENTRY_TYPE));
    entry1->data = 78;
    queue_push(&entry1->queue,&queue1);
    printf("queue size %d\n",queue_size(&queue1));
    printf("queue_is_empty %d\n",queue_is_empty(&queue1));

    entry1->data = 99;
    entry1 = queue_front(&queue1);
    printf("queue entry1 data %d\n",entry1->data);

    queue_pop(&queue1);
    printf("queue size %d\n",queue_size(&queue1));
    printf("queue_is_empty %d\n",queue_is_empty(&queue1));
}

