/*
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
int nthUglyNumber(int n){

	minHeap *H = minheap_init(16900);
	minHeapPush(H,1);
	long int res = 0;

	for (long int i = 0; i < n;i++) {
		res = minHeapPop(H);
		for (long int j = 0;  j < sizeof(b)/sizeof(int); j++) {
			long int a = res * b[j];
			if (minHeapGetIndex(H, a) == -1)
				minHeapPush(H, a);
		}
	}

	return res;
}


/*
题目描述
评论 (62)
题解(42)
提交记录
373. 查找和最小的K对数字
给定两个以升序排列的整形数组 nums1 和 nums2, 以及一个整数 k。

定义一对值 (u,v)，其中第一个元素来自 nums1，第二个元素来自 nums2。

找到和最小的 k 对数字 (u1,v1), (u2,v2) ... (uk,vk)。

示例 1:

输入: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
输出: [1,2],[1,4],[1,6]
解释: 返回序列中的前 3 对数：
     [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
示例 2:

输入: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
输出: [1,1],[1,1]
解释: 返回序列中的前 2 对数：
     [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
示例 3:

输入: nums1 = [1,2], nums2 = [3], k = 3
输出: [1,3],[2,3]
解释: 也可能序列中所有的数对都被返回:[1,3],[2,3]

*/
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** kSmallestPairs(int* nums1, int nums1Size, int* nums2,
int nums2Size, int k, int* returnSize, int** returnColumnSizes)
{
	if (nums1 == NULL || nums2 == NULL || nums1Size <= 0 || nums2Size <= 0 || k <= 0) {
		*returnSize = 0;
		return NULL;
	}

	struct PriorityQueue *pq = priorityQueue_init(k, PRIORITY_QUEUE_MAX);

	for (int i = 0; i < nums1Size; i++) {
		for (int j = 0; j < nums2Size; j++) {
			if (priorityQueue_isFull(pq)) {
				int sum = nums1[i] + nums2[j];
				struct Entry top = priorityQueue_top(pq);
				if (sum < top.key) {
					priorityQueue_pop(pq);
					struct Entry newNode;
					newNode.key = sum;
					newNode.num1 = nums1[i];
					newNode.num2 = nums2[j];
					priorityQueue_push(pq, newNode);
				}
			} else {
					struct Entry newNode;
					newNode.key = nums1[i] + nums2[j];
					newNode.num1 = nums1[i];
					newNode.num2 = nums2[j];
					priorityQueue_push(pq, newNode);
			}
		}
	}

	int ** res = (int **)calloc(1024 * 1024, sizeof(int));
	*returnColumnSizes = (int *)calloc(1024, sizeof(int));
	*returnSize = priorityQueue_size(pq);
	int i = 0;
	while(!priorityQueue_isEmpty(pq)) {
		res[i] = (int *)calloc(1024, sizeof(int));
		struct Entry newNode = priorityQueue_pop(pq);
		res[i][0] = newNode.num1;
		res[i][1] = newNode.num2;
		(*returnColumnSizes)[i] = 2;
		i++;
	}

	return res;
}


/*
面试题 17.09. 第 k 个数
难度中等13
有些数的素因子只有 3，5，7，请设计一个算法找出第 k 个数。注意，不是必须有这些素因子，而是必须不包含其他的素因子。例如，前几个数按顺序应该是 1，3，5，7，9，15，21。
示例 1:
输入: k = 5

输出: 9

*/

int getKthMagicNumber(int k){
	int rat[] = {3,5,7};
	int ret = 0;
	struct PriorityQueue *pq =  priorityQueue_init(1024,  PRIORITY_QUEUE_MIN);
	struct DataEntry node;
	node.key = 1;
	priorityQueue_push(pq, node);
	while(k-- && !priorityQueue_isEmpty(pq)) {
		struct DataEntry top =  priorityQueue_pop(pq);
		ret = top.key;
		for(int i = 0; i < 3 ;i++) {
			struct DataEntry node;
			node.key = top.key * rat[i];
			priorityQueue_push_sole(pq, node);
		}
	}

	return ret;
}