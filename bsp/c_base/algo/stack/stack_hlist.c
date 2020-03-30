#ifndef STACK_HLIST_H
#define STACK_HLIST_H
void stack_init(struct List *list)
{
	ListInit(list);
}

void stack_push(struct List *list, struct Node *node)
{
	ListAddTail(list, node);
}

void stack_push_key(struct List *list, int  key)
{
	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
	entry->key = key;
	ListAddTail(list, &entry->node);
}

static inline bool stack_empty(const struct List *list)
{
	return ListEmpty(list);
}

struct Node * stack_top(const struct List *list)
{
	return list->base.prev;
}

struct DataEntry * stack_entry_top(const struct List *list)
{
	struct Node * node = stack_top(list);
	if (node == NULL) {
		return NULL;
	}

	return NODE_ENTRY(node, struct DataEntry, node);
}

struct Node * stack_pop(const struct List *list)
{
	struct Node *node;
	node = list->base.prev;
	ListRemoveTail(list);
	return node;
}
#endif

