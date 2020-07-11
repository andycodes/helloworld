/*

BFS


while queue 非空:
	node = queue.pop()
    for node 的所有相邻结点 m:
        if m 未访问过:
            queue.push(m)


求最短路径!!!!!!

depth = 0 # 记录遍历到第几层
while queue 非空:
    depth++
    n = queue 中的元素个数
    循环 n 次:
        node = queue.pop()
        for node 的所有相邻结点 m:
            if m 未访问过:
                queue.push(m)

*/


/*
994. 腐烂的橘子
在给定的网格中，每个单元格可以有以下三个值之一：

值 0 代表空单元格；
值 1 代表新鲜橘子；
值 2 代表腐烂的橘子。
每分钟，任何与腐烂的橘子（在 4 个正方向上）相邻的新鲜橘子都会腐烂。

返回直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1。

方法：广度优先搜索
思路

每一轮，腐烂将会从每一个烂橘子蔓延到与其相邻的新鲜橘子
上。一开始，腐烂的橘子的深度为 0，
每一轮腐烂会从腐烂橘子传染到之相邻新鲜橘子上，
并且设置这些新的腐烂橘子的深度为自己深度 +1，
我们想知道完成这个过程之后的最大深度值是多少。

算法

我们可以用一个广度优先搜索来建模这一过程。
因为我们总是选择去使用深度值最小的（且之前未使用过的）
腐烂橘子去腐化新鲜橘子，
如此保证每一个橘子腐烂时的深度标号也是最小的。

我们还应该检查最终状态下，是否还有新鲜橘子。

*/
int orangesRotting(int** grid, int gridSize, int* gridColSize)
{
    if (grid == NULL || gridSize == 0 || gridColSize == NULL || gridColSize[0] == 0) {
        return 0;
    }

	int row = gridSize;
	int col = gridColSize[0];

	int queue[row * col];
	int head = 0;
	int rear = 0;

    // bfs
    int count = 0;// count 表示新鲜橘子的数量
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 2) {
		 queue[rear++] = i * col + j;//烂橘子入队列
            } else if (grid[i][j] == 1) {
                count++;
            }
        }
    }

    int deep = 0;// round 表示腐烂的轮数，或者分钟数
    while (count > 0 && head != rear) {
	deep++;
	int floorSize = rear - head;

	for (int i = 0; i < floorSize; i++) {
		int pop = queue[head++];// 一定是烂橘子
		int pop_x = pop / col;
		int pop_y = pop % col;

		int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
	        for (int k = 0; k < 4; k++) {
	            int dx = pop_x + dir[k][0];
	            int dy = pop_y + dir[k][1];
	            if (dx < 0 || dx >= row || dy < 0 || dy >= col) {
	                continue;
	            }

	            if (grid[dx][dy] != 1) {
	                continue;
	            }

			grid[dx][dy] = 2;
			count--;
			queue[rear++] = dx * col + dy;//烂橘子入队列
	        }
	}
    }

    return (count > 0) ? -1: deep;
}




struct queue_load{
	int row;
	int col;
};
/*tile see dfs floodFill*/
int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc,
	int newColor, int* returnSize, int** returnColumnSizes)
{
	*returnSize = imageSize;
	*returnColumnSizes = malloc(sizeof(int) * imageSize);

	for (int i = 0; i < imageSize; i++) {
		(*returnColumnSizes)[i] = imageColSize[i];
	}

	if (newColor == image[sr][sc])
		return image;

	int directions[4][2] = {
		{1,0},
		{-1,0},
		{0,1},
		{0,-1}
	};
	int originalcolor = image[sr][sc];

	struct queue_blk * queue = create_array_queue(50);

	struct queue_load start;
	start.row = sr;
	start.col = sc;

	push(queue,start);

	while(!is_empty(queue)) {
		struct queue_load cur = pop(queue);
		image[cur.row][cur.col] = newColor;

		for(int i = 0; i < 4; i++) {
			int new_i = cur.row + directions[i][0];
			int new_j = cur.col + directions[i][1];
			if ((0 <= new_i) && (new_i < imageSize)  && (0 <= new_j) &&
				(new_j < imageColSize[0]) && image[new_i][new_j] == originalcolor) {
				start.row = new_i;
				start.col = new_j;
				push(queue,start);
			}
		}
	}

	return image;
}


