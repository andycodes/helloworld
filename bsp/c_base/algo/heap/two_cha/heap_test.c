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

/*
218. ���������
���е�������Ǵ�Զ���ۿ��ó��������н������γɵ��������ⲿ���������ڣ�����������˳��з����Ƭ��ͼA������ʾ�����н������λ�ú͸߶ȣ����дһ���������������Щ�������γɵ�����ߣ�ͼB����

Buildings Skyline Contour

ÿ��������ļ�����Ϣ����Ԫ�� [Li��Ri��Hi] ��ʾ������ Li �� Ri �ֱ��ǵ� i �����������ұ�Ե�� x ���꣬Hi ����߶ȡ����Ա�֤ 0 �� Li, Ri �� INT_MAX, 0 < Hi �� INT_MAX �� Ri - Li > 0�������Լ������н����ﶼ���ھ���ƽ̹�Ҹ߶�Ϊ 0 �ı����ϵ��������Ρ�

���磬ͼA�����н�����ĳߴ��¼Ϊ��[ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] ��

������� [ [x1,y1], [x2, y2], [x3, y3], ... ] ��ʽ�ġ��ؼ��㡱��ͼB�еĺ�㣩���б�����Ψһ�ض���������ߡ��ؼ�����ˮƽ�߶ε���˵㡣��ע�⣬���Ҳཨ��������һ���ؼ�������ڱ������ߵ��յ㣬��ʼ��Ϊ��߶ȡ����⣬�κ��������ڽ�����֮��ĵ��涼Ӧ����Ϊ�����������һ���֡�

���磬ͼB�е������Ӧ�ñ�ʾΪ��[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ]��
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

    // �ڵ�x����
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
    step 1 �ҳ��������������ϡ����ϵĵ㣬����vetex�С����ϵĵ㣬��ȡ����
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
    ���Զ�
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
    step 2 ɨ���ߴ�������ɨ�裬��ȡת�۵�
    1)ɨ�赽���������߽�ʱ�����ߴ����
    2)ɨ�赽��������ұ߽�ʱ�����ߴӶ���ȡ��
    3)�����롢ȡ��ʱ�����߶ȷ����仯ʱ������ת�۵㡣����µ�height��ת�۵�Ϊ ��ǰ�ڵ㣬height
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