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

	struct UnionFind duf;
	struct UnionFind *uf = &duf;

	uf_init(uf);
	for (int i = 0; i < edgesSize; i++) {
		if (uf_isOneUnion(uf, edges[i][0], edges[i][1])) {
			res[0] = edges[i][0];
			res[1] = edges[i][1];
		} else {
			uf_union(uf, edges[i][0], edges[i][1]);
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

	struct UnionFind duf;
	struct UnionFind *uf = &duf;

	uf_init(uf, n);

	int cnt = 0;// 多余的线缆数量
	int part = n;//连通分量
	for (int i = 0; i < connectionsSize; i++) {
		// 两个点已经连通，不需要这个线缆
		if (uf_isOneUnion(uf, connections[i][0], connections[i][1])) {
			cnt++;
		}else {
			uf_union(uf, connections[i][0], connections[i][1]);
			part--;
		}
	}

	if (connectionsSize < n -1)
		return -1;
	part--;
	return cnt >=  part? part : -1;
}


/*
面试题 17.07. 婴儿名字
难度中等0
每年，政府都会公布一万个最常见的婴儿名字和它们出现
的频率，也就是同名婴儿的数量。有些名字有多种拼法，
例如，John 和 Jon 本质上是相同的名字，但被当成了两个名字
公布出来。给定两个列表，一个是名字及对应的频率，
另一个是本质相同的名字对。设计一个算法打印出每个
真实名字的实际频率。注意，如果 John 和 Jon 是相同的，
并且 Jon 和 Johnny 相同，则 John 与 Johnny 也相同，即它们有传递
和对称性。
在结果列表中，选择字典序最小的名字作为真实名字。
示例：
输入：
names = ["John(15)","Jon(12)","Chris(13)","Kris(4)","Christopher(19)"],
synonyms = ["(Jon,John)","(John,Johnny)","(Chris,Kris)","(Chris,Christopher)"]
输出：["John(27)","Chris(36)"]

*/
#define STR_LEN     50
typedef struct _info_st
{
    char name[STR_LEN];
    char *root;
    int id;
    int cnt;
}info_st;

char** trulyMostPopular(char** names, int namesSize,
char** synonyms, int synonymsSize, int* returnSize)
{
	if(namesSize == 0) {
		*returnSize = 0;
		return NULL;
	}

	info_st *info = (info_st *)calloc(namesSize, sizeof(info_st));
	HashMap * hashmap = hashmap_init(namesSize, 1);
	for(int i = 0; i < namesSize; i++) {
		char *iterator;
		char *p;
		iterator = strtok_r(names[i], "(", &p);
		strcpy(info[i].name, iterator);

		iterator = strtok_r(NULL, ")", &p);
		info[i].cnt = atoi(iterator);

		info[i].root = info[i].name;
		info[i].id = i;

		DataType hashdata;
		hashdata.key = info[i].name;
		hashdata.val = i;
		hashmap_getValue(hashmap, &hashdata);
		if (hashdata.id == -1) {
			hashmap_push(hashmap, hashdata);
		}

		printf("%d: %s, %d   ", info[i].id, info[i].name, info[i].cnt);
	}

	printf("\n");

	struct UnionFind* obj = uf_init(namesSize);

	for(int i = 0; i < synonymsSize; i++) {
	        int slen = strlen(synonyms[i]);
	        char tmps[2][STR_LEN];

		char *iterator;
		char *p;
		iterator = strtok_r(synonyms[i], ",", &p);
		strcpy(tmps[0],iterator + 1);

		strcpy(tmps[1], p);
		int len = strlen(tmps[1]);
		tmps[1][len - 1] = '\0';

	        printf("%s; %s ", tmps[0], tmps[1]);

	        int id[2];
	        bool find = true;
	        for(int j = 0; j < 2; j++) {
			DataType hashdata;
			hashdata.key = tmps[j];
			hashmap_getValue(hashmap, &hashdata);
			if (hashdata.id == -1) {
				find = false;
				break;
			}

			id[j] = hashdata.val;
	        }

	        if(find == false)
	        {
	            continue;
	        }

	        printf("%d; %d\n", id[0], id[1]);

		uf_union(obj, id[0], id[1]);
	}


    	printf("\n");

	int rsize = 0;
	for(int i = 0; i < namesSize; i++) {
		int ff = uf_findRoot(obj, i);
		if(strcmp(info[i].name, info[ff].root) < 0) {
			info[ff].root = info[i].name;
		}

		if(i == ff) {
			rsize++;
			continue;
		} else {
			info[ff].cnt += info[i].cnt;
		}
	}

	char **ret = (char **)calloc(rsize, sizeof(char *));
	int rid = 0;
	for (int i = 0; i < namesSize; i++) {
		if(i == uf_findRoot(obj, i)) {
			ret[rid] = info[i].root;
			char tmp[STR_LEN] = {{'\0'}};
			sprintf(tmp, "(%d)", info[i].cnt);
			strcat(ret[rid], tmp);
			printf("%s    ", ret[rid]);
			rid++;
		}
	}
	*returnSize = rsize;
	return ret;
}

/*
1202. 交换字符串中的元素
给你一个字符串 s，以及该字符串中的一些「索引对」数组 pairs，其中 pairs[i] = [a, b] 表示字符串中的两个索引（编号从 0 开始）。

你可以 任意多次交换 在 pairs 中任意一对索引处的字符。

返回在经过若干次交换后，s 可以变成的按字典序最小的字符串。



示例 1:

输入：s = "dcab", pairs = [[0,3],[1,2]]
输出："bacd"
解释：
交换 s[0] 和 s[3], s = "bcad"
交换 s[1] 和 s[2], s = "bacd"
示例 2：

输入：s = "dcab", pairs = [[0,3],[1,2],[0,2]]
输出："abcd"
解释：
交换 s[0] 和 s[3], s = "bcad"
交换 s[0] 和 s[2], s = "acbd"
交换 s[1] 和 s[2], s = "abcd"
*/
char arrayblk[10001][10001];
//int colsize[10001];
//int scol[10001];
char * smallestStringWithSwaps(char * s, int** pairs, int pairsSize, int* pairsColSize)
{
	if (s == NULL || pairs == NULL || pairsSize <= 0 || pairsColSize == NULL) {
		return s;
	}

	size_t ufSize = strlen(s);
	struct UnionFind *uf =  uf_init(ufSize);
	for (int i = 0; i < pairsSize; i++) {
		uf_union(uf, pairs[i][0], pairs[i][1]);
	}

	struct HashTable ht;
	int ret = HashInit(&ht, ufSize, hashequal_int, hashcode_int);
	for (int i = 0; i < ufSize; i++) {
		struct DataEntry *entry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
		entry->key = uf_findRoot(uf, i);
		entry->value = s[i];
		HashAdd(&ht, &entry->node);
	}

	//hashPrint(&ht);
	memset(arrayblk, 0, sizeof(arrayblk));
	int *colsize = (int *)calloc(10001, sizeof(int));
	//memset(colsize, 0, sizeof(colsize));
	for (int i = 0; i < ht.bktSize; i++) {
	    struct Node *node;
	    LIST_FOR_EACH(node, &ht.bkts[i]) {
		struct DataEntry *getEntry;
		getEntry = NODE_ENTRY(node, struct DataEntry, node);
		arrayblk[i][colsize[i]] = getEntry->value;
		colsize[i]++;
	    }
	}

	for (int i = 0; i < ufSize; i++) {
		qsort(arrayblk[i], colsize[i], sizeof(arrayblk[i][0]), cmp_char);
	}
	int *scol = (int *)calloc(10001, sizeof(int));
	//memset(scol, 0, sizeof(scol));
	int i = 0;
	char *res = strdup(s);
	while(s[i] != '\0') {
		int hashkey = uf_findRoot(uf, i);
		unsigned int bid = hashGetBlkid_int(&ht, hashkey) ;
		int col = scol[bid];
		res[i] = arrayblk[bid][col];
		scol[bid]++;
		i++;
	}

	return res;
}

/*
1391. 检查网格中是否存在有效路径
给你一个 m x n 的网格 grid。网格里的每个单元都代表一条街道。grid[i][j] 的街道可以是：

1 表示连接左单元格和右单元格的街道。
2 表示连接上单元格和下单元格的街道。
3 表示连接左单元格和下单元格的街道。
4 表示连接右单元格和下单元格的街道。
5 表示连接左单元格和上单元格的街道。
6 表示连接右单元格和上单元格的街道。

*/

int patterns[7] = {0, 0b1010, 0b0101, 0b1100, 0b0110, 0b1001, 0b0011};
int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int dimenMap(int x, int y, int colSize)
{
	return x * colSize+ y;
}

void hander(struct UnionFind* uf, int** grid, int row, int col, int x, int y)
{
            int pattern = patterns[grid[x][y]];
            for (int i = 0; i < 4; ++i) {
                if (pattern & (1 << i)) {
                    int sx = x + dirs[i][0];
                    int sy = y + dirs[i][1];
                    if (sx >= 0 && sx < row && sy >= 0 && sy < col && (patterns[grid[sx][sy]] & (1 << ((i + 2) % 4)))) {
                        uf_union(uf, dimenMap(x, y, col), dimenMap(sx, sy, col));
                    }
                }
            }
}

bool hasValidPath(int** grid, int gridSize, int* gridColSize)
{
	int row = gridSize;
	int col = gridColSize[0];

	struct UnionFind* uf = uf_init(row * col);

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                hander(uf, grid, row, col, i, j);
            }
        }

	return uf_isOneUnion(uf, dimenMap(0, 0, col), dimenMap(row - 1, col - 1, col));
}
/*
1101. 彼此熟识的最早时间
难度中等7
在一个社交圈子当中，有 N 个人。每个人都有一个从 0 到 N-1 唯一的 id 编号。
我们有一份日志列表 logs，其中每条记录都包含一个非负整数的时间戳，以及分属两个人的不同 id，logs[i] = [timestamp, id_A, id_B]。
每条日志标识出两个人成为好友的时间，友谊是相互的：如果 A 和 B 是好友，那么 B 和 A 也是好友。
如果 A 是 B 的好友，或者 A 是 B 的好友的好友，那么就可以认为 A 也与 B 熟识。
返回圈子里所有人之间都熟识的最早时间。如果找不到最早时间，就返回 -1 。

示例：
输入：logs = [[20190101,0,1],[20190104,3,4],[20190107,2,3],[20190211,1,5],[20190224,2,4],[20190301,0,3],[20190312,1,2],[20190322,4,5]], N = 6
输出：20190301
解释：
第一次结交发生在 timestamp = 20190101，0 和 1 成为好友，社交朋友圈如下 [0,1], [2], [3], [4], [5]。
第二次结交发生在 timestamp = 20190104，3 和 4 成为好友，社交朋友圈如下 [0,1], [2], [3,4], [5].
第三次结交发生在 timestamp = 20190107，2 和 3 成为好友，社交朋友圈如下 [0,1], [2,3,4], [5].
第四次结交发生在 timestamp = 20190211，1 和 5 成为好友，社交朋友圈如下 [0,1,5], [2,3,4].
第五次结交发生在 timestamp = 20190224，2 和 4 已经是好友了。
第六次结交发生在 timestamp = 20190301，0 和 3 成为好友，大家都互相熟识了。

*/
/*
变形的并查集问题。

根据题意：

1.全部认识的最早时间=（集合A认识的最早时间，集合B都认识的最早时间，AB认识的最早时间）中的最迟时间

2.如果集合A和集合B为同一集合，则新加入log无效

3.本题的难点是，如何避免日期迟的一个log先促成A、B合并，可以预先排序，让所有合并动作都尽早发生

*/
int find(int *fa, int x) {
    if(fa[x] == x) {
        return fa[x];
    }

    fa[x] = find(fa, fa[x]);
    return fa[x];
}

