struct Node{
    int val;
    int start;
    int end;
}Node;
Node V[N];

 // 把所有边排序，记第i小的边为e[i] (1<=i<=m)m为边的个数
 // 初始化MST为空
 // 初始化连通分量，使每个点各自成为一个独立的连通分量

 for (int i = 0; i < m; i++)
 {
     if (e[i].u和e[i].v不在同一连通分量)
     {
         // 把边e[i]加入ＭＳＴ
         // 合并e[i].u和e[i].v所在的连通分量
     }
 }

/*
1135. 最低成本联通所有城市
难度中等23
想象一下你是个城市基建规划者，地图上有 N 座城市，
它们按以 1 到 N 的次序编号。
给你一些可连接的选项 conections，其中每个选项 conections[i] =
[city1, city2, cost] 表示将城市 city1 和城市 city2 连接所要的成本。
（连接是双向的，也就是说城市 city1 和城市 city2 相连也同样
意味着城市 city2 和城市 city1 相连）。
返回使得每对城市间都存在将它们连接在一起的连通路
径（可能长度为 1 的）最小成本。该最小成本应该是所用
全部连接代价的综合。如果根据已知条件无法完成该项任
务，则请你返回 -1。

示例 1：

输入：N = 3, conections = [[1,2,5],[1,3,6],[2,3,1]]
输出：6
解释：
选出任意 2 条边都可以连接所有城市，我们从中选取成本最
小的 2 条。

*/

/*
预备知识最小生成树图的生成树是一棵含有其所有的顶点的
无环联通子图，一幅加权图的最小生成树（ MST ） 是它的一
颗权值（树中所有边的权值之和）最小的生成树。
并查集并查集是一种树型的数据结构，用于处理一些不相
交集合的合并及查询问题。常常在使用中以森林来表示。
方法一：kruskal 算法思路根据题意，我们可以把 N 座城市看成
N 个顶点，连接两个城市的成本 cost 就是对应的权重，需要
返回连接所有城市的最小成本。很显然，这是一个标准的
最小生成树，首先我们介绍第一种经典算法： kruskal 算法。
既然我们需要求最小成本，那么可以肯定的是这个图没有
环（如果有环的话无论如何都可以删掉一条边使得成本更
小）。该算法就是基于这个特性：按照边的权重顺序（从
小到大）处理所有的边，将边加入到最小生成树中，
加入的边不会与已经加入的边构成环，直到树中含有 N - 1 条
边为止。这些边会由一片森林变成一个树，这个树就是图
的最小生成树。
*/

 int minimumCost(int N, int** connections, int connectionsSize, int* connectionsColSize)
{
	qsort(connections, connectionsSize, sizeof(connections[0]), cmp_point);
	int cost = 0;

	struct UnionFind duf;
	struct UnionFind* uf = &duf;
	uf_init(uf, N + 1);
	uf->cnt = N;
	for (int i = 0; i < connectionsSize; i++) {
		if (!uf_isOneUnion(uf, connections[i][0], connections[i][1])) {
			uf_union(uf, connections[i][0], connections[i][1]);
			cost += connections[i][2];
		}
	}

	return uf->cnt == 1 ? cost : -1;
}


/*
1584. 连接所有点的最小费用
给你一个points 数组，表示 2D 平面上的一些点，其中 points[i] = [xi, yi] 。

连接点 [xi, yi] 和点 [xj, yj] 的费用为它们之间的 曼哈顿距离 ：|xi - xj| + |yi - yj| ，其中 |val| 表示 val 的绝对值。

请你返回将所有点连接的最小总费用。只有任意两点之间 有且仅有 一条简单路径时，才认为所有点都已连接。



示例 1：



输入：points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
输出：20
解释：

我们可以按照上图所示连接所有点得到最小总费用，总费用为 20 。
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

//Prim算法

int res;

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize){
    res = 0;
    int n = pointsSize;
    bool collected[n];
    int dist[n];    //dist[i]表示i号点到点集的最短距离
    int fee[n][n];  //fee[i][j] 表示i、j连接所需的费用
    memset(collected, 0, sizeof(collected));

    for(int i = 0; i < n; i++){
        fee[i][i] = 0;
        for(int j = i + 1; j < n; j++)
            fee[i][j] = fee[j][i] = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
        }
    //从0号点开始,此时点集只有0
    collected[0] = true;
    for(int i = 0; i < n; i++) dist[i] = fee[i][0];

    while(1){
        int v = -1;
        int mindist = INT_MAX;
        for(int i = 0; i < n; i++){
            if(collected[i]) continue;
            if(dist[i] < mindist){
                mindist = dist[i];
                v = i;
                }
            }
        if(v == -1) break;
        res += mindist;
        collected[v] = true;
        dist[v] = 0;
        for(int i = 0; i < n; i++)  //更新未收录顶点与收录点集的最短距离
            if(!collected[i] && dist[i] > fee[v][i])
                dist[i] = fee[v][i];
        }
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