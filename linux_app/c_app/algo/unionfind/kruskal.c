/*
克鲁斯卡尔算法
最小生成树
从边的视角

主体:unionFind
对所有边排序或者全部放入heap
*/

struct Edge{
    int cost;
    int start;
    int end;
};

struct Edge edges[N];


/*
1584. 连接所有点的最小费用
给你一个points 数组，表示 2D 平面上的一些点，其中 points[i] = [xi, yi] 。
连接点 [xi, yi] 和点 [xj, yj] 的费用为它们之间的 曼哈顿距离 ：
|xi - xj| + |yi - yj| ，其中 |val| 表示 val 的绝对值。
请你返回将所有点连接的最小总费用。只有任意两点之间 有
且仅有 一条简单路径时，才认为所有点都已连接。
示例 1：
输入：points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
输出：20
解释：
我们可以按照上图所示连接所有点得到最小总费用，
总费用为 20 。
注意到任意两个点之间只有唯一一条路径互相到达。
*/
struct Edge{
    int start;
    int end;
    int w;
};

int cmp_struct(const void *a, const void *b)
{
	struct Edge* aa = (struct Edge*)a;
	struct Edge* bb = (struct Edge*)b;
	return aa->w - bb->w;
}

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize)
{
	int res = 0;
	int start, end, w;

	if (pointsSize < 2) {
		return 0;
	}

	int edgeSize = (pointsSize * (pointsSize - 1))/2;
	struct Edge edges[edgeSize];
	int size = 0;
	for(int i = 0; i < pointsSize; i++){
		for(int j = i + 1; j < pointsSize; j++){
			edges[size].start = i;
			edges[size].end = j;
			edges[size++].w = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
		}
	}

	qsort(edges, edgeSize, sizeof(edges[0]), cmp_struct);

	struct UnionFind duf;
	struct UnionFind *uf = &duf;
	uf_init(uf, pointsSize);

	int pos = 0;
	while(uf->sideCnt > 1){
		start = edges[pos].start;
		end = edges[pos].end;
		w = edges[pos].w;

		if (!uf_isOneUnion(uf, start, end)) {
			uf_union(uf, start, end);
			res += w;
		}

		pos++;
	}

	return res;
}

