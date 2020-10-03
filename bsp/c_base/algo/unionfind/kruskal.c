/*
克鲁斯卡尔算法
把所有边排序的unionFind
*/

struct Node{
    int val;
    int start;
    int end;
}Node;
Node V[N];


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
//记录两个点的编号和权值
struct Edge{
    int u;
    int v;
    int w;
};
typedef struct Edge Edge;

//路径压缩
int find(int* S, int x){
    if(S[x] < 0)
        return x;
    else
        return S[x] = find(S, S[x]);
}

//按秩归并
void Union(int* S, int root1, int root2){
    if(S[root1] < S[root2])
        S[root2] = root1;
    else{
        if(S[root1] == S[root2])
            S[root1]--;
        S[root2] = root1;
        }
}

//按权值进行快速排序
void quick_sort(Edge* E, int l, int r){
    if(l >= r) return;
    int i = l - 1, j = r + 1, x = E[l + r >> 1].w;
    while(i < j){
        while(E[++i].w < x);
        while(E[--j].w > x);
        if(i < j){
            Edge tmp;
            tmp.u = E[i].u, tmp.v = E[i].v, tmp.w = E[i].w;
            E[i].u = E[j].u, E[i].v = E[j].v, E[i].w = E[j].w;
            E[j].u = tmp.u, E[j].v = tmp.v, E[j].w = tmp.w;
            }
        }
    quick_sort(E, l, j);
    quick_sort(E, j + 1, r);
}

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize){
    int edges = 0;
    int res = 0;
    int u, v, w;
    int n = pointsSize;
    int* S = (int*)calloc(n, sizeof(int));
    memset(S, -1, sizeof(int) * n);
    Edge* E = (Edge*)calloc((n * (n - 1))/2, sizeof(Edge));
    int size = 0;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            E[size].u = i;
            E[size].v = j;
            E[size++].w = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
            }
        }
    quick_sort(E, 0, size - 1);
    int pos = 0;
    while(edges != n - 1){
        u = E[pos].u;
        v = E[pos].v;
        w = E[pos].w;
        int root1 = find(S, u);
        int root2 = find(S, v);
        if(root1 != root2){
            edges++;
            res += w;
            Union(S, root1, root2);
            }
        pos++;
        }
    free(S);
    free(E);

    return res;
}


/*
1168. 水资源分配优化
村里面一共有 n 栋房子。我们希望通过建造水井和铺设管道来为所有房子供水。

对于每个房子 i，我们有两种可选的供水方案：

一种是直接在房子内建造水井，成本为 wells[i]；
另一种是从另一口井铺设管道引水，数组 pipes 给出了在房子间铺设管道的成本，其中每个 pipes[i] = [house1, house2, cost] 代表用管道将 house1 和 house2 连接在一起的成本。当然，连接是双向的。
请你帮忙计算为所有房子都供水的最低总成本。
*/

int minCostToSupplyWater(int n, int* wells, int wellsSize,
int** pipes, int pipesSize, int* pipesColSize)
{
	struct HeapCtrl *hp = heapInit(wellsSize + pipesSize);
	for (int i = 0; i < wellsSize; i++) {
		struct heapEntry node;
		node.start = i + 1;
		node.end = 0;
		node.key = wells[i];
		heapPush(hp, node);
	}

	for (int i = 0; i < pipesSize; i++) {
		struct heapEntry node;
		node.start = pipes[i][0];
		node.end = pipes[i][1];
		node.key = pipes[i][2];
		heapPush(hp, node);
	}

	struct UnionFind duf;
	struct UnionFind *uf = &duf;
	uf_init(uf, n + 1);

	int cost = 0;
	while(!heapEmpty(hp)) {
		struct heapEntry pop = heapPop(hp);
		if (!uf_isOneUnion(uf, pop.start, pop.end)) {
			uf_union(uf, pop.start, pop.end);
			cost += pop.key;
		}
	}

	return cost;
}