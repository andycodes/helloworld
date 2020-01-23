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


struct stack_blk *array_stack_init(int sz)
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


void array_stack_exit(struct stack_blk * stack)
{
	if (stack != NULL) {
		free(stack);
		stack = NULL;
	}
}


void array_stack_push(struct stack_blk * stack,struct stack_load load)
{
	stack->load[stack->count++] = load;
	if (stack->count > stack->size) {
		printf("[%s] array_stack_push count[%d] too big\n", __func__, stack->count);
		stack->count = stack->count % stack->size;
	}
}

// 返回“栈顶元素值”
struct stack_load  array_stack_top(struct stack_blk * stack)
{
	return stack->load[stack->count-1];
}

// 返回“栈顶元素值”，并删除“栈顶元素”
struct stack_load  array_stack_pop(struct stack_blk * stack)
{
	struct stack_load  ret = stack->load[stack->count-1];
	stack->count--;
	return ret;
}

// 返回“栈”的大小
int array_stack_size(struct stack_blk * stack)
{
	return stack->count;
}

// 返回“栈”是否为空
int array_stack_empty(struct stack_blk * stack)
{
	return array_stack_size(stack)==0;
}

// 打印“栈”
void array_stack_print(struct stack_blk * stack)
{
	if (array_stack_empty(stack)) {
		printf("stack is Empty\n");
		return ;
	}

	printf("stack size()=%d\n", array_stack_size(stack));

	int i=array_stack_size(stack)-1;
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
	struct stack_blk * stack = array_stack_init(12);

	// 将10, 20, 30 依次推入栈中
	struct stack_load load;
	load.data =10;
	array_stack_push(stack,load);
	load.data =20;
	array_stack_push(stack,load);
	load.data =30;
	array_stack_push(stack,load);

	//array_stack_print();	// 打印栈

	// 将“栈顶元素”赋值给tmp，并删除“栈顶元素”
	tmp = array_stack_pop(stack);
	printf("tmp=%d\n", tmp.data);
	//array_stack_print();	// 打印栈

	// 只将“栈顶”赋值给tmp，不删除该元素.
	tmp = array_stack_top(stack);
	printf("tmp=%d\n", tmp.data);
	//array_stack_print();	// 打印栈

	load.data =40;
	array_stack_push(stack,load);
	array_stack_print(stack);	// 打印栈

	// 销毁栈
	array_stack_exit(stack);
}



