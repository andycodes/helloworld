#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef int bool;
#define false -1
#define true 0

typedef struct entry {
    void * key;             // ��
    void * value;           // ֵ
    struct entry * next;    // ��ͻ����
}*Entry;


typedef struct hashMap *HashMap;

// ��ϣ��������
typedef int(*HashCode)(HashMap, void * key);

// �еȺ�������
typedef bool(*Equal)(void * key1, void * key2);

// ��Ӽ���������
typedef void(*Put)(HashMap hashMap, void * key, void * value);

// ��ȡ����Ӧֵ�ĺ�������
typedef void * (*Get)(HashMap hashMap, void * key);

// ɾ�����ĺ�������
typedef bool(*Remove)(HashMap hashMap, void * key);

// ���Map�ĺ�������
typedef void(*Clear)(HashMap hashMap);

// �жϼ�ֵ�Ƿ���ڵĺ�������
typedef bool(*Exists)(HashMap hashMap, void * key);

typedef struct hashMap {
    int size;           // ��ǰ��С
    int listSize;       // ��Ч�ռ��С
    HashCode hashCode;  // ��ϣ����
    Equal equal;        // �еȺ���
    Entry list;         // �洢����
    Put put;            // ��Ӽ��ĺ���
    Get get;            // ��ȡ����Ӧֵ�ĺ���
    Remove remove;      // ɾ����
    Clear clear;        // ���Map
    Exists exists;      // �жϼ��Ƿ����
    bool autoAssign;	// �趨�Ƿ���ݵ�ǰ��������̬�����ڴ��С��Ĭ�Ͽ���
}*HashMap;



// Ĭ�Ϲ�ϣ����
static int defaultHashCode(HashMap hashMap, void * key);

// Ĭ���жϼ�ֵ�Ƿ����
static bool defaultEqual(void * key1, void * key2)
{
	return !strcmp(key1, key2);
}


// Ĭ��ɾ����
static bool defaultRemove(HashMap hashMap, void * key);

// Ĭ�����Map
static void defaultClear(HashMap hashMap);

// ����һ����ϣ�ṹ
HashMap createHashMap(HashCode hashCode, Equal equal);

// ���¹���
static void resetHashMap(HashMap hashMap, int listSize);

// �������ṹ
typedef struct hashMapIterator {
    Entry entry;    // ��������ǰָ��
    int count;      // ��������
    int hashCode;   // ��ֵ�ԵĹ�ϣֵ
    HashMap hashMap;
}*HashMapIterator;

#define newHashMapIterator() NEW(struct hashMapIterator)

// ����һ����ϣ�ṹ
HashMap createHashMap(HashCode hashCode, Equal equal);

// ������ϣ�ṹ������
HashMapIterator createHashMapIterator(HashMap hashMap);

// �������Ƿ�����һ��
bool hasNextHashMapIterator(HashMapIterator iterator);

// ��������һ��
HashMapIterator nextHashMapIterator(HashMapIterator iterator);

// �ͷŵ������ڴ�
void freeHashMapIterator(HashMapIterator * iterator);

int defaultHashCode(HashMap hashMap, void *key)
{
    char *k = (char *)key;
    unsigned long h = 0;
    while (*k) {
        h = (h << 4) + *k++;
        unsigned long g = h & 0xF0000000L;
        if (g) {
            h ^= g >> 24;
        }
        h &= ~g;
    }
    return h % hashMap->listSize;
}

void resetHashMap(HashMap hashMap, int listSize) {

    if (listSize < 8) return;

    // ��ֵ����ʱ�洢�ռ�
	Entry tempList = (Entry)calloc(hashMap->size, sizeof(struct entry));

    HashMapIterator iterator = createHashMapIterator(hashMap);
    int length = hashMap->size;
    for (int index = 0; hasNextHashMapIterator(iterator); index++) {
        // ����ȡ�����м�ֵ��
        iterator = nextHashMapIterator(iterator);
        tempList[index].key = iterator->entry->key;
        tempList[index].value = iterator->entry->value;
        tempList[index].next = NULL;
    }
    freeHashMapIterator(&iterator);

    // ���ԭ�м�ֵ������
    hashMap->size = 0;
    for (int i = 0; i < hashMap->listSize; i++) {
        Entry current = &hashMap->list[i];
        current->key = NULL;
        current->value = NULL;
        if (current->next != NULL) {
            while (current->next != NULL) {
                Entry temp = current->next->next;
                free(current->next);
                current->next = temp;
            }
        }
    }

    // �����ڴ��С
    hashMap->listSize = listSize;
    Entry relist = (Entry)realloc(hashMap->list, hashMap->listSize * sizeof(struct entry));
    if (relist != NULL) {
        hashMap->list = relist;
        relist = NULL;
    }

    // ��ʼ������
    for (int i = 0; i < hashMap->listSize; i++) {
        hashMap->list[i].key = NULL;
        hashMap->list[i].value = NULL;
        hashMap->list[i].next = NULL;
    }

    // �����м�ֵ������д���ڴ�
    for (int i = 0; i < length; i++) {
        //Array x = tempList[i].value;
        hashMap->put(hashMap, tempList[i].key, tempList[i].value);
    }
    free(tempList);
}

