#include <stdio.h>
#include <malloc.h>

/**
 * C ����: ����ʵ�ֵĶ��У�ֻ�ܴ洢int���ݡ�
 *
 * @author skywang
 * @date 2013/11/07
 */

// �������ݵ�����
static int *arr=NULL;
// ���е�ʵ�ʴ�С
static int count;

// ���������С�
int create_array_queue(int sz) 
{
	arr = (int *)malloc(sz*sizeof(int));
	if (!arr) 
	{
		printf("arr malloc error!");
		return -1;
	}
	count = 0;

	return 0;
}

// ���١����С�
int destroy_array_queue() 
{
	if (arr) 
	{
		free(arr);
		arr = NULL;
	}

	return 0;
}

// ��val��ӵ����е�ĩβ
void add(int val) 
{
	arr[count++] = val;
}

// ���ء����п�ͷԪ�ء�
int front() 
{
	return arr[0];
}

// ���ز�ɾ�������п�ͷԪ�ء�
int pop() 
{
	int i = 0;;
	int ret = arr[0];

	count--;
	while (i++<count)
		arr[i-1] = arr[i];

	return ret;
}

// ���ء����С��Ĵ�С
int size() 
{
	return count;
}

// ���ء����С��Ƿ�Ϊ��
int is_empty()
{
	return count==0;
}

void main() 
{
	int tmp=0;

	// ���������С�
	create_array_queue(12);

	// ��10, 20, 30 �������������
	add(10);
	add(20);
	add(30);

	// �������п�ͷ��Ԫ�ء���ֵ��tmp����ɾ������Ԫ�ء�
	tmp = pop();
	printf("tmp=%d\n", tmp);

	// ֻ�������п�ͷ��Ԫ�ء���ֵ��tmp����ɾ����Ԫ��.
	tmp = front();
	printf("tmp=%d\n", tmp);

	add(40);

	// ��ӡ����
	printf("is_empty()=%d\n", is_empty());
	printf("size()=%d\n", size());
	while (!is_empty())
	{
		printf("%d\n", pop());
	}

	// ���ٶ���
	destroy_array_queue();
}
