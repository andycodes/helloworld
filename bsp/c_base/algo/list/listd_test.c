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
�Ѷ�����238
����Ϊ �����ʹ�ã�LFU�������㷨��Ʋ�ʵ�����ݽṹ����Ӧ��֧�����²�����get �� put��
"	get(key) - ����������ڻ����У����ȡ����ֵ�����������������򷵻� -1��
"	put(key, value) - ������Ѵ��ڣ�������ֵ������������ڣ�������ֵ�ԡ�������ﵽ������ʱ����Ӧ���ڲ�������֮ǰ��ʹ�����ʹ�õ�����Ч���ڴ������У�������ƽ�֣���������������������ͬʹ��Ƶ�ʣ�ʱ��Ӧ��ȥ�����δʹ�õļ���
�����ʹ�ô����������Բ����������������� get �� put �����Ĵ���֮�͡�ʹ�ô������ڶ�Ӧ��Ƴ�����Ϊ 0 ��

���ף�
���Ƿ������ O(1) ʱ�临�Ӷ���ִ�����������

ʾ����
LFUCache cache = new LFUCache( 2 /* capacity (��������) */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // ���� 1
cache.put(3, 3);    // ȥ�� key 2
cache.get(2);       // ���� -1 (δ�ҵ�key 2)
cache.get(3);       // ���� 3
cache.put(4, 4);    // ȥ�� key 1
cache.get(1);       // ���� -1 (δ�ҵ� key 1)
cache.get(3);       // ���� 3
cache.get(4);       // ���� 4
*/
struct DListNode {
  int key;                         //��
  int value;                       //ֵ
  int freq;                        //����Ƶ��
  struct DListNode *prior, *next;  //ǰ�������
};

typedef struct {
  struct DListNode* head;
  int capacity;
} LFUCache;

LFUCache* lFUCacheCreate(int capacity) {
  LFUCache* cache = (LFUCache*)malloc(sizeof(LFUCache));
  // ��ʼ������ͷ���
  cache->capacity = capacity;
  cache->head = (struct DListNode*)malloc(sizeof(struct DListNode));
  cache->head->prior = NULL;
  cache->head->next = NULL;
  return cache;
}

// �����������������ĸо�����ͬƵ�ʵķ���ͬƵ�ʵ���ǰ��
void lFUCaacheUp(LFUCache* obj, struct DListNode* p) {
  struct DListNode* q;
  p->freq++;
  if (p->next) {  //�����ǰ��������һ����㣬
    p->next->prior = p->prior;
    p->prior->next = p->next;  //��p����������ժ��
  } else
    p->prior->next = NULL;
  q = p->prior;
  while (q != obj->head && q->freq <= p->freq)  //��ǰ����p���Ĳ���λ��
    q = q->prior;
  p->next = q->next;  //��p�����룬����ͬƵ�ʵĵ�һ��
  if (q->next != NULL)
    q->next->prior = p;
  p->prior = q;
  q->next = p;
}

int lFUCacheGet(LFUCache* obj, int key) {
  int count = 0;
  struct DListNode *p = obj->head->next, *q;
  // ������������Ԫ��
  while (p && p->key != key && count < obj->capacity) {
    p = p->next;
    count++;
  }
  // �����ڷ��� -1
  if (p == NULL || count == obj->capacity) return -1;
  // ���ڣ�����Ƶ�ʼ�һ��������Ƶ�ʵ�����������ֵ
  lFUCaacheUp(obj, p);
  return p->value;
}

void lFUCachePut(LFUCache* obj, int key, int value) {
  int count = 0;
  struct DListNode *p = obj->head, *q;
  // �ȱ��������� key �Ƿ����
  while (p->next != NULL && p->next->key != key && count < obj->capacity) {
    p = p->next;
    count++;
  }
  // key�Ѵ��ڸ��� ��㣬������Ƶ�ʵ�������
  if (p->next != NULL && p->next->key == key && count < obj->capacity) {  //keyֵ�Ѵ���
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
    // ������㣬��ֵ
    struct DListNode* s = (struct DListNode*)malloc(sizeof(struct DListNode));
    s->key = key;
    s->value = value;
    s->freq = 1;
    // ����
    s->next = p->next;
    s->prior = p;
    p->next = s;
    if (s->next)
      s->next->prior = s;
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

#define LEN 10001
typedef struct {
    int key;
    int value;
    int times;
} Nums;

typedef struct {
    Nums queue[LEN];
    int start;
    int end;
    int capacity;
} LFUCache;

int Compare(const void *a, const void *b)
{
    Nums *aa = (Nums *)a;
    Nums *bb = (Nums *)b;
    return aa->times - bb->times;
}

void Sort(Nums *nums, int start, int end, Nums n)
{
    for (int i = start; i < end - 1; i++) {
        if (nums[i].times >= nums[i + 1].times) {
            nums[i] = nums[i + 1];
            nums[i + 1] = n;
            continue;
        }
        break;
    }
}

LFUCache* lFUCacheCreate(int capacity) {
    LFUCache *catch = (LFUCache *)malloc(sizeof(LFUCache));
    catch->start = 0;
    catch->end = 0;
    catch->capacity = capacity;
    return catch;
}

int lFUCacheGet(LFUCache* obj, int key) {
    int value = -1;
    int start = obj->start;
    int end = obj->end;
    for (int i = start; i < end; i++) {
        if (obj->queue[i].key == key) {
            value = obj->queue[i].value;
            obj->queue[i].times++;
            Sort(obj->queue, i, obj->end, obj->queue[i]);
            break;
        }
    }
    return value;
}

void lFUCachePut(LFUCache* obj, int key, int value) {
    Nums n = {0};
    n.key = key;
    n.value = value;
    n.times = 1;
    if (lFUCacheGet(obj, key) == -1) {
        obj->queue[obj->end++] = n;
        if (obj->end - obj->start > obj->capacity) {
            obj->start++;
        }
        int len = obj->end - obj->start;
        qsort(obj->queue + obj->start, len, sizeof(Nums), Compare);
    } else {
        for (int i = obj->start; i < obj->end; i++) {
            if (obj->queue[i].key == key) {
                 obj->queue[i].value = value;
                obj->queue[i].times++;
                Sort(obj->queue, i, obj->end, obj->queue[i]);
                break;
            }
        }
    }
}

void lFUCacheFree(LFUCache* obj) {
    free(obj);
}

/**
 * Your LFUCache struct will be instantiated and called as such:
 * LFUCache* obj = lFUCacheCreate(capacity);
 * int param_1 = lFUCacheGet(obj, key);

 * lFUCachePut(obj, key, value);

 * lFUCacheFree(obj);
*/


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
	struct date* pre;
	struct date* next;
	UT_hash_handle hh;
} AllOne;
struct date* users = NULL;
/** Initialize your data structure here. */
AllOne* allOneCreate() {
	struct date* obj = (struct date*)malloc(sizeof(struct date));
	struct date* tail = (struct date*)malloc(sizeof(struct date));
	obj->n = 0;
	obj->pre = tail;
	obj->next = tail;
	tail->n = INT_MAX;
	tail->pre = obj;
	tail->next = obj;
	return obj;
}
/** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
void allOneInc(AllOne* obj, char * key) {
	struct date* node = NULL;
	HASH_FIND_STR(users, key, node);
	if (!node){
		node = (struct date*)malloc(sizeof(struct date));
		node->n = 1;
		node->key = key;
		node->pre = obj;
		node->next = obj->next;
		obj->next->pre = node;
		obj->next = node;
        HASH_ADD_STR(users, key, node);
	}
	else{
		node->n++;
		while (node->n > node->next->n){
			struct date* t = node->next;
            t->next->pre = node;
            node->pre->next = t;
			node->next = t->next;
			t->pre = node->pre;
			t->next = node;
			node->pre = t;
		}
	}
}
/** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
void allOneDec(AllOne* obj, char * key) {
	struct date* node = NULL;
	HASH_FIND_STR(users, key, node);
	if (node){
		if (node->n > 1){
			node->n--;
			while (node->n < node->pre->n){
				struct date* t = node->pre;
                t->pre->next = node;
                node->next->pre = t;
				node->pre = t->pre;
				t->pre = node;
				t->next = node->next;
				node->next = t;
			}
		}
		else{
			node->pre->next = node->next;
			node->next->pre = node->pre;
			HASH_DEL(users, node);
			free(node);
		}
	}
}
/** Returns one of the keys with maximal value. */
char * allOneGetMaxKey(AllOne* obj) {
	if (obj->pre->pre->n)
		return obj->pre->pre->key;
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
	HASH_ITER(hh, users, current_user, tmp) {
		HASH_DEL(users, current_user);
		free(current_user);
	}
	struct date *t = obj->pre;
	free(t);
    free(obj);
	obj = NULL;
}

