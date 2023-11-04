// Physical memory allocator, for user processes,
// kernel stacks, page-table pages,
// and pipe buffers. Allocates whole 4096-byte pages.

#include "spinlock.h"
#include <string.h>

extern unsigned int __heap_start;
extern unsigned int __heap_end;

#define PGSIZE 4096 // bytes per page
#define PGSHIFT 12  // bits of offset within a page

#define PGROUNDUP(sz)  (((sz)+PGSIZE-1) & ~(PGSIZE-1))
#define PGROUNDDOWN(a) (((a)) & ~(PGSIZE-1))

struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  struct run *freelist;
} kmem;


void kfree(void *pa)
{
  struct run *r;

  if(((unsigned int)pa % PGSIZE) != 0 || (char*)pa < &__heap_start || (unsigned int)pa >= &__heap_end)
    printk("kfree err");

  memset(pa, 0, PGSIZE);
  r = (struct run*)pa;

  //acquire(&kmem.lock);
  r->next = kmem.freelist;
  kmem.freelist = r;
  //release(&kmem.lock);
}

void freerange(void *pa_start, void *pa_end)
{
  char *p = (char*)PGROUNDUP((unsigned int)pa_start);
  for(; p + PGSIZE <= (char*)pa_end; p += PGSIZE)
    kfree(p);
}

void kmalloc_init(void)
{
  //initlock(&kmem.lock, "kmem");
  freerange(&__heap_start, (void*)&__heap_end);
  //  freerange(end, (void*)&__heap_end);
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
void *kalloc(void)
{
  struct run *r;

  //acquire(&kmem.lock);
  r = kmem.freelist;
  if(r)
    kmem.freelist = r->next;
  //release(&kmem.lock);

  if(r)
    memset((char*)r, 5, PGSIZE); // fill with junk
  return (void*)r;
}

