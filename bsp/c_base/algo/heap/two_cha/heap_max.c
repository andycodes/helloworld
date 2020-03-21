#include <stdio.h>
#include <stdlib.h>

struct Entry {
	int key;
};

struct HeapStruct {
     int size;
     int capacity;
     struct Entry node[0];
};


int maxIndex(int left, int right, struct HeapStruct * heap)
{
    return heap->node[left].key > heap->node[right].key ? left : right;
}


struct HeapStruct * maxheap_init(int maxCapacity)
{
	//第一个位置不存任何数据,交换结点时可以作为中间变量
	int memSize = sizeof(struct HeapStruct) + (maxCapacity+1) * sizeof(struct Entry);
	struct HeapStruct * heap = (struct HeapStruct *)calloc(1, memSize);
	heap->capacity = maxCapacity;
	return heap;
}


/*
原理:现在堆的最后增加一个结点,然后沿这堆树上升.
*/
void maxheap_push(struct HeapStruct * heap, struct Entry newNode)
{
     if (heap->capacity == heap->size) {
        return;
    }

    heap->size++;
    heap->node[heap->size] = newNode;
    for (int sIndex = heap->size; sIndex > 1;) {
         int fatherIdx = sIndex / 2;
        if (heap->node[fatherIdx].key < heap->node[sIndex].key) {
            heap->node[0] = heap->node[fatherIdx];
            heap->node[fatherIdx] = heap->node[sIndex];
            heap->node[sIndex] = heap->node[0];
            heap->node[0].key = 0;
            sIndex = fatherIdx;
        } else {
            break;
        }
    }
}


/*
 * 最大堆的向上调整算法(从start开始向上直到0，调整堆)
 *
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *
 * 参数说明：
 *     start -- 被上调节点的起始位置(一般为数组中最后一个元素的索引)
 */
static void maxheap_filterup(struct HeapStruct * heap, int start)
{
    int c = start;// 当前节点(current)的位置
    int p = (c-1)/2;		// 父(parent)结点的位置
    struct Entry tmp = heap->node[c];		// 当前节点(current)的大小

    while(c > 0)
    {
        if(heap->node[p].key>= tmp.key)
            break;
        else {
            heap->node[c] = heap->node[p];
            c = p;
            p = (p-1)/2;
        }
    }
    heap->node[c] = tmp;
}

/*
 * 将data插入到二叉堆中
 *
 * 返回值：
 *     0，表示成功
 *    -1，表示失败
 */
int maxheap_insert(struct HeapStruct * heap, struct Entry newNode)
{
	if (heap->capacity == heap->size) {
		return -1;
	}

	heap->node[heap->size] = newNode;
	maxheap_filterup(heap, heap->size);
	heap->size++;
	return 0;
}



/*
原理:将堆的最后的结点提到根结点，
然后删除最大值，然后再把新的根结点向下进行调整,
直到找到其符合的的位置.
*/
void maxheap_pop(struct HeapStruct * heap, struct Entry *popNode)
{
	if (heap->size == 0) {
		return;
	}

	*popNode = heap->node[1];
	heap->node[1] = heap->node[heap->size];
	heap->size--;
	int pIndex = 1;
	while (pIndex << 1 <= heap->size) { //有子结点
		int maxChild = 0;
		if (pIndex << 1 > heap->size) { //没有右孩子
			maxChild = pIndex << 1;
		} else {
			maxChild = maxIndex(pIndex << 1, (pIndex << 1) + 1, heap);
		}
		if (heap->node[pIndex].key < heap->node[maxChild].key) {
			heap->node[0] = heap->node[pIndex];
			heap->node[pIndex] = heap->node[maxChild];
			heap->node[maxChild] = heap->node[0];
			heap->node[0].key = 0;
			pIndex = maxChild;
		} else {
			break;
		}
	}
}


/*
 * 返回data在二叉堆中的索引
 *
 * 返回值：
 *     存在 -- 返回data在数组中的索引
 *     不存在 -- -1
 */
int get_index(struct HeapStruct * heap, int data)
{
	int i=0;

	for(i=0; i<heap->size; i++)
		if (data ==heap->node[i].key)
			return i;

	return -1;
}

/*
 * 最大堆的向下调整算法
 *
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *
 * 参数说明：
 *     start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
 *     end   -- 截至范围(一般为数组中最后一个元素的索引)
 */
static void maxheap_filterdown(struct HeapStruct * heap, int start, int end)
{
    int c = start; 	 	// 当前(current)节点的位置
    int l = 2*c + 1; 	// 左(left)孩子的位置
    struct Entry tmp = heap->node[c];	// 当前(current)节点的大小

    while(l <= end)
    {
		// "l"是左孩子，"l+1"是右孩子
        if(l < end && heap->node[l].key < heap->node[l+1].key)
            l++;		// 左右两孩子中选择较大者，即heap->node[l+1]
        if(tmp.key >= heap->node[l].key)
            break;		//调整结束
        else
        {
            heap->node[c] = heap->node[l];
            c = l;
            l = 2*l + 1;
        }
    }
    heap->node[c] = tmp;
}

/*
 * 删除最大堆中的data
 *
 * 返回值：
 *      0，成功
 *     -1，失败
 */
int maxheap_remove(struct HeapStruct * heap, int data)
{
	int index;
    // 如果"堆"已空，则返回-1
    if(heap->size == 0)
        return -1;

	// 获取data在数组中的索引
	index = get_index(heap, data);
	if (index==-1)
		return -1;

    heap->node[index] = heap->node[--heap->size];
    maxheap_filterdown(heap, index, heap->size-1);
    return 0;
}


void maxheap_print(struct HeapStruct * heap)
{
	int i;
	for (i = 0; i< heap->capacity; i++)
		printf("%d ", heap->node[i].key);
	printf("\n");
}

#if 0
int main() {
	int arr[] = { 5, 1, 13, 3, 16, 7, 10, 14, 6, 9 };

	struct HeapStruct * heap = maxheap_init(20);
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		struct Entry newNode;
		newNode.key = arr[i];
		maxheap_push(heap, newNode);
	}


	while(heap->size) {
		struct Entry getNode;
		maxheap_pop(heap, &getNode);
		printf("%d ", getNode.key);
	}

	printf("\n");
	return 0;
}

#endif

int main() {
	int arr[] = { 5, 1, 13, 3, 16, 7, 10, 14, 6, 9 };

	struct HeapStruct * heap = maxheap_init(20);
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		struct Entry newNode;
		newNode.key = arr[i];
		maxheap_insert(heap, newNode);
	}


	while(heap->size) {
		printf("%d ", heap->node[0].key);
		maxheap_remove(heap, heap->node[0].key);
	}

	printf("\n");
	return 0;
}

