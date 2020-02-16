
#ifndef MYHASHMAP_H_INCLUDED
#define MYHASHMAP_H_INCLUDED
#include "myList.h"

#define DEFAULT_INITIAL_CAPACITY 16
#define DEFAULT_LOAD_FACTOR 0.75f

typedef struct entry
{
    void * key;
    void * value;
} Entry;

typedef struct myHashMap
{
    int size;   //大小
    int initialCapacity; //初始容量
    float loadFactor;   //加载因子
    int (*hashCode)(void *key);
    int (*equal)(void *key1,void *key2);
    MyList ** entryList;
} MyHashMap;

typedef struct myHashMapEntryIterator
{
    int index;       //第几个链表
    MyHashMap *map;
    MyNode *current;
    int count;        //第几个数据
} MyHashMapEntryIterator;

//创建HashMap
MyHashMap *createMyHashMap(int (*hashCode)(void *key),int (*equal)(void *key1,void *key2));

//使用全部参数创建HashMap
MyHashMap *createMyHashMapForAll(int initialCapacity,float loadFactor,int (*hashCode)(void *key),int (*equal)(void *key1,void *key2));

//释放HashMap
void freeMyHashMap(MyHashMap * map);

//是否包含某个key
int myHashMapContainsKey(MyHashMap *const map,void * const key);

//增加一条映射
void myHashMapPutData(MyHashMap *const map,void * const key,void * const value);

//通过key得到数据，如果没有数据则返回null
void* myHashMapGetDataByKey(MyHashMap * const map,void *const key);

//数据的容量
int myHashMapGetSize(const MyHashMap * const map);

//创建Entry迭代器
MyHashMapEntryIterator* createMyHashMapEntryIterator( MyHashMap *const map);

//释放Entry迭代器
void freeMyHashMapEntryIterator(MyHashMapEntryIterator* iterator);

//Entry迭代器是否有下一个
int myHashMapEntryIteratorHasNext(MyHashMapEntryIterator* iterator);

//遍历下一个Entry元素
Entry* myHashMapEntryIteratorNext(MyHashMapEntryIterator* iterator);

//删除一条数据，返回是否删除成功
int myHashMapRemoveDataByKey(MyHashMap *const map,void * const key);

//遍历
void myHashMapOutput(MyHashMap *map, void(*pt)(Entry*));

#endif // MYHASHMAP_H_INCLUDED

