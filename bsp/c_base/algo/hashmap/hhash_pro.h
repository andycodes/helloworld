
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
	char *str = (char *)entry->key;
	register size_t ch = 0;
	struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);

	while ((ch = (size_t)(*str++)) != '\0') {
		// hash = hash * 131 + ch;
		hash = (hash << 7) + (hash << 1) + hash + ch;
	}
	return hash % bktSize;
}

