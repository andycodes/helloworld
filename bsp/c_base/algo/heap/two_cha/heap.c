/*
����"��һ��Ԫ��"�������е�����Ϊ 0 �Ļ���
�򸸽ڵ���ӽڵ��λ�ù�ϵ���£�
(01) ����Ϊi�����ӵ������� (2*i+1);
(02) ����Ϊi�����ӵ������� (2*i+2);
(03) ����Ϊi�ĸ����������� floor((i-1)/2);

����ѵĺ�����"��ӽڵ�"��"ɾ���ڵ�"

��KСԪ�� ----���ջ
*/

struct heapEntry {
	int key;
};

struct HeapCtrl{
	int size;
	int cap;
	void (*rmdown)(struct HeapCtrl *, int , int);
	void (*pushup)(struct HeapCtrl *, int);
	struct heapEntry node[0];
};

#ifdef PRIORITY_QUEUE_MAX
void maxheapPushup(struct HeapCtrl *hp, int start)
{
	int child = start; // ��ǰ�ڵ�(current)��λ��
	int p = (child - 1) / 2;// ��(parent)����λ��
	struct heapEntry cur = hp->node[child];// ��ǰ�ڵ�(current)�Ĵ�С

	while(child > 0) {
		if(hp->node[p].key >= cur.key) {
			break;
		} else {
			hp->node[child] = hp->node[p];
			child = p;
			p = (child - 1) / 2;
		}
	}

	hp->node[child] = cur;
}

void maxheapRmdown(struct HeapCtrl *hp, int start, int end)
{
	int p = start;
	int lchild = 2*p + 1;
	struct heapEntry cur = hp->node[p];

	while(lchild <= end) {
		if(lchild < end && hp->node[lchild].key < hp->node[lchild+1].key)
			lchild++;// ������������ѡ��ϴ��ߣ���m_heap[l+1]

		if(cur.key >= hp->node[lchild].key) {
			break;//��������
		} else {
			hp->node[p] = hp->node[lchild];
			p = lchild;
			lchild = 2*p + 1;
		}
	}

	hp->node[p] = cur;
}
#endif

#ifdef PRIORITY_QUEUE_MIN
void minheapPushup(struct HeapCtrl *hp, int start)
{
	int child = start;
	int p = (child - 1) / 2;
	struct heapEntry cur = hp->node[child];

	while(child > 0) {
		if (hp->node[p].key <= cur.key) {
			break;
		} else {
			hp->node[child] = hp->node[p];
			child = p;
			p = (child - 1) / 2;
		}
	}

	hp->node[child] = cur;
}

void minheapRmdown(struct HeapCtrl *hp, int start, int end)
{
	int p = start;
	int lchild = 2*p + 1;
	struct heapEntry cur = hp->node[p];

	while(lchild <= end) {
		if(lchild < end && hp->node[lchild].key > hp->node[lchild+1].key)
			lchild++;// ������������ѡ���С�ߣ���m_heap[l+1]

		if(cur.key <= hp->node[lchild].key)
			break;//��������
		else {
			hp->node[p] = hp->node[lchild];
			p = lchild;
			lchild = 2*lchild + 1;
		}
	}

	hp->node[p] = cur;
}
#endif

int heapGetIdx(struct HeapCtrl *hp, int key)
{
	for(int i = 0; i < hp->size; i++) {
		if (key == hp->node[i].key) {
			return i;
		}
	}

	return -1;
}

bool heapEmpty(struct HeapCtrl *hp)
{
	return hp->size == 0;
}

bool heapFull(struct HeapCtrl *hp)
{
	return hp->size == hp->cap;
}

int heapSize(struct HeapCtrl *hp)
{
	return hp->size;
}

int heapRm(struct HeapCtrl *hp, int data)
{
	int index;
	if(hp->size == 0)
		return  -1;

	index = heapGetIdx(hp, data);
	if (index== -1) {
		return -1;
	}

	hp->node[index] = hp->node[--hp->size];// �����Ԫ���
	// ��indexλ�ÿ�ʼ�������µ���Ϊ����
	hp->rmdown(hp, index, hp->size -1);
	return 0;
}

struct heapEntry heapPop(struct HeapCtrl *hp)
{
	struct heapEntry top;

	top = hp->node[0];
	heapRm(hp, top.key);
	return top;
}

int heapPush(struct HeapCtrl *hp, struct heapEntry node)
{
	if(heapFull(hp)) {
		return -1;
	}

	hp->node[hp->size] = node;
	hp->pushup(hp, hp->size);
	hp->size++;

	return 0;
}

struct HeapCtrl *heapInit(int cap)
{
	struct HeapCtrl * hp = (struct HeapCtrl *)calloc(1, sizeof(struct HeapCtrl) + sizeof(struct heapEntry) * cap);
	hp->cap = cap;
	hp->rmdown = maxheapRmdown;//minheapRmdown
	hp->pushup = maxheapPushup;
	return hp;
}

