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

#ifdef PRIORITY_QUEUE_MAX
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

int heapSize(struct HeapCtrl *hp)
{
	return hp->size;
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

/*
 * 返回data在二叉堆中的索引
 *
 * 返回值：
 *     存在 -- 返回data在数组中的索引
 *     不存在 -- -1
 */
int get_index(struct HeapCtrl *hp, int data)
{
    int i=0;

    for(i=0; i<hp->size; i++)
        if (data==hp->node[i].key)
            return i;

    return -1;
}

/*
 * 最大堆的向下调整算法
 *
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *
 * 参数说明：
 *     start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
 *     end   -- 截至范围(一般为数组中最后一个元素的索引)
 */
static void maxheap_filterdown(struct HeapCtrl *hp, int start, int end)
{
    int c = start;          // 当前(current)节点的位置
    int l = 2*c + 1;     // 左(left)孩子的位置
    struct heapEntry tmp = hp->node[c];    // 当前(current)节点的大小

    while(l <= end)
    {
        // "l"是左孩子，"l+1"是右孩子
        if(l < end && hp->node[l].key < hp->node[l+1].key)
            l++;        // 左右两孩子中选择较大者，即m_heap[l+1]
        if(tmp.key >= hp->node[l].key)
            break;        //调整结束
        else
        {
            hp->node[c] = hp->node[l];
            c = l;
            l = 2*l + 1;
        }
    }

    hp->node[c] = tmp;
}

/*
 * 删除最大堆中的data
 *
 * 返回值：
 *      0，成功
 *     -1，失败
 */
int maxheap_remove(struct HeapCtrl *hp, int data)
{
    int index;
    // 如果"堆"已空，则返回-1
    if(hp->size== 0)
        return -1;

    // 获取data在数组中的索引
    index = get_index(hp, data);
    if (index==-1)
        return -1;

    hp->node[index] = hp->node[--hp->size];        // 用最后元素填补
    maxheap_filterdown(hp, index, hp->size-1);    // 从index位置开始自上向下调整为最大堆

    return 0;
}

#endif

#ifdef PRIORITY_QUEUE_MIN
void heapPush(struct HeapCtrl *hp, struct heapEntry node)
{
	if(heapFull(hp)) {
		return;
	}

	int cidx = hp->size;
	int fidx = (cidx - 1) / 2;

	while(cidx > 0) {
		if (hp->node[fidx].key > node.key) {
			hp->node[cidx] = hp->node[fidx]; // 下沉
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
	struct heapEntry top = hp->node[0];
	if (heapEmpty(hp)) {
		return top; // err
	}

	struct heapEntry cmp =  hp->node[--hp->size];// 用最后元素填补
	int fidx = 0;
	int cidx = 2* fidx + 1;

	while(cidx < hp->size) {
		if(cidx < hp->size -1 && hp->node[cidx].key > hp->node[cidx+1].key)
			cidx++;// 左右两孩子中选择较小者，

		if(hp->node[cidx].key < cmp.key) {
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

struct HeapCtrl *heapInit(int cap)
{
	struct HeapCtrl * hp = (struct HeapCtrl *)calloc(1, sizeof(struct HeapCtrl) + sizeof(struct heapEntry) * cap);
	hp->cap = cap;
	return hp;
}
#endif