void join(int *fa, int x, int y) {
    int xx = find(fa, x);
    int yy = find(fa, y);

    if(xx == yy) {
        return;
    }

    if(xx < yy) {
        fa[yy] = xx;
    } else {
        fa[xx] = yy;
    }
}

int compare(const void *a, const void *b) {
    return (*(int **)a)[0] - (*(int **)b)[0];
}

//【算法思路】排序+并查集。全部认识的最早时间=（集合A认识的最早时间，集合B都认识的最早时间，AB认识的最早时间）中的最迟时间
int earliestAcq(int** logs, int logsSize, int* logsColSize, int N)
{
    int *fa  = (int *)calloc(N, sizeof(int));
    int *times  = (int *)calloc(N, sizeof(int));

    for(int i = 0; i < N; i++) {
        fa[i] = i;
        times[i] = -1;
    }

    //排序后，促使集合合并的时间尽早发生，后续再有合并动作，因为已经是一个集合所以被减除
    qsort(logs, logsSize, sizeof(int *), compare);

	int cnt = N;
    for(int i = 0; i < logsSize; i++) {
        int x = logs[i][1];
        int y = logs[i][2];

        int xx = find(fa, x);
        int yy = find(fa, y);

        if(xx == yy) {
            continue;
        }

        int timex = times[xx];
        int timey = times[yy];
        int timexy = logs[i][0];

        int time = fmax(timex, fmax(timey, timexy));

        //实现join的功能而不直接调用接口
        if(xx < yy) {
            fa[yy] = xx;
            times[xx] = time;
        } else {
            fa[xx] = yy;
            times[yy] = time;
        }
// N个人只需要N-1次合并就能认识所有人，判断条件为N=1 说明全认识了。
	cnt--;
	if (cnt == 1) {
		return logs[i][0];
	}
    }

	return -1;
}

