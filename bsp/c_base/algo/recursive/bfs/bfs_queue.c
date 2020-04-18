/*
BFS模板

条件判断（边界判断，其他要求的判断）

创建队列

在队列中加入第一个满足条件的元素

while(队列不为空) {
    取出队列头部元素
    操作
    根据头部元素，往队列中再次加入满足条件的元素
}

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>


/*
[
[2,1,1],
[1,1,0],
[0,1,1]
]
*/

struct queue_load{
	int num;
	int deep;
};


/*
在给定的网格中，每个单元格可以有以下三个值之一：

值 0 代表空单元格；
值 1 代表新鲜橘子；
值 2 代表腐烂的橘子。
每分钟，任何与腐烂的橘子（在 4 个正方向上）相邻的新鲜橘子都会腐烂。

返回直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1。

方法：广度优先搜索
思路

每一轮，腐烂将会从每一个烂橘子蔓延到与其相邻的新鲜橘子上。一开始，腐烂的橘子的深度为 0，每一轮腐烂会从腐烂橘子传染到之相邻新鲜橘子上，并且设置这些新的腐烂橘子的深度为自己深度 +1，我们想知道完成这个过程之后的最大深度值是多少。

算法

我们可以用一个广度优先搜索来建模这一过程。因为我们总是选择去使用深度值最小的（且之前未使用过的）腐烂橘子去腐化新鲜橘子，如此保证每一个橘子腐烂时的深度标号也是最小的。

我们还应该检查最终状态下，是否还有新鲜橘子。

*/
int orangesRotting(int** grid, int gridSize, int* gridColSize){
		int ans = 0;
		int dr[] = { -1,0,1,0 };
		int dc[] = { 0,-1,0,1 };
		int row = gridSize, col = gridColSize[0];

		struct queue_blk *queue = create_array_queue(row*col);

		for(int r=0;r<row;r++)
			for(int c=0;c<col;c++)
				if (grid[r][c] == 2){
					struct queue_load load;
					load.deep = 0;
					load.num = r*col + c;
					push(queue,load);
				}

		while (!is_empty(queue)) {
			struct queue_load curr = pop(queue);
			int r = curr.num / col, c = curr.num % col;
			for (int k = 0; k < 4; k++) {
				int nr = r + dr[k];
				int nc = c + dc[k];
				if (0 <= nr && nr < row && 0 <= nc && nc < col && grid[nr][nc] == 1) {
					grid[nr][nc] = 2;
					struct queue_load load;
					load.num = nr * col + nc;
					load.deep = curr.deep + 1;
					push(queue,load);
					ans = curr.deep + 1;
				}
			}
		}

		for(int r=0;r<row;r++)
			for(int c=0;c<col;c++)
				if (grid[r][c] == 1){
					return -1;
				}

		return ans;
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