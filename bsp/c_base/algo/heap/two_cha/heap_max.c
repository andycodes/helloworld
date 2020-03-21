#include <stdio.h>
#include <stdlib.h>

struct Entry {
	int key;
	int value;
	int nums1;
	int nums2;
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


void maxheap_print(struct HeapStruct * heap)
{
	int i;
	for (i = 0; i< heap->capacity; i++)
		printf("%d ", heap->node[i].key);
	printf("\n");
}

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
