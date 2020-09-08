/*
373. ���Һ���С��K������
�����������������е��������� nums1 �� nums2, �Լ�һ������ k��
����һ��ֵ (u,v)�����е�һ��Ԫ������ nums1��
�ڶ���Ԫ������ nums2��
�ҵ�����С�� k ������ (u1,v1), (u2,v2) ... (uk,vk)��
ʾ�� 1:

����: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
���: [1,2],[1,4],[1,6]
����: ���������е�ǰ 3 ������
     [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
ʾ�� 2:
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
264. ���� II
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
������ 17.09. �� k ����
�Ѷ��е�13
��Щ����������ֻ�� 3��5��7�������һ���㷨�ҳ��� k ������
ע�⣬���Ǳ�������Щ�����ӣ����Ǳ��벻���������������ӡ�
���磬ǰ��������˳��Ӧ���� 1��3��5��7��9��15��21��
ʾ�� 1:
����: k = 5

���: 9

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
378. ��������е�KС��Ԫ��
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
295. ����������λ��
bseach
*/

/*
����"��һ��Ԫ��"�������е�����Ϊ 0 �Ļ���
�򸸽ڵ���ӽڵ��λ�ù�ϵ���£�
(01) ����Ϊi�����ӵ������� (2*i+1);
(02) ����Ϊi�����ӵ������� (2*i+2);
(03) ����Ϊi�ĸ����������� floor((i-1)/2);

����ѵĺ�����"��ӽڵ�"��"ɾ���ڵ�"

��KСԪ�� ----���ջ
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


