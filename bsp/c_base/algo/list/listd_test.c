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

/*
432. ȫ O(1) �����ݽṹ
�Ѷ�����57
����ʵ��һ�����ݽṹ֧�����²�����
1.	Inc(key) - ����һ���µ�ֵΪ 1 �� key������ʹһ�����ڵ� key
����һ����֤ key ��Ϊ���ַ�����
2.	Dec(key) - ������ key ��ֵ�� 1����ô���������ݽṹ����
����������ʹһ�����ڵ� key ֵ��һ�������� key �����ڣ�������������κ����顣key ��֤��Ϊ���ַ�����
3.	GetMaxKey() - ���� key ��ֵ��������һ�������û��Ԫ��
���ڣ�����һ�����ַ���"" ��
4.	GetMinKey() - ���� key ��ֵ��С������һ�������û��Ԫ��
���ڣ�����һ�����ַ���""��
*/

typedef struct date{
	int n;
	char* key;
	struct date* prev;
	struct date* next;
	UT_hash_handle hh;
} AllOne;

struct date* hashmap = NULL;
AllOne* allOneCreate() {
	struct date* obj = (struct date*)malloc(sizeof(struct date));
	struct date* tail = (struct date*)malloc(sizeof(struct date));
	obj->n = 0;
	obj->prev = tail;
	obj->next = tail;
	tail->n = INT_MAX;
	tail->prev = obj;
	tail->next = obj;
	return obj;
}

/** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
void allOneInc(AllOne* obj, char * key)
{
	struct date* find = NULL;
	HASH_FIND_STR(hashmap, key, find);
	if (!find){
		find = (struct date*)malloc(sizeof(struct date));
		find->n = 1;
		find->key = key;
		find->prev = obj;
		find->next = obj->next;
		obj->next->prev = find;
		obj->next = find;
		HASH_ADD_STR(hashmap, key, find);
	} else{
		find->n++;
		while (find->n > find->next->n) {
			struct date* t = find->next;
			t->next->prev = find;
			find->prev->next = t;
			find->next = t->next;
			t->prev = find->prev;
			t->next = find;
			find->prev = t;
		}
	}
}

/** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
void allOneDec(AllOne* obj, char * key)
{
	struct date* node = NULL;
	HASH_FIND_STR(hashmap, key, node);
	if (node == NULL)
		return;

	if (node->n > 1){
		node->n--;
		while (node->n < node->prev->n){
			struct date* t = node->prev;
			t->prev->next = node;
			node->next->prev = t;
			node->prev = t->prev;
			t->prev = node;
			t->next = node->next;
			node->next = t;
		}
	} else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
		HASH_DEL(hashmap, node);
		free(node);
	}
}

/** Returns one of the keys with maximal value. */
char * allOneGetMaxKey(AllOne* obj) {
	if (obj->prev->prev->n)
		return obj->prev->prev->key;

	return "";
}
/** Returns one of the keys with Minimal value. */
char * allOneGetMinKey(AllOne* obj) {
	if (obj->next->n < INT_MAX)
		return obj->next->key;
	return "";
}
void allOneFree(AllOne* obj) {
	struct date *current_user, *tmp;
	HASH_ITER(hh, hashmap, current_user, tmp) {
		HASH_DEL(hashmap, current_user);
		free(current_user);
	}
	struct date *t = obj->prev;
	free(t);
    free(obj);
	obj = NULL;
}

