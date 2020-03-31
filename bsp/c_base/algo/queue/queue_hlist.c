#include <stdio.h>
#include <malloc.h>

#ifndef QUEUE_HLIST_H
#define QUEUE_HLIST_H
void queue_init(struct List *list)
{
	ListInit(list);
}

void queue_push(struct List *list, struct Node *node)
{
	ListAddTail(list, node);
}

void queue_push_key(struct List *list, int  key)
{
	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
	entry->key = key;
	ListAddTail(list, &entry->node);
}

static inline bool queue_empty(const struct List *list)
{
	return ListEmpty(list);
}

struct Node * queue_pop(const struct List *list)
{
	struct Node *node;
	node = list->base.next;
	ListRemoveHead(list);
	return node;
}
#endif

