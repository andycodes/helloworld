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
#define MAX 101
typedef struct {
    char name[MAX];
    int index;
    int count;
    UT_hash_handle hh;
} ChildName;

int cmp (ChildName *p1, ChildName *p2) {
    return strcmp(p1->name, p2->name);
}

int FindRoot(int root, int *pre) {
    int son, temp;
    son = root;
    while (root != pre[root]) {
        root = pre[root];
    }

    while (son != root) {
        temp = pre[son];
        pre[son] = root;
        son = temp;
    }

    return root;
}

void UnionWord(ChildName *names1, ChildName *names2, int *pre) {
    if (names1 == NULL || names2 == NULL) {
        return;
    }
    int root1 = FindRoot(names1->index, pre);
    int root2 = FindRoot(names2->index, pre);
    if (root1 == root2) {
        return;
    }
    if (strcmp(names1->name, names2->name) < 0) { //连接边，字典序小的作为根节点
        pre[root2] = root1;
    } else {
        pre[root1] = root2;
    }
}

char** trulyMostPopular(char** names, int namesSize, char** synonyms, int synonymsSize, int* returnSize){

    ChildName *childrenMap = NULL;
    ChildName *node;

    for (int i = 0; i < namesSize; i++) {
        node = malloc(sizeof(ChildName));
        char *split;
        split = strtok(names[i], "(");
        strcpy(node->name, split);
        split = strtok(NULL, ")");
        node->count = atoi(split);
        node->index = i;
        HASH_ADD_STR(childrenMap, name, node);
    }

    HASH_SORT(childrenMap, cmp);

    int pre[namesSize];
    for (int i = 0; i <namesSize; i++) {
        pre[i] = i;
    }

    for (int i = 0; i < synonymsSize; i++) {
        ChildName *names1, *names2;
        char *split;
        split = strtok(synonyms[i], "(,");
        HASH_FIND_STR(childrenMap, split, names1);
        split = strtok(NULL, ")");
        HASH_FIND_STR(childrenMap, split, names2);
        UnionWord(names1, names2, pre);
    }

    ChildName *newChildMap = NULL;
    ChildName *newNode, *temp;
    HASH_ITER(hh, childrenMap, node, temp) {
        int rootIndex = FindRoot(node->index, pre);
        HASH_FIND_INT(newChildMap, &rootIndex, newNode); // 以序号为键值，新建哈希表
        if (newNode == NULL) {
            newNode = malloc(sizeof(ChildName));
            newNode->count = node->count;
            newNode->index = rootIndex;
            strcpy(newNode->name, node->name);
            HASH_ADD_INT(newChildMap, index, newNode);
        } else {
            newNode->count += node->count;
        }
    }

    char **strRes = malloc(HASH_COUNT(newChildMap) * sizeof(char *));

    int index = 0;
    HASH_ITER(hh, newChildMap, newNode, temp) {
        strRes[index] = malloc(MAX);
        sprintf(strRes[index], "%s(%d)", newNode->name, newNode->count);
        index++;
    }

    *returnSize = index;

    return strRes;

}


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
1101. 彼此熟识的最早时间
难度中等7
在一个社交圈子当中，有 N 个人。每个人都有一个从 0 到
N-1 唯一的 id 编号。
我们有一份日志列表 logs，其中每条记录都包含一个非负整数
的时间戳，以及分属两个人的不同 id，logs[i] = [timestamp, id_A, id_B]。
每条日志标识出两个人成为好友的时间，友谊是相互的：如
果 A 和 B 是好友，那么 B 和 A 也是好友。
如果 A 是 B 的好友，或者 A 是 B 的好友的好友，那么就可以认
为 A 也与 B 熟识。
返回圈子里所有人之间都熟识的最早时间。如果找不到最早
时间，就返回 -1 。

