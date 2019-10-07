#include "stdio.h"
#include "stdlib.h"
#define HeapSize 128
typedef struct minHeap{
	int heap[HeapSize];    //存放小根堆中元素的数组
    int n;                  //小根堆当前元素的个数，初始值为0
}minHeap;

/*自顶向下调整算法*/
//自上向下调整，在调整的过程中要将根节点的所有子树调节为最小堆
void shifDown(minHeap *H, int m) {
	//m是开始调整的结点,n是调整结束的点
	int tmp = H->heap[m];  //j是i的左子女
	for (int j = 2 * m + 1; j <= H->n-1; j=2*j+1) {
		if (j<H->n-1&&H->heap[j]>H->heap[j + 1])
			j++;
		if (tmp <= H->heap[j])
			break;
		else {
			tmp = H->heap[m];
			H->heap[m] = H->heap[j];
			H->heap[j] = tmp;
			m = j;
		}
	}
}


//逐步构建小根堆
//构建的是从下到上，调整的时候是从上至下
void createMinHeap(minHeap *H, int arr[], int n) {
	for ( int i = 0; i < n; i++)
		H->heap[i] = arr[i];
	H->n = n;
	for (int i = (H->n - 2) / 2; i >=0;i--) {   //自底向上逐步扩大小根堆
		shifDown(H,i);                       //局部自上向下筛选
	}
}

/*---------------------------------------------------------------------------*/

/*自底向上调整小根堆*/
void shifUp(minHeap *H,int start) {
	int j= start;
	int i = (j - 1) / 2;
	int tmp = H->heap[start];
	while (j>0)
	{
		if (H->heap[i] <= tmp) break;
		else
		{
			H->heap[j] = H->heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	H->heap[j] = tmp;
}
//小根堆的插入,采用局部自下而上得调整算法
void Insert(minHeap *H,int x) {
	if (H->n==HeapSize)
	{
		printf("堆满");
	}
	H->heap[H->n] = x;
	shifUp(H, H->n);
	H->n++;
}



//小根堆的删除
int Remove(minHeap *H) {
	int min;
	if (!H->n)
		return 0;               //堆空返回0
	min = H->heap[0];
	H->heap[0] = H->heap[H->n - 1];
	H->n--;
	for (int i = (H->n - 2) / 2; i >= 0; i--) {   //自底向上逐步扩大小根堆
		shifDown(H, i);                          //局部自上向下筛选
	}
	return min;
}


int main() {
    int arr[8] = { 53,17,78,9,45,65,87,23};
    minHeap H;
    createMinHeap(&H,arr,8);

    printf("小根堆的建立\n");

    for (int i = 0; i < 8; i++)
    {
    	printf(" %d ",H.heap[i]);
    }
    printf("\n小根堆的插入元素10\n");
    Insert(&H,10);
    for (int i = 0; i < 9; i++)
    {
    	printf(" %d ", H.heap[i]);
    }
    int x;
    x=Remove(&H);
    printf("\n小根堆的删除\n");
    printf("删除的元素为\n%d\n",x);
    printf("删除堆顶元素，进行调整后的元素为\n");
    for (int i = 0; i < 8; i++)
    {
    	printf(" %d ", H.heap[i]);
    }
    system("pause");
    return 0;
 }
