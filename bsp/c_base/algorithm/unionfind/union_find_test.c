/*
684. 冗余连接
难度中等82
在本问题中, 树指的是一个连通且无环的无向图。
输入一个图，该图由一个有着N个节点 (节点值不重复1, 2, ..., N) 的树及一条附加的边构成。附加的边的两个顶点包含在1到N中间，这条附加的边不属于树中已存在的边。
结果图是一个以边组成的二维数组。每一个边的元素是一对[u, v] ，满足 u < v，表示连接顶点u 和v的无向图的边。
返回一条可以删去的边，使得结果图是一个有着N个节点的树。如果有多个答案，则返回二维数组中最后出现的边。答案边 [u, v] 应满足相同的格式 u < v。
示例 1：
输入: [[1,2], [1,3], [2,3]]
输出: [2,3]
解释: 给定的无向图为:
  1
 / \
2 - 3

*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 /**
 * Note: The returned array must be malloced, assume caller calls free().
 */
/*
遍历所有的边edges，将连通的结点放入同一个集合，
形成一个联通分量GG。
在遍历的过程中，
如果边(a, b)(a,b)的两个结点aa, bb已经属于同一联通分量，
则(a, b)(a,b)就是该联通分量的冗余边。

如前面所述，我们可以遍历每一条边，
而遍历到该条边时我们如果查询这条边
左右两个顶点所在到树之根节点相同，
即代表两个顶点在同一棵树，
故该条边为当前情况「不必要的边」。

如果那一条边是必要的，
那代表两个顶点代表着两颗不同的树，
此时我们将他们合并为同一棵。

*/
int* findRedundantConnection(int** edges, int edgesSize,
int* edgesColSize, int* returnSize){
	int *res = (int *)calloc(2, sizeof(int));
	*returnSize = 2;

	uf_init(MAX);
	for (int i = 0; i < edgesSize; i++) {
		if (uf_isOneUnion(edges[i][0], edges[i][1])) {
			res[0] = edges[i][0];
			res[1] = edges[i][1];
		} else {
			uf_union(edges[i][0], edges[i][1]);
		}
	}

	return res;
}

/*
1319. 连通网络的操作次数
难度中等15
用以太网线缆将 n 台计算机连接成一个网络，计算机的编号从 0 到 n-1。线缆用 connections 表示，其中 connections[i] = [a, b] 连接了计算机 a 和 b。
网络中的任何一台计算机都可以通过网络直接或者间接访问同一个网络中其他任意一台计算机。
给你这个计算机网络的初始布线 connections，你可以拔开任意两台直连计算机之间的线缆，并用它连接一对未直连的计算机。请你计算并返回使所有计算机都连通所需的最少操作次数。如果不可能，则返回 -1 。

示例 1：

输入：n = 4, connections = [[0,1],[0,2],[1,2]]
输出：1
解释：拔下计算机 1 和 2 之间的线缆，并将它插到计算机 1 和 3 上。
示例 2：

输入：n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
输出：2
示例 3：
输入：n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
输出：-1
解释：线缆数量不足。
示例 4：
输入：n = 5, connections = [[0,1],[0,2],[3,4],[2,3]]
输出：0

*/

/*
1)当计算机的数量为 m 时，我们至少需要 m - 1 根线缆才能将它们进行连接

因此如果数组 connections 的长度小于 n - 1，我们可以直接返回 -1

比较 n - 1 和 len(connections)：

如果前者大于后者，那么一定无解，返回 -1；

如果前者小于等于后者，那么我们统计出图中的连通分量数 k，返回 k - 1。

统计图中连通分量数的方法有很多，我们介绍深度优先搜索和并查集两种方法。

*/
int makeConnected(int n, int** connections, int connectionsSize, int* connectionsColSize)
{
	if (n <= 0 || connections == NULL || connectionsSize <= 0 || connectionsColSize == NULL)
		return 0;

	uf_init(n);

	int cnt = 0;// 多余的线缆数量
	int part = n;//连通分量
	for (int i = 0; i < connectionsSize; i++) {
		int x = connections[i][0];
		int y = connections[i][1];
		// 两个点已经连通，不需要这个线缆
		if (uf_find(x) == uf_find(y)) {
			cnt++;
		}else {
			uf_union(x, y);
			part--;
		}
	}

	if (connectionsSize < n -1)
		return -1;

	return part - 1;
}

