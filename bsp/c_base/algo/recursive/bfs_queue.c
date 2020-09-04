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
	grid[x][y] = '0'; /*先修改后加入queue，减少入队*/

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
407. 接雨水 II
难度困难214
给你一个 m x n 的矩阵，其中的值均为非负整数，代表二维高度图每个单元的高度，请计算图中形状最多能接多少体积的雨水。

示例：
给出如下 3x6 的高度图:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]

返回 4 。
*/
/*
Given the following 3x6 height map:
[
[1,4,3,1,3,2],
[3,2,1,3,2,4],
[2,3,3,2,3,1]
]
*/

/*
Q<x,y,h>：优先级队列；
将地图的四周作为第一个边界，存入Q；
总储水量 = 0;
while(Q不空){
    <x,y,h> = Q弹出堆顶;
    for(<nx,ny> in <x,y>的上下左右){
        if(<nx,ny> 在图上 且 在边界内部){
            总储水量 += max(0, h - <nx,ny>的高度);
            新边界位置<nx,ny, max(h,<nx,ny>的高度)>入Q;
        }
    }
}
*/
/*
假设"第一个元素"在数组中的索引为 0 的话，
则父节点和子节点的位置关系如下：
(01) 索引为i的左孩子的索引是 (2*i+1);
(02) 索引为i的左孩子的索引是 (2*i+2);
(03) 索引为i的父结点的索引是 floor((i-1)/2);

二叉堆的核心是"添加节点"和"删除节点"

第K小元素 ----大堆栈
*/
#define PRIORITY_QUEUE_MIN
int dirR[4] = {-1, 0, 1, 0};
int dirC[4] = {0, 1, 0, -1};
int trapRainWater(int** heightMap, int heightMapSize, int* heightMapColSize)
{
	int row = heightMapSize;
	int col = *heightMapColSize;

	if (row == 0 || col ==0) return 0;

	int hpSzie = fmax(1024, row * col);
	struct HeapCtrl *hp = heapInit(hpSzie);
	// 是否访问到；是否在围墙外层
	int visited[row][col];
	memset(visited, 0, sizeof(visited));

	// 边界入堆
        for (int i =0; i< col; i++){
		struct heapEntry node;
		node.x = 0;
		node.y = i;
		node.key = heightMap[0][i];
		heapPush(hp,node);

		node.x = row - 1;
		node.y = i;
		node.key = heightMap[row-1][i];
		heapPush(hp,node);

            visited[0][i] = visited[row-1][i] = 1;
        }

        for (int i = 1; i< row -1; i++){
		struct heapEntry node;
		node.x = i;
		node.y = 0;
		node.key = heightMap[i][0];
		heapPush(hp,node);
		node.x = i;
		node.y = col - 1;
		node.key = heightMap[i][col-1];
		heapPush(hp,node);
              visited[i][0] = visited[i][col-1] = 1;
        }

        int ans = 0;
        while (!heapEmpty(hp)){
            struct heapEntry top = heapPop(hp);

            for (int d = 0; d< 4; d++) {
		int nx = dirR[d] + top.x;
		int ny = dirC[d] + top.y;
		if (nx <0 || nx >=row || ny < 0|| ny >= col)
			continue;
		if (visited[nx][ny])
			continue;
		visited[nx][ny] = 1;
		if (heightMap[nx][ny] < top.key){
			ans += (top.key - heightMap[nx][ny]);
		}
		struct heapEntry node;
		node.x = nx;
		node.y = ny;
		node.key = fmax(top.key, heightMap[nx][ny]);
		heapPush(hp,node);
            }
        }
        return ans;
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


/*
490. 迷宫
难度中等43
由空地和墙组成的迷宫中有一个球。球可以向上下左右四个方向滚动，但在遇到墙壁前不会停止滚动。当球停下时，可以选择下一个方向。
给定球的起始位置，目的地和迷宫，判断球能否在目的地停下。
迷宫由一个0和1的二维数组表示。 1表示墙壁，0表示空地。你可以假定迷宫的边缘都是墙壁。起始位置和目的地的坐标通过行号和列号给出。

示例 1:
输入 1: 迷宫由以下二维数组表示

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

输入 2: 起始位置坐标 (rowStart, colStart) = (0, 4)
输入 3: 目的地坐标 (rowDest, colDest) = (4, 4)

输出: true

*/
bool hasPath(int** maze, int mazeSize, int* mazeColSize, int* start, int startSize,
int* destination, int destinationSize)
{
	int row = mazeSize;
	int col = *mazeColSize;

	int visited[row][col];
	memset(visited, 0, sizeof(visited));

        int dirs[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
	int queueSize = fmax(1024, row * col);
	int queue[queueSize];
	memset(queue, 0, sizeof(queue));
	int head = 0;
	int rear = 0;
        queue[rear++] = start[0] * col + start[1];
        visited[start[0]][start[1]] = true;
        while (head != rear) {
		int top = queue[head++];
		int s[2];
		s[0] = top / col;
		s[1] = top % col;

            if (s[0] == destination[0] && s[1] == destination[1])
                return true;
            for (int i = 0; i < 4; i++) {
                int x = s[0] + dirs[i][0];
                int y = s[1] + dirs[i][1];
                while (x >= 0 && y >= 0 && x < row && y < col && maze[x][y] == 0) {
                    x += dirs[i][0];
                    y += dirs[i][1];
                }

			x -= dirs[i][0];
			y -= dirs[i][1];

                if (visited[x][y] == 0) {
			queue[rear++] = x * col + y;
                    visited[x][y] = 1;
                }
            }
        }
        return false;
}

/*
505. 迷宫 II
难度中等32
由空地和墙组成的迷宫中有一个球。球可以向上下左右四个方向滚动，但在遇到墙壁前不会停止滚动。当球停下时，可以选择下一个方向。
给定球的起始位置，目的地和迷宫，找出让球停在目的地的最短距离。距离的定义是球从起始位置（不包括）到目的地（包括）经过的空地个数。如果球无法停在目的地，返回 -1。
迷宫由一个0和1的二维数组表示。 1表示墙壁，0表示空地。你可以假定迷宫的边缘都是墙壁。起始位置和目的地的坐标通过行号和列号给出。

示例 1:
输入 1: 迷宫由以下二维数组表示

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

输入 2: 起始位置坐标 (rowStart, colStart) = (0, 4)
输入 3: 目的地坐标 (rowDest, colDest) = (4, 4)

输出: 12

解析: 一条最短路径 : left -> down -> left -> down -> right -> down -> right。
             总距离为 1 + 1 + 3 + 1 + 2 + 2 + 2 = 12。

*/
int shortestDistance(int** maze, int mazeSize, int* mazeColSize,
int* start, int startSize, int* destination, int destinationSize){
	int row = mazeSize;
	int col = *mazeColSize;

	int distance[row][col];
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			distance[i][j] = INT_MAX;
		}
	}

	int dirs[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
	int queueSize = fmax(1024, row * col);
	int queue[queueSize];
	memset(queue, 0, sizeof(queue));
	int head = 0;
	int rear = 0;
	queue[rear++] = start[0] * col + start[1];
	distance[start[0]][start[1]] = 0;

        while (head != rear) {
		int top = queue[head++];
		int s[2];
		s[0] = top / col;
		s[1] = top % col;
            for (int i = 0; i < 4; i++) {
                int x = s[0] + dirs[i][0];
                int y = s[1] + dirs[i][1];
			int count = 0;
                while (x >= 0 && y >= 0 && x < row && y < col && maze[x][y] == 0) {
                    x += dirs[i][0];
                    y += dirs[i][1];
			count++;
                }

			x -= dirs[i][0];
			y -= dirs[i][1];

			if (distance[s[0]][s[1]] + count < distance[x][y]) {
				distance[x][y] = distance[s[0]][s[1]] + count;
				queue[rear++] = x * col + y;
			}
            }
        }

        return distance[destination[0]][destination[1]] == INT_MAX ? -1 : distance[destination[0]][destination[1]];
}

/*
499. 迷宫 III
由空地和墙组成的迷宫中有一个球。球可以向上（u）下（d）左（l）右（r）四个方向滚动，但在遇到墙壁前不会停止滚动。当球停下时，可以选择下一个方向。迷宫中还有一个洞，当球运动经过洞时，就会掉进洞里。

给定球的起始位置，目的地和迷宫，找出让球以最短距离掉进洞里的路径。 距离的定义是球从起始位置（不包括）到目的地（包括）经过的空地个数。通过'u', 'd', 'l' 和 'r'输出球的移动方向。 由于可能有多条最短路径， 请输出字典序最小的路径。如果球无法进入洞，输出"impossible"。

迷宫由一个0和1的二维数组表示。 1表示墙壁，0表示空地。你可以假定迷宫的边缘都是墙壁。起始位置和目的地的坐标通过行号和列号给出。



示例1:

输入 1: 迷宫由以下二维数组表示

0 0 0 0 0
1 1 0 0 1
0 0 0 0 0
0 1 0 0 1
0 1 0 0 0
*/
#define MAX_ROW 30
#define MAX_COL 30

typedef struct MazeSearch_t {
    int visited;
    int step;
    char* path;
}MazeSearch;

MazeSearch g_MazeSearch[MAX_ROW][MAX_COL];

void directMove(int** maze, int row, int col, int* hole,
	int curIdx, int *queue, int dir, int *head, int *rear)
{
	int curStep;
	char *curPath;
	int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	char str[4] = {'d', 'u', 'r', 'l'};

	int curRow = curIdx / col;
	int curCol = curIdx % col;
	curStep = g_MazeSearch[curRow][curCol].step;
	curPath = g_MazeSearch[curRow][curCol].path;

	int nextRow = curRow;
	int nextCol = curCol;
	while(((nextRow + dirs[dir][0]) >= 0) && ((nextRow + dirs[dir][0]) < row)
		&& ((nextCol + dirs[dir][1]) >= 0) && ((nextCol + dirs[dir][1]) < col)) {

		if (maze[nextRow + dirs[dir][0]][nextCol + dirs[dir][1]] == 1) // 1表示墙壁
			break;

		nextRow += dirs[dir][0];
		nextCol += dirs[dir][1];
		curStep++;

		if ((nextRow == hole[0]) && (nextCol == hole[1])) // 洞
			break;

		if (g_MazeSearch[nextRow][nextCol].visited == 1)
			return;
	}

	if (curStep == g_MazeSearch[curRow][curCol].step)
		return;
	if ((g_MazeSearch[hole[0]][hole[1]].step > 0) && (curStep > g_MazeSearch[hole[0]][hole[1]].step))
		return;
	if ((g_MazeSearch[nextRow][nextCol].step > 0) && (curStep > g_MazeSearch[nextRow][nextCol].step))
		return;

	char* newPath = (char*)malloc(sizeof(char) * (strlen(curPath) + 2));
	snprintf(newPath, strlen(curPath) + 2, "%s%c", curPath, str[dir]);

	if ((g_MazeSearch[nextRow][nextCol].step == curStep) &&
		(strcmp(newPath, g_MazeSearch[nextRow][nextCol].path) >= 0)) {
		free(newPath);
		return;
	}

	g_MazeSearch[nextRow][nextCol].step = curStep;
	if (g_MazeSearch[nextRow][nextCol].path != NULL)
		free(g_MazeSearch[nextRow][nextCol].path);
	g_MazeSearch[nextRow][nextCol].path = newPath;

	if ((nextRow == hole[0]) && (nextCol == hole[1]))
		return;

	queue[*rear] = nextRow * col + nextCol;
	(*rear)++;
}

char* findShortestWay(int** maze, int mazeSize, int* colSize, int* ball, int ballSize, int* hole, int holeSize) {
	int row = mazeSize;
	int col = colSize[0];

	memset(g_MazeSearch, 0, sizeof(g_MazeSearch));
	int  queue[row * col];
	int head = 0;
	int rear = 0;

	queue[rear++] = ball[0] * col + ball[1];
	g_MazeSearch[ball[0]][ball[1]].visited = 1;
	g_MazeSearch[ball[0]][ball[1]].path = (char*)malloc(sizeof(char));
	g_MazeSearch[ball[0]][ball[1]].path = "\0";

	while(head != rear) {
		int pop = queue[head++];
		for (int i = 0; i < 4; i++) {
			directMove(maze, row, col, hole, pop, queue, i, &head, &rear);
		}
	}

	if (g_MazeSearch[hole[0]][hole[1]].path == NULL)
		return "impossible";
	return g_MazeSearch[hole[0]][hole[1]].path;
}

/*
1036. 逃离大迷宫
在一个 10^6 x 10^6 的网格中，每个网格块的坐标为 (x, y)，其中 0 <= x, y < 10^6。

我们从源方格 source 开始出发，意图赶往目标方格 target。每次移动，我们都可以走到网格中在四个方向上相邻的方格，只要该方格不在给出的封锁列表 blocked 上。

只有在可以通过一系列的移动到达目标方格时才返回 true。否则，返回 false。



示例 1：

输入：blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
输出：false
解释：
从源方格无法到达目标方格，因为我们无法在网格中移动。
示例 2：

输入：blocked = [], source = [0,0], target = [999999,999999]
输出：true
解释：
因为没有方格被封锁，所以一定可以到达目标方格。
*/
struct node {
    int x;
    int y;
};

int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// -1表示被困住了，2表示达到了目的地，1表示超过了len的封锁
int bfs(int* source, int* target, int** blocked , int blockedSize) {
    struct node nn[100000] = {0};
    int cnt = 1;
    nn[0].x = source[0];
    nn[0].y = source[1];
    int ll = 2 * (blockedSize + 2);
    bool visited[ll][ll];
    memset(visited, 0, ll*ll);
    int cur = 0;
    while (cur < cnt) {
        struct node n = nn[cur++];
        int x = n.x;
        int y = n.y;
        int disx = x - source[0] > 0 ? x - source[0] : source[0] - x;
        int disy = y - source[1] > 0 ? y - source[1] : source[1] - y;
        if (disx > blockedSize || disy > blockedSize) return 1;
        if (x == target[0] && y == target[1]) return 2;
        for (int i = 0; i < 4; i++) {
            int nx = x + dirs[i][0];
            int ny = y + dirs[i][1];
            if (nx < 0 || nx >= 1000000) continue;
            if (ny < 0 || ny >= 1000000) continue;
            if (visited[nx-source[0]+blockedSize+1][ny-source[1]+blockedSize+1] == 1) continue;
            bool isBlock = false;
            for (int k = 0; k < blockedSize; k++) {
                if (nx == blocked[k][0] && ny == blocked[k][1]) {
                    isBlock = true;
                    break;
                }
            }
            if (isBlock) continue;
            nn[cnt].x = nx;
            nn[cnt].y = ny;
            cnt++;
            visited[nx-source[0]+blockedSize+1][ny-source[1]+blockedSize+1] = 1;
        }
    }
    return -1;
}

bool isEscapePossible(int** blocked, int blockedSize, int* blockedColSize, int* source, int sourceSize, int* target, int targetSize){
    // block的长度为len，接住矩形的边，障碍点最多可以封住边长为len的矩形
    // 从source和target按普通的bfs去走，如果碰到了彼此则成功，如果到达点的坐标离起始点坐标大于len则也会成功
    int r = bfs(source, target, blocked, blockedSize);
    if (r == -1) return false;
    if (r == 2) return true;
    r = bfs(target, source, blocked, blockedSize);
    if (r == -1) return false;
    return true;
}

/*
22. 括号生成dfs
bfs  left right 为总数减法到0 */
struct DataEntry {
	int left;
	int right;
	char* path;
};

/*
22. 括号生成dfs
bfs  left right 为总数减法到0 */
char** generateParenthesis(int n, int* returnSize)
{
	*returnSize = 0;
	if (n == 0) {
		return NULL;
	}

	char** res = (char**)calloc(1024 * 1024, sizeof(char*));
	struct DataEntry queue[1024 * 1024];
	int head = 0;
	int rear = 0;
	queue[rear].left= n;
	queue[rear].right = n;
	queue[rear].path = calloc(1, sizeof(char));
	rear++;

	while(head != rear) {
		struct DataEntry pop = queue[head++];
		int popsize = strlen(pop.path);

		if (pop.left == 0 && pop.right == 0) {
			res[*returnSize] = strdup(pop.path);
			(*returnSize)++;
		}

		if (pop.left > 0) {
			queue[rear].left = pop.left - 1;
			queue[rear].right = pop.right;
			queue[rear].path = (char *)calloc(popsize + 2, sizeof(char));
			strcpy(queue[rear].path, pop.path);
			strcat(queue[rear].path, "(");
			rear++;
		}

		if (pop.right > 0 && pop.left < pop.right) {
			queue[rear].left = pop.left;
			queue[rear].right = pop.right - 1;
			queue[rear].path = (char *)calloc(popsize + 2, sizeof(char));
			strcpy(queue[rear].path, pop.path);
			strcat(queue[rear].path, ")");
			rear++;
		}

		free(pop.path);
		pop.path = NULL;
	}

	return res;
}

/*
1293. 网格中的最短路径
难度困难63
给你一个 m * n 的网格，其中每个单元格不是 0（空）就是 1（障碍物）。每一步，您都可以在空白单元格中上、下、左、右移动。
如果您 最多 可以消除 k 个障碍物，请找出从左上角 (0, 0) 到右下角 (m-1, n-1) 的最短路径，并返回通过该路径所需的步数。如果找不到这样的路径，则返回 -1。

示例 1：
输入：
grid =
[[0,0,0],
 [1,1,0],
 [0,0,0],
 [0,1,1],
 [0,0,0]],
k = 1
输出：6
解释：
不消除任何障碍的最短路径是 10。
消除位置 (3,2) 处的障碍后，最短路径是 6 。该路径是 (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).

*/
/*
1 把障碍物k 作为最多可经过多少个障碍
2 使用二位数组visit 作为能否
经过的判断条件（
-1 ：未经过
其他：路径从该点出发 还能再经过的障碍数）
举例1：A路径到达该点时 还可以再经过3个障碍
B路径到达该点时 还可以再经过1个障碍则认为B路径不如A路径，
不能加入队列
举例2：A路径到达该点时 还可以再经过3个障碍B路径到
达该点时 还可以再经过3个障碍则认为B路径与A路径无差别，
不必加入队列ps：3维数组也是这个意思3 C语言使用数据实现队列
通过宏优化代码执行时间（缺点 数组较长）ps：如果使用循环队
列的话 队列长度最大只需要 39394
*/
int shortestPath(int** grid, int gridSize, int* gridColSize, int k)
{
	int row = gridSize;
	int col = *gridColSize;
	int queue[100000][2];//0---xy , 1 --k
	int head = 0;
	int rear = 0;
	queue[rear][0] = 0;
	queue[rear++][1] = k;
	int deep = -1;
	int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	int visited[row][col];
	memset(visited, -1, sizeof(visited));

	while(head != rear) {
		int floorSize = rear - head;
		deep++;
		for (int i = 0; i < floorSize; i++) {
			int cx = queue[head][0] / col;
			int cy = queue[head][0] % col;
			int ck = queue[head++][1];

			if (cx == row -1 && cy == col -1) {
				return deep;
			}

			for (int i = 0; i < 4; i++) {
				int nx = cx + d[i][0];
				int ny = cy + d[i][1];
				int nk = ck;

				if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
					continue;
				}

				if (ck - grid[nx][ny] > visited[nx][ny]) {
					queue[rear][0] = nx * col + ny;
					queue[rear++][1] = ck - grid[nx][ny];
					visited[nx][ny] = ck - grid[nx][ny];
				}
			}
		}
	}

	return -1;
}


