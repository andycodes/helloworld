#ifndef __JERRY_RADIX_TREE__                                                                                               
#define __JERRY_RADIX_TREE__


#include "radix_tree.h"
#include <malloc.h>


#define ARRARY_SIZE(a) ((sizeof(a)) / (sizeof((a)[0])))

/**
 * Radix_tree node definiton
 */
#if 0
#define RADIX_TREE_MAP_SHIFT 8
#define RADIX_TREE_MAP_SIZE (1 << RADIX_TREE_MAP_SHIFT)
#define RADIX_TREE_MAP_MASK (RADIX_TREE_MAP_SIZE - 1)
#define RADIX_TREE_INDEX_BITS (8 * sizeof(unsigned int))
#define RADIX_TREE_MAX_PATH ( RADIX_TREE_INDEX_BITS / RADIX_TREE_MAP_SHIFT + 1)
#endif
#define RADIX_TREE_MAP_SHIFT 3
#define RADIX_TREE_MAP_SIZE (1 << RADIX_TREE_MAP_SHIFT)
#define RADIX_TREE_MAP_MASK (RADIX_TREE_MAP_SIZE - 1)
#define RADIX_TREE_INDEX_BITS (8 * sizeof(unsigned int))
#define RADIX_TREE_MAX_PATH ( 4 )

typedef struct radix_tree_node
{
    unsigned int count;
    void *slots[RADIX_TREE_MAP_SIZE];
}radix_tree_node;

typedef radix_tree_node * Pradix_tree_node;
typedef Pradix_tree_node * PPradix_tree_node;

struct radix_tree_head
{
    unsigned int height;
    Pradix_tree_node rnode;
    unsigned int height_to_maxindex[RADIX_TREE_MAX_PATH];
};

struct radix_tree_path
{
    Pradix_tree_node node;
    PPradix_tree_node slot;
};
typedef struct radix_tree_path radix_tree_path;
typedef radix_tree_path * Pradix_tree_path;

#endif /* __JERRY_RADIX_TREE__ */  
