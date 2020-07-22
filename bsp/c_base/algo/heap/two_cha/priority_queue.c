

#define HEAP_MAX 1024

struct heapEntry {
	int key;
	int value;
};

struct HeapSort{
	int cnt;
	int size;
	struct heapEntry heap[HEAP_MAX];
};

#ifndef PRIORITY_QUEUE_H

int heapsort_getIdx(struct HeapSort *hp, int key)
{
	for(int i = 0; i < hp->cnt; i++) {
		if (key == hp->heap[i].key) {
			return i;
		}
	}

	return -1;
}

int heapsort_getIdxbyValue(struct HeapSort *hp, int value)
{
	for(int i = 0; i < hp->cnt; i++) {
		if (value == hp->heap[i].value) {
			return i;
		}
	}

	return -1;
}


bool heapsort_empty(struct HeapSort *hp)
{
	return hp->cnt == 0;
}


bool heapsort_full(struct HeapSort *hp)
{
	return hp->cnt == hp->size;
}


int heapsort_size(struct HeapSort *hp)
{
	return hp->cnt;
}


static void minheap_filterdown(struct HeapSort *hp, int start, int end)
{
	int parent = start;
	int leftChild = 2*parent + 1;
	struct heapEntry tmp = hp->heap[parent];

	while(leftChild <= end) {
		if(leftChild < end && hp->heap[leftChild].key > hp->heap[leftChild+1].key)
			leftChild++;

		if(tmp.key <= hp->heap[leftChild].key)
			break;
		else {
			hp->heap[parent] = hp->heap[leftChild];
			parent = leftChild;
			leftChild = 2*leftChild + 1;
		}
	}

	hp->heap[parent] = tmp;
}


static void maxheap_filterdown(struct HeapSort *hp, int start, int end)
{
	int parent = start;
	int leftChild = 2*parent + 1;
	struct heapEntry tmp = hp->heap[parent];

	while(leftChild <= end) {
		if(leftChild < end && hp->heap[leftChild].key < hp->heap[leftChild+1].key)
			leftChild++;

		if(tmp.key >= hp->heap[leftChild].key) {
			break;
		} else {
			hp->heap[parent] = hp->heap[leftChild];
			parent = leftChild;
			leftChild = 2*parent + 1;
		}
	}

	hp->heap[parent] = tmp;
}



int heapsort_remove(struct HeapSort *hp, int data)
{
	int index;
	if(hp->cnt == 0)
		return  -1;

	index = heapsort_getIdx(hp, data);
	if (index== -1)
		return -1;

	hp->heap[index] = hp->heap[--hp->cnt];
	if (hp->type == PRIORITY_QUEUE_MIN) {
		minheap_filterdown(hp, index, hp->cnt - 1);
	} else {
		maxheap_filterdown(hp, index, hp->cnt -1);
	}

	return 0;
}

struct heapEntry heapsort_pop(struct HeapSort *hp)
{
	struct heapEntry top;

	top = hp->heap[0];
	heapsort_remove(hp, top.key);
	return top;
}

int heapsort_top_key(struct HeapSort *hp)
{
	return hp->heap[0].key;
}

static void minheap_filterup(struct HeapSort *hp, int start)
{
	int curIdx = start;
	int parent = (curIdx - 1) / 2;
	struct heapEntry newNode = hp->heap[curIdx];

	while(curIdx > 0) {
		if(hp->heap[parent].key > newNode.key) {
			hp->heap[curIdx] = hp->heap[parent];
			curIdx = parent;
			parent = (curIdx - 1) / 2;
		} else {
			break;
		}
	}

	hp->heap[curIdx] = newNode;
}


static void maxheap_filterup(struct HeapSort *hp, int start)
{
    int child = start; // 当前节点(current)的位置
    int parent = (child-1) / 2;// 父(parent)结点的位置
    struct heapEntry tmp = hp->heap[child];// 当前节点(current)的大小

    while(child > 0) {
        if(hp->heap[parent].key >= tmp.key) {
            break;
        } else {
            hp->heap[child] = hp->heap[parent];
            child = parent;
            parent = (child - 1) / 2;
        }
    }
    hp->heap[child] = tmp;
}


int heapsort_push(struct HeapSort *hp, struct heapEntry node)
{
	if(heapsort_full(hp)) {
		return -1;
	}

	hp->heap[hp->cnt] = node;
	if (hp->type == PRIORITY_QUEUE_MIN) {
		minheap_filterup(hp, hp->cnt);
	} else {
		maxheap_filterup(hp, hp->cnt);
	}

	hp->cnt++;

	return 0;
}

