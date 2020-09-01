/*
假设"第一个元素"在数组中的索引为 0 的话，
则父节点和子节点的位置关系如下：
如果 i=0，它是根节点
如果 i>0，它的父节点的索引为 floor（（i-1）/  2）
如果 2i + 1 <=  n-1，它的左子节点的索引为 2i + 1
如果 2i + 2 <=  n-1，它的右子节点的索引为 2i + 2
如果 2i + 1 > n-1，它无左子节点
如果 2i + 2 > n-1，它无右子节点

数组成员按照数的层序遍历布局!!!

二叉堆的核心是"添加节点"和"删除节点"

第K小元素 ----大堆栈

有叶子结点都是处于第 h 或 h - 1层（h为树的高度）
*/
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
	struct heapEntry node[0];
};

bool heapFull(struct HeapCtrl *hp)
{
	return hp->size == hp->cap;
}

bool heapEmpty(struct HeapCtrl *hp)
{
	return hp->size == 0;
}

#ifdef PRIORITY_QUEUE_MAX
void heapPush(struct HeapCtrl *hp, struct heapEntry node)
{
	if(heapFull(hp)) {
		return;
	}

	int cidx = hp->size;
	int fidx  = (cidx - 1) / 2;

	while(cidx > 0) {
		if(hp->node[fidx].key < node.key) {
			hp->node[cidx] = hp->node[fidx];//下沉
			cidx = fidx;
			fidx = (cidx - 1) / 2;
		} else {
			break;
		}
	}

	hp->node[cidx] = node;
	hp->size++;
}

struct heapEntry heapPop(struct HeapCtrl *hp)
{
	if (heapEmpty(hp)) {
		return hp->node[0]; /* err */
	}

	struct heapEntry top;
	top = hp->node[0];

	struct heapEntry cmp = hp->node[--hp->size];
	int fidx  = 0;
	int cidx = 2 * fidx + 1;

	while(cidx < hp->size) {
		if (cidx < hp->size -1 && hp->node[cidx].key < hp->node[cidx + 1].key)
			cidx++; // 左右两孩子中选择较大者

		if (hp->node[cidx].key > cmp.key) {
			hp->node[fidx] = hp->node[cidx];
			fidx = cidx;
			cidx = 2 * fidx + 1;
		} else {
			break;
		}
	}

	hp->node[fidx] = cmp;

	return top;
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
	return hp;
}

