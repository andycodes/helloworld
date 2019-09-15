#include<stdio.h>
#include<stdlib.h>

/*
最大堆和最小堆是二叉堆的两种形式。

最大堆：根结点的键值是所有堆结点键值中最大者，
且每个结点的值都比其孩子的值大。

最小堆：根结点的键值是所有堆结点键值中最小者，
且每个结点的值都比其孩子的值小。
*/

#define MinData -100//哨兵元素的值
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
//	printf("最小堆中的元素依次为：");
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
//		printf("最小堆已满，无法插入元素");
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
	//	printf("最小堆已满，无法删除元素");
        printf("null");
        return -999;
	}

	minvalue = H->p[1];
	lastvalue = H->p[H->size--];
	for (parent = 1; 2 * parent <= H->size; parent = child)
	{
		child = 2 * parent;/*默认左结点的元素值更小*/
		if (child != H->size && H->p[child + 1] < H->p[child])/*若右节点的元素值更小，则调整child*/
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
            //printf("要创建的元素个数超过堆的最大容量，创建失败");
            printf("create err\n");
            return;
	}

       printf("pls input data:");
	for (i = 1; i <= N; i++)
	{
            //printf("请输入要插入的元素值:");
            scanf("%d", &num);
            H->p[i] = num;
	}
	H->size = N;

	root = N / 2;/*从第N/2个结点到第1个结点依次进行下滤 近似N/2次删除操作*/
	while (root)
	{
		lastvalue = H->p[root];
		for (parent = root; 2 * parent <= H->size; parent = child)
		{
			child = 2 * parent;/*默认左结点的元素值更小*/
			if (child != H->size && H->p[child + 1] < H->p[child])/*右结点元素值更小*/
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

//	printf("请输入你要插入的数据：");
	printf("insert you data:");
	scanf("%d", &num);
	Insert(H, num);
	PrintValue(H);
//	printf("请输入你要插入的数据：");
       printf("insert your data:");
	scanf("%d", &num);
	Insert(H, num);
	PrintValue(H);

	num = Delete(H);
//	printf("删除的元素为：%d\n", num);
       printf("del data:");
	PrintValue(H);
}
