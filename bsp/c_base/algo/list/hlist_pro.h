#ifndef HLIST_PRO_H
#define HLIST_PRO_H
/* list map set */
struct DataEntry {
	int key;
	int value;
	struct Node node;
};

void ListPushLast(struct List *list, int nodeKey)
{
	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry));
	entry->key = nodeKey;
	ListAddTail(list, &entry->node);
}


bool ListIsContainsKey(struct List *list, int nodeKey)
{
	struct Node *node = NULL;
	struct DataEntry *entry = NULL;

	LIST_FOR_EACH(node, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if (entry->key == nodeKey) {
			return true;
		}
	}

	return false;
}

struct DataEntry *ListFindKey(struct List *list, int nodeKey)
{
	struct Node *node = NULL;
	struct DataEntry *entry = NULL;

	LIST_FOR_EACH(node, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if (entry->key == nodeKey) {
			return entry;
		}
	}

	return NULL;
}


void ListRmKey(struct List *list, int nodeKey)
{
	struct Node *node = NULL;
	struct Node *tmp = NULL;
	struct DataEntry *entry = NULL;

	LIST_FOR_EACH_SAFE(node, tmp, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if (entry->key == nodeKey) {
			ListRemove(&entry->node);
			free(entry);
		}
	}
}

/*
for (int i = 0; i < ht.bktSize; i++) {
	if(!ListEmpty(&ht.bkts[i])) {
		struct Node *node;
		LIST_FOR_EACH(node, &ht.bkts[i]) {
			nodeFuncX(node, &arg);
		}
	}
}
*/

#endif

