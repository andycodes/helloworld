#ifndef HHSH_PRO_H
#define HHSH_PRO_H

/*
	没有维护key值
*/
bool hashequal_str(const struct Node *node1, const struct Node *node2)
{
	struct DataEntry *entry1 = NODE_ENTRY(node1, struct DataEntry, node);
	struct DataEntry *entry2 = NODE_ENTRY(node2, struct DataEntry, node);

	if ((char *)entry1->key == NULL || (char *)entry2->key == NULL)
		return 0;

	return !strcmp((char *)entry1->key,  (char *)entry2->key);
}


size_t hashcode_str(const struct Node *node, size_t bktSize)
{
	size_t hash = 0;
	register size_t ch = 0;
	struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);
	char *str = (char *)entry->key;
	while ((ch = (size_t)(*str++)) != '\0') {
		// hash = hash * 131 + ch;
		hash = (hash << 7) + (hash << 1) + hash + ch;
	}
	return hash % bktSize;
}


size_t hashcode_int(const struct Node *node,  size_t bktSize)
{
	struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);
	return abs((int)(entry->key)) % bktSize;
}

bool hashequal_int(const struct Node *node1, const struct Node *node2)
{
	struct DataEntry *entry1 = NODE_ENTRY(node1, struct DataEntry, node);
	struct DataEntry *entry2 = NODE_ENTRY(node2, struct DataEntry, node);

	return entry1->key == entry2->key;
}

unsigned int  hashcode_char(const struct Node *node,  size_t bktSize)
{
	struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);
	return abs((char)(entry->key)) % bktSize;
}

bool hashequal_char(const struct Node *node1, const struct Node *node2)
{
	struct DataEntry *entry1 = NODE_ENTRY(node1, struct DataEntry, node);
	struct DataEntry *entry2 = NODE_ENTRY(node2, struct DataEntry, node);

	return entry1->key == entry2->key;
}


void hashPushKey(struct HashTable *ht,  int key)
{
	struct DataEntry *entry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
	entry->key = key;
	HashAdd(ht, &entry->node);
}


struct DataEntry *hashFind(const struct HashTable *ht, struct DataEntry *cmpEntry)
{
	struct Node *node = HashFind(ht, &cmpEntry->node);
	if (node == NULL) {
		return NULL;
	}

	return NODE_ENTRY(node, struct DataEntry, node);
}

struct DataEntry *hashFindKey(const struct HashTable *ht, int key)
{
	struct DataEntry cmpEntry;
	cmpEntry.key = key;
	return hashFind(ht, &cmpEntry);
}

size_t hashGetBlkid_int(const struct HashTable *ht, int key)
{
	return abs(key) % ht->bktSize;
}


struct List *hashGetBlkList_int(const struct HashTable *ht, int key)
{
	size_t blkid = abs(key) % ht->bktSize;
	return &ht->bkts[blkid];
}

void hashPrint(struct HashTable *ht)
{
	size_t i;
	for (i = 0; i < ht->bktSize; i++) {
		struct Node *node;
		LIST_FOR_EACH(node, &ht->bkts[i]) {
			struct DataEntry * entry = NODE_ENTRY(node, struct DataEntry, node);
			printf("[%d %c]", entry->key, entry->value);
		}
		printf("\n");
	}
}

#endif

