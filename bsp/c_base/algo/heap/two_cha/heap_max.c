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
	//��һ��λ�ò����κ�����,�������ʱ������Ϊ�м����
	int memSize = sizeof(struct HeapStruct) + (maxCapacity+1) * sizeof(struct Entry);
	struct HeapStruct * heap = (struct HeapStruct *)calloc(1, memSize);
	heap->capacity = maxCapacity;
	return heap;
}


/*
ԭ��:���ڶѵ��������һ�����,Ȼ�������������.
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
 * ���ѵ����ϵ����㷨(��start��ʼ����ֱ��0��������)
 *
 * ע������ʵ�ֵĶ��У���N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
 *
 * ����˵����
 *     start -- ���ϵ��ڵ����ʼλ��(һ��Ϊ���������һ��Ԫ�ص�����)
 */
static void maxheap_filterup(struct HeapStruct * heap, int start)
{
    int c = start;// ��ǰ�ڵ�(current)��λ��
    int p = (c-1)/2;		// ��(parent)����λ��
    struct Entry tmp = heap->node[c];		// ��ǰ�ڵ�(current)�Ĵ�С

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
 * ��data���뵽�������
 *
 * ����ֵ��
 *     0����ʾ�ɹ�
 *    -1����ʾʧ��
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
ԭ��:���ѵ����Ľ���ᵽ����㣬
Ȼ��ɾ�����ֵ��Ȼ���ٰ��µĸ�������½��е���,
ֱ���ҵ�����ϵĵ�λ��.
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
	while (pIndex << 1 <= heap->size) { //���ӽ��
		int maxChild = 0;
		if (pIndex << 1 > heap->size) { //û���Һ���
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
 * ����data�ڶ�����е�����
 *
 * ����ֵ��
 *     ���� -- ����data�������е�����
 *     ������ -- -1
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
 * ���ѵ����µ����㷨
 *
 * ע������ʵ�ֵĶ��У���N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
 *
 * ����˵����
 *     start -- ���µ��ڵ����ʼλ��(һ��Ϊ0����ʾ�ӵ�1����ʼ)
 *     end   -- ������Χ(һ��Ϊ���������һ��Ԫ�ص�����)
 */
static void maxheap_filterdown(struct HeapStruct * heap, int start, int end)
{
    int c = start; 	 	// ��ǰ(current)�ڵ��λ��
    int l = 2*c + 1; 	// ��(left)���ӵ�λ��
    struct Entry tmp = heap->node[c];	// ��ǰ(current)�ڵ�Ĵ�С

    while(l <= end)
    {
		// "l"�����ӣ�"l+1"���Һ���
        if(l < end && heap->node[l].key < heap->node[l+1].key)
            l++;		// ������������ѡ��ϴ��ߣ���heap->node[l+1]
        if(tmp.key >= heap->node[l].key)
            break;		//��������
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
 * ɾ�������е�data
 *
 * ����ֵ��
 *      0���ɹ�
 *     -1��ʧ��
 */
int maxheap_remove(struct HeapStruct * heap, int data)
{
	int index;
    // ���"��"�ѿգ��򷵻�-1
    if(heap->size == 0)
        return -1;

	// ��ȡdata�������е�����
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

