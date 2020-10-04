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

MedianFinder* medianFinderCreate()
{
	MedianFinder *obj = (MedianFinder *)calloc(1, sizeof(MedianFinder));
	obj->maxheap = heapInit(10240);
	obj->minheap = heapInit(10240);
	return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num)
{
	struct heapEntry node;
	node.key = num;
	maxheapPush(obj->maxheap, node);

	// balancing step
	struct heapEntry maxtop = maxheapPop(obj->maxheap);
	minheapPush(obj->minheap, maxtop);

	 // maintain size property
	 if (heapSize(obj->maxheap) < heapSize(obj->minheap)) {
		struct heapEntry mintop = minheapPop(obj->minheap);
		maxheapPush(obj->maxheap, mintop);
	 }
}

double medianFinderFindMedian(MedianFinder* obj)
{
	if (heapSize(obj->maxheap)  > heapSize(obj->minheap)) {
		return obj->maxheap->node[0].key;
	} else {
		return (obj->maxheap->node[0].key + obj->minheap->node[0].key) * 0.5;
	}
}

void medianFinderFree(MedianFinder* obj) {

}

/*
218. ���������
���е�������Ǵ�Զ���ۿ��ó��������н������γɵ�������
�ⲿ���������ڣ�����������˳��з����Ƭ��ͼA������ʾ
�����н������λ�ú͸߶ȣ����дһ���������������Щ
�������γɵ�����ߣ�ͼB����

Buildings Skyline Contour

ÿ��������ļ�����Ϣ����Ԫ�� [Li��Ri��Hi] ��ʾ������ Li �� Ri
�ֱ��ǵ� i �����������ұ�Ե�� x ���꣬Hi ����߶ȡ����Ա�
֤ 0 �� Li, Ri �� INT_MAX, 0 < Hi �� INT_MAX �� Ri - Li > 0�������Լ�������
�����ﶼ���ھ���ƽ̹�Ҹ߶�Ϊ 0 �ı����ϵ��������Ρ�

���磬ͼA�����н�����ĳߴ��¼Ϊ��
[ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] ��

������� [ [x1,y1], [x2, y2], [x3, y3], ... ] ��ʽ�ġ��ؼ��㡱��ͼB�еĺ�
�㣩���б�����Ψһ�ض���������ߡ��ؼ�����ˮƽ�߶�
����˵㡣��ע�⣬���Ҳཨ��������һ���ؼ��������
�������ߵ��յ㣬��ʼ��Ϊ��߶ȡ����⣬�κ���������
������֮��ĵ��涼Ӧ����Ϊ�����������һ���֡�

���磬ͼB�е������Ӧ�ñ�ʾΪ��
[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ]��
*/
int comp_array(const void *a,const void *b)
{
	if (((int *)a)[0] != ((int *)b)[0]) {
		return ((int *)a)[0]-((int *)b)[0];//first cow
	} else {
		return ((int *)a)[1]-((int *)b)[1];//Second column
	}
}

int** getSkyline(int** buildings, int buildingsSize, int* buildingsColSize,
	int* returnSize, int** returnColumnSizes)
{
	*returnSize = 0;

	if (buildings == NULL || buildingsSize <= 0) {
		return NULL;
	}

	int point[buildingsSize * 2][2];
	int pointCnt = 0;
	for (int i = 0; i < buildingsSize; i++) {
		point[pointCnt][0] = buildings[i][0];
		point[pointCnt++][1] = -buildings[i][2];

		point[pointCnt][0] = buildings[i][1];
		point[pointCnt++][1] = buildings[i][2];
	}

	qsort(point, pointCnt, sizeof(point[0]), comp_array);
	int **res = (int **)calloc(pointCnt, sizeof(int *));
	*returnColumnSizes = (int *)calloc(pointCnt, sizeof(int));

	struct HeapCtrl *hp = heapInit(pointCnt);

	int lastMaxHeight = 0;
	for (int i = 0; i < pointCnt; i++) {
		if (point[i][1] < 0) {
			struct heapEntry node;
			node.x = point[i][0];
			node.key = -point[i][1];
			heapPush(hp, node);// ��˵㣬�߶����
		} else {
			/*
			�Ҷ˵㲻һ������ֵ
			�Ҷ˵㣬�Ƴ��߶�
			*/
			maxheap_remove(hp, point[i][1]);
		}

		if (heapEmpty(hp)) {
			hp->node[0].key = 0;
		}

		int curMaxHeight = hp->node[0].key;
		if (curMaxHeight != lastMaxHeight) {
			res[*returnSize] = (int *)calloc(2, sizeof(int));
			res[*returnSize][0] = point[i][0];
			res[*returnSize][1] = curMaxHeight;
			(*returnColumnSizes)[*returnSize] = 2;
			(*returnSize)++;

			lastMaxHeight = curMaxHeight;
		}
	}

	return res;
}

/*
1499. ���㲻��ʽ�����ֵ
����һ������ points ��һ������ k ��������ÿ��Ԫ�ض���ʾ��ά
ƽ���ϵĵ�����꣬�����պ����� x ��ֵ��С��������Ҳ
����˵ points[i] = [xi, yi] �������� 1 <= i < j <= points.length ��ǰ���£� xi < xj
�ܳ�����
�����ҳ� yi + yj + |xi - xj| �� ���ֵ������
|xi - xj| <= k �� 1 <= i < j <= points.length��
��Ŀ�������ݱ�֤���ٴ���һ���ܹ����� |xi - xj| <= k �ĵ㡣
ʾ�� 1��
���룺points = [[1,3],[2,0],[5,10],[6,-10]], k = 1
�����4
���ͣ�ǰ���������� |xi - xj| <= 1 �����뷽�̼��㣬��õ�ֵ
3 + 0 + |1 - 2| = 4 ���������͵��ĸ���Ҳ�����������õ�ֵ
10 + -10 + |5 - 6| = 1 ��
û���������������ĵ㣬���Է��� 4 �� 1 �������Ǹ���
*/

int findMaxValueOfEquation(int** points, int pointsSize, int* pointsColSize, int k)
{
	int res = INT_MIN;
	struct HeapCtrl *hp = heapInit(pointsSize);

	for (int j = 0; j < pointsSize; j++) {
		//�������ڳ��ȵľ� ����
		while(!heapEmpty(hp) && (points[j][0] - points[hp->node[0].xidx][0] > k))
			heapPop(hp);

		//���㵱ǰ�����ڵ����ֵ
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

