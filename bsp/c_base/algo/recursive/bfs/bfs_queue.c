/*         BFS

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


1)上下左右或者8个方向
2)相互依次依赖抽象入度出度
	入度前置条件
	出度后置条件
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

/*
733. 图像渲染
see dfs floodFill*/
int** floodFill(int** image, int imageSize, int* imageColSize,
	int sr, int sc, int newColor, int* returnSize, int** returnColumnSizes)
{
	int row = imageSize;
	int col = imageColSize[0];

	*returnSize = imageSize;
	*returnColumnSizes = imageColSize;

	if (newColor == image[sr][sc]) {
		return image;
	}

	int queue[row * col];
	int head = 0;
	int rear = 0;

	queue[rear++] = sr * col + sc;
	int oldColor = image[sr][sc];
	image[sr][sc] = newColor;

	int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	int deep = 0;
	while(rear != head) {
		int floorSize = rear - head;
		deep++;

		for (int i = 0; i < floorSize; i++) {
			int pop = queue[head++];
			int pop_x = pop / col;
			int pop_y = pop % col;

			for (int k = 0; k < 4; k++) {
				int nx = pop_x + d[k][0];
				int ny = pop_y + d[k][1];

				if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
					continue;
				}

				if (image[nx][ny] != oldColor) {
					continue;
				}

				image[nx][ny] = newColor;
				queue[rear++] = nx * col + ny;
			}
		}
	}

	return image;
}


/*
200. 岛屿数量
难度中等647
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，
请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向或竖直方向
上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。

示例 1:
输入:
[
['1','1','1','1','0'],
['1','1','0','1','0'],
['1','1','0','0','0'],
['0','0','0','0','0']
]
输出: 1
*/
void bfs(char** grid, int row, int col, int x, int y)
{
	int queue[row * col];
	int head = 0;
	int rear = 0;

	queue[rear++] = x * col + y;
	grid[x][y] = '0';

	int d[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
	int deep = 0;
	while(head != rear) {
		int floorSize = rear - head;
		deep++;

		for (int i = 0; i < floorSize; i++) {
			int pop = queue[head++];
			int popx = pop / col;
			int popy = pop % col;

			for (int k = 0; k < 4; k++) {
				int nx = popx + d[k][0];
				int ny = popy + d[k][1];

				if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
					continue;
				}

				if (grid[nx][ny] != '1') {
					continue;
				}

				grid[nx][ny] = '0';
				queue[rear++] = nx * col +ny;
			}
		}
	}
}

