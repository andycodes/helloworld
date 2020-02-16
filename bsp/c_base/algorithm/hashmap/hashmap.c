#include "myHashMap.h"
#include <stdlib.h>

//ĳ��Entry�������Ƿ����ĳ��keyֵ��
Entry* listContainsEntry(MyList * list, void * key,
		int(*equal)(void *key1, void *key2)) {
	MyListIterator* it = createMyListIterator(list);
	while (myListIteratorHasNext(it)) {
		Entry * entry = (Entry *) (myListIteratorNext(it));
		if (entry->key == key || (equal != NULL && (*equal)(entry->key, key))) {
			return entry;
		}
	}
	freeMyListIterator(it);
	return NULL;
}

void rebuildMyHashMap(MyHashMap * map) {
	int newSize = map->initialCapacity * 2;
	MyList **newentryList = (MyList **) malloc(sizeof(MyList*) * newSize);
	for (int i = 0; i < newSize; i++) {
		newentryList[i] = createMyList();
	}
	MyHashMapEntryIterator* it = createMyHashMapEntryIterator(map);
	while (myHashMapEntryIteratorHasNext(it)) {
		Entry * entry = myHashMapEntryIteratorNext(it);
		int hasCode = (*(map->hashCode))(entry->key);
		hasCode %= newSize;
		if (hasCode < 0)
			hasCode += newSize;
		myListInsertDataAtLast(newentryList[hasCode], entry);
	}
	freeMyHashMapEntryIterator(it);
	for (int i = 0; i < map->initialCapacity; i++) {
		freeMyList(map->entryList[i]);
	}
	free(map->entryList);
	map->entryList = newentryList;
	map->initialCapacity = newSize;
}

//����HashMap
MyHashMap *createMyHashMap(int(*hashCode)(void *key),
		int(*equal)(void *key1, void *key2)) {
	MyHashMap *re = (MyHashMap *) malloc(sizeof(MyHashMap));
	re->size = 0;
	re->loadFactor = DEFAULT_LOAD_FACTOR;
	re->initialCapacity = DEFAULT_INITIAL_CAPACITY;
	re->entryList = (MyList **) malloc(sizeof(MyList*) * re->initialCapacity);
	re->hashCode = hashCode;
	re->equal = equal;
	for (int i = 0; i < re->initialCapacity; i++) {
		re->entryList[i] = createMyList();
	}
	return re;
}

//ʹ��ȫ����������HashMap
MyHashMap *createMyHashMapForAll(int initialCapacity, float loadFactor,
		int(*hashCode)(void *key), int(*equal)(void *key1, void *key2)) {
	MyHashMap *re = createMyHashMap(hashCode, equal);
	re->initialCapacity = initialCapacity;
	re->loadFactor = loadFactor;
	return re;
}

//�Ƿ����ĳ��key
int myHashMapContainsKey(MyHashMap * const map, void * const key) {
	int hasCode = (*(map->hashCode))(key);
	hasCode %= map->initialCapacity;
	if (hasCode < 0)
		hasCode += map->initialCapacity;
	Entry * re = listContainsEntry(map->entryList[hasCode], key, map->equal);
	return re != NULL;
}

//����һ��ӳ��
void myHashMapPutData(MyHashMap * const map, void * const key,
		void * const value) {
	int hasCode = (*(map->hashCode))(key);
	hasCode %= map->initialCapacity;
	if (hasCode < 0)
		hasCode += map->initialCapacity;
	Entry * re = listContainsEntry(map->entryList[hasCode], key, map->equal);
	if (re == NULL) {
		Entry * entry = (Entry*) malloc(sizeof(Entry));
		entry->key = key;
		entry->value = value;
		myListInsertDataAtLast(map->entryList[hasCode], entry);
		(map->size)++;
		if (map->size > map->initialCapacity * map->loadFactor) {
			rebuildMyHashMap(map);
		}
	} else {
		re->value = value;
	}
}

//ͨ��key�õ����ݣ����û�������򷵻�null
void* myHashMapGetDataByKey(MyHashMap * const map, void * const key) {
	int hasCode = (*(map->hashCode))(key);
	hasCode %= map->initialCapacity;
	if (hasCode < 0)
		hasCode += map->initialCapacity;
	Entry * re = listContainsEntry(map->entryList[hasCode], key, map->equal);
	if (re == NULL) {
		return NULL;
	}
	return re->value;
}

//���ݵ�����
int myHashMapGetSize(const MyHashMap * const map) {
	return map->size;
}

//����Entry������
MyHashMapEntryIterator* createMyHashMapEntryIterator(MyHashMap * const map) {
	MyHashMapEntryIterator* re = (MyHashMapEntryIterator*) malloc(
			sizeof(MyHashMapEntryIterator));
	re->count = 0;
	re->index = 0;
	re->map = map;
	re->current = map->entryList[0]->first;
	return re;
}

//�ͷ�Entry������
void freeMyHashMapEntryIterator(MyHashMapEntryIterator* iterator) {
	free(iterator);
}

//Entry�������Ƿ�����һ��
int myHashMapEntryIteratorHasNext(MyHashMapEntryIterator* iterator) {
	return iterator->count < iterator->map->size;
}

//������һ��EntryԪ��
Entry* myHashMapEntryIteratorNext(MyHashMapEntryIterator* iterator) {
	(iterator->count)++;
	while (!(iterator->current)) {
		(iterator->index)++;
		iterator->current = iterator->map->entryList[iterator->index]->first;
	}
	Entry * re = (Entry *) iterator->current->data;
	iterator->current = iterator->current->next;
	return re;
}

//ɾ��һ�����ݣ������Ƿ�ɾ���ɹ�
int myHashMapRemoveDataByKey(MyHashMap * const map, void * const key) {
	int hasCode = (*(map->hashCode))(key);
	hasCode %= map->initialCapacity;
	if (hasCode < 0)
		hasCode += map->initialCapacity;
	MyListIterator* it = createMyListIterator(map->entryList[hasCode]);
	int re = 0;
	while (myListIteratorHasNext(it)) {
		Entry * entry = (Entry *) (myListIteratorNext(it));
		if ((*(map->equal))(entry->key, key)) {
			myListRemoveDataAt(map->entryList[hasCode], it->count - 1);
			re = 1;
			(map->size)--;
			break;
		}
	}
	freeMyListIterator(it);
	return re;
}

void myFree(Entry * p){
    free(p);
}

//�ͷ�HashMap
void freeMyHashMap(MyHashMap * map) {
	myHashMapOutput(map, myFree);
	for (int i = 0; i < map->initialCapacity; i++) {
		freeMyList(map->entryList[i]);
	}
	free(map->entryList);
	free(map);
}

//����
void myHashMapOutput(MyHashMap *map, void(*pt)(Entry*)) {
	MyHashMapEntryIterator* iterator = createMyHashMapEntryIterator(map);
	while (myHashMapEntryIteratorHasNext(iterator)) {
		pt(myHashMapEntryIteratorNext(iterator));
	}
	freeMyHashMapEntryIterator(iterator);
}

