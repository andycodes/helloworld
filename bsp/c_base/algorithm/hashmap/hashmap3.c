/*
 * hashmap.c
 *        Generic hashmap implementation.
 *      a map for pair of key-value. key must be a null-end string, value is any type of data.
 *        cheungmine
 *      Sep. 22, 2007.  All rights reserved.
 */
#include "hashmap.h"
#include "list.h"

typedef struct _hash_map_t
{
    size_t            size;
    listnode_t**    key;
    listnode_t**    value;
}hash_map_t;

/* Hash a string, return a hash key */
static ulong  hash_string(const char  *s, int len)
{
    ulong h = 0;
    int   i = 0;
    assert (s);
    if (len < 0)
        len = (s? (int)strlen(s): 0);
    while(i++ < len) { h = 17*h + *s++; }
    return h;
}

static void _free_map_key(listnode_t* node)
{
    listnode_t    *old;
    while(node)
    {
        old = node;
        node = node->next;

        free(old->data);
        free (old);
    }
}

static void _free_map_value(listnode_t* node, pfcb_hmap_value_free pfunc)
{
    listnode_t    *old;
    while(node)
    {
        old = node;
        node = node->next;

        if (pfunc)
            (*pfunc)(old->data);
        free (old);
    }
}

/*=============================================================================
                            Public Functions
=============================================================================*/
/* Create before use */
void
hmap_create(hash_map *hmap, int size)
{
    (*hmap) = (hash_map_t*) malloc(sizeof(hash_map_t));
    (*hmap)->size = size;
    (*hmap)->key = (listnode_t**) calloc(size, sizeof(listnode_t*));
    (*hmap)->value = (listnode_t**) calloc(size, sizeof(listnode_t*));
}

/* Destroy after use */
extern void
hmap_destroy(hash_map hmap, pfcb_hmap_value_free pfunc)
{
    size_t i;
    for(i=0; i<hmap->size; i++){
        _free_map_key(hmap->key[i]);
        _free_map_value(hmap->value[i], pfunc);
    }

    free(hmap->key);
    free(hmap->value);
    free(hmap);
}

/* Insert a key-value into hash map. value is a pointer to callee-allocated memory */
void
hmap_insert(hash_map hmap, const char* key, int key_len, void* value)
{
    listnode_t    *node_key, *node_val;
    ulong        h;
    char        *s;
    assert (key);

    if (key_len<0) key_len = (int) strlen (key);
    s = (char*) malloc (key_len+1);
    assert(s);

#pragma warning(push)    /* C4996 */
#pragma warning( disable : 4996 )
    strncpy (s, key, key_len);
#pragma warning(pop)    /* C4996 */
    s[key_len] = 0;

    node_key = list_node_create ( (void*)s );
    node_val = list_node_create ( value );
    assert(node_key && node_val);

    h = hash_string (s, key_len) % hmap->size;

    node_key->next = hmap->key[h];
    hmap->key[h] = node_key;

    node_val->next = hmap->value[h];
    hmap->value[h] = node_val;
}

/* Search a hash map for value of given key string */
void*
hmap_search(hash_map hmap, const char *key)
{
    ulong        h    = hash_string (key, -1) % hmap->size;
    listnode_t  *pk = hmap->key[h];
    listnode_t  *pv = hmap->value[h];

    while (pk)
    {
        if (strcmp(key, pk->str) == 0)
            return pv->data;
        pk = pk->next;
        pv = pv->next;
    }

    return NULL;
}