/*
给定一个由 '1'（陆地）和 '0'（水）组成的的二维网格，计算岛屿的数量。一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设网格的四个边均被水包围。

示例 1:

输入:
11110
11010
11000
00000

输出: 1

struct queue_load{
	int x;
	int y;
};
*/
int numIslands(char** grid, int gridSize, int* gridColSize){
	int num = 0;

	if(grid == NULL  || gridSize == 0 || gridColSize == NULL)
		return num;

	int visited[gridSize][*gridColSize];
	memset((void*)visited,0,sizeof(visited));



	struct queue_blk *qe = create_array_queue(gridSize*(* gridColSize));


	int d[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

	for(int i = 0; i < gridSize; i++) {
		for (int j = 0; j < *gridColSize;j++) {
			if (grid[i][j] == '1') {
				if ((visited[i][j]) == 0) {
					visited[i][j] = 1;
					num++;
				}

				struct queue_load load;
				load.x = i;
				load.y = j;
				push(qe,load);

				while(!is_empty(qe)) {
					struct queue_load get = pop(qe);

					for(int k = 0; k < 4; k++) {
						int nX = get.x + d[k][0];
						int nY = get.y + d[k][1];
						if (nX >=0 && nX < gridSize && nY >=0 && nY < *gridColSize){
							if (grid[nX][nY] == '1' && visited[nX][nY] == 0) {
								visited[nX][nY] = 1;
								struct queue_load load;
								load.x = nX;
								load.y = nY;
								push(qe, load);
							}
						}
					}
				}
			}
		}
	}

	return num;
}

/*
529. 扫雷游戏
让我们一起来玩扫雷游戏！

给定一个代表游戏板的二维字符矩阵。
'M' 代表一个未挖出的地雷，
'E' 代表一个未挖出的空方块，
'B' 代表没有相邻（上，下，左，右，和所有4个对角线）
地雷的已挖出的空白方块，
数字（'1' 到 '8'）表示有多少地雷与这块已挖出的方块相邻，
'X' 则表示一个已挖出的地雷。

现在给出在所有未挖出的方块中（'M'或者'E'）的
下一个点击位置（行和列索引），
根据以下规则，返回相应位置被点击后对应的面板：

如果一个地雷（'M'）被挖出，游戏就结束了- 把它改为 'X'。
如果一个没有相邻地雷的空方块（'E'）被挖出，修改它为（'B'），
并且所有和其相邻的方块都应该被递归地揭露。
如果一个至少与一个地雷相邻的空方块（'E'）被挖出，
修改它为数字（'1'到'8'），表示相邻地雷的数量。
如果在此次点击中，若无更多方块可被揭露，则返回面板。


示例 1：

输入:

[['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'M', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E']]

Click : [3,0]

*/

const int dir[8][2] = {{0,1}, {1,0}, {0,-1}, {-1,0},
                 	      {1,1}, {-1,-1},{-1,1},{1,-1}
                 	     };


struct queue_load{
	int x;
	int y;
};


void  pushNeighborsInQueue(struct queue_blk * queue,
	int x, int y,  char **res, int boardSize, int* boardColSize)
{
	for (int i = 0; i < 8; i++) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];

		if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardColSize[nx]) {
			if (res[nx][ny] == 'E') {
				struct queue_load load;
				load.x = nx;
				load.y = ny;
				aqueue_push_last(queue, load);
			}
		}
	}
}


int  NeighborsHavenumsM(int x, int y,  char **res, int boardSize, int* boardColSize)
{
	int Mcnt = 0;

	for (int i = 0; i < 8; i++) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];

		if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardColSize[nx]) {
			if (res[nx][ny] == 'M')
				Mcnt++;
		}
	}

	return Mcnt;
}


