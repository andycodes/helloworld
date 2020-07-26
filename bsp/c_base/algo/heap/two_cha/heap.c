/*
����"��һ��Ԫ��"�������е�����Ϊ 0 �Ļ���
�򸸽ڵ���ӽڵ��λ�ù�ϵ���£�
(01) ����Ϊi�����ӵ������� (2*i+1);
(02) ����Ϊi�����ӵ������� (2*i+2);
(03) ����Ϊi�ĸ����������� floor((i-1)/2);

����ѵĺ�����"��ӽڵ�"��"ɾ���ڵ�"
*/

struct heapEntry {
	int key;
	int value;
};

struct HeapCtrl{
	int size;
	int capacity;
	void (*remove_down)(struct HeapCtrl *, int , int);
	void (*push_up)(struct HeapCtrl *, int);
	struct heapEntry heap[0];
};

#ifdef PRIORITY_QUEUE_H
void maxheap_pushup(struct HeapCtrl *hp, int start)
{
	int child = start; // ��ǰ�ڵ�(current)��λ��
	int p = (child - 1) / 2;// ��(parent)����λ��
	struct heapEntry cur = hp->heap[child];// ��ǰ�ڵ�(current)�Ĵ�С

	while(child > 0) {
		if(hp->heap[p].key >= cur.key) {
			break;
		} else {
			hp->heap[child] = hp->heap[p];
			child = p;
			p = (child - 1) / 2;
		}
	}

	hp->heap[child] = cur;
}

void maxheap_rmdown(struct HeapCtrl *hp, int start, int end)
{
	int p = start;
	int lchild = 2*p + 1;
	struct heapEntry cur = hp->heap[p];

	while(lchild <= end) {
		if(lchild < end && hp->heap[lchild].key < hp->heap[lchild+1].key)
			lchild++;// ������������ѡ��ϴ��ߣ���m_heap[l+1]

		if(cur.key >= hp->heap[lchild].key) {
			break;//��������
		} else {
			hp->heap[p] = hp->heap[lchild];
			p = lchild;
			lchild = 2*p + 1;
		}
	}

	hp->heap[p] = cur;
}
#endif

#ifdef PRIORITY_QUEUE_MIN
void minheap_pushup(struct HeapCtrl *hp, int start)
{
	int cur = start;
	int p = (cur - 1) / 2;
	struct heapEntry newNode = hp->heap[cur];

	while(cur > 0) {
		if (hp->heap[p].key <= newNode.key) {
			break;
		} else {
			hp->heap[cur] = hp->heap[p];
			cur = p;
			p = (cur - 1) / 2;
		}
	}

	hp->heap[cur] = newNode;
}

void minheap_rmdown(struct HeapCtrl *hp, int start, int end)
{
	int p = start;
	int lchild = 2*p + 1;
	struct heapEntry cur = hp->heap[p];

	while(lchild <= end) {
		if(lchild < end && hp->heap[lchild].key > hp->heap[lchild+1].key)
			lchild++;// ������������ѡ���С�ߣ���m_heap[l+1]

		if(cur.key <= hp->heap[lchild].key)
			break;//��������
		else {
			hp->heap[p] = hp->heap[lchild];
			p = lchild;
			lchild = 2*lchild + 1;
		}
	}

	hp->heap[p] = cur;
}
#endif

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

struct heapEntry heap_pop(struct HeapCtrl *hp)
{
	struct heapEntry top;

	top = hp->heap[0];
	heap_remove(hp, top.key);
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

struct HeapCtrl *heap_init(int capacity)
{
	struct HeapCtrl * hp = (struct HeapCtrl *)calloc(1, sizeof(struct HeapCtrl) + sizeof(struct heapEntry) * capacity);
	hp->capacity = capacity;
	hp->remove_down = maxheap_rmdown;//minheap_rmdown
	hp->push_up = maxheap_pushup;
	return hp;
}

