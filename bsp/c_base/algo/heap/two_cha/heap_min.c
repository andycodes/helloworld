#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Entry {
	int key;
};

typedef struct minHeap{
	int cnt;
	int size;
	struct Entry heap[0];
}minHeap;


int minHeapGetIndex(minHeap *mh, int key)
{
	int i=0;

	for(i = 0; i < mh->cnt; i++)
		if (key == mh->heap[i].key)
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


int minHeapGetSize(minHeap *mh)
{
	return mh->cnt;
}


static void minheap_filterdown(minHeap *mh, int start, int end)
{
	int curNode = start;
	int leftChild = 2*curNode + 1;
	struct Entry tmp = mh->heap[curNode];

	while(leftChild <= end) {
		if(leftChild < end && mh->heap[leftChild].key > mh->heap[leftChild+1].key)
			leftChild++;

		if(tmp.key <= mh->heap[leftChild].key)
			break;
		else {
			mh->heap[curNode] = mh->heap[leftChild];
			curNode = leftChild;
			leftChild = 2*leftChild + 1;
		}
	}

	mh->heap[curNode] = tmp;
}


int minheap_remove(minHeap *mh, int data)
{
	int index;
	if(mh->cnt == 0)
		return  -1;

	index = minHeapGetIndex(mh, data);
	if (index== -1)
		return -1;

	mh->heap[index] = mh->heap[--mh->cnt];
	minheap_filterdown(mh, index, mh->cnt-1);

	return 0;
}


struct Entry  minheap_pop(minHeap *mh)
{
	struct Entry min;

	min = mh->heap[0];
	minheap_remove(mh, min.key);
	return min;
}


static void filter_up(minHeap *mh, int start)
{
	int curNode = start;
	int parent = (curNode - 1)/2;
	struct Entry tmp = mh->heap[curNode];

	while(curNode > 0) {
		if(mh->heap[parent].key <= tmp.key)
			break;
		else {
			mh->heap[curNode] = mh->heap[parent];
			curNode = parent;
			parent = (parent-1)/2;
		}
	}

	mh->heap[curNode] = tmp;
}

int minheap_push(minHeap *mh, struct Entry node)
{
	if(minHeapisFull(mh)) {
		return -1;
	}

	mh->heap[mh->cnt] = node;
	filter_up(mh, mh->cnt);
	mh->cnt++;

	return 0;
}


void minheap_print(minHeap *mh)
{
	int i;
	for (i=0; i<mh->cnt; i++)
		printf("%d ", mh->heap[i].key);
}


minHeap * minheap_init(int size)
{
	minHeap * mh = (minHeap *)malloc(sizeof(minHeap) + sizeof(struct Entry) * size);
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

	int a[] = {80, 40, 30, 60, 90, 70, 10, 50, 20};

	int i;
	for(i=0; i< sizeof(a) / sizeof(a[0]); i++) {
		printf("%d ", a[i]);
		struct Entry node;
		node.key = a[i];
		minheap_push(mh, node);
	}

	printf("\n== minheap_print: \n10 20 30 50 90 70 40 80 60 :\n");
	minheap_print(mh);

	i=10;
	minheap_remove(mh, i);
	printf("\n== minheap_remove: %d", i);
	printf("\n== minheap_print: \n15 20 30 50 90 70 40 80 60 :\n");
	minheap_print(mh);
	printf("\n");

	printf("\n minheap_pop test:\n");
	while(!minHeapisEmpty(mh)) {
		struct Entry get = minheap_pop(mh);
		printf(" %d ", get.key);
	}

	printf("\n");

	return 0;
}