char** updateBoard(char** board, int boardSize, int* boardColSize,
int* click, int clickSize, int* returnSize, int** returnColumnSizes){

	char **res = (char **)calloc(boardSize, sizeof(char *));
	for (int i = 0; i < boardSize; i++) {
	        res[i] = (char *)calloc(boardColSize[i], sizeof(char));
	}

	*returnColumnSizes = calloc(boardSize, sizeof(int *));

	for (int i = 0; i < boardSize; i++){
	        for (int j = 0; j < boardColSize[i]; j++) {
	            res[i][j] = board[i][j];
	        }

		(*returnColumnSizes)[i] = boardColSize[i];
	}

	*returnSize = boardSize;

	struct queue_blk * queue = aqueue_init(boardSize * boardColSize[0]);
	int x = click[0];
	int y = click[1];

	if (res[x][y] == 'M') {
	    res[x][y] = 'X';
	} else if (res[x][y] == 'E') {
		struct queue_load load;
		load.x = x;
		load.y = y;
		aqueue_push_last(queue, load);

		while(!aqueue_empty(queue)) {
			struct queue_load out = aqueue_pop_first(queue);
			int nums = NeighborsHavenumsM(out.x, out.y, res, boardSize, boardColSize);
			if (nums > 0) {
				res[out.x][out.y] = '0' + nums;
			} else {
				res[out.x][out.y] = 'B';
				pushNeighborsInQueue(queue, out.x, out.y, res, boardSize, boardColSize);
			}
		}
	}

	aqueue_exit(queue);
	return res;
}

/*
207. 课程表
现在你总共有 n 门课需要选，记为 0 到 n-1。

在选修某些课程之前需要一些先修课程。 例如，想要学习
课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他
们: [0,1]

给定课程总量以及它们的先决条件，判断是否可能完成所有
课程的学习？

示例 1:

输入: 2, [[1,0]]
输出: true
解释: 总共有 2 门课程。学习课程 1 之前，
你需要完成课程 0。所以这是可能的。



1、在开始排序前，扫描对应的存储空间（使用邻接表），
将入度为 00 的结点放入队列。

2、只要队列非空，就从队首取出入度为 00 的结点，
将这个结点输出到结果集中，并且将这个结点的所有邻接结
点（它指向的结点）的入度减 11，在减 11 以后，如果这个被
减 11 的结点的入度为 00 ，就继续入队。

3、当队列为空的时候，检查结果集中的顶点个数是否和
课程数相等即可。

也可以用DFS 判断是否存在环

*/
bool canFinish(int numCourses, int** prerequisites,
int prerequisitesSize, int* prerequisitesColSize)
{
	/*某课的入度可以理解为该课同时有多少个前置课*/
	int *inDegree = (int *)calloc(numCourses, sizeof(int));
	for (int i = 0; i < prerequisitesSize; i++) {
		inDegree[prerequisites[i][0]]++;
	}

	struct aqueue_blk * queue =  aqueue_init(numCourses);

	for (int i = 0; i < numCourses; i++) {
		if (inDegree[i] == 0) {
			struct aqueue_load load;
			load.data = i;
			aqueue_push_last(queue, load);
		}
	}
/*
	for_aqueue_entry(queue) {
		printf("%d ",queue->load[i].data);
	}
*/
	int cnt = 0;
	while(!aqueue_empty(queue)) {
		struct aqueue_load out = aqueue_pop_first(queue);
		cnt++;
		for (int i = 0 ; i < prerequisitesSize; i++) {
			if (prerequisites[i][1] == out.data) {
				int x = prerequisites[i][0];
				inDegree[x]--;
				if (inDegree[x] == 0) {
					struct aqueue_load load;
					load.data = x;
					aqueue_push_last(queue, load);
				}
			}
		}
	}

	return cnt == numCourses;
}

/*
210. 课程表 II
难度中等122
现在你总共有 n 门课需要选，记为 0 到 n-1。
在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]
给定课程总量以及它们的先决条件，返回你为了学完所有课程所安排的学习顺序。
可能会有多个正确的顺序，你只要返回一种就可以了。如果不可能完成所有课程，返回一个空数组。
示例 1:
输入: 2, [[1,0]]
输出: [0,1]
解释: 总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1] 。
示例 2:
输入: 4, [[1,0],[2,0],[3,1],[3,2]]
输出: [0,1,2,3] or [0,2,1,3]
解释: 总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
     因此，一个正确的课程顺序是 [0,1,2,3] 。另一个正确的排序是 [0,2,1,3] 。
说明:
1.	输入的先决条件是由边缘列表表示的图形，而不是邻接矩阵。详情请参见图的表示法。
2.	你可以假定输入的先决条件中没有重复的边。
提示:
1.	这个问题相当于查找一个循环是否存在于有向图中。如果存在循环，则不存在拓扑排序，因此不可能选取所有课程进行学习。
2.	通过 DFS 进行拓扑排序 - 一个关于Coursera的精彩视频教程（21分钟），介绍拓扑排序的基本概念。
3.	拓扑排序也可以通过 BFS 完成。
1.	nums1和nums2 的数组大小都不超过1000。

*/