/*
542. 01 矩阵
给定一个由 0 和 1 组成的矩阵，找出每个元素到最近的 0 的距离。

两个相邻元素间的距离为 1 。

示例 1:
输入:

0 0 0
0 1 0
0 0 0
*/

int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int** updateMatrix(int** matrix, int matrixSize,
	int* matrixColSize, int* returnSize, int** returnColumnSizes)
{
	int row = matrixSize;
	int col = *matrixColSize;
	int **res = (int **)calloc(row, sizeof(int *));
	for (int i = 0; i < row; i++) {
		res[i] = (int *)calloc(col, sizeof(int));
	}

	int visited[row][col];
	memset(visited, 0, sizeof(visited));
	int queue[10001];
	int head = 0;
	int rear = 0;

	// 将所有的 0 添加进初始队列中
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (matrix[i][j] == 0) {
				queue[rear++] = i * col + j;
				visited[i][j] = 1;
			}
		}
	}

	while (head != rear) {
		int top = queue[head++];
		int i = top / col;
		int j = top % col;
		for (int d = 0; d < 4; ++d) {
			int nx = i + dir[d][0];
			int ny = j + dir[d][1];
			if (nx >= 0 && nx < row && ny >= 0 && ny < col && !visited[nx][ny]) {
				res[nx][ny] = res[i][j] + 1;
				queue[rear++] = nx * col + ny;
				visited[nx][ny] = 1;
			}
		}
	}

	*returnSize = matrixSize;
	*returnColumnSizes = matrixColSize;
	return res;
}

