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