示例：
输入：logs = [[20190101,0,1],[20190104,3,4],[20190107,2,3],[20190211,1,5],
[20190224,2,4],[20190301,0,3],[20190312,1,2],[20190322,4,5]], N = 6
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
int uf_union(struct UnionFind* uf, int** logs, int logsSize)
{
	for (int i = 0; i < logsSize; i++) {
		int root0 = uf_findRoot(uf, logs[i][1]);
		int root1 = uf_findRoot(uf, logs[i][2]);
		if (root0 == root1)
			continue;

		int timemax = fmax(fmax(uf->timestamp[root0], uf->timestamp[root1]), logs[i][0]);

		if (uf->rank[root0] < uf->rank[root1]) {
			uf->root[root0] = root1;
			uf->timestamp[root1] = timemax;
		} else if (uf->rank[root0] > uf->rank[root1]) {
			uf->root[root1] = root0;
			uf->timestamp[root0] = timemax;
		} else {
			uf->root[root0] = root1;
			uf->rank[root1]++;
			uf->timestamp[root1] = timemax;
		}
	/*
	N个人只需要N-1次合并就能认识所有人，
	判断条件为N=1 说明全认识了。
	*/
		uf->unionCnt--;
		if (uf->unionCnt == 1) {
			return logs[i][0];
		}
	}

	return -1;
}

/*
全部认识的最早时间=（
集合A认识的最早时间，
集合B都认识的最早时间，
AB认识的最早时间）
中的最迟时间
*/
int earliestAcq(int** logs, int logsSize, int* logsColSize, int N)
{
	struct UnionFind duf;
	struct UnionFind *uf = &duf;

	uf_init(uf, N);
	qsort(logs, logsSize, sizeof(logs[0]), cmp_point);
	return uf_union(uf, logs, logsSize);
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
947. 移除最多的同行或同列石头
难度中等65
我们将石头放置在二维平面中的一些整数坐标点上。每个坐标点上最多只能有一块石头。
每次 move 操作都会移除一块所在行或者列上有其他石头存在的石头。
请你设计一个算法，计算最多能执行多少次 move 操作？

示例 1：
输入：stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
输出：5
示例 2：
输入：stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
输出：3

*/
int removeStones(int** stones, int stonesSize, int* stonesColSize)
{
        int n = stonesSize;
        if(!n) return 0;

	struct UnionFind duf;
	struct UnionFind *uf = &duf;
	uf->root = (int *)calloc(n, sizeof(int));
	uf->rank = (int *)calloc(n, sizeof(int));
	uf->cnt = n;
	uf_init(uf);

        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                if(stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]){
                        uf_union(uf, i,j);
                    }
            }
        }
        return n -uf->cnt;
}

/*
685. 冗余连接 II
在本问题中，有根树指满足以下条件的有向图。该树只有一个根节点，所有其他节点都是该根节点的后继。每一个节点只有一个父节点，除了根节点没有父节点。

输入一个有向图，该图由一个有着N个节点 (节点值不重复1, 2, ..., N) 的树及一条附加的边构成。附加的边的两个顶点包含在1到N中间，这条附加的边不属于树中已存在的边。

结果图是一个以边组成的二维数组。 每一个边 的元素是一对 [u, v]，用以表示有向图中连接顶点 u 和顶点 v 的边，其中 u 是 v 的一个父节点。

返回一条能删除的边，使得剩下的图是有N个节点的有根树。若有多个答案，返回最后出现在给定二维数组的答案。

示例 1:

输入: [[1,2], [1,3], [2,3]]
输出: [2,3]
解释: 给定的有向图如下:
  1
 / \
v   v
2-->3
*/

int* findRedundantDirectedConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize){
    int parent[edgesSize+1];
    memset(parent, 0, sizeof parent);
    *returnSize = 2;
    int *r = NULL, *q = NULL;
    for (int i=0; i<edgesSize; ++i) {
        int p = edges[i][0], x = edges[i][1];
        if (parent[x]) {
            //入度冲突
            r = edges[i];
        } else {
            while (parent[p]) p = parent[p];
            while (parent[x]) x = parent[x];
            if (p == x) {
                //环路冲突
                q = edges[i];
            } else {
                parent[edges[i][1]] = edges[i][0];
            }
        }
    }
    if (r && q) {
        while (q[1] != r[1]) {
            q[1] = q[0];
            q[0] = parent[q[0]];
        }
        return q;
    }
    if (r) {
        return r;
    }
    return q;
}

