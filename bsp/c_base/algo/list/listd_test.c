/*
146. LRU�������
�Ѷ��е�768
�����������յ����ݽṹ����ƺ�ʵ��һ��  LRU (�������ʹ��)
������ơ���Ӧ��֧�����²����� ��ȡ���� get �� д������ put ��
��ȡ���� get(key) - ����ؼ��� (key) �����ڻ����У����ȡ�ؼ���
��ֵ�����������������򷵻� -1��
д������ put(key, value) - ����ؼ����Ѿ����ڣ�����������ֵ��
����ؼ��ֲ����ڣ��������顸�ؼ���/ֵ��������������
�ﵽ����ʱ����Ӧ����д��������֮ǰɾ�����δʹ�õ���
��ֵ���Ӷ�Ϊ�µ�����ֵ�����ռ䡣
����:
���Ƿ������ O(1) ʱ�临�Ӷ�����������ֲ�����
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
��ȡ���� get(key) - ����ؼ��� (key) �����ڻ����У�
���ȡ�ؼ��ֵ�ֵ�����������������򷵻� -1��
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
д������ put(key, value) - ����ؼ����Ѿ����ڣ�
����������ֵ��
����ؼ��ֲ����ڣ�
�������顸�ؼ���/ֵ���������������ﵽ����ʱ��
��Ӧ����д��������֮ǰɾ�����δʹ�õ�����ֵ��
�Ӷ�Ϊ�µ�����ֵ�����ռ䡣
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
460. LFU����
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
�����������������ĸо�����ͬƵ�ʵķ���ͬƵ��
����ǰ��
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

	 //��ǰ����p���Ĳ���λ��
	while (q != obj->head && q->freq <= p->freq)
		q = q->prev;

	p->next = q->next;  //��p�����룬����ͬƵ�ʵĵ�һ��

	if (q->next != NULL)
		q->next->prev = p;
	p->prev = q;
	q->next = p;
}


int lFUCacheGet(LFUCache* obj, int key)
{
	int count = 0;
	struct DListNode *p = obj->head->next, *q;
	// ������������Ԫ��
	while (p && p->key != key && count < obj->capacity) {
		p = p->next;
		count++;
	}

	// �����ڷ��� -1
	if (p == NULL || count == obj->capacity) return -1;
/*
���ڣ�����Ƶ�ʼ�һ��������Ƶ�ʵ�����������ֵ
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

	if (count == obj->capacity) {  //�����β��ֱ�Ӹ���β���
		p->key = key;
		p->value = value;
		p->freq = 1;
	} else {  //δ�����β
		struct DListNode* s = (struct DListNode*)malloc(sizeof(struct DListNode));
		s->key = key;
		s->value = value;
		s->freq = 1;
		// ����
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


