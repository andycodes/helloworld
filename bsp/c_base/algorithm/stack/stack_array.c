#include <stdio.h>
#include <malloc.h>




struct stack_load{
	int data;
};

struct stack_blk{
	int count;
	int size;
	struct stack_load load[0];
};


struct stack_blk *create_array_stack(int sz)
{
	struct stack_blk * stack =
		(struct stack_blk  *)malloc(sizeof(struct stack_blk) + sz*sizeof(struct stack_load));
	if (stack == NULL) {
		printf("arr malloc error!");
		return NULL;
	}

	stack->size = sz;
	stack->count = 0;

	return stack;
}


void destroy_array_stack(struct stack_blk * stack)
{
	if (stack != NULL) {
		free(stack);
		stack = NULL;
	}
}


void push(struct stack_blk * stack,struct stack_load load)
{
	stack->load[stack->count++] = load;
	if (stack->count > stack->size) {
		printf("[%s] push count[%d] too big\n", __func__, stack->count);
		stack->count = stack->count % stack->size;
	}
}

// 返回“栈顶元素值”
struct stack_load  peek(struct stack_blk * stack)
{
	return stack->load[stack->count-1];
}

// 返回“栈顶元素值”，并删除“栈顶元素”
struct stack_load  pop(struct stack_blk * stack)
{
	struct stack_load  ret = stack->load[stack->count-1];
	stack->count--;
	return ret;
}

// 返回“栈”的大小
int size(struct stack_blk * stack)
{
	return stack->count;
}

// 返回“栈”是否为空
int is_empty(struct stack_blk * stack)
{
	return size(stack)==0;
}

// 打印“栈”
void print_array_stack(struct stack_blk * stack)
{
	if (is_empty(stack)) {
		printf("stack is Empty\n");
		return ;
	}

	printf("stack size()=%d\n", size(stack));

	int i=size(stack)-1;
	while (i>=0)
	{
		printf("%d\n", stack->load[i].data);
		i--;
	}
}


void main()
{
	struct stack_load tmp;

	// 创建“栈”
	struct stack_blk * stack = create_array_stack(12);

	// 将10, 20, 30 依次推入栈中
	struct stack_load load;
	load.data =10;
	push(stack,load);
	load.data =20;
	push(stack,load);
	load.data =30;
	push(stack,load);

	//print_array_stack();	// 打印栈

	// 将“栈顶元素”赋值给tmp，并删除“栈顶元素”
	tmp = pop(stack);
	printf("tmp=%d\n", tmp.data);
	//print_array_stack();	// 打印栈

	// 只将“栈顶”赋值给tmp，不删除该元素.
	tmp = peek(stack);
	printf("tmp=%d\n", tmp.data);
	//print_array_stack();	// 打印栈

	load.data =40;
	push(stack,load);
	print_array_stack(stack);	// 打印栈

	// 销毁栈
	destroy_array_stack(stack);
}



