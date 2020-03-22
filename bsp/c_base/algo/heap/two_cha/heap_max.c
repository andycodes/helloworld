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


struct HeapStruct * maxheap_init(int maxCapacity)
{
	int memSize = sizeof(struct HeapStruct) + (maxCapacity) * sizeof(struct Entry);
	struct HeapStruct * heap = (struct HeapStruct *)calloc(1, memSize);
	heap->capacity = maxCapacity;
	return heap;
}


static void maxheap_filterup(struct HeapStruct * heap, int start)
{
    int child = start;
    int parent = (child-1) / 2;
    struct Entry tmp = heap->node[child];

    while(child > 0) {
        if(heap->node[parent].key >= tmp.key) {
            break;
        } else {
            heap->node[child] = heap->node[parent];
            child = parent;
            parent = (child - 1) / 2;
        }
    }
    heap->node[child] = tmp;
}


int maxheap_push(struct HeapStruct * heap, struct Entry newNode)
{
	if (heap->capacity == heap->size) {
		return -1;
	}

	heap->node[heap->size] = newNode;
	maxheap_filterup(heap, heap->size);
	heap->size++;
	return 0;
}

int get_index(struct HeapStruct * heap, int key)
{
	int i=0;

	for(i = 0; i < heap->size; i++)
		if (key == heap->node[i].key)
			return i;

	return -1;
}


static void maxheap_filterdown(struct HeapStruct * heap, int start, int end)
{
	int parent = start;
	int leftChild = 2*parent + 1;
	struct Entry tmp = heap->node[parent];

	while(leftChild <= end) {
		if(leftChild < end && heap->node[leftChild].key < heap->node[leftChild+1].key)
			leftChild++; // 左右两孩子中选择较大者，即heap->node[l+1]

		if(tmp.key >= heap->node[leftChild].key) {
			break;
		} else {
			heap->node[parent] = heap->node[leftChild];
			parent = leftChild;
			leftChild = 2*parent + 1;
		}
	}

	heap->node[parent] = tmp;
}


int maxheap_remove(struct HeapStruct * heap, int key)
{
	int index;
    if(heap->size == 0)
        return -1;

	index = get_index(heap, key);
	if (index==-1)
		return -1;

    heap->node[index] = heap->node[--heap->size];
    maxheap_filterdown(heap, index, heap->size-1);
    return 0;
}

void maxheap_pop(struct HeapStruct * heap,  struct Entry *popNode)
{
	*popNode = heap->node[0];
	 heap->node[0] = heap->node[--heap->size];
	 maxheap_filterdown(heap, 0, heap->size-1);
}

struct Entry maxheap_top(struct HeapStruct * heap)
{
	return heap->node[0];
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
		printf("%d(%d) ", getNode.key, heap->size);
	}

	printf("\n");
	return 0;
}


