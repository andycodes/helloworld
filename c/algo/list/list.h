#ifndef LIST_H
#define LIST_H

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

#endif /* LIST_H */

