/*
假设"第一个元素"在数组中的索引为 0 的话，
则父节点和子节点的位置关系如下：
(01) 索引为i的左孩子的索引是 (2*i+1);
(02) 索引为i的左孩子的索引是 (2*i+2);
(03) 索引为i的父结点的索引是 floor((i-1)/2);

二叉堆的核心是"添加节点"和"删除节点"

第K小元素 ----大堆栈
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
	int child = start; // 当前节点(current)的位置
	int p = (child - 1) / 2;// 父(parent)结点的位置
	struct heapEntry cur = hp->node[child];// 当前节点(current)的大小

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
			lchild++;// 左右两孩子中选择较大者，即m_heap[l+1]

		if(cur.key >= hp->node[lchild].key) {
			break;//调整结束
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
			lchild++;// 左右两孩子中选择较小者，即m_heap[l+1]

		if(cur.key <= hp->node[lchild].key)
			break;//调整结束
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

	hp->node[index] = hp->node[--hp->size];// 用最后元素填补
	// 从index位置开始自上向下调整为最大堆
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

