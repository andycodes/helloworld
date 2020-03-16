/*
1. 两数之和
难度简单7810
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
示例:
给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]

*/
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
	HashMap *hashmap = hashmap_init(numsSize, hashcode_int, hashequal_int);
	int* res = (int *)calloc(2, sizeof(int));

	for (int i = 0; i < numsSize; i++) {
		int diff = target - nums[i];
		DataType entry;
		entry.key = diff;
		hashmap_getValue(hashmap, &entry);
		if (entry.id == -1) {
			DataType push;
			push.key = nums[i];
			push.val = i;
			hashmap_push(hashmap, push);
		} else {
				*returnSize = 2;
				res[0] = i;
				res[1] = entry.val;
				break;
		}
	}

	return res;
}




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

#ifndef HLIST_H
#define HLIST_H

#include <stddef.h>
#include <stdbool.h>

/*
 * 该结构体用于嵌入到业务数据结构体中(entry)，用于实现链表
 * 例：
 *     struct Entry {           // 你的业务数据结构体
 *         ...
 *         struct Node node;    // 嵌入其中，位置任意
 *         ...
 *     };
 */
struct Node {
    struct Node *next, *prev;
};

/*
 * 由成员变量 node 地址获取结构体 entry 地址
 * 例：
 *     struct Entry entry;
 *     struct Node *n = &entry.node;
 *     struct Entry *p = NODE_ENTRY(n, struct Entry, node);
 *     此时 p 指向 entry
 */
#define NODE_ENTRY(node, type, member) \
    ((type*)((char*)(node) - (size_t)&((type*)0)->member))

/*
 * 用户定义，针对 node 节点的处理函数
 * 注意: 入参是 node 指针！
 * 你可能需要使用 NODE_ENTRY 来获取并处理 entry
 */
typedef void (*NodeFunc)(struct Node *node);

/*
 * 用户定义，针对 node 节点的处理函数，带可选参数
 * 注意: 入参是 node 指针！
 * 你可能需要使用 NODE_ENTRY 来获取并处理 entry
 */
typedef void (*NodeFuncX)(struct Node *node, void *arg);


/* 带哨兵节点的双向链表 */
struct List {
    struct Node base;
};

static inline void ListInit(struct List *list)
{
    list->base.next = &list->base;
    list->base.prev = &list->base;
}

static inline bool ListEmpty(const struct List *list)
{
    return list->base.next == &list->base;
}

static inline bool ListIsHead(const struct List *list, const struct Node *node)
{
    return list->base.next == node;
}

static inline bool ListIsTail(const struct List *list, const struct Node *node)
{
    return list->base.prev == node;
}

/* node 插入到 pos 前面 */
static inline void ListInsert(struct Node *pos, struct Node *node)
{
    node->prev = pos->prev;
    node->next = pos;
    node->prev->next = node;
    node->next->prev = node;
}

static inline void ListAddTail(struct List *list, struct Node *node)
{
    ListInsert(&list->base, node);
}

static inline void ListAddHead(struct List *list, struct Node *node)
{
    ListInsert(list->base.next, node);
}

