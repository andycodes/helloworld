/*
 * Simple pointer stack
 *
 * (c) 2010 Arnaldo Carvalho de Melo <acme@redhat.com>
 */

#include "pstack.h"
#include <linux/kernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define pr_err(fmt, ...) \
	printf(fmt, ##__VA_ARGS__)

#define pstack_debug(fmt, ...) \
	printf(fmt, ##__VA_ARGS__)

struct pstack {
	unsigned short	 top;
	unsigned short	 max_nr_entries;
	void		*entries[0];
};

struct pstack *pstack__new(unsigned short max_nr_entries)
{
	struct pstack *self = (struct pstack *)malloc((sizeof(*self) +
				     max_nr_entries * sizeof(void *)));
	if (self != NULL)
	    {
	        memset((void*)self,0,(sizeof(*self) +
				     max_nr_entries * sizeof(void *)));

		    self->max_nr_entries = max_nr_entries;
	    }

	return self;
}

void pstack__delete(struct pstack *self)
{
	free((void*)self);
}

bool pstack__empty(const struct pstack *self)
{
	return self->top == 0;
}

void pstack__remove(struct pstack *self, void *key)
{
	unsigned short i = self->top, last_index = self->top - 1;

	while (i-- != 0) {
		if (self->entries[i] == key) {
			if (i < last_index)
				memmove(self->entries + i,
					(const void*)(self->entries + i + 1),
					(last_index - i) * sizeof(void *));
			--self->top;
			return;
		}
	}
	pr_err("%s: %p not on the pstack!\n", __func__, key);
}

void pstack__push(struct pstack *self, void *key)
{
	if (self->top == self->max_nr_entries) {
		pr_err("%s: top=%d, overflow!\n", __func__, self->top);
		return;
	}
	self->entries[self->top++] = key;
}

void *pstack__pop(struct pstack *self)
{
	void *ret;

	if (self->top == 0) {
		pr_err("%s: underflow!\n", __func__);
		return NULL;
	}

	ret = self->entries[--self->top];
	self->entries[self->top] = NULL;
	return ret;
}


/*main : just for test -s*/
/* gdb is good*/

void pstack_debugfun(struct pstack *self)
{
    int i = 0;
    for(i = 0;i<self->top;i++)
    {
        if(NULL != self->entries[i])
            {
                pstack_debug("entries %p\n",self->entries[i]);
            }
    }
}

int main( int argc, char *argv[])
{
    int i = 6;
    void* entries[] = {1,2,3,4,5,6};
    struct pstack *self = pstack__new(8);

    while(i--)
        {
            pstack__push(self,entries[i]);
        }


    pstack_debugfun(self);
    pstack_debug("max_nr_entries:%d \ntop: %d\n",self->max_nr_entries,self->top);
    pstack__remove(self,(void*)0);
    pstack_debug("\nafter pstack__remove-----\n");
    pstack_debugfun(self);
    pstack_debug("max_nr_entries:%d \ntop: %d\n",self->max_nr_entries,self->top);
    pstack_debug("self %p\n",(void*)self);

    return 0;
}

/*main : just for test -e*/

