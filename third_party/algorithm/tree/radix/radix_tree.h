#ifndef __JERRY_RADIX                                                                                                      
#define __JERRY_RADIX

#include <stdio.h>

struct radix_tree_head;
typedef struct radix_tree_head radix_tree_head;
typedef radix_tree_head * Pradix_tree_head;

#ifdef __cplus_cplus
extern "c" {
#endif

extern Pradix_tree_head radix_tree_head_new(void);
extern void radix_tree_initial(Pradix_tree_head thiz);
extern int radix_tree_destroy(Pradix_tree_head thiz);
extern int radix_tree_insert(Pradix_tree_head thiz, unsigned int index, void *item); 
extern void * radix_tree_lookup(Pradix_tree_head thiz, unsigned index); 
extern void * radix_tree_delete(Pradix_tree_head thiz, unsigned index); 
extern unsigned int radix_tree_gang_lookup(Pradix_tree_head thiz,
                                           void ** results,
                                           unsigned int firs_index,
                                           unsigned int max_items);

#ifdef __cplus_cplus
}
#endif

#endif