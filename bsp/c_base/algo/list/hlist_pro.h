/*
list
map
set
*/

void ListPushLast(struct List *list, int nodeKey)
{
	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
	entry->key = nodeKey;
	ListAddTail(list, &entry->node);
}


bool SetContainsKey(struct List *list, int nodeKey)
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

struct DataEntry * setFindKey(struct List *list, int nodeKey)
{
	struct Node *node, *tmp;
	struct DataEntry *entry;

	LIST_FOR_EACH_SAFE(node, tmp, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if(entry->key == nodeKey) {
			return entry;
		}
	}
}

void SetRmKey(struct List *list, int nodeKey)
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