/*
1162. 地图分析
难度中等134
你现在手里有一份大小为 N x N 的「地图」（网格） grid，上面的每个「区域」（单元格）都用 0 和 1 标记好了。其中 0 代表海洋，1 代表陆地，请你找出一个海洋区域，这个海洋区域到离它最近的陆地区域的距离是最大的。
我们这里说的距离是「曼哈顿距离」（ Manhattan Distance）：(x0, y0) 和 (x1, y1) 这两个区域之间的距离是 |x0 - x1| + |y0 - y1| 。
如果我们的地图上只有陆地或者海洋，请返回 -1。

示例 1：

输入：[[1,0,1],[0,0,0],[1,0,1]]
输出：2
解释：
海洋区域 (1, 1) 和所有陆地区域之间的距离都达到最大，最大距离为 2。

*/
/*
[
[1,0,1],
[0,0,0],
[1,0,1]
]
0 --sea
1---land
如果我们的地图上只有陆地或者海洋，请返回 -1。
*/
int maxDistance(int** grid, int gridSize, int* gridColSize)
{
	int queue[100 * 1000];
	int rear = 0;
	int head = 0;
	int row = gridSize;
	int col = *gridColSize;

	int cnt = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (grid[i][j] == 1) {
				queue[rear++] = i * col + j;
				cnt++;
			}
		}
	}

	if (cnt == 0 || cnt == row * col)
		return -1;

	int deep = -1;
	int dir[][2] = {{0,1}, {0, -1}, {1, 0}, {-1, 0}};
	while(rear != head) {
		deep++;
		int floorSize = rear - head;
		for (int i = 0; i < floorSize; i++) {
			int top = queue[head++];
			int cx = top / col;
			int cy = top % col;

			for (int j = 0; j < 4; j ++) {
				int nx = cx + dir[j][0];
				int ny = cy + dir[j][1];

				if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
					continue;
				}

				if (grid[nx][ny] != 0)
					continue;

				grid[nx][ny] = 1;
				queue[rear++] = nx * col + ny;
			}
		}
	}

	return deep;
}