void  heapsort_push_sole(struct HeapSort *hp, struct heapEntry node)
{
	if(heapsort_getIdx(hp, node.key) != -1) {
		return;
	}

	heapsort_push(hp, node);
}



void minheap_print(struct HeapSort *hp)
{
	printf("%s\n", __func__);
	for (int i = 0; i < hp->cnt; i++)
		printf("%d ", hp->heap[i].key);
	printf("\n");
}


struct HeapSort *heapsort_init(int size, int type)
{
	struct HeapSort * hp = (struct HeapSort *)malloc(sizeof(struct HeapSort) + sizeof(struct heapEntry) * size);
	hp->cnt = 0;
	hp->size = size;
	hp->type = type;
	return hp;
}


void heapsort_exit(struct HeapSort * hp)
{
	free(hp);
	hp = NULL;
}

#endif
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
enum {
	PRIORITY_QUEUE_MIN,
	PRIORITY_QUEUE_MAX,
};

struct heapEntry {
	int key;
	int value;
};

struct HeapSort{
	int cnt;
	int size;
	int type;
	struct heapEntry heap[0];
};


int heapsort_getIdx(struct HeapSort *pq, int key)
{
	for(int i = 0; i < pq->cnt; i++) {
		if (key == pq->heap[i].key) {
			return i;
		}
	}

	return -1;
}

int heapsort_getIdxbyValue(struct HeapSort *pq, int value)
{
	for(int i = 0; i < pq->cnt; i++) {
		if (value == pq->heap[i].value) {
			return i;
		}
	}

	return -1;
}


bool heapsort_empty(struct HeapSort *pq)
{
	return pq->cnt == 0;
}


bool heapsort_full(struct HeapSort *pq)
{
	return pq->cnt == pq->size;
}


int heapsort_size(struct HeapSort *pq)
{
	return pq->cnt;
}


static void minheap_filterdown(struct HeapSort *pq, int start, int end)
{
	int parent = start;
	int leftChild = 2*parent + 1;
	struct heapEntry tmp = pq->heap[parent];

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


static void maxheap_filterdown(struct HeapSort *pq, int start, int end)
{
	int parent = start;
	int leftChild = 2*parent + 1;
	struct heapEntry tmp = pq->heap[parent];

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



int heapsort_remove(struct HeapSort *pq, int data)
{
	int index;
	if(pq->cnt == 0)
		return  -1;

	index = heapsort_getIdx(pq, data);
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

struct heapEntry heapsort_pop(struct HeapSort *pq)
{
	struct heapEntry top;

	top = pq->heap[0];
	heapsort_remove(pq, top.key);
	return top;
}

int heapsort_top_key(struct HeapSort *pq)
{
	return pq->heap[0].key;
}

static void minheap_filterup(struct HeapSort *pq, int start)
{
	int curIdx = start;
	int parent = (curIdx - 1) / 2;
	struct heapEntry newNode = pq->heap[curIdx];

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


static void maxheap_filterup(struct HeapSort *pq, int start)
{
    int child = start; // 当前节点(current)的位置
    int parent = (child-1) / 2;// 父(parent)结点的位置
    struct heapEntry tmp = pq->heap[child];// 当前节点(current)的大小

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


int heapsort_push(struct HeapSort *pq, struct heapEntry node)
{
	if(heapsort_full(pq)) {
		return -1;
	}

	pq->heap[pq->cnt] = node;
	if (pq->type == PRIORITY_QUEUE_MIN) {
		minheap_filterup(pq, pq->cnt);
	} else {
		maxheap_filterup(pq, pq->cnt);
	}

	pq->cnt++;

	return 0;
}

void  heapsort_push_sole(struct HeapSort *pq, struct heapEntry node)
{
	if(heapsort_getIdx(pq, node.key) != -1) {
		return;
	}

	heapsort_push(pq, node);
}



void minheap_print(struct HeapSort *pq)
{
	printf("%s\n", __func__);
	for (int i = 0; i < pq->cnt; i++)
		printf("%d ", pq->heap[i].key);
	printf("\n");
}


struct HeapSort *heapsort_init(int size, int type)
{
	struct HeapSort * pq = (struct HeapSort *)malloc(sizeof(struct HeapSort) + sizeof(struct heapEntry) * size);
	pq->cnt = 0;
	pq->size = size;
	pq->type = type;
	return pq;
}


void heapsort_exit(struct HeapSort * pq)
{
	free(pq);
	pq = NULL;
}

#endif


