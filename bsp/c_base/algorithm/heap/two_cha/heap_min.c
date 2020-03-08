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


int minHeapGetIndex(minHeap *mh, HEAP_DTYPE data)
{
	long int i=0;

	for(i=0; i<mh->cnt; i++)
		if (data==mh->heap[i])
			return i;

	return -1;
}


bool minHeapisEmpty(minHeap *mh)
{
	return mh->cnt == 0;
}

bool minHeapisFull(minHeap *mh)
{
	printf("heap is full\n");
	return mh->cnt == mh->size;
}


long int minHeapGetSize(minHeap *mh)
{
	return mh->cnt;
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
static void minheap_filterdown(minHeap *mh, long int start, long int end)
{
	long int curNode = start;
	long int left = 2*curNode + 1;
	HEAP_DTYPE tmp = mh->heap[curNode];

	while(left <= end) {
		// "left"是左孩子，"left+1"是右孩子
		if(left < end && mh->heap[left] > mh->heap[left+1])
			left++;		// 左右两孩子中选择较小者，即mh->heap[left+1]

		if(tmp <= mh->heap[left])
			break;		//调整结束
		else {
			mh->heap[curNode] = mh->heap[left];
			curNode = left;
			left = 2*left + 1;
		}
	}

	mh->heap[curNode] = tmp;
}


/*
 * 删除最小堆中的data
 */
int minheap_remove(minHeap *mh, long int data)
{
	long int index;
	if(mh->cnt == 0)
		return  -1;

	index = minHeapGetIndex(mh, data);
	if (index== -1)
		return -1;

	mh->heap[index] = mh->heap[--mh->cnt];		// 用最后元素填补
	// 从index号位置开始自上向下调整为最小堆
	minheap_filterdown(mh, index, mh->cnt-1);

	return 0;
}


long int minHeapPop(minHeap *mh)
{
	HEAP_DTYPE min;

	if(minHeapisEmpty(mh))
		return 0;

	min = mh->heap[0];
	minheap_remove(mh, min);
	return min;
}


/*
 * 最小堆的向上调整算法(从start开始向上直到0，调整堆)
 *
 * 参数说明：
 *     start -- 被上调节点的起始位置
 (一般为数组中最后一个元素的索引)
 */
static void filter_up(minHeap *mh, long int start)
{
	long int curNode = start;
	long int root = (curNode - 1)/2;		// 父(parent)结点的位置
	HEAP_DTYPE tmp = mh->heap[curNode];

	while(curNode > 0) {
		if(mh->heap[root] <= tmp)
			break;
		else {
			mh->heap[curNode] = mh->heap[root];
			curNode = root;
			root = (root-1)/2;
		}
	}

	mh->heap[curNode] = tmp;
}

/*
插入操作一般使用的策略叫做上滤（percolate up）：
新元素在堆中上滤直到找出正确的位置
（设堆为H,待插入的元素为X,首先在size+1的位置建立一个空穴，
然后比较X和空穴的父亲的大小，
把“大的父亲”换下来，以此推进，
最后把X放到合适的位置）。
*/
int minHeapPush(minHeap *mh, long int data)
{
	if(minHeapisFull(mh)) {
		return -1;
	}

	mh->heap[mh->cnt] = data;// 将"数组"插在表尾
	filter_up(mh, mh->cnt);
	mh->cnt++;

	return 0;
}


/*
 * 打印二叉堆
 *
 * 返回值：
 *     0，表示成功
 *    -1，表示失败
 */
void minheap_print(minHeap *mh)
{
	long int i;
	for (i=0; i<mh->cnt; i++)
		printf("%ld ", mh->heap[i]);
}


minHeap * minheap_init(long int size)
{
	minHeap * mh = (minHeap *)malloc(sizeof(minHeap) + sizeof(HEAP_DTYPE) * size);
	mh->cnt = 0;
	mh->size = size;
	return mh;
}


void minheap_exit(minHeap * mh)
{
	free(mh);
	mh = NULL;
}

int main(void)
{
	minHeap *mh = minheap_init(1024);

	HEAP_DTYPE a[] = {80, 40, 30, 60, 90, 70, 10, 50, 20};
	long int i, len=LENGTH(a);

	printf("== minHeapPush: ");
	for(i=0; i<len; i++) {
		printf("%ld ", a[i]);
		minHeapPush(mh, a[i]);
	}

	printf("\n== minheap_print: \n10 20 30 50 90 70 40 80 60 :\n");
	minheap_print(mh);

	i=15;
	minHeapPush(mh, i);
	printf("\n== minHeapPush: %ld", i);
	printf("\n== minheap_print: \n10 15 30 50 20 70 40 80 60 90:\n");
	minheap_print(mh);

	i=10;
	minheap_remove(H, i);
	printf("\n== minheap_remove: %ld", i);
	printf("\n== minheap_print: \n15 20 30 50 90 70 40 80 60 :\n");
	minheap_print(mh);
	printf("\n");

	printf("\n minHeapPop test:\n");
	while(!minHeapisEmpty(mh)) {
		printf(" %ld ", minHeapPop(mh));
	}

	printf("\n");

	return 0;
}