/*
显然这不是一个「单源」最短路问题（SSSP）。在我们学习过的最短路算法中，求解 SSSP 问题的方法有 Dijkstra 算法和 SPFA算法，而求解任意两点之间的最短路一般使用 Floyd 算法。那我们在这里就应该使用 Floyd 算法吗？要考虑这个问题，我们需要分析一下这里使用 Floyd 算法的时间复杂度。我们知道在网格图中求最短路，作者：LeetCode-Solution链接：https://leetcode-cn.com/problems/as-far-from-land-as-possible/solution/di-tu-fen-xi-by-leetcode-solution/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int maxDistance(int** grid, int gridSize, int* gridColSize)
{
	int row = gridSize;
	int col = *gridColSize;
	int d[row][col];
	int visited[row][col];
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                d[i][j] = INT_MAX;
		visited[i][j] = 0;
            }
        }

	int queue[100 * 1000];
	int head = 0;
	int rear = 0;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (grid[i][j]) {
                    d[i][j] = 0;
                    //q.push({i, j});
			queue[rear++] = i * col + j;
                    visited[i][j] = 1;
                }
            }
        }

	int dir[][2] = {{0,1}, {0, -1}, {1, 0}, {-1, 0}};
        while (head != rear) {
            int f = queue[head++];
		int cx = f / col;
		int cy = f % col;
			visited[cx][cy] = 0;
            for (int i = 0; i < 4; ++i) {
                int nx = cx + dir[i][0], ny = cy + dir[i][1];
                if (!(nx >= 0 && nx <= row - 1 && ny >= 0 && ny <= col - 1)) continue;
                if (d[nx][ny] > d[cx][cy] + 1) {
                    d[nx][ny] = d[cx][cy] + 1;
                    if (!visited[nx][ny]) {
                        queue[rear++] = nx * col + ny;
                        visited[nx][ny] = 1;
                    }
                }
            }
        }

        int ans = -1;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (!grid[i][j]) ans = fmax(ans, d[i][j]);
            }
        }

        return (ans == INT_MAX) ? -1 : ans;
}


/*
DFS
301
*/
#define MAX_QUEUE_SIZE 10000
#define MAX_WORD_SIZE  50
#define LEFT_P '('
#define RIGHT_P ')'

