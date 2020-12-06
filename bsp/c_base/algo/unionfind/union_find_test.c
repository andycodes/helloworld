
/*
1391. 检查网格中是否存在有效路径
给你一个 m x n 的网格 grid。网格里的每个单元都代表一条街道。
grid[i][j] 的街道可以是：
1 表示连接左单元格和右单元格的街道。
2 表示连接上单元格和下单元格的街道。
3 表示连接左单元格和下单元格的街道。
4 表示连接右单元格和下单元格的街道。
5 表示连接左单元格和上单元格的街道。
6 表示连接右单元格和上单元格的街道。
*/
/*
     0
     ^
     |
3 <-- --> 1
     |
     v
     2

这样编号的好处是什么呢？可以发现，只有在这些情况下，
两个相邻的单元格才能相连：
如果某一个单元格有第 00 个方向，那么它上方的单元格必须
有第 22 个方向；
如果某一个单元格有第 11 个方向，那么它右侧的单元格必
须有第 33 个方向；
如果某一个单元格有第 22 个方向，那么它下方的单元格必须
有第 00 个方向；
如果某一个单元格有第 33 个方向，那么它左侧的单元格必须
有第 11 个方向。
发现了什么规律？
如果某一个单元格有第 ii 个方向，那么它在第 ii 个方向相邻的
单元格必须有第 (i + 2) \% 4(i+2)%4 个方向。
因此，我们遍历整个网格，对于其中的每一个单元格 (x, y)(x,y)，
我们枚举它的四个相邻的单元格，对于第 ii 个方向的相邻单元
格，它和 (x, y)(x,y) 相连当且仅当 (x, y)(x,y) 对应的二进制数的第 ii 位
和相邻单元格对应的二进制数的第 (i + 2) % 4 位均为 11。
在遍历结束之后，我们判断左上角和右下角在并查集中是否
属于同一集合即可。
*/

int patterns[7] = {0, 0b1010, 0b0101, 0b1100, 0b0110, 0b1001, 0b0011};
int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int dimenMap(int x, int y, int colSize)
{
	return x * colSize+ y;
}

void hander(struct UnionFind* uf, int** grid, int row, int col, int x, int y)
{
        for (int i = 0; i < 4; ++i) {// 4 bit 四个方向
	    	if ((patterns[grid[x][y]] & (1 << i)) == 0)
				continue;//自己不通

		//each set bit
		int nx = x + dirs[i][0];
		int ny = y + dirs[i][1];
		if (nx >= 0 && nx < row && ny >= 0 && ny < col &&
			(patterns[grid[nx][ny]] & (1 << ((i + 2) % 4)))) {
			uf_union(uf, dimenMap(x, y, col), dimenMap(nx, ny, col));
		}
        }
}

bool hasValidPath(int** grid, int gridSize, int* gridColSize)
{
	int row = gridSize;
	int col = gridColSize[0];

	struct UnionFind duf;
	struct UnionFind *uf = &duf;
	uf_init(uf, row * col);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                hander(uf, grid, row, col, i, j);
            }
        }

	return uf_isOneUnion(uf, dimenMap(0, 0, col), dimenMap(row - 1, col - 1, col));
}


/*
1102. 得分最高的路径
BFS
*/
typedef struct {
    int x;
    int y;
    int value;
} Node;

int NodeCmp (const void *p1, const void *p2)
{
    return (((Node *)p2)->value - ((Node*)p1)->value);
}

