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
		if (point[i][1] < 0) {//left side
			struct heapEntry node;
			node.x = point[i][0];
			node.key = -point[i][1];
			heapPush(hp, node);// ��˵㣬�߶����
		} else { //right side
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

/*
767. �ع��ַ���
����һ���ַ���S������Ƿ��������Ų����е���ĸ��ʹ�������ڵ��ַ���ͬ��

�����У����������еĽ�����������У����ؿ��ַ�����

ʾ�� 1:

����: S = "aab"
���: "aba"
ʾ�� 2:

����: S = "aaab"
���: ""
*/

struct tagNode{
    int cnt;
    char val;
};

int compare(const void *a, const void *b)
{
    return (*(struct tagNode *)a).cnt - (*(struct tagNode *)b).cnt;
}



char * reorganizeString(char * S){


if(S == NULL)
    return NULL;

struct tagNode hash[26] = {0};
int len = strlen(S);
int i, j;
char *ret = (char *)calloc(len+1, sizeof(char));


for(i=0; i<26; i++)
{
    hash[i].cnt = 0;
}

for(i=0; i<len; i++)
{
    hash[S[i] - 'a'].cnt++;
    hash[S[i] - 'a'].val = S[i];
}

//printf("%d %d\n", hash[0].cnt, hash[1].cnt);

qsort(hash, 26, sizeof(struct tagNode), compare);

//printf("%c cnt:%d %c cnt:%d %c cnt:%d\n", hash[25].val, hash[25].cnt, hash[24].val, hash[24].cnt, hash[23].val, hash[23].cnt);


if(hash[25].cnt > (len+1)/2)
{
    return "";
}

//printf("len: %d", len);

int ptr = 0;
// ��ʼ���
for(i=25; i>=0; i--)
{
    for(j=0; j<hash[i].cnt; j++, ptr+=2)
    {
        if(ptr >= len)
            ptr = 1;
        ret[ptr] = hash[i].val;
    }
}

return ret;


}

#define MAXNUM 26
typedef struct {
int num;
char key;
}NodeMap;

int CombFun(const void *a, const void *b)
{
NodeMap *nodeA = (NodeMap *)a;
NodeMap *nodeB = (NodeMap *)b;

return nodeB->num - nodeA->num;
}

char * reorganizeString(char * S){
if (S == NULL) {
return NULL;
}
NodeMap nodeMap[MAXNUM] = {0};
int i;
int len = strlen(S);
char *outPut = NULL;
bool result = false;
int count = 0;
int validNum = 0;

outPut = (char *)calloc(len + 1, sizeof(char));
for (i = 0; i < MAXNUM; i++) {
    nodeMap[i].key = 'a' + i;
}
for (i = 0; i < len; i++) {
    nodeMap[S[i] - 'a'].num++;
}

while (1) {
    qsort(nodeMap, MAXNUM, sizeof(NodeMap), CombFun);
    if(nodeMap[0].num == 0) {
        break;
    }
     for (i = 0; i < 2; i++) {
        if (i < MAXNUM && nodeMap[i].num != 0) {
            nodeMap[i].num--;
            outPut[count++] = nodeMap[i].key;
            validNum++;
            if (validNum == len) {
                break;
            }
        } else {
            outPut[0] = '\0';
            return outPut;
        }
    }
}

return outPut;
}

typedef struct Hash {
    char alph;
    int num;
} hash;

int cmp(const void* a, const void* b) {
    hash* A = (hash*)a;
    hash* B = (hash*)b;
    return B->num - A->num;
}

char * reorganizeString(char * S){
    int i, j = 0, cnt;
    if (S == "") {
        return S;
    }

    hash hashTable[26] = {0};
    int len = strlen(S);
    for (int i = 0; i < len; i++) {
        hashTable[S[i] - 'a'].alph = S[i];
        hashTable[S[i] - 'a'].num++;
    }
    qsort(hashTable, 26,  sizeof(hash), cmp);
    if (hashTable[0].num > (len + 1) / 2) {
        return "";
    }

    for (i = 0; i < 26; i++) {
        cnt = hashTable[i].num;
        if (cnt == 0) {
            break;
        }
        char alph = hashTable[i].alph;
        while (cnt--) {
            S[j] = alph;
            if (j + 2 >= len) {  //�˷�ֻ֧�����һ�Σ���һ�¾������
                j = 1;
            } else {
                j += 2;
            }
        }
    }

    return S;
}

/*
1642. ���Ե������Զ����
����һ���������� heights ����ʾ������ĸ߶ȡ�����һЩש�� bricks ������ ladders ��

��ӽ����� 0 ��ʼ�ọ́����������Ľ������ƶ����ڼ���ܻ��õ�ש������ӡ�

���ӽ����� i �ƶ��������� i+1���±� �� 0 ��ʼ ��ʱ��

�����ǰ������ĸ߶� ���ڻ���� ��һ������ĸ߶ȣ�����Ҫ���ӻ�ש��
�����ǰ�����ĸ߶� С�� ��һ�������ĸ߶ȣ�������ʹ�� һ������ �� (h[i+1] - h[i]) ��ש��
�������ѷ�ʽʹ�ø��������Ӻ�ש�飬��������Ե������Զ��������±꣨�±� �� 0 ��ʼ ��
*/
int furthestBuilding(int* heights, int heightsSize, int bricks, int ladders)
{
	struct HeapCtrl *hp = heapInit(ladders + 1);

	int sumh = 0;
	for (int i = 1; i < heightsSize; i++) {
		int diffhigh = heights[i] - heights[i - 1];
		if (diffhigh <= 0) {
			continue;
		}

		struct heapEntry node;
		node.key = diffhigh;
		heapPush(hp, node);

		if (heapSize(hp) > ladders) {
			sumh += heapTop(hp);
			heapPop(hp);
		}

		if (sumh > bricks) {
			return i - 1;
		}
	}

	return heightsSize - 1;
}

/*
1054. ������ȵ�������
��һ���ֿ����һ�������룬���е� i ��������Ϊ barcodes[i]��

��������������Щ�����룬ʹ�����������ڵ������� ���� ��ȡ� ����Է����κ������Ҫ��Ĵ𰸣����Ᵽ֤���ڴ𰸡�



ʾ�� 1��

���룺[1,1,1,2,2,2]
�����[2,1,2,1,2,1]
*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAX_CNT 10001
typedef struct {
    int cnt;  /* ���ָ��� */
    int num;  /* ���ֵ�ֵ */
}DATA;
DATA g_array[MAX_CNT];
int cmp(void* a, void* b)
{
    DATA* aa = (DATA*)a;
    DATA* bb = (DATA*)b;
    if (aa->cnt == bb->cnt) {
        return bb->num - aa->num;
    }
    return bb->cnt - aa->cnt;
}
int* rearrangeBarcodes(int* barcodes, int barcodesSize, int* returnSize){
    *returnSize = barcodesSize;
    if (barcodesSize < 3) {
        return barcodes;
    }
    memset(g_array, 0, sizeof(DATA));
    for (int i = 0; i < barcodesSize; i++) {
        g_array[barcodes[i]].cnt++;
        g_array[barcodes[i]].num = barcodes[i];
    }
    qsort(g_array, MAX_CNT, sizeof(DATA), cmp);
    memset(barcodes, 0, sizeof(int));
    /* �Ѿ�������ɣ��ȷ�����λ�ӣ�Ȼ���ٷ�ż��λ�� */
    int i = 0;
    int j = 0;
    while (i < barcodesSize) {
        if (j > MAX_CNT) {
            break;
        }
        if (g_array[j].cnt > 0) {
            barcodes[i] = g_array[j].num;
            g_array[j].cnt--;
            i += 2;
        } else {
            j++;
        }
    }
    i = 1;
    /* �������������Ȼ���ʣ��ķ���ż��λ */
    while (i < barcodesSize) {
        if (j > MAX_CNT) {
            break;
        }
        if (g_array[j].cnt > 0) {
            barcodes[i] = g_array[j].num;
            g_array[j].cnt--;
            i += 2;
        } else {
            j++;
        }
    }
    return barcodes;
}
