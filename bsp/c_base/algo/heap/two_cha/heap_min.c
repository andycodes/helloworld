#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Entry {
	int key;
};

struct PriorityQueue{
	int cnt;
	int size;
	struct Entry heap[0];
};


int minHeapGetIndex(struct PriorityQueue *pq, int key)
{
	int i=0;

	for(i = 0; i < pq->cnt; i++)
		if (key == pq->heap[i].key)
			return i;

	return -1;
}


bool PriorityQueue_isEmpty(struct PriorityQueue *pq)
{
	return pq->cnt == 0;
}

bool PriorityQueue_isFull(struct PriorityQueue *pq)
{
	return pq->cnt == pq->size;
}


int minHeapGetSize(struct PriorityQueue *pq)
{
	return pq->cnt;
}


static void minheap_filterdown(struct PriorityQueue *pq, int start, int end)
{
	int curNode = start;
	int leftChild = 2*curNode + 1;
	struct Entry tmp = pq->heap[curNode];

	while(leftChild <= end) {
		if(leftChild < end && pq->heap[leftChild].key > pq->heap[leftChild+1].key)
			leftChild++;

		if(tmp.key <= pq->heap[leftChild].key)
			break;
		else {
			pq->heap[curNode] = pq->heap[leftChild];
			curNode = leftChild;
			leftChild = 2*leftChild + 1;
		}
	}

	pq->heap[curNode] = tmp;
}


int minheap_remove(struct PriorityQueue *pq, int data)
{
	int index;
	if(pq->cnt == 0)
		return  -1;

	index = minHeapGetIndex(pq, data);
	if (index== -1)
		return -1;

	pq->heap[index] = pq->heap[--pq->cnt];
	minheap_filterdown(pq, index, pq->cnt-1);

	return 0;
}


struct Entry  minheap_pop(struct PriorityQueue *pq)
{
	struct Entry min;

	min = pq->heap[0];
	minheap_remove(pq, min.key);
	return min;
}


static void filter_up(struct PriorityQueue *pq, int start)
{
	int curNode = start;
	int parent = (curNode - 1)/2;
	struct Entry tmp = pq->heap[curNode];

	while(curNode > 0) {
		if(pq->heap[parent].key <= tmp.key)
			break;
		else {
			pq->heap[curNode] = pq->heap[parent];
			curNode = parent;
			parent = (parent-1)/2;
		}
	}

	pq->heap[curNode] = tmp;
}

#if 0
int priorityQueue_push(struct PriorityQueue *pq, struct Entry node)
{
	if(PriorityQueue_isFull(pq)) {
		return -1;
	}

	pq->heap[pq->cnt] = node;
	filter_up(pq, pq->cnt);
	pq->cnt++;

	return 0;
}
#else
void priorityQueue_push( struct PriorityQueue * pq, struct Entry node)
{
	int i;

	if ( PriorityQueue_isFull( pq ) )
	{
		printf( "Priority queue is full" );
		return ;
	}

	for ( i = ++pq->cnt; pq->heap[i / 2].key > node.key; i /= 2)
		pq->heap[ i ] = pq->heap[i / 2];

	pq->heap[i] = node;
}
#endif


void minheap_print(struct PriorityQueue *pq)
{
	int i;
	for (i=0; i<pq->cnt; i++)
		printf("%d ", pq->heap[i].key);
}


struct PriorityQueue * minheap_init(int size)
{
	struct PriorityQueue * pq = (struct PriorityQueue *)malloc(sizeof(struct PriorityQueue) + sizeof(struct Entry) * size);
	pq->cnt = 0;
	pq->size = size;
	return pq;
}


void minheap_exit(struct PriorityQueue * pq)
{
	free(pq);
	pq = NULL;
}

int main(void)
{
	struct PriorityQueue *pq = minheap_init(1024);

	int a[] = {80, 40, 30, 60, 90, 70, 10, 50, 20};

	int i;
	for(i=0; i< sizeof(a) / sizeof(a[0]); i++) {
		printf("%d ", a[i]);
		struct Entry node;
		node.key = a[i];
		priorityQueue_push(pq, node);
	}

	printf("\n== minheap_print: \n10 20 30 50 90 70 40 80 60 :\n");
	minheap_print(pq);

	i=10;
	minheap_remove(pq, i);
	printf("\n== minheap_remove: %d", i);
	printf("\n== minheap_print: \n15 20 30 50 90 70 40 80 60 :\n");
	minheap_print(pq);
	printf("\n");

	printf("\n minheap_pop test:\n");
	while(!PriorityQueue_isEmpty(pq)) {
		struct Entry get = minheap_pop(pq);
		printf(" %d ", get.key);
	}

	printf("\n");

	return 0;
}

