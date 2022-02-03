/*
146. LRU缓存机制
难度中等768
运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用)
缓存机制。它应该支持以下操作： 获取数据 get 和 写入数据 put 。
获取数据 get(key) - 如果关键字 (key) 存在于缓存中，则获取关键字
的值（总是正数），否则返回 -1。
写入数据 put(key, value) - 如果关键字已经存在，则变更其数据值；
如果关键字不存在，则插入该组「关键字/值」。当缓存容量
达到上限时，它应该在写入新数据之前删除最久未使用的数
据值，从而为新的数据值留出空间。
进阶:
你是否可以在 O(1) 时间复杂度内完成这两种操作？
*/

typedef struct {
	int capacity;
	struct List list;
	struct HashTable ht;
} LRUCache;


LRUCache* lRUCacheCreate(int capacity) {
	LRUCache *obj = (LRUCache *)calloc(1, sizeof(LRUCache));
	obj->capacity = capacity;
	ListInit(&obj->list);
	HashInit(&obj->ht, capacity, hashequal_int, hashcode_int);
	return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
/*
获取数据 get(key) - 如果关键字 (key) 存在于缓存中，
则获取关键字的值（总是正数），否则返回 -1。
*/
	int value = -1;
	struct DataEntry *find = hashFindKey(&obj->ht, key);
	if (find != NULL) {
		struct DataEntry *linkNode = NODE_ENTRY(find->link, struct DataEntry, node);
		value = linkNode->value;

		ListRemove(find->link);
		ListAddTail(&obj->list, find->link);
	}

	return value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
/*
写入数据 put(key, value) - 如果关键字已经存在，
则变更其数据值；
如果关键字不存在，
则插入该组「关键字/值」。当缓存容量达到上限时，
它应该在写入新数据之前删除最久未使用的数据值，
从而为新的数据值留出空间。
*/
struct DataEntry *find = hashFindKey(&obj->ht, key);
	if (find != NULL) {
		struct DataEntry *linkNode = NODE_ENTRY(find->link, struct DataEntry, node);
		linkNode->value = value;

		ListRemove(find->link);
		ListAddTail(&obj->list, find->link);

		return;
	}

	if (obj->capacity <= 0) {
		struct Node *node;
		node = obj->list.base.next;
		struct DataEntry *entry = NODE_ENTRY(node, struct DataEntry, node);

		struct DataEntry *del = hashFindKey(&obj->ht, entry->key);
		HashRemove(&del->node);

		ListRemoveHead(&obj->list);
		obj->capacity++;
	}

	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
	entry->key = key;
	entry->value = value;
	ListAddTail(&obj->list, &entry->node);

	struct DataEntry *hashentry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
	hashentry->key = key;
	hashentry->link = &entry->node;
	HashAdd(&obj->ht, &hashentry->node);

	obj->capacity--;
}

void lRUCacheFree(LRUCache* obj) {
	ListDeinit(&obj->list, node_free);
	HashDeinit(&obj->ht, node_free);
	free(obj);
}

/*
460. LFU缓存
*/
struct DListNode {
	int key;
	int value;
	int freq;
	struct DListNode *prev, *next;
};

typedef struct {
	int capacity;
	struct DListNode* head;
} LFUCache;

LFUCache* lFUCacheCreate(int capacity)
{
	LFUCache* cache = (LFUCache*)malloc(sizeof(LFUCache));
	cache->capacity = capacity;
	cache->head = (struct DListNode*)malloc(sizeof(struct DListNode));
	cache->head->prev = NULL;
	cache->head->next = NULL;
	return cache;
}

/*
结点提升，插入排序的感觉，相同频率的放在同频率
的最前面
*/
void lFUCaacheUp(LFUCache* obj, struct DListNode* p)
{
	struct DListNode* q;
	p->freq++;

	// del p
	if (p->next) {
		p->next->prev = p->prev;
		p->prev->next = p->next;
	} else
		p->prev->next = NULL;

	q = p->prev;

	 //向前查找p结点的插入位置
	while (q != obj->head && q->freq <= p->freq)
		q = q->prev;

	p->next = q->next;  //将p结点插入，排在同频率的第一个

	if (q->next != NULL)
		q->next->prev = p;
	p->prev = q;
	q->next = p;
}


int lFUCacheGet(LFUCache* obj, int key)
{
	int count = 0;
	struct DListNode *p = obj->head->next, *q;
	// 遍历链表，查找元素
	while (p && p->key != key && count < obj->capacity) {
		p = p->next;
		count++;
	}

	// 不存在返回 -1
	if (p == NULL || count == obj->capacity) return -1;
/*
存在：访问频率加一，按访问频率调整链表，返回值
*/
	lFUCaacheUp(obj, p);
	return p->value;
}

void lFUCachePut(LFUCache* obj, int key, int value)
{
	int count = 0;
	struct DListNode *p = obj->head, *q;
	while (p->next != NULL && p->next->key != key && count < obj->capacity) {
		p = p->next;
		count++;
	}

	if (p->next != NULL && p->next->key == key && count < obj->capacity) {
		p->next->value = value;
		lFUCaacheUp(obj, p->next);
		return;
	}

	count = 0;
	p = obj->head;
	while (p->next != NULL && p->next->freq > 1 && count < obj->capacity) {
		p = p->next;
		count++;
	}

	if (count == obj->capacity) {  //到达表尾，直接覆盖尾结点
		p->key = key;
		p->value = value;
		p->freq = 1;
	} else {  //未到达表尾
		struct DListNode* s = (struct DListNode*)malloc(sizeof(struct DListNode));
		s->key = key;
		s->value = value;
		s->freq = 1;
		// 插入
		s->next = p->next;
		s->prev = p;
		p->next = s;
		if (s->next)
			s->next->prev = s;
		else
			s->next = NULL;
	}
}

void lFUCacheFree(LFUCache* obj) {
	if (obj == NULL) return;
	struct DListNode* s;
	while (obj->head) {
	s = obj->head;
	obj->head = obj->head->next;
	free(s);
	}
	free(obj);
}


