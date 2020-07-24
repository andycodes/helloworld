/*
����"��һ��Ԫ��"�������е�����Ϊ 0 �Ļ���
�򸸽ڵ���ӽڵ��λ�ù�ϵ���£�
(01) ����Ϊi�����ӵ������� (2*i+1);
(02) ����Ϊi�����ӵ������� (2*i+2);
(03) ����Ϊi�ĸ����������� floor((i-1)/2);

����ѵĺ�����"��ӽڵ�"��"ɾ���ڵ�"
*/
#define HEAP_MAX 1024
struct heapEntry {
	int key;
	int value;
};

struct HeapCtrl{
	int size;
	int capacity;
	void (*remove_down)(struct HeapCtrl *, int , int);
	void (*push_up)(struct HeapCtrl *, int);
	struct heapEntry heap[HEAP_MAX];
};

int heap_getIdx(struct HeapCtrl *hp, int key)
{
	for(int i = 0; i < hp->size; i++) {
		if (key == hp->heap[i].key) {
			return i;
		}
	}

	return -1;
}

bool heap_empty(struct HeapCtrl *hp)
{
	return hp->size == 0;
}

bool heap_full(struct HeapCtrl *hp)
{
	return hp->size == hp->capacity;
}

int heap_size(struct HeapCtrl *hp)
{
	return hp->size;
}

struct HeapCtrl *heap_init(int capacity, int type)
{
	struct HeapCtrl * hp = (struct HeapCtrl *)malloc(sizeof(struct HeapCtrl) + sizeof(struct heapEntry) * capacity);
	hp->size = 0;
	hp->capacity = capacity;
	hp->type = type;
	return hp;
}

#ifdef PRIORITY_QUEUE_H
void maxheap_filterdown(struct HeapCtrl *hp, int start, int end)
{
	int parent = start;
	int leftChild = 2*parent + 1;
	struct heapEntry tmp = hp->heap[parent];

	while(leftChild <= end) {
		if(leftChild < end && hp->heap[leftChild].key < hp->heap[leftChild+1].key)
			leftChild++;// ������������ѡ��ϴ��ߣ���m_heap[l+1]

		if(tmp.key >= hp->heap[leftChild].key) {
			break;//��������
		} else {
			hp->heap[parent] = hp->heap[leftChild];
			parent = leftChild;
			leftChild = 2*parent + 1;
		}
	}

	hp->heap[parent] = tmp;
}

void maxheap_filterup(struct HeapCtrl *hp, int start)
{
	int child = start; // ��ǰ�ڵ�(current)��λ��
	int parent = (child - 1) / 2;// ��(parent)����λ��
	struct heapEntry tmp = hp->heap[child];// ��ǰ�ڵ�(current)�Ĵ�С

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

#endif

#ifdef PRIORITY_QUEUE_MIN
static void minheap_filterdown(struct HeapCtrl *pq, int start, int end)
{
	int parent = start;
	int leftChild = 2*parent + 1;
	struct heapEntry tmp = pq->heap[parent];

	while(leftChild <= end) {
		if(leftChild < end && pq->heap[leftChild].key > pq->heap[leftChild+1].key)
			leftChild++;// ������������ѡ���С�ߣ���m_heap[l+1]

		if(tmp.key <= pq->heap[leftChild].key)
			break;//��������
		else {
			pq->heap[parent] = pq->heap[leftChild];
			parent = leftChild;
			leftChild = 2*leftChild + 1;
		}
	}

	pq->heap[parent] = tmp;
}

static void minheap_filterup(struct HeapCtrl *pq, int start)
{
	int curIdx = start;
	int parent = (curIdx - 1) / 2;
	struct heapEntry newNode = pq->heap[curIdx];

	while(curIdx > 0) {
		if (pq->heap[parent].key <= newNode.key) {
			break;
		} else {
			pq->heap[curIdx] = pq->heap[parent];
			curIdx = parent;
			parent = (curIdx - 1) / 2;
		}
	}

	pq->heap[curIdx] = newNode;
}
#endif

struct HeapCtrl *heap_init(int capacity, int type)
{
	struct HeapCtrl * pq = (struct HeapCtrl *)malloc(sizeof(struct HeapCtrl) + sizeof(struct heapEntry) * capacity);
	pq->size = 0;
	pq->capacity = capacity;
	pq->type = type;

	pq->remove_down = maxheap_filterdown;//minheap_filterdown

	return pq;
}

int heap_remove(struct HeapCtrl *hp, int data)
{
	int index;
	if(hp->size == 0)
		return  -1;

	index = heap_getIdx(hp, data);
	if (index== -1) {
		return -1;
	}

	hp->heap[index] = hp->heap[--hp->size];// �����Ԫ���
	// ��indexλ�ÿ�ʼ�������µ���Ϊ����
	hp->remove_down(hp, index, hp->size -1);
	return 0;
}

struct heapEntry heap_pop(struct HeapCtrl *pq)
{
	struct heapEntry top;

	top = pq->heap[0];
	heap_remove(pq, top.key);
	return top;
}

int heap_push(struct HeapCtrl *hp, struct heapEntry node)
{
	if(heap_full(hp)) {
		return -1;
	}

	hp->heap[hp->size] = node;
	hp->push_up(hp, hp->size);
	hp->size++;

	return 0;
}


