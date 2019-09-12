#include <stdio.h>
#include <malloc.h>

/**
 * C ����: ����ʵ�ֵ�ջ��ֻ�ܴ洢int���ݡ�
 *
 * @author skywang
 * @date 2013/11/07
 */

// �������ݵ�����
static int *arr=NULL;
// ջ��ʵ�ʴ�С
static int count;

// ������ջ����Ĭ�ϴ�С��12
int create_array_stack(int sz) 
{
	arr = (int *)malloc(sz*sizeof(int));
	if (!arr) 
	{
		printf("arr malloc error!");
		return -1;
	}

	return 0;
}

// ���١�ջ��
int destroy_array_stack() 
{
	if (arr) 
	{
		free(arr);
		arr = NULL;
	}

	return 0;
}

// ��val��ӵ�ջ��
void push(int val) 
{
	arr[count++] = val;
}

// ���ء�ջ��Ԫ��ֵ��
int peek() 
{
	return arr[count-1];
}

// ���ء�ջ��Ԫ��ֵ������ɾ����ջ��Ԫ�ء�
int pop() 
{
	int ret = arr[count-1];
	count--;
	return ret;
}

// ���ء�ջ���Ĵ�С
int size() 
{
	return count;
}

// ���ء�ջ���Ƿ�Ϊ��
int is_empty()
{
	return size()==0;
}

// ��ӡ��ջ��
void print_array_stack()
{
	if (is_empty()) 
	{
		printf("stack is Empty\n");
		return ;
	}

	printf("stack size()=%d\n", size());

	int i=size()-1;
	while (i>=0)
	{
		printf("%d\n", arr[i]);
		i--;
	}
}


void main() 
{
	int tmp=0;

	// ������ջ��
	create_array_stack(12);

	// ��10, 20, 30 ��������ջ��
	push(10);
	push(20);
	push(30);

	//print_array_stack();	// ��ӡջ

	// ����ջ��Ԫ�ء���ֵ��tmp����ɾ����ջ��Ԫ�ء�
	tmp = pop();
	printf("tmp=%d\n", tmp);
	//print_array_stack();	// ��ӡջ

	// ֻ����ջ������ֵ��tmp����ɾ����Ԫ��.
	tmp = peek();
	printf("tmp=%d\n", tmp);
	//print_array_stack();	// ��ӡջ

	push(40);
	print_array_stack();	// ��ӡջ

	// ����ջ
	destroy_array_stack();
}