bool IsStringValid(char* pString, int* delta)
{
	int leftCount = 0;
	int rightCount = 0;
	bool flag = true;

	for (int i = 0; i < strlen(pString); i++) {
		if (pString[i] == LEFT_P) {
			leftCount++;
		} else if (pString[i] == RIGHT_P) {
			rightCount++;
		}

		if (leftCount < rightCount) {
			flag = false;
		}
	}

	*delta = leftCount - rightCount;
	if (flag && *delta == 0) {
		return true;
	} else {
		return false;
	}
}

bool IsInQueue(char **queue, int head, int rear, char* pString)
{
    for (int i = head; i < rear; i++) {
        if (strcmp(pString, queue[i]) == 0) {
            return true;
        }
    }
    return false;
}

void RemoveChar(char* pString, int index)
{
	int len = strlen(pString);
	if (index < 0 || index >= len) {
		return;
	}

	for (int i = index; i < len - 1; i++) {
		pString[i] = pString[i + 1];
	}
	pString[len - 1] = '\0';
}

char** removeInvalidParentheses(char* s, int* returnSize)
{
	char** res = (char**)calloc(MAX_QUEUE_SIZE, sizeof(char*));
	*returnSize = 0;

	char *queue[MAX_QUEUE_SIZE];
	int head = 0;
	int rear = 0;
	queue[rear++] = strdup(s);
	char* tmpStr = NULL;
	bool flag = false;
	int delta = 0;

	while (head != rear) {
		int floorSize = rear - head;
		for (int i = 0; i < floorSize; i++) {
			tmpStr = queue[head++];

			if (IsStringValid(tmpStr, &delta)) {
				res[*returnSize] = strdup(tmpStr);
				(*returnSize)++;
				flag = true;
			}

			// drill down and enqueue
			if (!flag) { // if find result this round
				for (int k = 0; k < strlen(tmpStr); k++) {
					if (tmpStr[k] != LEFT_P && tmpStr[k] != RIGHT_P) {
						continue;
					}

					if (tmpStr[k] == LEFT_P && delta < 0) {
						continue;
					}

					if (tmpStr[k] == RIGHT_P && delta > 0) {
						continue;
					}

					char* tmpStr2 = strdup(tmpStr);
					//strcpy(tmpStr2, tmpStr);
					RemoveChar(tmpStr2, k);
					if (!IsInQueue(queue, head, rear, tmpStr2)) {
						queue[rear++] = tmpStr2;
					} else {
						free(tmpStr2);
					}
				}
			}
		}
	}

	return res;
}