/*
1135. 最低成本联通所有城市
难度中等23
想象一下你是个城市基建规划者，地图上有 N 座城市，它们按以 1 到 N 的次序编号。
给你一些可连接的选项 conections，其中每个选项 conections[i] = [city1, city2, cost] 表示将城市 city1 和城市 city2 连接所要的成本。（连接是双向的，也就是说城市 city1 和城市 city2 相连也同样意味着城市 city2 和城市 city1 相连）。
返回使得每对城市间都存在将它们连接在一起的连通路径（可能长度为 1 的）最小成本。该最小成本应该是所用全部连接代价的综合。如果根据已知条件无法完成该项任务，则请你返回 -1。

示例 1：

输入：N = 3, conections = [[1,2,5],[1,3,6],[2,3,1]]
输出：6
解释：
选出任意 2 条边都可以连接所有城市，我们从中选取成本最小的 2 条。

*/

/*
预备知识最小生成树图的生成树是一棵含有其所有的顶点的无环联通子图，一幅加权图的最小生成树（ MST ） 是它的一颗权值（树中所有边的权值之和）最小的生成树。并查集并查集是一种树型的数据结构，用于处理一些不相交集合的合并及查询问题。常常在使用中以森林来表示。方法一：kruskal 算法思路根据题意，我们可以把 N 座城市看成 N 个顶点，连接两个城市的成本 cost 就是对应的权重，需要返回连接所有城市的最小成本。很显然，这是一个标准的最小生成树，首先我们介绍第一种经典算法： kruskal 算法。既然我们需要求最小成本，那么可以肯定的是这个图没有环（如果有环的话无论如何都可以删掉一条边使得成本更小）。该算法就是基于这个特性：按照边的权重顺序（从小到大）处理所有的边，将边加入到最小生成树中，加入的边不会与已经加入的边构成环，直到树中含有 N - 1 条边为止。这些边会由一片森林变成一个树，这个树就是图的最小生成树。作者：LeetCode-Solution链接：https://leetcode-cn.com/problems/connecting-cities-with-minimum-cost/solution/zui-di-cheng-ben-lian-tong-suo-you-cheng-shi-by-le/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int minimumCost(int N, int** connections, int connectionsSize, int* connectionsColSize)
{
	qsort(connections, connectionsSize, sizeof(connections[0]), cmp_point);
	int cost = 0;

	struct UnionFind* uf = uf_init(N + 1);
	for (int i = 0; i < connectionsSize; i++) {
		if (!uf_isOneUnion(uf, connections[i][0], connections[i][1])) {
			uf_union(uf, connections[i][0], connections[i][1]);
			cost += connections[i][2];
		}
	}

	int rooCnt = 0;
	for (int i = 1; i <= N; i++) {
		if (uf->father[i] == i) {
			if (++rooCnt > 1) {
				return -1;
			}
		}
	}

	return cost;
}

/*
1102. 得分最高的路径
BFS
*/

