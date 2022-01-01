#ifndef LIB_H
#define LIB_H

#include <stdint.h>

/*Double Linked List*/
typedef struct list_node_tag {
    struct list_node_tag *prev;
    struct list_node_tag *next;
}list_node_t;

extern void list_node_init(list_node_t *node);

typedef struct list_tag {
    list_node_t head;
    uint32_t node_count;
}list_t;

#define container_of(node, parent, name) (parent *)((uint32_t)node - (uint32_t)&((parent *)0)->name)
extern void list_init(list_t *list);
extern uint32_t list_count(list_t *list);
extern list_node_t *list_head(list_t *list);
extern list_node_t *list_tail(list_t *list);
extern list_node_t *node_prev(list_node_t *list_node);
extern list_node_t *node_next(list_node_t *list_node);
extern void list_remove_all(list_t *list);
extern void list_insert_head(list_t *list, list_node_t *list_node);
extern void list_append_last(list_t *list, list_node_t *list_node);
extern list_node_t *list_remove_first(list_t *list);
extern void list_remove(list_t *list, list_node_t *node);


extern uint32_t _bss;
extern uint32_t _ebss;
static inline void clear_bss(void)
{
    uint8_t *start = (uint8_t *)_bss;
    while ((uint32_t)start < _ebss) {
        *start = 0;
        start++;
    }
}

#endif /*LIB_H*/
