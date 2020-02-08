#include <stdio.h>
#include <malloc.h>

struct astack_load{
	union dtype { /*Overload*/
		int data;
		char *str;
	}utype;
};

struct astack{
	int count;
	int size;
	struct astack_load load[0];
};


struct astack *astack_init(int sz)
{
	struct astack * stack =
		(struct astack  *)malloc(sizeof(struct astack) + sz*sizeof(struct astack_load));
	if (stack == NULL) {
		printf("arr malloc error!");
		return NULL;
	}

	stack->size = sz;
	stack->count = 0;

	return stack;
}


void astack_exit(struct astack * stack)
{
	if (stack != NULL) {
		free(stack);
		stack = NULL;
	}
}


/*     1|2|3|4....       */
void astack_push(struct astack * stack,struct astack_load load)
{
	stack->load[stack->count++] = load;
	if (stack->count > stack->size) {
		printf("[%s] astack_push count[%d] too big\n", __func__, stack->count);
		stack->count = stack->count % stack->size;
	}
}

// 返回“栈”的大小
int astack_size(struct astack * stack)
{
	return stack->count;
}

// 返回“栈”是否为空
int astack_empty(struct astack * stack)
{
	return astack_size(stack)==0;
}

// 返回“栈顶元素值”
struct astack_load  astack_top(struct astack * stack)
{
	if (astack_empty(stack)) {
		printf("err astack_empty\n");
		return stack->load[0];
	}

	return stack->load[stack->count -1];
}


void astack_top_modify(struct astack * stack,  struct astack_load load)
{
	if (astack_empty(stack)) {
		printf("err astack_empty\n");
		return;
	}

	stack->load[stack->count -1] = load;
}


// 返回“栈顶元素值”，并删除“栈顶元素”
struct astack_load  astack_pop(struct astack * stack)
{
	if (astack_empty(stack)) {
		printf("err astack_empty\n");
		return stack->load[0];
	}

	struct astack_load  ret = stack->load[stack->count -1];
	stack->count--;
	return ret;
}


// 打印“栈”
void astack_print(struct astack * stack)
{
	if (astack_empty(stack)) {
		printf("stack is Empty\n");
		return ;
	}

	printf("stack size()=%d\n", astack_size(stack));

	int i=astack_size(stack)-1;
	while (i>=0)
	{
		printf("%d\n", stack->load[i].data);
		i--;
	}
}


void main()
{
	struct astack_load tmp;

	// 创建“栈”
	struct astack * stack = astack_init(12);

	// 将10, 20, 30 依次推入栈中
	struct astack_load load;
	load.data =10;
	astack_push(stack,load);
	load.data =20;
	astack_push(stack,load);
	load.data =30;
	astack_push(stack,load);

	//astack_print();	// 打印栈

	// 将“栈顶元素”赋值给tmp，并删除“栈顶元素”
	tmp = astack_pop(stack);
	printf("tmp 30=%d\n", tmp.data);
	//astack_print();	// 打印栈

	// 只将“栈顶”赋值给tmp，不删除该元素.
	tmp = astack_top(stack);
	printf("tmp 20 =%d\n", tmp.data);
	//astack_print();	// 打印栈

	load.data =40;
	astack_push(stack,load);
	astack_print(stack);	// 打印栈

	// 销毁栈
	astack_exit(stack);
}