#define min(a,b) (a) < (b) ? (a) : (b)
int direction[2][4] = {{1,-1,0,0},{0,0,1,-1}};
typedef struct {
    int x;
    int y;
    int value;
} Node;

int NodeCmp (const void *p1, const void *p2)
{
    return (((Node *)p2)->value - ((Node*)p1)->value);
}

int FindRoot (int root, int *parent) {
    int son,tmp;
    son = root;
    while (root != parent[root]) {
        root = parent[root];
    }
    while (son != root) {
        tmp = parent[son];
        parent[son] = root;
        son = tmp;
    }
    return root;
}

void Union(int x, int y, int *parent)
{
    int rootX, rootY;
    rootX = FindRoot(x, parent);
    rootY = FindRoot(y, parent);
    if (rootX == rootY) {
        return;
    } else if (rootX < rootY) {        //因为结构体数组已排序，所以序号较大的值树较深
        parent[rootX] = rootY;
    } else {
        parent[rootY] = rootX;
    }
}
int maximumMinimumPath(int** A, int ASize, int* AColSize){
    int matrixSize = ASize * (*AColSize);
    int trace[matrixSize];
    int parent[matrixSize];
    Node nodeArray[matrixSize];
    memset(trace, 0, sizeof(trace));
    memset(parent, 0, sizeof(parent));
    memset(nodeArray,0,sizeof(nodeArray));
    int count = 0;
    for (int i = 0; i < ASize; i++) {
        for (int j = 0; j < (*AColSize); j++) {
            parent[count] = i * (*AColSize) + j;
            nodeArray[count].x = i;
            nodeArray[count].y = j;
            nodeArray[count].value = A[i][j];
            count++;
        }
    }
    qsort(nodeArray, matrixSize, sizeof(Node), NodeCmp);
    count = 0;
    int ans = min(A[0][0], A[ASize - 1][*AColSize - 1]);
    while (FindRoot(0, parent) != FindRoot(matrixSize - 1, parent)) {
        int x = nodeArray[count].x;
        int y = nodeArray[count].y;
        int index = x * (*AColSize) + y;
        trace[index] = 1;                          //标记该点被加入当前路径内
        ans = min(ans, nodeArray[count].value);
        for (int i = 0; i < 4; i++)
        {
            int nx, ny;
            nx = x + direction[0][i];
            ny = y + direction[1][i];
            int indexNew = nx * (*AColSize) + ny;
            if (nx < ASize && nx > -1 && ny < (*AColSize) && ny > -1 && trace[indexNew] == 1) {
                Union(index, indexNew, parent);
            }
        }
        count++;
    }
    return ans;
}
