#ifndef HLIST_PRO_H
#define HLIST_PRO_H
/*
list
map
set
*/

struct DataEntry {
    int key;
    int value;
    struct Node node;
};

void ListPushLast(struct List *list, int nodeKey)
{
	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
	entry->key = nodeKey;
	ListAddTail(list, &entry->node);
}


bool ListIsContainsKey(struct List *list, int nodeKey)
{
	struct Node *node;
	struct DataEntry *entry;

	LIST_FOR_EACH(node, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if(entry->key == nodeKey) {
			return true;
		}
	}

	return false;
}

struct DataEntry *ListFindKey(struct List *list, int nodeKey)
{
	struct Node *node, *tmp;
	struct DataEntry *entry;

	LIST_FOR_EACH_SAFE(node, tmp, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if(entry->key == nodeKey) {
			return entry;
		}
	}

	return NULL;
}


void ListRmKey(struct List *list, int nodeKey)
{
	struct Node *node, *tmp;
	struct DataEntry *entry;

	LIST_FOR_EACH_SAFE(node, tmp, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if(entry->key == nodeKey) {
			ListRemove(&entry->node);
			free((void*)entry);
		}
	}
}

#endif