/*
拓扑排序入度：设有向图中有一结点 v ，其入度即为当前所有从其他结点出发，终点为 v 的的边的数目。出度：设有向图中有一结点 v ，其出度即为当前所有起点为 v ，指向其他结点的边的数目。每次从入度为 0 的结点开始，加入队列。入度为 0 ，表示没有前置结点。处理入度为 0 的结点，把这个结点指向的结点的入度 -1 。再把新的入度为 0 的结点加入队列。如果队列都处理完毕，但是和总结点数不符，说明有些结点形成环。
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize,
	int* prerequisitesColSize, int* returnSize)
{
	int inDegree[numCourses];
	memset(inDegree, 0, sizeof(inDegree));

	int matrix[numCourses][numCourses];
	int matrixCnt[numCourses];
	memset(matrix, 0, sizeof(matrix));
	memset(matrixCnt, 0, sizeof(matrixCnt));

	for (int i = 0; i < prerequisitesSize; i++) {
		//printf("%d", prerequisites[i][0]);
		inDegree[prerequisites[i][0]]++;
		int cnt = matrixCnt[prerequisites[i][1]];//out degree
		matrix[prerequisites[i][1]][cnt] = prerequisites[i][0];
		matrixCnt[prerequisites[i][1]]++;
	}

	struct List list;
	queue_init(&list);
	for (int i = 0; i < numCourses; i++) {
		if (inDegree[i] == 0) {
			queue_push_key(&list, i);
		}
	}

	int *ret = calloc(numCourses, sizeof(int));
	int retSize = 0;
	while(!queue_empty(&list)) {
		struct Node *popNode = queue_pop(&list);
		struct DataEntry *entry;
		entry = NODE_ENTRY(popNode, struct DataEntry, node);
		ret[retSize++] = entry->key;
		for(int i = 0; i < matrixCnt[entry->key]; i++) {
			int idx = matrix[entry->key][i];
			if (--inDegree[idx] == 0) {
				queue_push_key(&list, idx);
			}
		}
	}

	//printf("%d\n",retSize);
	*returnSize = retSize;
	if (retSize != numCourses)
		*returnSize = 0;
	return ret;
}

/*
22. 括号生成
难度中等955
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

示例：
输入：n = 3
输出：[
       "((()))",
       "(()())",
       "(())()",
       "()(())",
       "()()()"
     ]

*/
char** generateParenthesis(int n, int* returnSize)
{
	*returnSize = 0;
	if (n == 0) {
		return NULL;
	}

	char** res = (char**)calloc(1024 * 1024, sizeof(char*));
	struct List list;
	queue_init(&list);

	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry));
	entry->left = n;
	entry->right = n;
	memset(entry->data, 0, sizeof(entry->data));
	ListAddTail(&list, &entry->node);

	while(!queue_empty(&list)) {
		struct Node *pop = queue_pop(&list);
		struct DataEntry  *popEntry = NODE_ENTRY(pop, struct DataEntry, node);

		if (popEntry->left == 0 && popEntry->right == 0) {
			res[*returnSize] = (char*)calloc(1024 * 1024, sizeof(char));
			strcpy(res[*returnSize], popEntry->data);
			(*returnSize)++;
		}

		if (popEntry->left > 0) {
			struct DataEntry  *leftentry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry));
			leftentry->left = popEntry->left - 1;
			leftentry->right = popEntry->right;
			strcpy(leftentry->data, popEntry->data);
			strcat(leftentry->data, "(");
			ListAddTail(&list, &leftentry->node);
		}

		if (popEntry->right > 0 && popEntry->left < popEntry->right) {
			struct DataEntry  *rightentry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry));
			rightentry->left = popEntry->left;
			rightentry->right = popEntry->right - 1;
			strcpy(rightentry->data, popEntry->data);
			strcat(rightentry->data, ")");
			ListAddTail(&list, &rightentry->node);
		}
	}

	return res;
}

