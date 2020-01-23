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

// ���ء�ջ��Ԫ��ֵ��
struct stack_load  array_stack_top(struct stack_blk * stack)
{
	return stack->load[stack->count-1];
}

// ���ء�ջ��Ԫ��ֵ������ɾ����ջ��Ԫ�ء�
struct stack_load  array_stack_pop(struct stack_blk * stack)
{
	struct stack_load  ret = stack->load[stack->count-1];
	stack->count--;
	return ret;
}

// ���ء�ջ���Ĵ�С
int array_stack_size(struct stack_blk * stack)
{
	return stack->count;
}

// ���ء�ջ���Ƿ�Ϊ��
int array_stack_empty(struct stack_blk * stack)
{
	return array_stack_size(stack)==0;
}

// ��ӡ��ջ��
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

	// ������ջ��
	struct stack_blk * stack = array_stack_init(12);

	// ��10, 20, 30 ��������ջ��
	struct stack_load load;
	load.data =10;
	array_stack_push(stack,load);
	load.data =20;
	array_stack_push(stack,load);
	load.data =30;
	array_stack_push(stack,load);

	//array_stack_print();	// ��ӡջ

	// ����ջ��Ԫ�ء���ֵ��tmp����ɾ����ջ��Ԫ�ء�
	tmp = array_stack_pop(stack);
	printf("tmp=%d\n", tmp.data);
	//array_stack_print();	// ��ӡջ

	// ֻ����ջ������ֵ��tmp����ɾ����Ԫ��.
	tmp = array_stack_top(stack);
	printf("tmp=%d\n", tmp.data);
	//array_stack_print();	// ��ӡջ

	load.data =40;
	array_stack_push(stack,load);
	array_stack_print(stack);	// ��ӡջ

	// ����ջ
	array_stack_exit(stack);
}