static inline void ListRemove(struct Node *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

static inline void ListRemoveTail(struct List *list)
{
    ListRemove(list->base.prev);
}

static inline void ListRemoveHead(struct List *list)
{
    ListRemove(list->base.next);
}

static inline void ListReplace(struct Node *old, struct Node *node)
{
    node->next = old->next;
    node->next->prev = node;
    node->prev = old->prev;
    node->prev->next = node;
}

#define LIST_FOR_EACH(node, list) \
    for (node = (list)->base.next; \
         node != &(list)->base; \
         node = (node)->next)

#define LIST_FOR_EACH_SAFE(node, tmp, list) \
    for (node = (list)->base.next, tmp = (node)->next; \
         node != &(list)->base; \
         node = tmp, tmp = (node)->next)

/*
 * 遍历处理链表节点
 * 注意: nodeProc 函数入参是 node 指针！
 *       遍历时不要改变链表结构！
 */
static inline void ListIterate(struct List *list,
                               NodeFuncX nodeProc,
                               void *arg)
{
    struct Node *node;
    LIST_FOR_EACH(node, list) {
        nodeProc(node, arg);
    }
}

/* 注意：NodeFunc 函数入参是 node 而非 entry! */
static inline void ListDeinit(struct List *list, NodeFunc nodeDeinit)
{
    if (nodeDeinit == NULL) {
        return;
    }

    struct Node *node, *tmp;
    LIST_FOR_EACH_SAFE(node, tmp, list) {
        nodeDeinit(node);
    }
}

/* 获取头结点，或空 */
#define LIST_HEAD_ENTRY(list, type, member) \
    (ListEmpty(list) ? NULL : NODE_ENTRY((list)->base.next, type, member))

/* 获取尾结点，或空 */
#define LIST_TAIL_ENTRY(list, type, member) \
    (ListEmpty(list) ? NULL : NODE_ENTRY((list)->base.prev, type, member))

/* 获取下一结点，或空 */
#define LIST_NEXT_ENTRY(entry, list, type, member) \
    (ListIsTail(list, &(entry)->member) ? \
        NULL : \
        NODE_ENTRY((entry)->member.next, type, member))

/* 获取上一结点，或空 */
#define LIST_PREV_ENTRY(entry, list, type, member) \
    (ListIsHead(list, &(entry)->member) ? \
        NULL : \
        NODE_ENTRY((entry)->member.prev, type, member))

/* 遍历链表；过程中如需操作链表，请使用 _SAFE 版本 */
#define LIST_FOR_EACH_ENTRY(entry, list, type, member) \
    for (entry = NODE_ENTRY((list)->base.next, type, member); \
         &(entry)->member != &(list)->base; \
         entry = NODE_ENTRY((entry)->member.next, type, member))

#define LIST_FOR_EACH_ENTRY_SAFE(entry, tmp, list, type, member) \
    for (entry = NODE_ENTRY((list)->base.next, type, member), \
         tmp = NODE_ENTRY((entry)->member.next, type, member); \
         &(entry)->member != &(list)->base; \
         entry = tmp, tmp = NODE_ENTRY((entry)->member.next, type, member))

/* 倒序遍历链表；过程中如需操作链表，请使用 _SAFE 版本 */
#define LIST_FOR_EACH_ENTRY_REVERSE(entry, list, type, member) \
    for (entry = NODE_ENTRY((list)->base.prev, type, member); \
         &(entry)->member != &(list)->base; \
         entry = NODE_ENTRY((entry)->member.prev, type, member))

#define LIST_FOR_EACH_ENTRY_REVERSE_SAFE(entry, tmp, list, type, member) \
    for (entry = NODE_ENTRY((list)->base.prev, type, member), \
         tmp = NODE_ENTRY((entry)->member.prev, type, member); \
         &(entry)->member != &(list)->base; \
         entry = tmp, tmp = NODE_ENTRY((entry)->member.prev, type, member))

#endif /* HLIST_H */


#ifndef HHASH_H
#define HHASH_H

#include <stdbool.h>
#include <stdlib.h>

/* 基于链表，链地址法 */
//#include "hlist.h"

/*
 * 用户定义，判断两个节点是否相同
 * 入参是 node 指针！可使用 NODE_ENTRY 获取对应 entry
 */
typedef bool (*HashEqualFunc)(const struct Node *a, const struct Node *b);

/*
 * 用户定义，hash key 生成函数，用于索引 hash 桶
 * 返回值不应超过 hash 桶大小限制！
 * 入参是 node 指针！可使用 NODE_ENTRY 获取对应 entry
 */
typedef size_t (*HashKeyFunc)(const struct Node *node, size_t bktSize);

/*
 * Thomas Wong 整数散列函数
 * 你可以按需使用，并实现你的 HashKeyFunc
 * 注意：返回值或超过哈希桶大小，需要进一步处理！
 */
static inline size_t TwIntHash(unsigned int key)
{
    key = ~key + (key << 15);
    key = key ^ (key >> 12);
    key = key + (key << 2);
    key = key ^ (key >> 4);
    key = (key + (key << 3)) + (key << 11);
    key = key ^ (key >> 16);
    return (size_t)key;
}

/*
 * BKDR 字符串散列函数
 * 你可以按需使用，并实现你的 HashKeyFunc
 * 注意：返回值或超过哈希桶大小，需要进一步处理！
 */
static inline size_t BkdrHash(const char *str)
{
    size_t hash = 0;
    register size_t ch = 0;
    while ((ch = (size_t)(*str++)) != '\0') {
        // hash = hash * 131 + ch;
        hash = (hash << 7) + (hash << 1) + hash + ch;
    }
    return hash;
}

struct HashTable {
    size_t bktSize;
    HashEqualFunc equal;
    HashKeyFunc key;
    struct List *bkts;
};

/* 成功返回 0；失败返回 -1 */
static inline int HashInit(struct HashTable *ht,
                           size_t bktSize,
                           HashEqualFunc equal,
                           HashKeyFunc key)
{
    ht->bktSize = bktSize;
    ht->equal = equal;
    ht->key = key;
    ht->bkts = (struct List*)malloc(sizeof(struct List) * bktSize);
    if (ht->bkts == NULL) {
        return -1;
    }

    size_t i;
    for (i = 0; i < bktSize; i++) {
        ListInit(&ht->bkts[i]);
    }
    return 0;
}

/* 注意：NodeFunc 函数入参是 node 而非 entry! */
static inline void HashDeinit(struct HashTable *ht, NodeFunc nodeDeinit)
{
    if (nodeDeinit != NULL) {
        size_t i;
        for (i = 0; i < ht->bktSize; i++) {
            ListDeinit(&ht->bkts[i], nodeDeinit);
        }
    }
    free(ht->bkts);
}

static inline void HashAdd(struct HashTable *ht, struct Node *node)
{
    size_t k = ht->key(node, ht->bktSize);
    struct List *list = &ht->bkts[k];
    ListAddTail(list, node);
}

static inline void HashRemove(struct Node *node)
{
    ListRemove(node);
}

static inline struct Node *HashFind(const struct HashTable *ht,
                                    const struct Node *cmpNode)
{
    size_t k = ht->key(cmpNode, ht->bktSize);
    struct List *list = &ht->bkts[k];
    struct Node *node;
    LIST_FOR_EACH(node, list) {
        if (ht->equal(cmpNode, node)) {
            return node;
        }
    }
    return NULL;
}

/*
 * 遍历处理哈希节点
 * 注意: nodeProc 函数入参是 node 指针！
 *       遍历时不要改变 key 值及链表结构！
 */
static inline void HashIterate(struct HashTable *ht,
                               NodeFuncX nodeProc,
                               void *arg)
{
    size_t i;
    for (i = 0; i < ht->bktSize; i++) {
        struct Node *node;
        LIST_FOR_EACH(node, &ht->bkts[i]) {
            nodeProc(node, arg);
        }
    }
}

/*
 * 重置哈希表参数并触发 rehash
 * 传入零值参数可保持原值不变
 * 成功返回 0；失败返回 -1；失败时，原哈希表仍可使用
 */
static inline int HashReset(struct HashTable *ht,
                            size_t bktSize,
                            HashEqualFunc equal,
                            HashKeyFunc key)
{
    bktSize = bktSize != 0 ? bktSize : ht->bktSize;
    equal = equal != NULL ? equal : ht->equal;
    key = key != NULL ? key : ht->key;

    struct HashTable newHt;
    int ret = HashInit(&newHt, bktSize, equal, key);
    if (ret != 0) {
        return -1;
    }

    size_t i;
    for (i = 0; i < ht->bktSize; i++) {
        struct List *list = &ht->bkts[i];
        struct Node *node, *tmp;
        LIST_FOR_EACH_SAFE(node, tmp, list) {
            HashAdd(&newHt, node);
        }
    }

    free(ht->bkts);
    *ht = newHt;
    return 0;
}


#endif /* HHASH_H */

/*
1. 两数之和
难度简单7810
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整
数，并返回他们的数组下标。
你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
示例:
给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]

*/

#define MAXN 100

struct DataEntry {
    int key;
    int value;
    struct Node node;
};

static bool DataEntryEqual(const struct Node *a, const struct Node *b)
{
    struct DataEntry *d1 = NODE_ENTRY(a, struct DataEntry, node);
    struct DataEntry *d2 = NODE_ENTRY(b, struct DataEntry, node);
    return d1->key == d2->key;
}

static size_t DataEntryKey(const struct Node *node, size_t bktSize)
{
    struct DataEntry *e = NODE_ENTRY(node, struct DataEntry, node);
    return e->key % bktSize;
}


int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
	struct HashTable ht;
    	size_t bktSize = numsSize;
	int ret = HashInit(&ht, bktSize, DataEntryEqual, DataEntryKey);
	//SHOULD(ret == 0);

	int* res = (int *)calloc(2, sizeof(int));

	for (int i = 0; i < numsSize; i++) {
		int diff = target - nums[i];
		struct Node *findNode;
		struct DataEntry findEntry;
		findEntry.key = diff;
		findNode = HashFind(&ht, &findEntry.node);
		if(findNode == NULL) {
			struct DataEntry *newEntry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
			newEntry->key = nums[i];
			newEntry->value = i;
			HashAdd(&ht, &newEntry->node);
		} else {
				*returnSize = 2;
				res[1] = i;
				struct DataEntry *entry;
				entry = NODE_ENTRY(findNode, struct DataEntry, node);
				res[0] = entry->value;
				break;
		}
	}

	HashDeinit(&ht, NULL);
	return res;
}

int main()
{
	int array[] = {2, 7, 11, 15};
	int target = 9;
	int returnSize;
	int *ret = twoSum(array, 4, target, &returnSize);

	for (int i = 0; i < returnSize; i++) {
			printf("%d", ret[i]);
	}
}
