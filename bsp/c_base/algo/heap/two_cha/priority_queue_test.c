/*
��дһ�������ҳ��� n ��������

��������ֻ���������� 2, 3, 5 ����������

ʾ��:

����: n = 10
���: 12
����: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 ��ǰ 10 ��������
˵��:

1 �ǳ�����
n ������1690��

*/


/*
�ؼ�˼·����һ����С����

2��������С�ѣ�����1�����
Ȼ��ÿ���öѶ���С���ٳ�һ��2��3��5��
Ȼ���Ӷ��ֱ���öѶ�����Ϊn��
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
��Ŀ����
���� (62)
���(42)
�ύ��¼
373. ���Һ���С��K������
�����������������е��������� nums1 �� nums2, �Լ�һ������ k��

����һ��ֵ (u,v)�����е�һ��Ԫ������ nums1���ڶ���Ԫ������ nums2��

�ҵ�����С�� k ������ (u1,v1), (u2,v2) ... (uk,vk)��

ʾ�� 1:

����: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
���: [1,2],[1,4],[1,6]
����: ���������е�ǰ 3 ������
     [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
ʾ�� 2:

����: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
���: [1,1],[1,1]
����: ���������е�ǰ 2 ������
     [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
ʾ�� 3:

����: nums1 = [1,2], nums2 = [3], k = 3
���: [1,3],[2,3]
����: Ҳ�������������е����Զ�������:[1,3],[2,3]

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
������ 17.09. �� k ����
�Ѷ��е�13
��Щ����������ֻ�� 3��5��7�������һ���㷨�ҳ��� k ������ע�⣬���Ǳ�������Щ�����ӣ����Ǳ��벻���������������ӡ����磬ǰ��������˳��Ӧ���� 1��3��5��7��9��15��21��
ʾ�� 1:
����: k = 5

���: 9

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