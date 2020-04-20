#ifndef QUEUE_HLIST_H
#define QUEUE_HLIST_H
struct DataEntry {
	int key;
	int value;
	struct Node node;
};

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

struct Node *queue_pop(const struct List *list)
{
	struct Node *node;
	node = list->base.next;
	ListRemoveHead(list);
	return node;
}

struct DataEntry *queue_pop_entry(const struct List *list)
{
	struct Node *node;
	node = list->base.next;
	ListRemoveHead(list);
	struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);
	return entry;
}

int queue_top_key(const struct List *list)
{
	struct Node *node;
	node = list->base.next;
	struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);
	return entry->key;
}

int queue_size(const struct List *list)
{
	int size = 0;
	struct Node *node;
	LIST_FOR_EACH(node, list){
		size++;
	}

	return size;
}
#endif

