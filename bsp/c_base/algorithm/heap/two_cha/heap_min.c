/**
 * 二叉堆(最小堆)
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

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )


#define HeapSize 128
typedef struct minHeap{
	int heap[HeapSize];
	int cnt;
}minHeap;


/*
 * 返回data在二叉堆中的索引
 *
 * 返回值：
 *     存在 -- 返回data在数组中的索引
 *     不存在 -- -1
 */
int get_index(minHeap *H, int data)
{
	int i=0;

	for(i=0; i<H->cnt; i++)
		if (data==H->heap[i])
			return i;

	return -1;
}

/*
 * 最小堆的向下调整算法
 *
 * 注：数组实现的堆中，
 第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *
 * 参数说明：
 *     start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
 *     end   -- 截至范围(一般为数组中最后一个元素的索引)
 */
static void minheap_filterdown(minHeap *H, int start, int end)
{
    int c = start; 	 	// 当前(current)节点的位置
    int l = 2*c + 1; 	// 左(left)孩子的位置
    int tmp = H->heap[c];	// 当前(current)节点的大小

    while(l <= end)
    {
		// "l"是左孩子，"l+1"是右孩子
        if(l < end && H->heap[l] > H->heap[l+1])
            l++;		// 左右两孩子中选择较小者，即H->heap[l+1]
        if(tmp <= H->heap[l])
            break;		//调整结束
        else
        {
            H->heap[c] = H->heap[l];
            c = l;
            l = 2*l + 1;
        }
    }
    H->heap[c] = tmp;
}


/*
 * 删除最小堆中的data
 *
 * 返回值：
 *      0，成功
 *     -1，失败
 */
int minheap_remove(minHeap *H, int data)
{
	int index;
	// 如果"堆"已空，则返回-1
	if(H->cnt == 0)
		return -1;

	// 获取data在数组中的索引
	index = get_index(H, data);
	if (index==-1)
		return -1;

	H->heap[index] = H->heap[--H->cnt];		// 用最后元素填补
	// 从index号位置开始自上向下调整为最小堆
	minheap_filterdown(H, index, H->cnt-1);

	return 0;
}

int isEmpty(minHeap *H)
{
	return H->cnt == 0;
}


int minHeapGetSize(minHeap *H)
{
	return H->cnt;
}

//小根堆的删除
int minHeapPop(minHeap *H) {
	int min;

	if(isEmpty(H))
		return 0;

	min = H->heap[0];
	minheap_remove(H, min);
	return min;
}


/*
 * 最小堆的向上调整算法(从start开始向上直到0，调整堆)
 *
 * 注：数组实现的堆中，
 第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *
 * 参数说明：
 *     start -- 被上调节点的起始位置
 (一般为数组中最后一个元素的索引)
 */
static void filter_up(minHeap *H, int start)
{
    int c = start;			// 当前节点(current)的位置
    int p = (c-1)/2;		// 父(parent)结点的位置
    int tmp = H->heap[c];		// 当前节点(current)的大小

    while(c > 0)
    {
        if(H->heap[p] <= tmp)
            break;
        else
        {
            H->heap[c] = H->heap[p];
            c = p;
            p = (p-1)/2;
        }
    }
    H->heap[c] = tmp;
}

/*
 * 将data插入到二叉堆中
 *
 * 返回值：
 *     0，表示成功
 *    -1，表示失败
 */
int minHeapPush(minHeap *H, int data)
{
	// 如果"堆"已满，则返回
	if(H->cnt >= HeapSize) {
		printf("heap is full\n");
		return -1;
	}

	H->heap[H->cnt] = data;		// 将"数组"插在表尾
	filter_up(H, H->cnt);			// 向上调整堆
	H->cnt++;					// 堆的实际容量+1

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
	int i;
	for (i=0; i<H->cnt; i++)
		printf("%d ", H->heap[i]);
}


void minheap_init(minHeap *H) {
	H->cnt = 0;
}


int main(void)
{
	minHeap H;
	minheap_init(&H);

	int a[] = {80, 40, 30, 60, 90, 70, 10, 50, 20};
	int i, len=LENGTH(a);

	printf("== minHeapPush: ");
	for(i=0; i<len; i++) {
		printf("%d ", a[i]);
		minHeapPush(&H, a[i]);
	}

	printf("\n== minheap_print: \n10 20 30 50 90 70 40 80 60 :\n");
	minheap_print(&H);

	i=15;
	minHeapPush(&H, i);
	printf("\n== minHeapPush: %d", i);
	printf("\n== minheap_print: \n10 15 30 50 20 70 40 80 60 90:\n");
	minheap_print(&H);

	i=10;
	minheap_remove(&H, i);
	printf("\n== minheap_remove: %d", i);
	printf("\n== minheap_print: \n15 20 30 50 90 70 40 80 60 :\n");
	minheap_print(&H);
	printf("\n");

	printf("\n minHeapPop test:\n");
	while(!isEmpty(&H)) {
		printf(" %d ", minHeapPop(&H));
	}

	printf("\n");

	return 0;
}