int numIslands(char** grid, int gridSize, int* gridColSize)
{
	int row = gridSize;
	int col = gridColSize[0];

	if (grid == NULL || gridSize <= 0 || gridColSize == NULL)
		return 0;

	int num = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (grid[i][j] == '1') {
				num++;
				bfs(grid, row, col, i, j);
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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char** updateBoard(char** board, int boardSize, int* boardColSize,
	int* click, int clickSize, int* returnSize, int** returnColumnSizes)
{
	int row = boardSize;
	int col = boardColSize[0];
	int queue[row * col * 1000];
	int head = 0;
	int rear = 0;

	*returnSize = boardSize;
	*returnColumnSizes = boardColSize;
	if (board == NULL || boardSize <= 0 || boardColSize == NULL || click == NULL || clickSize != 2)
		return board;

	queue[rear++] = click[0] * col + click[1];

	int deep = 0;
	int d[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, -1}, {-1, 1}, {-1, -1}, {1, 1}};
	while(head != rear) {
		int floorSize = rear - head;
		deep++;
		for (int i = 0; i < floorSize; i++) {
			int pop = queue[head++];
			int popx = pop / col;
			int popy = pop % col;

			if (board[popx][popy] == 'M') {
				board[popx][popy] = 'X';
				return board;
			}

			int mineCnt = 0;
			for (int k = 0; k < 8; k++) {
				int nx = popx + d[k][0];
				int ny = popy + d[k][1];

				if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
					continue;
				}

				if (board[nx][ny] == 'M') {
					mineCnt++;
				}
			}

			if (mineCnt > 0 && board[popx][popy] == 'E') {
				board[popx][popy] = '0' + mineCnt;
			} else if (board[popx][popy] == 'E'){
				board[popx][popy] = 'B';
				for (int k = 0; k < 8; k++) {
					int nx = popx + d[k][0];
					int ny = popy + d[k][1];

					if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
						continue;
					}

					queue[rear++] = nx * col + ny;
				}
			}
		}
	}

	return board;
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
	int inDegree[numCourses];
	memset(inDegree, 0, sizeof(inDegree));//!!!
	for (int i = 0; i < prerequisitesSize; i++) {
		inDegree[prerequisites[i][0]]++;
	}

	int queue[numCourses];
	int head = 0;
	int rear = 0;

	for (int i = 0; i < numCourses; i++) {
		if (inDegree[i] == 0) {
			queue[rear++] = i;
		}
	}

	int cnt = 0;
	while(head != rear) {
		int floorSize = rear - head;
		for (int k = 0; k < floorSize; k++) {
			int pop = queue[head++];
			cnt++;
			for (int i = 0 ; i < prerequisitesSize; i++) {
				if (prerequisites[i][1] == pop) {
					int x = prerequisites[i][0];
					inDegree[x]--;
					if (inDegree[x] == 0) {
						queue[rear++] = x;
					}
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
在选修某些课程之前需要一些先修课程。 例如，想要学习
课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]
给定课程总量以及它们的先决条件，返回你为了学完所有课程
所安排的学习顺序。
可能会有多个正确的顺序，你只要返回一种就可以了。
如果不可能完成所有课程，返回一个空数组。
示例 1:
输入: 2, [[1,0]]
输出: [0,1]
解释: 总共有 2 门课程。要学习课程 1，你需要先完成课程 0。
因此，正确的课程顺序为 [0,1] 。
示例 2:
输入: 4, [[1,0],[2,0],[3,1],[3,2]]
输出: [0,1,2,3] or [0,2,1,3]
解释: 总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和
课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
因此，一个正确的课程顺序是 [0,1,2,3] 。另一个正确的排序是 [0,2,1,3] 。
说明:
1.	输入的先决条件是由边缘列表表示的图形，而不是邻接矩阵。详情请参见图的表示法。
2.	你可以假定输入的先决条件中没有重复的边。
*/
/*
拓扑排序入度：设有向图中有一结点 v ，其入度即为当前所有
从其他结点出发，终点为 v 的的边的数目。出度：设有向图中
有一结点 v ，其出度即为当前所有起点为 v ，指向其他结点的
边的数目。每次从入度为 0 的结点开始，加入队列。入度为
0 ，表示没有前置结点。处理入度为 0 的结点，把这个结点指
向的结点的入度 -1 。再把新的入度为 0 的结点加入队列。如果
队列都处理完毕，但是和总结点数不符，说明有些结点形成环。
*/
int* findOrder(int numCourses, int** prerequisites,
int prerequisitesSize, int* prerequisitesColSize, int* returnSize)
{
	int inDegree[numCourses];
	memset(inDegree, 0, sizeof(inDegree));
	for (int i = 0; i < prerequisitesSize; i++) {
		inDegree[prerequisites[i][0]]++;
	}

	int queue[numCourses];
	int head = 0;
	int rear = 0;

	for (int i = 0; i < numCourses; i++) {
		if (inDegree[i] == 0) {
			queue[rear++] = i;
		}
	}

	int *res = (int *)calloc(numCourses, sizeof(int));
	*returnSize = 0;
	while(head != rear) {
		int pop = queue[head++];//在队列中都是入度为0的对象

		res[*returnSize] = pop;
		(*returnSize)++;

		for (int i = 0; i < prerequisitesSize; i++) {
			if (prerequisites[i][1] == pop) {
				int nextCourse = prerequisites[i][0];
				if(--inDegree[nextCourse] == 0) {
					queue[rear++] = nextCourse;
				}
			}
		}
	}

	if (*returnSize != numCourses) {
		*returnSize = 0;
	}
	return res;
}

/*
279. 完全平方数
给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）
使得它们的和等于 n。你需要让组成和的完全平方数的个数
最少。

示例 1:

输入: n = 12
输出: 3
解释: 12 = 4 + 4 + 4.
示例 2:

输入: n = 13
输出: 2
解释: 13 = 4 + 9.
*/
int numSquares(int n)
{
	int queue[1024 * 1024 * 10];
	int head = 0;
	int rear = 0;

	queue[rear++] = n;
	int deep = 0;

	while(head != rear) {
		deep++;

		// 每一层的广度遍历
		int floorSize = rear - head;
		for (int i = 0; i < floorSize; i++) {
			int top = queue[head++];
			for (int j = 1; j <= sqrt(top); j++) {
				int target = top - pow(j, 2);
				// 说明已到最大平方数
				if (target < 0)
					break;
				/* 由于是广度遍历，所以当遍历到0时，
				肯定是最短路径*/
				if (target == 0)
					return deep;

				queue[rear++] = target;
			}
		}
	}

	return -1;
}


/*
752. 打开转盘锁
难度中等106
你有一个带有四个圆形拨轮的转盘锁。每个拨轮都有10个数字
： '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' 。每个拨轮可以自由旋转：
例如把 '9' 变为  '0'，'0' 变为 '9' 。每次旋转都只能旋转一个拨轮的
一位数字。
锁的初始数字为 '0000' ，一个代表四个拨轮的数字的字符串。
列表 deadends 包含了一组死亡数字，一旦拨轮的数字和列表里的
任何一个元素相同，这个锁将会被永久锁定，无法再被旋转。
字符串 target 代表可以解锁的数字，你需要给出最小的旋转次数，
如果无论如何不能解锁，返回 -1。
示例 1:
输入：deadends = ["0201","0101","0102","1212","2002"], target = "0202"
输出：6
解释：
可能的移动序列为 "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202"。
注意 "0000" -> "0001" -> "0002" -> "0102" -> "0202" 这样的序列是不能解锁的，
因为当拨动到 "0102" 时这个锁就会被锁定。
*/
/*
我们可以将 0000 到 9999 这 10000 状态看成图上的 10000 个节点，
两个节点之间存在一条边，当且仅当这两个节点对应的状态
只有 1 位不同，且不同的那位相差 1（包括 0 和 9 也相差 1 的情况），
并且这两个节点均不在数组 deadends 中。那么最终的答案即为 0000
到 target 的最短路径。

我们用广度优先搜索来找到最短路径，从 0000 开始搜索。
对于每一个状态，它可以扩展到最多 8 个状态，
即将它的第 i = 0, 1, 2, 3 位增加 1 或减少 1，将这些状态中没有搜索
过并且不在 deadends 中的状态全部加入到队列中，
并继续进行搜索。注意 0000 本身有可能也在 deadends 中。

*/
#define VISITED_OFFSET 10000
int openLock(char ** deadends, int deadendsSize, char * target)
{
	int i,j,k, ret, floorSize, deep = -1;
	char start[] = "0000";

	if (strcmp(start, target) == 0)
		return 0;

	int targetint = atoi(target);

	int queue[10000];
	int head = 0;
	int rear = 0;
	int visited[20000];
	memset(visited, 0, sizeof(visited));

    	for (i = 0; i < deadendsSize; i++) {
		int deadint = atoi(deadends[i]);
		visited[deadint + VISITED_OFFSET] = 1;
	}

	int startint = atoi(start);
	if (visited[startint + VISITED_OFFSET] == 1)
		return -1;

	queue[rear++] = startint;
	visited[startint + VISITED_OFFSET] = 1;

    	while(head != rear) {
	        ++deep;
	        floorSize = rear - head;
	        for (k = 0; k < floorSize; k++) {
			int pop = queue[head++];
	                if (pop == targetint) {
				return deep;
	                }

	            	for (i = 0; i < 4; i++) {//四个位置
				for (j = -1; j < 2; j += 2) {// 2个方向
					char newstr[6];
					sprintf(newstr, "%04d", pop);
					newstr[i] = (newstr[i] - '0' + j + 10)%10 + '0';
					int newobj = atoi(newstr);
					if (visited[newobj + VISITED_OFFSET] == 1) {
						continue;
					}

					queue[rear++] = newobj;
					visited[newobj + VISITED_OFFSET] = 1;
				}
			}
		}
	}

	return -1;
}

/*
1102. 得分最高的路径
难度中等33
给你一个 R 行 C 列的整数矩阵 A。矩阵上的路径从 [0,0] 开始，
在 [R-1,C-1] 结束。
路径沿四个基本方向（上、下、左、右）展开，
从一个已访问单元格移动到任一相邻的未访问单元格。
路径的得分是该路径上的 最小 值。例如，路径 8 →  4 →  5 →  9
的值为 4 。
找出所有路径中得分 最高 的那条路径，返回其 得分。

示例 1：

输入：[[5,4,5],[1,2,6],[7,4,6]]
输出：4
解释：
得分最高的路径用黄色突出显示。

*/

/*
不能直接每次取路径中的最大值当做下一条路径，
需要利用优先队列，把当前所有能走的路，按分值从大到小
排好序，不能做剪枝，否则可能会无解；每次都走当前路径
中的最大值，则最后走到终点时，自然就是所有路径中分值
的最大值，返回结果即可；每次取出当前点的时候，要计算一
下当前的结果，更新最大分数。
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

/*
317. 离建筑物最近的距离
难度困难29
你是个房地产开发商，想要选择一片空地 建一栋大楼。你想把这栋大楼够造在一个距离周边设施都比较方便的地方，通过调研，你希望从它出发能在 最短的距离和 内抵达周边全部的建筑物。请你计算出这个最佳的选址到周边全部建筑物的 最短距离和。

提示：
你只能通过向上、下、左、右四个方向上移动。
给你一个由 0、1 和 2 组成的二维网格，其中：
"	0 代表你可以自由通过和选择建造的空地
"	1 代表你无法通行的建筑物
"	2 代表你无法通行的障碍物

示例：
输入：[[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]

1 - 0 - 2 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0
输出：7
解析：
给定三个建筑物 (0,0)、(0,4) 和 (2,2) 以及一个位于 (0,2) 的障碍物。
由于总距离之和 3+3+1=7 最优，所以位置 (1,2) 是符合要求的最优地点，故返回7。
*/
#define QUEUE_LEN (10000)
int MinDist(int sum, int res){
    if(sum < res){
        return sum;
    }
    return res;
}
int shortestDistance(int** grid, int gridSize, int* gridColSize){
    int sum[gridSize][*gridColSize];
    memset(sum, 0, gridSize * (*gridColSize) * sizeof(int));
    int dist[gridSize][*gridColSize];
    memset(dist, 0, gridSize * (*gridColSize) * sizeof(int));
    int queue[QUEUE_LEN][2];
    memset(queue, 0, QUEUE_LEN * 2 * sizeof(int));
    int dirlist[][2] = { { -1, 0 }, { 1, 0 }, { 0, 1 }, { 0, -1 } };
    int head = 0;
    int tail = 0;
    int res = INT_MAX;

    int val = 0;
    for(int i  = 0; i < gridSize; i++){
        for(int j = 0; j < *gridColSize; j++){
            if(grid[i][j] == 1){
                queue[tail][0] = i;
                queue[tail][1] = j;
                tail++;
               // printf("pos is [%d, %d]", i, j);
                res = INT_MAX;
                while(head != tail){
                    int a = queue[head][0];
                    int b = queue[head][1];
                    head++;
                    for(int k = 0; k < 4; k++){
                        int x = a + dirlist[k][0];
                        int y = b + dirlist[k][1];
                        if(x >= 0 && x < gridSize && y >= 0 && y < *gridColSize && grid[x][y] == val){
                            --grid[x][y];
                            dist[x][y] = dist[a][b] + 1;
                            sum[x][y] += dist[x][y];// todo
                            res = MinDist(sum[x][y], res);
                            queue[tail][0] = x;
                            queue[tail][1] = y;
                            tail++;
                        }
                    }
                }
                val--;
                if(res == INT_MAX){
                    return -1;
                }
            }
        }
    }
    return res;
}
