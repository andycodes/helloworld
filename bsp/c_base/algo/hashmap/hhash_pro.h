#ifndef HHSH_PRO_H
#define HHSH_PRO_H

#define HASHCODE_MAGIC_7 7
#define HASHCODE_MAGIC_1 1

struct DataEntry {
	char *key;
	char *value;
	struct Node node;
};

bool hashequal_str(const struct Node *node1, const struct Node *node2)
{
	struct DataEntry *entry1 = NODE_ENTRY(node1, struct DataEntry, node);
	struct DataEntry *entry2 = NODE_ENTRY(node2, struct DataEntry, node);

	if ((char *)entry1->key == NULL || (char *)entry2->key == NULL)
		return 0;

	return !strcmp((char *)entry1->key,  (char *)entry2->key);
}

static size_t hashcode_str(const struct Node *node, size_t bktSize)
{
	size_t hash = 0;
	register size_t ch = 0;
	struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);
	char *str = (char *)entry->key;
	while ((ch = (size_t)(*str++)) != '\0') {
		hash = (hash << HASHCODE_MAGIC_7) + (hash << HASHCODE_MAGIC_1) + hash + ch;
	}

	if (bktSize == 0) {
		return hash;
	}else {
		return hash % bktSize;
	}
}

static size_t hashcode_int(const struct Node *node,  size_t bktSize)
{
	struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);
	if (bktSize == 0) {
		return labs(entry->key);
	}else {
		return labs(entry->key) % bktSize;
	}
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
	if (bktSize == 0) {
		return labs(entry->key);
	}else {
		return labs(entry->key) % bktSize;
	}
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

void hash_each_iterate(struct HashTable *ht, struct DataEntry cmpEntry)
{
	unsigned int blkid = ht->key(&cmpEntry.node, ht->bktSize);
	struct Node *node = NULL;
	LIST_FOR_EACH(node, &ht->bkts[blkid]) {
		struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);
		//do want you want
	}
}


void hashPrint(struct HashTable *ht)
{
	for (size_t i = 0; i < ht->bktSize; i++) {
		if (!ListEmpty(&ht->bkts[i])) {
			struct Node *node = NULL;
			LIST_FOR_EACH(node, &ht->bkts[i]) {
				struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);
				//printf("[%d %c]", entry->key, entry->value);
			}
			//printf("\n");
		}
	}
}

void node_free(struct Node *node)
{
	struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);
	free(entry);
	entry = NULL;
}//HashDeinit(ht, node_free);

#endif

