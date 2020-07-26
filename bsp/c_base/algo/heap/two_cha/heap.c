/*
假设"第一个元素"在数组中的索引为 0 的话，
则父节点和子节点的位置关系如下：
(01) 索引为i的左孩子的索引是 (2*i+1);
(02) 索引为i的左孩子的索引是 (2*i+2);
(03) 索引为i的父结点的索引是 floor((i-1)/2);

二叉堆的核心是"添加节点"和"删除节点"
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
	int child = start; // 当前节点(current)的位置
	int p = (child - 1) / 2;// 父(parent)结点的位置
	struct heapEntry cur = hp->heap[child];// 当前节点(current)的大小

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
			lchild++;// 左右两孩子中选择较大者，即m_heap[l+1]

		if(cur.key >= hp->heap[lchild].key) {
			break;//调整结束
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
			lchild++;// 左右两孩子中选择较小者，即m_heap[l+1]

		if(cur.key <= hp->heap[lchild].key)
			break;//调整结束
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

	hp->heap[index] = hp->heap[--hp->size];// 用最后元素填补
	// 从index位置开始自上向下调整为最大堆
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

