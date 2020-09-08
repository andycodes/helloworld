/*
373. 查找和最小的K对数字
给定两个以升序排列的整形数组 nums1 和 nums2, 以及一个整数 k。
定义一对值 (u,v)，其中第一个元素来自 nums1，
第二个元素来自 nums2。
找到和最小的 k 对数字 (u1,v1), (u2,v2) ... (uk,vk)。
示例 1:

输入: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
输出: [1,2],[1,4],[1,6]
解释: 返回序列中的前 3 对数：
     [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
示例 2:
*/
int** kSmallestPairs(int* nums1, int nums1Size,
int* nums2, int nums2Size, int k,
int* returnSize, int** returnColumnSizes)
{
	struct HeapCtrl *hp = heapInit(k);

	for (int i = 0; i < nums1Size; i++) {
		for (int j = 0; j < nums2Size; j++) {
			if (heapFull(hp)) {
				int sum = nums1[i] + nums2[j];
				struct heapEntry top = hp->node[0];
				if (sum >= top.key) {
					continue;
				} else {
					heapPop(hp);
				}
			}

			struct heapEntry node;
			node.n1 = nums1[i];
			node.n2 = nums2[j];
			node.key = node.n1 + node.n2;
			heapPush(hp, node);
		}
	}

	int size = hp->size;
	*returnSize = size;
	int **res = (int **)calloc(size, sizeof(int *));
	*returnColumnSizes = (int *)calloc(size, sizeof(int));
	for (int i = 0; i < size; i++) {
		res[i] = (int *)calloc(2, sizeof(int));
		res[i][0] = hp->node[i].n1;
		res[i][1] = hp->node[i].n2;
		(*returnColumnSizes)[i] = 2;
	}

	return res;
}

/*
264. 丑数 II
编写一个程序，找出第 n 个丑数。

丑数就是只包含质因数 2, 3, 5 的正整数。

示例:

输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
说明:

1 是丑数。
n 不超过1690。

*/


/*
关键思路：找一下最小丑数

2、利用最小堆，先扔1进堆里。
然后每次拿堆顶最小的再乘一下2、3、5，
然后扔堆里。直到拿堆顶次数为n。
*/
int b[] = {2,3,5};
int nthUglyNumber(int n)
{
	struct HeapCtrl *hp = heap_init(n);
	struct heapEntry node;
	node.key = 1;
	heap_push(hp, node);
	struct heapEntry pop;
	for (int i = 0; i < n; i++) {
		pop = heap_pop(hp);
		node.key = pop.key * 2;
		heap_push(hp, node);// sole push
		node.key = pop.key * 3;
		heap_push(hp, node);
		node.key = pop.key * 5;
		heap_push(hp, node);
	}

	return pop.key;
}


/*
面试题 17.09. 第 k 个数
难度中等13
有些数的素因子只有 3，5，7，请设计一个算法找出第 k 个数。
注意，不是必须有这些素因子，而是必须不包含其他的素因子。
例如，前几个数按顺序应该是 1，3，5，7，9，15，21。
示例 1:
输入: k = 5

输出: 9

*/
int getKthMagicNumber(int k){
	int rat[] = {3,5,7};
	int ret = 0;
	struct HeapCtrl *pq =  heapInit(1024);
	struct heapEntry node;
	node.key = 1;
	heapPush(pq, node);
	while(k-- && !heapEmpty(pq)) {
		struct heapEntry top =  heapPop(pq);
		ret = top.key;
		for(int i = 0; i < 3 ;i++) {
			struct heapEntry node;
			node.key = top.key * rat[i];
			heapPush(pq, node);
		}
	}

	return ret;
}


/*
378. 有序矩阵中第K小的元素
bseach
*/
int kthSmallest(int** matrix, int matrixSize, int* matrixColSize, int k){
    struct HeapSort *heap = heapsort_init(k, PRIORITY_QUEUE_MAX);

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize[i]; j++) {
                if (heapsort_full(heap)) {
                    if (matrix[i][j] < heapsort_top_key(heap))                      {
                        heapsort_pop(heap);
                        struct heapEntry node;
                        node.key = matrix[i][j];
                        heapsort_push(heap, node);
                    }
                } else {
                        struct heapEntry node;
                        node.key = matrix[i][j];
                        heapsort_push(heap, node);
                }

        }
    }

    return heapsort_top_key(heap);
}


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


