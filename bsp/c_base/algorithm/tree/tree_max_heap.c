#include<stdio.h>
#include<stdlib.h>

/*
���Ѻ���С���Ƕ���ѵ�������ʽ��

���ѣ������ļ�ֵ�����жѽ���ֵ������ߣ�
��ÿ������ֵ�����亢�ӵ�ֵ��

��С�ѣ������ļ�ֵ�����жѽ���ֵ����С�ߣ�
��ÿ������ֵ�����亢�ӵ�ֵС��
*/

#define MinData -100//�ڱ�Ԫ�ص�ֵ
typedef struct HeapStruct{
	int *p;
	int size;
	int capacity;
} *MinHeap;

MinHeap Init_MinHeap(int MaxSize);
int IsFull(MinHeap H);
int IsEmpty(MinHeap H);
void Insert(MinHeap H, int data);
int Delete(MinHeap H);
void BuildMinHeap(MinHeap H, int N);
void PrintValue(MinHeap H);

int IsFull(MinHeap H)
{
	return (H->size == H->capacity) ? 1 : 0;
}

int IsEmpty(MinHeap H)
{
	return (H->size == 0) ? 1 : 0;
}

void PrintValue(MinHeap H)
{
	int i;
//	printf("��С���е�Ԫ������Ϊ��");
        printf("show:");
	for (i = 1; i <= H->size; i++)
		printf("%d ", H->p[i]);
	printf("\n");
}

MinHeap Init_MinHeap(int MaxSize)
{
	MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));
	H->p = (int*)malloc((MaxSize + 1) * sizeof(int));
	H->p[0] = MinData;
	H->size = 0;
	H->capacity = MaxSize;
	return H;
}

void Insert(MinHeap H, int data)
{
	int i;
	if (IsFull(H))
	{
//		printf("��С���������޷�����Ԫ��");
              printf("full");
		return;
	}
	for (i = ++H->size; data < H->p[i / 2]; i /= 2)
		H->p[i] = H->p[i / 2];
	H->p[i] = data;
}

int Delete(MinHeap H)
{
	int minvalue , lastvalue, child, parent;
	if (IsEmpty(H))
	{
	//	printf("��С���������޷�ɾ��Ԫ��");
        printf("null");
        return -999;
	}

	minvalue = H->p[1];
	lastvalue = H->p[H->size--];
	for (parent = 1; 2 * parent <= H->size; parent = child)
	{
		child = 2 * parent;/*Ĭ�������Ԫ��ֵ��С*/
		if (child != H->size && H->p[child + 1] < H->p[child])/*���ҽڵ��Ԫ��ֵ��С�������child*/
			child++;
		if (lastvalue < H->p[child])
			break;
		else
			H->p[parent] = H->p[child];
	}
	H->p[parent] = lastvalue;
	return minvalue;
}

void BuildMinHeap(MinHeap H, int N)
{
	int i, num, parent, child, root, lastvalue;
	if (N > H->capacity)
	{
            //printf("Ҫ������Ԫ�ظ��������ѵ��������������ʧ��");
            printf("create err\n");
            return;
	}

       printf("pls input data:");
	for (i = 1; i <= N; i++)
	{
            //printf("������Ҫ�����Ԫ��ֵ:");
            scanf("%d", &num);
            H->p[i] = num;
	}
	H->size = N;

	root = N / 2;/*�ӵ�N/2����㵽��1��������ν������� ����N/2��ɾ������*/
	while (root)
	{
		lastvalue = H->p[root];
		for (parent = root; 2 * parent <= H->size; parent = child)
		{
			child = 2 * parent;/*Ĭ�������Ԫ��ֵ��С*/
			if (child != H->size && H->p[child + 1] < H->p[child])/*�ҽ��Ԫ��ֵ��С*/
				child++;
			if (lastvalue < H->p[child])
				break;
			else
				H->p[parent] = H->p[child];
		}
		H->p[parent] = lastvalue;
		--root;
	}
}


void main()
{
	int num;
	MinHeap H;
	H = Init_MinHeap(100);
	BuildMinHeap(H, 15);
	PrintValue(H);

//	printf("��������Ҫ��������ݣ�");
	printf("insert you data:");
	scanf("%d", &num);
	Insert(H, num);
	PrintValue(H);
//	printf("��������Ҫ��������ݣ�");
       printf("insert your data:");
	scanf("%d", &num);
	Insert(H, num);
	PrintValue(H);

	num = Delete(H);
//	printf("ɾ����Ԫ��Ϊ��%d\n", num);
       printf("del data:");
	PrintValue(H);
}
