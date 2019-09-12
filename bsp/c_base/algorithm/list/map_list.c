#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"

#define MAP_HEAD(name) LIST_HEAD(name)

typedef struct  {
    struct list_head list;
    int key;
    int data;
} MAP_ENTRY_TYPE;


static MAP_HEAD(map1);


static inline void map_insert(struct list_head *new, struct list_head *head)
{
    list_add_tail(new,head);
}


static MAP_ENTRY_TYPE  * map_find(int key, struct list_head *head)
{
    MAP_ENTRY_TYPE  *pos;

    list_for_each_entry(pos,head,list){
        if (pos->key == key) {
            return pos;
        }
    }

    return 0;
}


int main(int argc, char *argv[])
{
    MAP_ENTRY_TYPE entry1,entry2;
    MAP_ENTRY_TYPE *p_entry;

    entry1.key = 89;
    entry1.data = 1234;
    p_entry = &entry1;
    map_insert(&p_entry->list,&map1);


    entry2.key = 55;
    entry2.data = 7854;
    p_entry = &entry2;
    map_insert(&p_entry->list,&map1);


    p_entry = 0;
    p_entry = map_find(55,&map1);
    printf("key(55)--data(%d)\n",p_entry->data);
    return 0;
}