int maximumMinimumPath(int** A, int ASize, int* AColSize)
{
	int matrixSize = ASize * (*AColSize);
	int visited[matrixSize];
	Node nodeSet[matrixSize];//matrixSize个集合
	memset(visited, 0, sizeof(visited));
	memset(nodeSet,0,sizeof(nodeSet));

	struct UnionFind duf;
	struct UnionFind *uf = &duf;
	uf_init(uf, matrixSize);
	int count = 0;
	for (int i = 0; i < ASize; i++) {
		for (int j = 0; j < (*AColSize); j++) {
			nodeSet[count].x = i;
			nodeSet[count].y = j;
			nodeSet[count].value = A[i][j];
			count++;
		}
	}

	qsort(nodeSet, matrixSize, sizeof(Node), NodeCmp);

	count = 0;
	int ans = fmin(A[0][0], A[ASize - 1][*AColSize - 1]);
	int direction[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
	while (!uf_isOneUnion(uf, 0, matrixSize - 1)) {
		int x = nodeSet[count].x;
		int y = nodeSet[count].y;
		int index = x * (*AColSize) + y;
		visited[index] = 1;
		ans = fmin(ans, nodeSet[count].value);
		for (int i = 0; i < 4; i++) {
			int nx, ny;
			nx = x + direction[i][0];
			ny = y + direction[i][1];
			int indexNew = nx * (*AColSize) + ny;
			if (nx < ASize && nx > -1 && ny < (*AColSize) && ny > -1 && visited[indexNew] == 1) {
				uf_union(uf, index, indexNew);
			}
		}
		count++;
	}
	return ans;
}

/*
959. 由斜杠划分区域
难度中等73
在由 1 x 1 方格组成的 N x N 网格 grid 中，每个 1 x 1 方块由 /、\ 或空
格构成。这些字符会将方块划分为一些共边的区域。
（请注意，反斜杠字符是转义的，因此 \ 用 "\\" 表示。）。
返回区域的数目。

示例 1：
输入：
[
  " /",
  "/ "
]
输出：2
解释：2x2 网格如下：

*/
/*
*0*
1*2
*3*
*/
int regionsBySlashes(char ** grid, int gridSize)
{
        int N = gridSize;

	struct UnionFind duf;
	struct UnionFind* uf = &duf;

	int ufSize = 4 * N * N;
	uf_init(uf, ufSize);
        for (int r = 0; r < N; ++r) //row代表行
            for (int c = 0; c < N; ++c) { //col代表列  两个for遍历grid的每个字符
                int root = 4 * (r * N + c);
                char val = grid[r][c]; //字符

                if (val != '\\') {    //如果为 '/'或者' '则组合（0，1），（2，3）.
                    uf_union(uf, root + 0, root + 1);
                    uf_union(uf, root + 2, root + 3);
                }

                if (val != '/') {    //如果为 '\\'或者' '则组合（0，2），（1，3）
                    uf_union(uf, root + 0, root + 2);
                    uf_union(uf, root + 1, root + 3);
                }
// 如果不是最后一行，则向下归并 ：3 归并下行的0      0
                if (r + 1 < N)
                    uf_union(uf, root + 3, (root + 4 * N) + 0);                //     1    2    1    2
//如果不是第一行，则向上归并：0归并上行的3           3
                if (r - 1 >= 0)
                    uf_union(uf, root + 0, (root - 4 * N) + 3);                  //      0        0
                                                                           //       1   2    1    2
//如果不是最后一列，则向右归并：2归并右邻的1            3         3
		if (c + 1 < N)
                    uf_union(uf, root + 2, (root + 4) + 1);
//如果不是第一列，则向左归并：1归并左邻的2
                if (c - 1 >= 0)
                    uf_union(uf, root + 1, (root - 4) + 2);
            }

        int ans = 0;
        for (int x = 0; x < 4 * N * N; ++x) {
            if (uf_findRoot(uf, x) == x)
                ans++;
        }

        return ans;
    }

/*
685. 冗余连接 II
在本问题中，有根树指满足以下条件的有向图。该树只有一
个根节点，所有其他节点都是该根节点的后继。每一个节点
只有一个父节点，除了根节点没有父节点。
输入一个有向图，该图由一个有着N个节点 (节点值不重复1, 2,
..., N) 的树及一条附加的边构成。附加的边的两个顶点包含在
1到N中间，这条附加的边不属于树中已存在的边。
结果图是一个以边组成的二维数组。 每一个边 的元素是一
对 [u, v]，用以表示有向图中连接顶点 u 和顶点 v 的边，其中
u 是 v 的一个父节点。
返回一条能删除的边，使得剩下的图是有N个节点的有根树。
若有多个答案，返回最后出现在给定二维数组的答案。
示例 1:
输入: [[1,2], [1,3], [2,3]]
输出: [2,3]
解释: 给定的有向图如下:
  1
 / \
v   v
2-->3
*/

/*
先统计各点的入度；第1次遍历入度小于2的点，如果成环，则根据题意，不会存在入度为2的点，则返回当前成环的点；第2次遍历入度大于2的点，如果成环，则根据题意，返回当前成环的点，因为入度大于1的点只可能有1个；作者：ajoy链接：https://leetcode-cn.com/problems/redundant-connection-ii/solution/685rong-yu-lian-jie-ii-by-ajoy/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int Find(int uNums[], int q)
{
    while (uNums[q] != q) {
        uNums[q] = uNums[uNums[q]];
        q = uNums[q];
    }
    return q;
}

void Union(int uNums[], int p, int q)
{
    uNums[Find(uNums, p)] = Find(uNums, q);
}

int* findRedundantDirectedConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize){
    int uNums[edgesSize + 1];
    for (int i = 0; i < edgesSize + 1; i++) {
        uNums[i] = i;
    }
    *returnSize = 2;
    int indegree[edgesSize + 1];
    memset(indegree, 0, (edgesSize + 1) * sizeof(int));
    for (int i = 0; i < edgesSize; i++) {
        indegree[edges[i][1]]++;
    }
    for (int i = 0; i < edgesSize; i++) {
        if (indegree[edges[i][1]] <= 1) {
            if (Find(uNums, edges[i][0]) == Find(uNums, edges[i][1])) {
                return edges[i];
            }
            Union(uNums, edges[i][0], edges[i][1]);
        }
    }
    for (int i = 0; i < edgesSize; i++) {
        if (indegree[edges[i][1]] > 1) {
            if (Find(uNums, edges[i][0]) == Find(uNums, edges[i][1])) {
                return edges[i];
            }
            Union(uNums, edges[i][0], edges[i][1]);
        }
    }
    return NULL;
}

/*
924. 尽量减少恶意软件的传播
在节点网络中，只有当 graph[i][j] = 1 时，每个节点 i 能够直接连接到另一个节点 j。

一些节点 initial 最初被恶意软件感染。只要两个节点直接连接，且其中至少一个节点受到恶意软件的感染，那么两个节点都将被恶意软件感染。这种恶意软件的传播将继续，直到没有更多的节点可以被这种方式感染。

假设 M(initial) 是在恶意软件停止传播之后，整个网络中感染恶意软件的最终节点数。

我们可以从初始列表中删除一个节点。如果移除这一节点将最小化 M(initial)， 则返回该节点。如果有多个节点满足条件，就返回索引最小的节点。

请注意，如果某个节点已从受感染节点的列表 initial 中删除，它以后可能仍然因恶意软件传播而受到感染。
*/
/*
根据题目要求减少恶意软件的传播，大体的意思是要求将该节点删除之后，不受感染的软件数量最多。简单的思考了一下，如果该节点连通的节点数量越多，那么该节点删除之后必然受影响的节点数最多。这是我最开始的一个思路，而且感觉这个思路，发现给出的几个举例都能顺利通过，如果只是这个问题，通过并查集理论上能够快速的搞定，但是发现提交后并没有通过，确实对的起这个问题的难度(困难)。这个题目中只是简单的找某个节点连通的节点最多还不行，为什么呢？因为如果连通的节点中，有多个在传染源中，我们及时找到其中一个将其删除，也不能减少软件被传染的节点数量。因为只要是连通的，那么其中一个的删除，也会被其他连通节点的传染源感染，因此不能简单的直接删除连通节点最多的节点，可行的方法是首先统计传染源节点中在同一个连通域(集合)中的节点个数，如果连通域中的节点数大于1，则该节点不能删除，如果该连通域中的节点数等于1，那么删除该连通域的节点就能减少被感染的节点。不受感染的节点数量最多，那么就是找到连通域中感染源只有1个，连接节点最多的那个感染源就是最终的答案。综合上述的分析可以通过如下的方法解决：1、首先根据当前的链接矩阵，快速的创建一个并查集，需要统计权重（主要是统计合并的个数），同时尽可能的往小的索引合并。2、由于需要输出索引小的感染源，因此按照升级排列感染源。3、根据感染源节点列表计算连通域的感染节点个数。4、根据感染源个数等于1，找到权重最大的，索引最小的感染源，该感染源就是要删除的节点。作者：gpking链接：https://leetcode-cn.com/problems/minimize-malware-spread/solution/jian-shao-e-yi-ruan-jian-de-chuan-bo-bing-cha-ji-d/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

/*
核心思想求出联通子图个数统计各个子图中包含感染节点个数（一个感染节点就足以感染整个子图，所以如果一个子图有多于一个感染节点，那么即使去掉一个，也不会减少受感染节点数）选择子图中节点最多，且只有一个感染节点的结果作者：chaoooooo链接：https://leetcode-cn.com/problems/minimize-malware-spread/solution/cyu-yan-bing-cha-ji-by-chaoooooo/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/


#define MAXPOINTS 301
typedef struct {
    int parent[MAXPOINTS];
    int weight[MAXPOINTS];
    int max;
    int cnt;
} UF_t;

UF_t g_uf;

UF_t *UFInit(int max)
{
    memset(&g_uf, 0, sizeof(UF_t));

    g_uf.max = max;
    g_uf.cnt = max;
    for (int i = 0; i < max; ++i) {
        g_uf.parent[i] = i;
        g_uf.weight[i] = 1;
    }

    return &g_uf;
}

int UFFind(UF_t *uf, int id)
{
    int son = id;

    while (id != uf->parent[id]) {
        id = uf->parent[id];
    }

    while (son != id) { // 路劲压缩
        int tmp = uf->parent[son];
        uf->parent[son] = id;
        son = tmp;
    }

    return id;
}

void UFUnion(UF_t *uf, int id1, int id2)
{
    int id1Root = UFFind(uf, id1);
    int id2Root = UFFind(uf, id2);

    if (id1Root == id2Root) {
        return;
    }

    if (id1Root < id2Root) {
        uf->parent[id2Root] = id1Root;
        uf->weight[id1Root] += uf->weight[id2Root]; // 计算出节点的权重
    } else {
        uf->parent[id1Root] = id2Root;
        uf->weight[id2Root] += uf->weight[id1Root];
    }

    uf->cnt--;
}

int UFCount(UF_t *uf)
{
    return uf->cnt;
}

int UFWeight(UF_t *uf, int id)
{
    int root = UFFind(uf, id);
    return uf->weight[root];
}

int UFSize(UF_t *uf)
{
    return uf->max;
}

int CheckParam(int **graph, int graphSize, int *graphColSize, int *initial, int initialSize)
{
    if (graph == NULL || graphSize <= 0 || graphColSize == NULL || initial == NULL || initialSize <= 0) {
        return -1;
    }

    if (graphColSize[0] <= 0) {
        return -1;
    }

    return 0;
}

UF_t * BuildUF(int **graph, int graphSize, int *graphColSize)
{
    UF_t *uf = UFInit(graphSize);

    for (int i = 0; i < graphSize; ++i) {
        for (int j = i + 1; j < graphSize; ++j) {
            if (graph[i][j] == 1) {
                UFUnion(uf, i, j); // 合并连通域
            }
        }
    }

    return uf;
}

int InitCmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int Search(UF_t *uf, int *initial, int initialSize)
{
    if (UFCount(uf) == 1) {
        return initial[0];
    }

    int count[MAXPOINTS] = {0};
    for (int i = 0; i < initialSize; ++i) {
        int rootId = UFFind(uf, initial[i]);
        count[rootId]++; // 基于连通域统计感染源
    }

    int weight = -1;
    int index = -1;
    for (int i = 0; i < UFSize(uf); ++i) {
        if (count[i] == 1) { // 感染源只有1个的连通域
            int w = UFWeight(uf, i);
            if (w > weight) { // 找到权重（连通节点）最多的连通域
                weight = w;
                index = i;
            }
        }
    }

    if (index != -1) { // 找到连通域
        for (int i = 0; i < initialSize; ++i) {
            int rootId = UFFind(uf, initial[i]);
            if (rootId == index) { // 再从感染源节点中找到符合连通域的节点，然后返回感染源索引即可。
                return initial[i];
            }
        }
    }

    return initial[0]; // 如果找不到满足要求的连通域，那么删除任何一个节点都无法解决问题，因此输出最小的索引。
}

int minMalwareSpread(int **graph, int graphSize, int *graphColSize, int *initial, int initialSize)
{
    if (CheckParam(graph, graphSize, graphColSize, initial, initialSize)) {
        return -1;
    }

    if (initialSize == 1) {
        return initial[0]; // 只有一个节点直接返回即可，不管是否有用。
    }

    UF_t * uf = BuildUF(graph, graphSize, graphColSize);
    qsort(initial, initialSize, sizeof(int), InitCmp);
    return Search(uf, initial, initialSize);
}


