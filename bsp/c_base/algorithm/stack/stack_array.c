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

// ���ء�ջ��Ԫ��ֵ��
struct stack_load  peek(struct stack_blk * stack)
{
	return stack->load[stack->count-1];
}

// ���ء�ջ��Ԫ��ֵ������ɾ����ջ��Ԫ�ء�
struct stack_load  pop(struct stack_blk * stack)
{
	struct stack_load  ret = stack->load[stack->count-1];
	stack->count--;
	return ret;
}

// ���ء�ջ���Ĵ�С
int size(struct stack_blk * stack)
{
	return stack->count;
}

// ���ء�ջ���Ƿ�Ϊ��
int is_empty(struct stack_blk * stack)
{
	return size(stack)==0;
}

// ��ӡ��ջ��
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

	// ������ջ��
	struct stack_blk * stack = create_array_stack(12);

	// ��10, 20, 30 ��������ջ��
	struct stack_load load;
	load.data =10;
	push(stack,load);
	load.data =20;
	push(stack,load);
	load.data =30;
	push(stack,load);

	//print_array_stack();	// ��ӡջ

	// ����ջ��Ԫ�ء���ֵ��tmp����ɾ����ջ��Ԫ�ء�
	tmp = pop(stack);
	printf("tmp=%d\n", tmp.data);
	//print_array_stack();	// ��ӡջ

	// ֻ����ջ������ֵ��tmp����ɾ����Ԫ��.
	tmp = peek(stack);
	printf("tmp=%d\n", tmp.data);
	//print_array_stack();	// ��ӡջ

	load.data =40;
	push(stack,load);
	print_array_stack(stack);	// ��ӡջ

	// ����ջ
	destroy_array_stack(stack);
}



