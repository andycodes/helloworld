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