/*
279. 完全平方数
给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。

示例 1:

输入: n = 12
输出: 3
解释: 12 = 4 + 4 + 4.
示例 2:

输入: n = 13
输出: 2
解释: 13 = 4 + 9.
*/
int numSquares(int n){
	struct List queue;
	queue_init(&queue);

	queue_push_key(&queue, n);
	int level = 0;
	while(!queue_empty(&queue)) {
		level++;

		// 每一层的广度遍历
		int size = queue_size(&queue);
		for (int i = 0; i < size; i++) {
			struct DataEntry *top = queue_pop_entry(&queue);

			for (int j = 1; j <= sqrt(n); j++) {
				int target = top->key - pow(j, 2);
				// 说明已到最大平方数
				if (target < 0)
					break;
				// 由于是广度遍历，所以当遍历到0时，肯定是最短路径
				if (target == 0)
					return level;
				queue_push_key(&queue, target);
			}
		}
	}

	return -1;
}

/*
752. 打开转盘锁
难度中等106
你有一个带有四个圆形拨轮的转盘锁。每个拨轮都有10个数字： '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' 。每个拨轮可以自由旋转：例如把 '9' 变为  '0'，'0' 变为 '9' 。每次旋转都只能旋转一个拨轮的一位数字。
锁的初始数字为 '0000' ，一个代表四个拨轮的数字的字符串。
列表 deadends 包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，这个锁将会被永久锁定，无法再被旋转。
字符串 target 代表可以解锁的数字，你需要给出最小的旋转次数，如果无论如何不能解锁，返回 -1。

示例 1:
输入：deadends = ["0201","0101","0102","1212","2002"], target = "0202"
输出：6
解释：
可能的移动序列为 "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202"。
注意 "0000" -> "0001" -> "0002" -> "0102" -> "0202" 这样的序列是不能解锁的，
因为当拨动到 "0102" 时这个锁就会被锁定。

*/
/*
我们可以将 0000 到 9999 这 10000 状态看成图上的 10000 个节点，两个节点之间存在一条边，当且仅当这两个节点对应的状态只有 1 位不同，且不同的那位相差 1（包括 0 和 9 也相差 1 的情况），并且这两个节点均不在数组 deadends 中。那么最终的答案即为 0000 到 target 的最短路径。

我们用广度优先搜索来找到最短路径，从 0000 开始搜索。对于每一个状态，它可以扩展到最多 8 个状态，即将它的第 i = 0, 1, 2, 3 位增加 1 或减少 1，将这些状态中没有搜索过并且不在 deadends 中的状态全部加入到队列中，并继续进行搜索。注意 0000 本身有可能也在 deadends 中。

*/
int openLock(char ** deadends, int deadendsSize, char * target)
{
	int i,j,k, ret, len, steps = -1;
	char start[] = "0000";

	if (strcmp(start, target) == 0)
		return 0;

	struct List dlist;
	struct List *list = &dlist;
	queue_init(list);

	struct HashTable dht;
	struct HashTable *ht = &dht;
	HashInit(ht, 2 << 10, hashequal_str, hashcode_str);

    	for (i = 0; i < deadendsSize; i++) {
		struct DataEntry *entry = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
		entry->key = deadends[i];
		HashAdd(ht, &entry->node);
	}

	struct DataEntry cmpEntry;
	cmpEntry.key = start;
	struct DataEntry *find = hashFind(ht, &cmpEntry);
	if (find != NULL) {
		return -1;
	}

	struct DataEntry  *entryQueue = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
	entryQueue->key = start;
	ListAddTail(list, &entryQueue->node);

    	while(!queue_empty(list)) {
        ++steps;
        len = queue_size(list);
        for (k = 0; k < len; k++) {
		struct DataEntry *pop = queue_pop_entry(list);
                if (strcmp(pop->key, target) == 0) {
			//free(pop);
			//HashDeinit(ht, node_free);
			return steps;
                }

		//struct DataEntry *entryhash = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
		//entryhash->key = pop->key;
		//HashAdd(ht, &entryhash->node);

            	for (i = 0; i < 4; i++) {
			for (j = -1; j < 2; j += 2) {
				char *newstr = strdup(pop->key);
				newstr[i] = (newstr[i] - '0' + j + 10)%10 + '0';

				struct DataEntry nextEntry;
				nextEntry.key = newstr;
				struct DataEntry *find =  hashFind(ht, &nextEntry);
				if (find != NULL) {
					continue;
				}

				struct DataEntry *entryhash = (struct DataEntry *)calloc(1, sizeof(struct DataEntry));
				entryhash->key = newstr;
				HashAdd(ht, &entryhash->node);

				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->key = newstr;
				ListAddTail(list, &entry->node);
			}
		}
	}
	}

	//HashDeinit(ht, node_free);
	return -1;
}

