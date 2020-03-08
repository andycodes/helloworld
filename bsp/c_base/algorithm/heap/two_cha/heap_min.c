/**
优先队列---二叉堆(最小堆)
最小堆：根结点的键值是所有堆结点键值中最小者，
且每个结点的值都比其孩子的值小。
它是一颗完全二叉树,它可以是空
树中结点的值总是不大于其孩子结点的值
每一个结点的子树也是一个堆

最小堆的优点在于它的动态可维护性。

当前实现是存在重复数

 */

#include <stdio.h>
#include <stdlib.h>

typedef long int HEAP_DTYPE;

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )


typedef struct minHeap{
	long int cnt;
	long int size;
	HEAP_DTYPE heap[0];
}minHeap;


int minHeapGetIndex(minHeap *H, HEAP_DTYPE data)
{
	long int i=0;

	for(i=0; i<H->cnt; i++)
		if (data==H->heap[i])
			return i;

	return -1;
}


int minHeapisEmpty(minHeap *H)
{
	return H->cnt == 0;
}


long int minHeapGetSize(minHeap *H)
{
	return H->cnt;
}


/*
 * 最小堆的向下调整算法
 *
 * 注：数组实现的堆中，
 第N个节点的
 左孩子的索引值是(2N+1)，
 右孩子的索引是(2N+2)。
 *
 * 参数说明：
 *     start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
 *     end   -- 截至范围(一般为数组中最后一个元素的索引)
 */
static void minheap_filterdown(minHeap *H, long int start, long int end)
{
	long int curNode = start;
	long int left = 2*curNode + 1;
	HEAP_DTYPE tmp = H->heap[curNode];

	while(left <= end) {
		// "left"是左孩子，"left+1"是右孩子
		if(left < end && H->heap[left] > H->heap[left+1])
			left++;		// 左右两孩子中选择较小者，即H->heap[left+1]

		if(tmp <= H->heap[left])
			break;		//调整结束
		else {
			H->heap[curNode] = H->heap[left];
			curNode = left;
			left = 2*left + 1;
		}
	}

	H->heap[curNode] = tmp;
}


/*
 * 删除最小堆中的data
 */
int minheap_remove(minHeap *H, long int data)
{
	long int index;
	if(H->cnt == 0)
		return  -1;

	index = minHeapGetIndex(H, data);
	if (index== -1)
		return -1;

	H->heap[index] = H->heap[--H->cnt];		// 用最后元素填补
	// 从index号位置开始自上向下调整为最小堆
	minheap_filterdown(H, index, H->cnt-1);

	return 0;
}


long int minHeapPop(minHeap *H)
{
	HEAP_DTYPE min;

	if(minHeapisEmpty(H))
		return 0;

	min = H->heap[0];
	minheap_remove(H, min);
	return min;
}


/*
 * 最小堆的向上调整算法(从start开始向上直到0，调整堆)
 *
 * 参数说明：
 *     start -- 被上调节点的起始位置
 (一般为数组中最后一个元素的索引)
 */
static void filter_up(minHeap *H, long int start)
{
	long int curNode = start;
	long int root = (curNode - 1)/2;		// 父(parent)结点的位置
	HEAP_DTYPE tmp = H->heap[curNode];

	while(curNode > 0) {
		if(H->heap[root] <= tmp)
			break;
		else {
			H->heap[curNode] = H->heap[root];
			curNode = root;
			root = (root-1)/2;
		}
	}

	H->heap[curNode] = tmp;
}


int minHeapPush(minHeap *H, long int data)
{
	if(H->cnt >= H->size) {
		printf("heap is full\n");
		return -1;
	}

	H->heap[H->cnt] = data;// 将"数组"插在表尾
	filter_up(H, H->cnt);
	H->cnt++;

	return 0;
}


/*
 * 打印二叉堆
 *
 * 返回值：
 *     0，表示成功
 *    -1，表示失败
 */
void minheap_print(minHeap *H)
{
	long int i;
	for (i=0; i<H->cnt; i++)
		printf("%ld ", H->heap[i]);
}


minHeap * minheap_init(long int size) {
	minHeap * H = (minHeap *)malloc(sizeof(minHeap) + sizeof(long int) * size);
	H->cnt = 0;
	H->size = size;
	return H;
}


int main(void)
{
	minHeap *H = minheap_init(1024);

	HEAP_DTYPE a[] = {80, 40, 30, 60, 90, 70, 10, 50, 20};
	long int i, len=LENGTH(a);

	printf("== minHeapPush: ");
	for(i=0; i<len; i++) {
		printf("%ld ", a[i]);
		minHeapPush(H, a[i]);
	}

	printf("\n== minheap_print: \n10 20 30 50 90 70 40 80 60 :\n");
	minheap_print(H);

	i=15;
	minHeapPush(H, i);
	printf("\n== minHeapPush: %ld", i);
	printf("\n== minheap_print: \n10 15 30 50 20 70 40 80 60 90:\n");
	minheap_print(H);

	i=10;
	minheap_remove(H, i);
	printf("\n== minheap_remove: %ld", i);
	printf("\n== minheap_print: \n15 20 30 50 90 70 40 80 60 :\n");
	minheap_print(H);
	printf("\n");

	printf("\n minHeapPop test:\n");
	while(!minHeapisEmpty(H)) {
		printf(" %ld ", minHeapPop(H));
	}

	printf("\n");

	return 0;
}

