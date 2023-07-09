#ifndef KALLOC_H
#define KALLOC_H

void*           kalloc(void);
void            kfree(void *);
void            kmalloc_init(void);

#endif /*KALLOC_H*/