/*
863. 二叉树中所有距离为 K 的结点
给定一个二叉树（具有根结点 root）， 一个目标结点 target ，和一个整数值 K 。

返回到目标结点 target 距离为 K 的所有结点的值的列表。 答案可以以任何顺序返回。



示例 1：

输入：root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2
输出：[7,4,1]
解释：
所求结点为与目标结点（值为 5）距离为 2 的结点，
值分别为 7，4，以及 1
*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 /*
首先使用 DFS 遍历二叉树，为每个节点保存其父结点；
使用 BFS 向三个方向搜索（左孩子、右孩子、父结点），当搜索第 K 次时，队列中的全部结点即为所求；

注意：

BFS 要保存已访问结点；
每次都将当前队列中全部元素向外延伸一个结点；

 */
void dfs(struct List *listFather, struct TreeNode* root, struct TreeNode* father)
{
	if (root == NULL) {
		return;
	}

	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry));
	entry->cur = root;
	entry->father = father;
	entry->visited = 0;
	ListAddTail(listFather, &entry->node);

	dfs(listFather, root->left, root);
	dfs(listFather, root->right, root);
}

void setVisited(struct List *list, struct TreeNode* target)
{
	struct Node *node = NULL;
	struct DataEntry *entry = NULL;

	LIST_FOR_EACH(node, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if (entry->cur == target) {
			entry->visited = 1;
		}
	}
}

bool checkVisited(struct List *list, struct TreeNode* target)
{
	struct Node *node = NULL;
	struct DataEntry *entry = NULL;

	LIST_FOR_EACH(node, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if (entry->cur == target) {
			return entry->visited;
		}
	}

	return false;
}

struct TreeNode* getFather(struct List *list, struct TreeNode* target)
{
	struct Node *node = NULL;
	struct DataEntry *entry = NULL;

	LIST_FOR_EACH(node, list) {
		entry = NODE_ENTRY(node, struct DataEntry, node);
		if (entry->cur == target) {
			return entry->father;
		}
	}

	return NULL;
}


int* distanceK(struct TreeNode* root, struct TreeNode* target, int K, int* returnSize)
{
	struct List dListFather;
	struct List *listFather = &dListFather;

	ListInit(listFather);
	dfs(listFather, root, NULL); //记录父结点

	struct List dqueue;
	struct List *queue = &dqueue;

	queue_init(queue);

	struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
	entry->cur = target;
	ListAddTail(queue, &entry->node);
	setVisited(listFather, target);

	while(!queue_empty(queue)) {
		if (K-- == 0) {
			*returnSize = 0;
			int *res = (int *)calloc(2048, sizeof(int));
			while(!queue_empty(queue)) {
				struct DataEntry *pop = queue_pop_entry(queue);
				res[*returnSize] = pop->cur->val;
				(*returnSize)++;
			}

			return res;
		}

		int qSize = queue_size(queue);
		for (int i = 0; i < qSize; i++) {
			struct DataEntry *pop = queue_pop_entry(queue);
			if (pop->cur->left && !checkVisited(listFather, pop->cur->left)) {
				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->cur = pop->cur->left;
				ListAddTail(queue, &entry->node);
				setVisited(listFather, pop->cur->left);
			}

			if (pop->cur->right && !checkVisited(listFather, pop->cur->right)) {
				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->cur = pop->cur->right;
				ListAddTail(queue, &entry->node);
				setVisited(listFather, pop->cur->right);
			}

			struct TreeNode* father = getFather(listFather, pop->cur);
			if (father != NULL && !checkVisited(listFather, father)) {
				struct DataEntry  *entry = (struct DataEntry  *)calloc(1, sizeof(struct DataEntry ));
				entry->cur = father;
				ListAddTail(queue, &entry->node);
				setVisited(listFather, father);
			}
		}
	}

	return NULL;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#define MAXSIZE 510
struct TreeNode** parent_array;
int flag[MAXSIZE];
int count;

void get_parent(struct TreeNode* node, struct TreeNode** parent_array);
void dfs(struct TreeNode* node, int K, int dis, int* res);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* distanceK(struct TreeNode* root, struct TreeNode* target, int K, int* returnSize)
{
    if (root == NULL || target == NULL || K < 0 || K > 500) {
        *returnSize = 0;
        return NULL;
    }

    // 父结点数组申请内存
    parent_array = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * MAXSIZE);
    memset(parent_array, 0, MAXSIZE * sizeof(struct TreeNode*));
    // flag数组初始化，用于标记访问过的结点
    memset(flag, 0, MAXSIZE * sizeof(int));
    // 存放满足要求的结点值的结果数组
    int *res = (int *)malloc(sizeof(int) * MAXSIZE);
    memset(res, -1, MAXSIZE * sizeof(int));

    // 二叉树遍历找到每个结点的父结点，将该结点的值作为parent_array的索引，在parent_array中存放对应父结点
    get_parent(root, parent_array);

    // DFS搜索
    count = 0;
    flag[target->val] = 1;
    dfs(target, K, 0, res);

    // 返回结果
    *returnSize = count;
    return res;
}

