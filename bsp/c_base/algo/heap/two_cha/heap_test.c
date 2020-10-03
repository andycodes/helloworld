/*
295. 数据流的中位数
bseach
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

typedef struct {
	struct HeapCtrl *maxheap;
	struct HeapCtrl *minheap;
} MedianFinder;

/** initialize your data structure here. */

MedianFinder* medianFinderCreate() {
	MedianFinder *obj = (MedianFinder *)calloc(1, sizeof(MedianFinder));
	obj->maxheap = maxheapInit(10240);
	obj->minheap = minheapInit(10240);
	return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
	// Add to max heap
	struct heapEntry node;
	node.key = num;
	heapPush(obj->maxheap, node);

	// balancing step
	struct heapEntry maxtop = heapPop(obj->maxheap);
	heapPush(obj->minheap, maxtop);

	 // maintain size property
	 if (heapSize(obj->maxheap) < heapSize(obj->minheap)) {
		struct heapEntry mintop = heapPop(obj->minheap);
		heapPush(obj->maxheap, mintop);
	 }
}

double medianFinderFindMedian(MedianFinder* obj) {

	if (obj->maxheap->size > obj->minheap->size) {
		return obj->maxheap->node[0].key;
	} else {
		return (obj->maxheap->node[0].key + obj->minheap->node[0].key) * 0.5;
	}
}

/*
218. 天际线问题
城市的天际线是从远处观看该城市中所有建筑物形成的轮廓的外部轮廓。现在，假设您获得了城市风光照片（图A）上显示的所有建筑物的位置和高度，请编写一个程序以输出由这些建筑物形成的天际线（图B）。

Buildings Skyline Contour

每个建筑物的几何信息用三元组 [Li，Ri，Hi] 表示，其中 Li 和 Ri 分别是第 i 座建筑物左右边缘的 x 坐标，Hi 是其高度。可以保证 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX 和 Ri - Li > 0。您可以假设所有建筑物都是在绝对平坦且高度为 0 的表面上的完美矩形。

例如，图A中所有建筑物的尺寸记录为：[ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] 。

输出是以 [ [x1,y1], [x2, y2], [x3, y3], ... ] 格式的“关键点”（图B中的红点）的列表，它们唯一地定义了天际线。关键点是水平线段的左端点。请注意，最右侧建筑物的最后一个关键点仅用于标记天际线的终点，并始终为零高度。此外，任何两个相邻建筑物之间的地面都应被视为天际线轮廓的一部分。

例如，图B中的天际线应该表示为：[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ]。
*/
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
struct Heap {
    int capacity;
    int size;
    int *arr;
};

struct Heap* HeapInit(int maxSize)
{
    struct Heap* heap;

    heap = malloc(sizeof(struct Heap));
    heap->capacity = maxSize;
    heap->size = 0;
    heap->arr = malloc(sizeof(int)*(maxSize+1));

    return heap;
}

void HeapInsert(int x, struct Heap *obj)
{
    int i;
    obj->size += 1;
    for (i=obj->size; i!=1 && x>(obj->arr)[i/2]; i=i/2) {
        (obj->arr)[i] = (obj->arr)[i/2];
    }
    (obj->arr)[i] = x;
    return;
}

int HeapDeleteMax(struct Heap *obj)
{
    int ret = (obj->arr)[1];
    int x = (obj->arr)[obj->size];
    int i, child;

    obj->size -= 1;
    for (i=1; i<=obj->size/2;i=child) {
        child = i*2;
        if (child < obj->size && (obj->arr)[child]<(obj->arr)[child+1]) {
            child++;
        }
        if (x < (obj->arr)[child])
            (obj->arr)[i] = (obj->arr)[child];
        else
            break;
    }
    (obj->arr)[i] = x;

    return ret;
}

void HeapDelete(int x, struct Heap *obj)
{
    int i;

    for(i=1; i<=obj->size; i++) {
        if (x == (obj->arr)[i]) {
            break;
        }
    }
    if (i > obj->size)
        return;

    // 节点x上滤
    for (; i!=1; i=i/2) {
        (obj->arr)[i] = (obj->arr)[i/2];
    }
    (obj->arr)[i] = INT_MAX;

    HeapDeleteMax(obj);

    return;
}

int HeapGetMax(struct Heap *obj)
{
    if (obj->size > 0) {
        return (obj->arr)[1];
    } else {
        return 0;
    }
}
void HeapPrint(struct Heap *obj)
{
    int i;
    for(i=1; i<=obj->size; i++) {
        printf("%d ", (obj->arr)[i]);
    }
    printf("\n");
}

int Abs(int a)
{
    return a<0?-a:a;
}