/*
127. 单词接龙
给定两个单词（beginWord 和 endWord）和一个字典，找到从 beginWord 到 endWord 的最短转换序列的长度。转换需遵循如下规则：

每次转换只能改变一个字母。
转换过程中的中间单词必须是字典中的单词。
说明:

如果不存在这样的转换序列，返回 0。
所有单词具有相同的长度。
所有单词只由小写字母组成。
字典中不存在重复的单词。
你可以假设 beginWord 和 endWord 是非空的，且二者不相同。
示例 1:

输入:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

输出: 5

解释: 一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog",
     返回它的长度 5。
*/

#define MAX_QUEUE_SIZE 10000

int isValidString(char *popString, char *dicString)
{
    int diffNum = 0;
    int len = strlen(popString);
    for (int i = 0; i < len; i++) {
        if (popString[i] != dicString[i]) {
            diffNum++;
        }

        if (diffNum > 1) {
            return 0;;
        }
    }
    return 1;
}

int ladderLength(char * beginWord, char * endWord, char ** wordList, int wordListSize){
	if ((beginWord == NULL) || (strlen(beginWord) <= 0) || (endWord == NULL) || (strlen(endWord) <= 0) || (wordList == NULL) || (wordListSize <= 0)) {
		return 0;
	}

	char *queue[MAX_QUEUE_SIZE];
	int front = 0;
	int rear = 0;
	int visited[wordListSize];
	memset(visited, 0, sizeof(visited));

	queue[rear++] = beginWord;
	int step = 0;

	while (front != rear) {
		step++;
		int floorSize = rear - front;
		if (floorSize < 0) {
			floorSize = front - rear + 1;
		}

		for (int k = 0; k < floorSize; k++) {
			char *pop = queue[front];
			front = (front + 1) % MAX_QUEUE_SIZE;

			if (strcmp(pop, endWord) == 0) {
				return step;
			}

			for (int i = 0; i < wordListSize; i++) {
				if ((visited[i] == 0) && (isValidString(pop, wordList[i]))) {
					queue[rear++] = wordList[i];
					//rear = (rear + 1) % MAX_QUEUE_SIZE;
					visited[i] = 1;
				}
			}
		}
	}
	//free(visited);
	return 0;
}