void defaultPut(HashMap hashMap, void *key, void *value) {
    if (hashMap->autoAssign && hashMap->size >= hashMap->listSize) {
        // �ڴ�������ԭ��������
        // *ע: ����ʱ���ǵ��ǵ�ǰ�洢Ԫ��������洢�ռ�Ĵ�С��ϵ�������Ǵ洢�ռ��Ƿ��Ѿ�������
        // ����: �洢�ռ�Ϊ10��������10����ֵ�ԣ�����ȫ����ͻ�ˣ����Դ洢�ռ����9���������ȫ������һ�����棬
        // ����������ʱ��ͱ�����ѯû��ʲô�����ˣ����Լ�������⣬���Ҵ����11����ֵ�Ե�ʱ��һ���ᷢ����ͻ��
        // �����ɹ�ϣ�������������(ȡģ)�����ģ���ͻ�ͻᵼ�¼���������������ʱ������洢�ռ䣬��ԭ�м�ֵ�Խ���
        // �ٴ�ɢ�У���ѳ�ͻ�������ٴη�ɢ�����ӿ�������λ�ٶȡ�
        resetHashMap(hashMap, hashMap->listSize * 2);
    }

    int index = hashMap->hashCode(hashMap, key);
    if (hashMap->list[index].key == NULL) {
        hashMap->size++;
        // �õ�ַΪ��ʱֱ�Ӵ洢
        //Array x = value;
        hashMap->list[index].key = key;
        hashMap->list[index].value = value;
    } else {
        Entry current = &hashMap->list[index];
        while (current != NULL) {
            if (hashMap->equal(key, current->key)) {
                // ���ڼ�ֵ�Ѿ����ڵ�ֱ�Ӹ���
                hashMap->list[index].value = value;
                return;
            }
            current = current->next;
        };

        // ������ͻ�򴴽��ڵ�ҵ���Ӧλ�õ�next��
	Entry entry = (Entry)calloc(1, sizeof(struct entry));
        entry->key = key;
        entry->value = value;
        entry->next = hashMap->list[index].next;
        hashMap->list[index].next = entry;
        hashMap->size++;
    }
}


// Ĭ�ϻ�ȡ����Ӧֵ
void * defaultGet(HashMap hashMap, void * key) {
    int index = hashMap->hashCode(hashMap, key);
    Entry entry = &hashMap->list[index];
    while (entry != NULL && entry->key != NULL && !hashMap->equal(entry->key, key)) {
        entry = entry->next;
    }

    return entry == NULL ? NULL : entry->value;
}


bool defaultRemove(HashMap hashMap, void * key) {
    int index = hashMap->hashCode(hashMap, key);
    Entry entry = &hashMap->list[index];
    if (entry->key == NULL) {
        return false;
    }
    bool result = false;
    if (hashMap->equal(entry->key, key)) {
        hashMap->size--;
        if (entry->next != NULL) {
            Entry temp = entry->next;
            entry->key = temp->key;
            entry->value = temp->value;
            entry->next = temp->next;
            free(temp);
        }
        else {
            entry->key = entry->value = NULL;
        }
        result = true;
    }
    else {
        Entry p = entry;
        entry = entry->next;
        while (entry != NULL) {
            if (hashMap->equal(entry->key, key)) {
                hashMap->size--;
                p->next = entry->next;
                free(entry);
                result = true;
                break;
            }
            p = entry;
            entry = entry->next;
        };
    }

    // ����ռ�ռ�ò���һ�룬���ͷŶ����ڴ�
    if (result && hashMap->autoAssign &&  hashMap->size < hashMap->listSize / 2) {
        resetHashMap(hashMap, hashMap->listSize / 2);
    }
    return result;
}


