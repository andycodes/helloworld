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
218. 天际线问题
城市的天际线是从远处观看该城市中所有建筑物形成的轮廓的
外部轮廓。现在，假设您获得了城市风光照片（图A）上显示
的所有建筑物的位置和高度，请编写一个程序以输出由这些
建筑物形成的天际线（图B）。

Buildings Skyline Contour

每个建筑物的几何信息用三元组 [Li，Ri，Hi] 表示，其中 Li 和 Ri
分别是第 i 座建筑物左右边缘的 x 坐标，Hi 是其高度。可以保
证 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX 和 Ri - Li > 0。您可以假设所有
建筑物都是在绝对平坦且高度为 0 的表面上的完美矩形。

例如，图A中所有建筑物的尺寸记录为：
[ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] 。

输出是以 [ [x1,y1], [x2, y2], [x3, y3], ... ] 格式的“关键点”（图B中的红
点）的列表，它们唯一地定义了天际线。关键点是水平线段
的左端点。请注意，最右侧建筑物的最后一个关键点仅用于
标记天际线的终点，并始终为零高度。此外，任何两个相邻
建筑物之间的地面都应被视为天际线轮廓的一部分。

例如，图B中的天际线应该表示为：
[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ]。
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
			heapPush(hp, node);// 左端点，高度入堆
		} else { //right side
			/*
			右端点不一定是最值
			右端点，移除高度
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
1499. 满足不等式的最大值
给你一个数组 points 和一个整数 k 。数组中每个元素都表示二维
平面上的点的坐标，并按照横坐标 x 的值从小到大排序。也
就是说 points[i] = [xi, yi] ，并且在 1 <= i < j <= points.length 的前提下， xi < xj
总成立。
请你找出 yi + yj + |xi - xj| 的 最大值，其中
|xi - xj| <= k 且 1 <= i < j <= points.length。
题目测试数据保证至少存在一对能够满足 |xi - xj| <= k 的点。
示例 1：
输入：points = [[1,3],[2,0],[5,10],[6,-10]], k = 1
输出：4
解释：前两个点满足 |xi - xj| <= 1 ，代入方程计算，则得到值
3 + 0 + |1 - 2| = 4 。第三个和第四个点也满足条件，得到值
10 + -10 + |5 - 6| = 1 。
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

/*
767. 重构字符串
给定一个字符串S，检查是否能重新排布其中的字母，使得两相邻的字符不同。

若可行，输出任意可行的结果。若不可行，返回空字符串。

示例 1:

输入: S = "aab"
输出: "aba"
示例 2:

输入: S = "aaab"
输出: ""
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
// 开始填充
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
            if (j + 2 >= len) {  //此分支只会出现一次，画一下就清楚了
                j = 1;
            } else {
                j += 2;
            }
        }
    }

    return S;
}

/*
1642. 可以到达的最远建筑
给你一个整数数组 heights ，表示建筑物的高度。另有一些砖块 bricks 和梯子 ladders 。

你从建筑物 0 开始旅程，不断向后面的建筑物移动，期间可能会用到砖块或梯子。

当从建筑物 i 移动到建筑物 i+1（下标 从 0 开始 ）时：

如果当前建筑物的高度 大于或等于 下一建筑物的高度，则不需要梯子或砖块
如果当前建筑的高度 小于 下一个建筑的高度，您可以使用 一架梯子 或 (h[i+1] - h[i]) 个砖块
如果以最佳方式使用给定的梯子和砖块，返回你可以到达的最远建筑物的下标（下标 从 0 开始 ）
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
1054. 距离相等的条形码
在一个仓库里，有一排条形码，其中第 i 个条形码为 barcodes[i]。

请你重新排列这些条形码，使其中两个相邻的条形码 不能 相等。 你可以返回任何满足该要求的答案，此题保证存在答案。



示例 1：

输入：[1,1,1,2,2,2]
输出：[2,1,2,1,2,1]
*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAX_CNT 10001
typedef struct {
    int cnt;  /* 数字个数 */
    int num;  /* 数字的值 */
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
    /* 已经排序完成，先放奇数位子，然后再放偶数位子 */
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
    /* 奇数放完后排序，然后把剩余的放在偶数位 */
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