void get_parent(struct TreeNode* node, struct TreeNode** parent_array)
{
    if (node->right != NULL) {
        parent_array[node->right->val] = node;
        get_parent(node->right, parent_array);
    }
    if (node->left != NULL) {
        parent_array[node->left->val] = node;
        get_parent(node->left, parent_array);
    }
}

void dfs(struct TreeNode* node, int K, int dis, int* res)
{
    if (dis == K) {
        res[count] = node->val;
        count++;
        return;
    }

    if (node->left != NULL && flag[node->left->val] != 1) {
        flag[node->left->val] = 1;
        dfs(node->left, K, dis + 1, res);
    }

    if (node->right != NULL && flag[node->right->val] != 1) {
        flag[node->right->val] = 1;
        dfs(node->right, K, dis + 1, res);
    }

    if (parent_array[node->val] != 0 && flag[parent_array[node->val]->val] != 1) {
        flag[parent_array[node->val]->val] = 1;
        dfs(parent_array[node->val], K, dis + 1, res);
    }
}

/*
1102. 得分最高的路径
难度中等33
给你一个 R 行 C 列的整数矩阵 A。矩阵上的路径从 [0,0] 开始，在 [R-1,C-1] 结束。
路径沿四个基本方向（上、下、左、右）展开，从一个已访问单元格移动到任一相邻的未访问单元格。
路径的得分是该路径上的 最小 值。例如，路径 8 →  4 →  5 →  9 的值为 4 。
找出所有路径中得分 最高 的那条路径，返回其 得分。

示例 1：

输入：[[5,4,5],[1,2,6],[7,4,6]]
输出：4
解释：
得分最高的路径用黄色突出显示。

*/

/*
不能直接每次取路径中的最大值当做下一条路径，需要利用优先队列，把当前所有能走的路，按分值从大到小排好序，不能做剪枝，否则可能会无解；每次都走当前路径中的最大值，则最后走到终点时，自然就是所有路径中分值的最大值，返回结果即可；每次取出当前点的时候，要计算一下当前的结果，更新最大分数。作者：goodgoodstudy-5链接：https://leetcode-cn.com/problems/path-with-maximum-minimum-value/solution/li-yong-you-xian-dui-lie-bfsqiu-lu-jing-zhong-de-z/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int maximumMinimumPath(int** A, int ASize, int* AColSize)
{
	int row = ASize;
	int col = AColSize[0];

	struct HeapSort *hp = heapsort_init(col * row, PRIORITY_QUEUE_MAX);
	int visited[row][col];
	memset(visited, 0, sizeof(visited));

	struct heapEntry node;
	node.key = A[0][0];
	node.x = 0;
	node.y = 0;
	heapsort_push(hp, node);
	visited[0][0] = 1;

	int d[4][2] = { { 0, 1 }, { 1, 0 }, { -1, 0 }, { 0, -1 } };
	int res = INT_MAX;
	while(!heapsort_empty(hp)) {
		struct heapEntry pop = heapsort_pop(hp);
		res = fmin(res, pop.key);
		if (pop.x == row -1 && pop.y == col - 1) {
			return res;
		}

		for (int i = 0; i < 4; i++) {
			int x = pop.x + d[i][0];
			int y = pop.y + d[i][1];

			if (x < 0 || x >= row || y < 0 || y >= col) {
				continue;
			}

			if (visited[x][y] == 1) {
				continue;
			}

			struct heapEntry node;
			node.key = A[x][y];
			node.x = x;
			node.y = y;
			heapsort_push(hp, node);
			visited[x][y] = 1;
		}
	}

	return res;
}