// Ĭ���жϼ��Ƿ����
bool defaultExists(HashMap hashMap, void * key)
{
    int index = hashMap->hashCode(hashMap, key);
    Entry entry = &hashMap->list[index];
    if (entry->key == NULL) {
        return false;
    }
    if (hashMap->equal(entry->key, key)) {
        return true;
    }
    if (entry->next != NULL) {
        do {
            if (hashMap->equal(entry->key, key)) {
                return true;
            }
            entry = entry->next;

        } while (entry != NULL);
        return false;
    }
    else {
        return false;
    }
}


void defaultClear(HashMap hashMap) {
    for (int i = 0; i < hashMap->listSize; i++) {
        // �ͷų�ͻֵ�ڴ�
        Entry entry = hashMap->list[i].next;
        while (entry != NULL) {
            Entry next = entry->next;
            free(entry);
            entry = next;
        }
        hashMap->list[i].next = NULL;
    }
    // �ͷŴ洢�ռ�
    free(hashMap->list);
    hashMap->list = NULL;
    hashMap->size = -1;
    hashMap->listSize = 0;
}


HashMap createHashMap(HashCode hashCode, Equal equal) {
	HashMap hashMap = (HashMap)calloc(1, sizeof(struct hashMap));
	hashMap->size = 0;
	hashMap->listSize = 8;
	hashMap->hashCode = hashCode == NULL ? defaultHashCode : hashCode;
	hashMap->equal = equal == NULL ? defaultEqual : equal;
	hashMap->exists = defaultExists;
	hashMap->get = defaultGet;
	hashMap->put = defaultPut;
	hashMap->remove = defaultRemove;
	hashMap->clear = defaultClear;
	hashMap->autoAssign = true;
	// ��ʼ����8���ڴ�ռ䣬���ʱ���Զ�����
	hashMap->list = (Entry)calloc(hashMap->listSize, sizeof(struct entry));
	return hashMap;
}


HashMapIterator createHashMapIterator(HashMap hashMap) {
    HashMapIterator iterator = (HashMapIterator)calloc(1, sizeof(struct hashMapIterator));
    iterator->hashMap = hashMap;
    iterator->count = 0;
    iterator->hashCode = -1;
    iterator->entry = NULL;
    return iterator;
}

bool hasNextHashMapIterator(HashMapIterator iterator) {
    return iterator->count < iterator->hashMap->size ? true : false;
}

HashMapIterator nextHashMapIterator(HashMapIterator iterator) {
    if (hasNextHashMapIterator(iterator)) {
        if (iterator->entry != NULL && iterator->entry->next != NULL) {
            iterator->count++;
            iterator->entry = iterator->entry->next;
            return iterator;
        }
        while (++iterator->hashCode < iterator->hashMap->listSize) {
            Entry entry = &iterator->hashMap->list[iterator->hashCode];
            if (entry->key != NULL) {
                iterator->count++;
                iterator->entry = entry;
                break;
            }
        }
    }
    return iterator;
}

void freeHashMapIterator(HashMapIterator * iterator) {
    free(*iterator);
    *iterator = NULL;
}


void hashmap_print(struct hashMap * map)
{
	printf("++++++%s+++++\n", __func__);
	for (int i = 0; i < map->listSize; i++) {
		printf("key %s,val %s, next %d\n",
			map->list[i].key, map->list[i].value,map->list[i].next);
	}
	printf("++++++%s+++++\n", __func__);
}

int main() {
	HashMap map = createHashMap(NULL, NULL);
	map->put(map, "asdfasdf", "asdfasdfds");
	map->put(map, "sasdasd", "asdfasdfds");
	map->put(map, "asdhfgh", "asdfasdfds");
	map->put(map, "4545", "asdfasdfds");
	map->put(map, "asdfaasdasdsdf", "asdfasdfds");
	map->put(map, "asdasg", "asdfasdfds");
	map->put(map, "qweqeqwe", "asdfasdfds");

	hashmap_print(map);

	printf("key: 4545, exists: %s\n", map->exists(map, "4545") ? "true" : "false");
	printf("4545: map->get : %s\n", map->get(map, "4545"));
	printf("remove 4545 %s\n", map->remove(map, "4545") ? "true" : "false");
	printf("remove 4545 %s\n", map->remove(map, "4545") ? "true" : "false");
	printf("key: 4545, exists: %s\n", map->exists(map, "4545") ? "true" : "false");

	HashMapIterator iterator = createHashMapIterator(map);
	while (hasNextHashMapIterator(iterator)) {
		iterator = nextHashMapIterator(iterator);
		printf("{ key: %s, key: %s, hashcode: %d }\n",
		(char *)iterator->entry->key, (char *)iterator->entry->value, iterator->hashCode);
	}
	map->clear(map);
	freeHashMapIterator(&iterator);

	return 0;
}

