#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack {
	unsigned int top;
	unsigned int max_entries;
	unsigned int entries[0];
};

struct stack *stack_new(unsigned int max_entries)
{
	struct stack *self = (struct stack *)malloc((sizeof(*self) +
				     max_entries * sizeof(unsigned int)));
	if (self != NULL)
	    {
	        memset((void*)self,0,(sizeof(*self) +
				     max_entries * sizeof(unsigned int)));

		    self->max_entries = max_entries;
	    }

	return self;
}

void stack_delete(struct stack *self)
{
	free((void*)self);
	self = NULL;
}

int stack_empty(const struct stack *self)
{
	return self->top == 0;
}

void stack_remove(struct stack *self, unsigned int key)
{
	unsigned int i = self->top, last_index = self->top - 1;

	while (i-- != 0) {
		if (self->entries[i] == key) {
			if (i < last_index)
				memmove(self->entries + i,
					(const void*)(self->entries + i + 1),
					(last_index - i) * sizeof(unsigned int));
			--self->top;
			return;
		}
	}
}

void stack_push(struct stack *self, unsigned int key)
{
	if (self->top == self->max_entries) {
		printf("%s: top=%d, overflow!\n", __func__, self->top);
		return;
	}
	self->entries[self->top++] = key;
}

unsigned int stack_pop(struct stack *self)
{
	unsigned int ret;

	if (self->top == 0) {
		printf("%s: underflow!\n", __func__);
		return 0;
	}

	ret = self->entries[--self->top];
	self->entries[self->top] = 0;
	return ret;
}


void stack_debug(struct stack *self)
{
    int i = 0;
    printf("stack_debug\n");
    for(i = 0;i<self->top;i++) {
        printf("stack_debug entries %d\n",self->entries[i]);
    }
}

int main( int argc, char *argv[])
{
    int i = 6;
    unsigned int entries[] = {1,2,3,4,5,6};
    struct stack *self = stack_new(8);

    while(i--){
            stack_push(self,entries[i]);
	}

    stack_debug(self);
    stack_remove(self,0);
    stack_debug(self);
    stack_push(self,88);
    stack_debug(self);
    stack_pop(self);
    stack_debug(self);
    return 0;
}

/*main : just for test -e*/

