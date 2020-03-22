#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	PRIORITY_QUEUE_MIN,
	PRIORITY_QUEUE_MAN,
};

struct Entry {
	int key;
};

struct PriorityQueue{
	int cnt;
	int size;
	int type;
	struct Entry heap[0];
};


int priorityQueue_getIdx(struct PriorityQueue *pq, int key)
{
	for(int i = 0; i < pq->cnt; i++)
		if (key == pq->heap[i].key)
			return i;

	return -1;
}


bool priorityQueue_isEmpty(struct PriorityQueue *pq)
{
	return pq->cnt == 0;
}


bool priorityQueue_isFull(struct PriorityQueue *pq)
{
	return pq->cnt == pq->size;
}


int priorityQueue_getSize(struct PriorityQueue *pq)
{
	return pq->cnt;
}


static void minheap_filterdown(struct PriorityQueue *pq, int start, int end)
{
	int parent = start;
	int leftChild = 2*parent + 1;
	struct Entry tmp = pq->heap[parent];

	while(leftChild <= end) {
		if(leftChild < end && pq->heap[leftChild].key > pq->heap[leftChild+1].key)
			leftChild++;

		if(tmp.key <= pq->heap[leftChild].key)
			break;
		else {
			pq->heap[parent] = pq->heap[leftChild];
			parent = leftChild;
			leftChild = 2*leftChild + 1;
		}
	}

	pq->heap[parent] = tmp;
}


static void maxheap_filterdown(struct PriorityQueue *pq, int start, int end)
{
	int parent = start;
	int leftChild = 2*parent + 1;
	struct Entry tmp = pq->heap[parent];

	while(leftChild <= end) {
		if(leftChild < end && pq->heap[leftChild].key < pq->heap[leftChild+1].key)
			leftChild++;

		if(tmp.key >= pq->heap[leftChild].key) {
			break;
		} else {
			pq->heap[parent] = pq->heap[leftChild];
			parent = leftChild;
			leftChild = 2*parent + 1;
		}
	}

	pq->heap[parent] = tmp;
}



int priorityQueue_remove(struct PriorityQueue *pq, int data)
{
	int index;
	if(pq->cnt == 0)
		return  -1;

	index = priorityQueue_getIdx(pq, data);
	if (index== -1)
		return -1;

	pq->heap[index] = pq->heap[--pq->cnt];
	if (pq->type == PRIORITY_QUEUE_MIN) {
		minheap_filterdown(pq, index, pq->cnt - 1);
	} else {
		maxheap_filterdown(pq, index, pq->cnt -1);
	}

	return 0;
}


struct Entry  priorityQueue_pop(struct PriorityQueue *pq)
{
	struct Entry min;

	min = pq->heap[0];
	priorityQueue_remove(pq, min.key);
	return min;
}


static void filter_up(struct PriorityQueue *pq, int start)
{
	int curIdx = start;
	int parent = (curIdx - 1) / 2;
	struct Entry newNode = pq->heap[curIdx];

	while(curIdx > 0) {
		if(pq->heap[parent].key > newNode.key) {
			pq->heap[curIdx] = pq->heap[parent];
			curIdx = parent;
			parent = (curIdx - 1) / 2;
		} else {
			break;
		}
	}

	pq->heap[curIdx] = newNode;
}


static void maxheap_filterup(struct PriorityQueue *pq, int start)
{
    int child = start;
    int parent = (child-1) / 2;
    struct Entry tmp = pq->heap[child];

    while(child > 0) {
        if(pq->heap[parent].key >= tmp.key) {
            break;
        } else {
            pq->heap[child] = pq->heap[parent];
            child = parent;
            parent = (child - 1) / 2;
        }
    }
    pq->heap[child] = tmp;
}


int priorityQueue_push(struct PriorityQueue *pq, struct Entry node)
{
	if(priorityQueue_isFull(pq)) {
		return -1;
	}

	pq->heap[pq->cnt] = node;
	if (pq->type == PRIORITY_QUEUE_MIN) {
		filter_up(pq, pq->cnt);
	} else {
		maxheap_filterup(pq, pq->cnt);
	}

	pq->cnt++;

	return 0;
}



void minheap_print(struct PriorityQueue *pq)
{
	printf("%s\n", __func__);
	for (int i = 0; i < pq->cnt; i++)
		printf("%d ", pq->heap[i].key);
	printf("\n");
}


struct PriorityQueue * minheap_init(int size, int type)
{
	struct PriorityQueue * pq = (struct PriorityQueue *)malloc(sizeof(struct PriorityQueue) + sizeof(struct Entry) * size);
	pq->cnt = 0;
	pq->size = size;
	pq->type = type;
	return pq;
}


void minheap_exit(struct PriorityQueue * pq)
{
	free(pq);
	pq = NULL;
}

int main(void)
{
	struct PriorityQueue *pq = minheap_init(1024, PRIORITY_QUEUE_MAN);

	int a[] = {90,80,60,70,40,50,30,20,10,0};

	int i;
	for(i=0; i< sizeof(a) / sizeof(a[0]); i++) {
		printf("%d ", a[i]);
		struct Entry node;
		node.key = a[i];
		priorityQueue_push(pq, node);
	}

	minheap_print(pq);

	while(!priorityQueue_isEmpty(pq)) {
		struct Entry get = priorityQueue_pop(pq);
		printf(" %d ", get.key);
	}

	printf("\n");

	return 0;
}