int arraycmp(const void *elem1,const void *elem2)
{
    int ret;
    int a, b;

    ret = (*((int**)elem1))[0]-(*((int**)elem2))[0];
    if (ret == 0) {
        a = -(*((int**)elem2))[1];
        b = -(*((int**)elem1))[1];
        ret = a - b;
    }
    return ret;
}

int** getSkyline(int** buildings, int buildingsSize, int* buildingsColSize, int* returnSize, int** returnColumnSizes){
    int **vetex;
    int vetexCount = buildingsSize*2;
    int **ret;
    int retCount;
    struct Heap *heap;
    int i;
    int lastHeight;

    /*
    step 1 找出建筑物所有左上、右上的点，存入vetex中。左上的点，高取负数
    */
    vetex = malloc(sizeof(int*)*vetexCount);
    for (i=0; i<vetexCount; i++) {
        vetex[i] = malloc(sizeof(int)*2);
    }
    for (i=0; i<buildingsSize; i++) {
        vetex[i*2][0] = buildings[i][0];
        vetex[i*2][1] = -buildings[i][2];
        vetex[i*2+1][0] = buildings[i][1];
        vetex[i*2+1][1] = buildings[i][2];
    }
    qsort(vetex, vetexCount, sizeof(int*), arraycmp);
    // for(i=0; i<vetexCount; i++) {
    //     printf("(%d %d)", vetex[i][0], vetex[i][1]);
    // }
    // printf("\n");

    /*
    调试堆
    */
    // heap = HeapInit(10);
    // HeapInsert(8, heap);
    // HeapInsert(20, heap);
    // HeapInsert(2, heap);
    // HeapInsert(15, heap);
    // HeapInsert(19, heap);
    // HeapPrint(heap);
    // HeapDelete(19, heap);
    // printf("\n");
    // HeapPrint(heap);

    /*
    step 2 扫描线从左向右扫描，获取转折点
    1)扫描到建筑物的左边界时，将高存入堆
    2)扫描到建筑物的右边界时，将高从堆中取出
    3)当存入、取出时，最大高度发生变化时，遇到转折点。算出新的height，转折点为 当前节点，height
    */
    heap = HeapInit(buildingsSize+1);
    retCount = 0;
    ret = malloc(sizeof(int*)*vetexCount);
    lastHeight = 0;
    for (i=0; i<vetexCount; i++) {
        // printf("i=%d size=%d\n",i, heap->size);
        if (vetex[i][1] < 0) {
            HeapInsert(-vetex[i][1], heap);
        } else {
            HeapDelete(vetex[i][1], heap);
        }
        // HeapPrint(heap);
        // printf("1111111\n");
        if (lastHeight != HeapGetMax(heap)) {
            lastHeight = HeapGetMax(heap);
            //get i, lastHeight;
            ret[retCount] = malloc(sizeof(int)*2);
            ret[retCount][0] = vetex[i][0];
            ret[retCount][1] = HeapGetMax(heap);
            retCount++;
        }
    }
    *returnColumnSizes = malloc(sizeof(int)*retCount);
    for (i=0; i<retCount; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    *returnSize = retCount;
    return ret;
}

/*
1499. 满足不等式的最大值
给你一个数组 points 和一个整数 k 。数组中每个元素都表示二维平面上的点的坐标，并按照横坐标 x 的值从小到大排序。也就是说 points[i] = [xi, yi] ，并且在 1 <= i < j <= points.length 的前提下， xi < xj 总成立。

请你找出 yi + yj + |xi - xj| 的 最大值，其中 |xi - xj| <= k 且 1 <= i < j <= points.length。

题目测试数据保证至少存在一对能够满足 |xi - xj| <= k 的点。



示例 1：

输入：points = [[1,3],[2,0],[5,10],[6,-10]], k = 1
输出：4
解释：前两个点满足 |xi - xj| <= 1 ，代入方程计算，则得到值 3 + 0 + |1 - 2| = 4 。第三个和第四个点也满足条件，得到值 10 + -10 + |5 - 6| = 1 。
没有其他满足条件的点，所以返回 4 和 1 中最大的那个。
*/

int findMaxValueOfEquation(int** points, int pointsSize, int* pointsColSize, int k)
{
	int res = INT_MIN;
	struct HeapCtrl *hp = heapInit(pointsSize);

	for (int j = 0; j < pointsSize; j++) {
		//超出窗口长度的就 弹出
		while(!heapEmpty(hp) && (points[j][0] - points[hp->node[0].xidx][0] > k))
			heapPop(hp);

		//计算当前窗口内的最大值
		if (!heapEmpty(hp)) {
			res = fmax(res, points[j][0] + points[j][1] +
				points[hp->node[0].xidx][1] - points[hp->node[0].xidx][0]);
		}

		struct heapEntry node;
		node.key = points[j][1] - points[j][0];
		node.xidx = j;
		heapPush(hp, node);
	}

	return res;
}

