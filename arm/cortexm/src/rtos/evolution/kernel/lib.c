#include "lib.h"
#include "os_stdio.h"


void list_node_init(list_node_t *node)
{
    if (node != (list_node_t *) NULL) {
        node->prev = node;
        node->next = node;
    }
}

void list_init(list_t *list)
{

    if (list != (list_t * )NULL) {
        list->node_count = 0;
        list_node_init(&(list->head));
    }
}

uint32_t list_count(list_t *list)
{
    uint32_t ret = 0;
    if (list != (list_t * )NULL) {
       ret = list->node_count;
    }
    return ret;
}

list_node_t *list_head(list_t *list)
{
    list_node_t *head = &(list->head);
    list_node_t *ret = (list_node_t *)NULL;
    if (list->node_count != 0) {
        ret = head->next;
    }
    return ret;
}

list_node_t *list_tail(list_t *list)
{
    list_node_t *head = &(list->head);
    list_node_t *ret = (list_node_t *)NULL;
    if (list->node_count != 0) {
        ret = head->prev;
    }
    return ret;
}

list_node_t *node_prev(list_node_t *list_node)
{
    list_node_t *ret = (list_node_t *)NULL;
    if (list_node != (list_node_t *)NULL) {
        ret = list_node->prev;
    }
    return ret;
}

list_node_t *node_next(list_node_t *list_node)
{
    list_node_t *ret = (list_node_t *)NULL;
    if (list_node != (list_node_t *)NULL) {
        ret = list_node->next;
    }
    return ret;
}

void list_remove_all(list_t *list)
{
    uint32_t count;
    list_node_t *head = (list_node_t *)NULL;
    list_node_t *next_node = (list_node_t *)NULL;
    list_node_t *cur_node = (list_node_t *)NULL;
    if (list == (list_t *)NULL) {
        goto cleanup;
    }

    head = &(list->head);
    next_node = head->next;
    for (count = list->node_count; count != 0; count--) {
        cur_node = next_node;
        next_node = cur_node->next;
        cur_node->next = cur_node;
        cur_node->prev = cur_node;
    }

    head->prev = head;
    head->next = head;
    list->node_count = 0;
cleanup:
    return;

}

void list_insert_head(list_t *list, list_node_t *list_node)
{
    list_node_t *head = (list_node_t *)NULL;
    list_node_t *next = (list_node_t *)NULL;
    if (list == (list_t *)NULL) {
        goto cleanup;
    }

    head = &(list->head);
    next = head->next;

    head->next = list_node;
    next->prev = list_node;
    list_node->prev = head;
    list_node->next = next;
    list->node_count++;
cleanup:
    return;
}

void list_append_last(list_t *list, list_node_t *list_node)
{
    list_node_t *head = (list_node_t *)NULL;
    list_node_t *last = (list_node_t *)NULL;
    if (list == (list_t *)NULL) {
        goto cleanup;
    }

    head = &(list->head);
    last = head->prev;

    list_node->next = head;
    list_node->prev = last;
    last->next = list_node;
    head->prev = list_node;
    list->node_count++;
cleanup:
    return;
}

list_node_t *list_remove_first(list_t *list)
{
    list_node_t *head = (list_node_t *)NULL;
    list_node_t *next = (list_node_t *)NULL;
    list_node_t *ret = (list_node_t *)NULL;

    if (list == (list_t *)NULL) {
        goto cleanup;
    }

    head = &(list->head);
    ret = head->next;
    if (ret == head) {
        ret = (list_node_t *)NULL;
        goto cleanup;
    }

    next = ret->next;
    head->next = next;
    next->prev = head;
    ret->next = ret;
    ret->prev = ret;
    list->node_count--;
cleanup:
    return ret;
}

void list_remove(list_t *list, list_node_t *node)
{
    list_node_t *next = (list_node_t *)NULL;
    list_node_t *prev = (list_node_t *)NULL;

    if (list == (list_t *) NULL || node == (list_node_t *)NULL) {
        goto cleanup;
    }

    next = node->next;
    prev = node->prev;
    if (next == (list_node_t *)NULL || prev == (list_node_t *)NULL) {
        goto cleanup;
    }

    prev->next = next;
    next->prev = prev;
    list->node_count--;
cleanup:
    return;
}
