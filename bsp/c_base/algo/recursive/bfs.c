/*         BFS

BFS 使用queue 或者heap

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
126. 单词接龙 II
给定两个单词（beginWord 和 endWord）和一个字典 wordList，找出所有从 beginWord 到 endWord 的最短转换序列。转换需遵循如下规则：

每次转换只能改变一个字母。
转换后得到的单词必须是字典中的单词。
说明:

如果不存在这样的转换序列，返回一个空列表。
所有单词具有相同的长度。
所有单词只由小写字母组成。
字典中不存在重复的单词。
你可以假设 beginWord 和 endWord 是非空的，且二者不相同。
示例 1:

输入:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

输出:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]
示例 2:

输入:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

输出: []

解释: endWord "cog" 不在字典中，所以不存在符合要求的转换序列。
*/
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

//学习一篇代码质量很高的C代码，认真学习并重写了一遍

//参见：https://leetcode-cn.com/problems/word-ladder-ii/solution/lai-ge-cde-ti-jie-xie-de-hen-shang-xin-by-hong-65/

//思路：
//1，构造新的字典,将 beginword 加入字典 为首单词
//2,获取 endWord 在字典中的下标,找不到则直接返回空
//3,构造字典中每个单词的相邻关系
//4,BFS广度优先搜索，获取最短转换序列层数，并且构建搜索关系树
//5,DFS深度优先搜索，递归遍历搜索关系树，找到最短转换序列

#define     MIN(a, b)       ((a) < (b) ? (a) : (b))
#define     MAX(a, b)       ((a) > (b) ? (a) : (b))
#define     INVALID_INDEX   0xffffffff
#define     PRT_SW          0

//记录每个单词的转换单词信息
typedef struct {
    unsigned int    adjNum;         //字典总转换单词的个数
    unsigned int*   adjIndex;       //转换单词在字典中的索引
} WordAdj;

//记录每个单词的搜索信息
typedef struct {
    unsigned int    isOk;           //记录当前单词是否被搜索过
    unsigned int    minLen;         //记录当前单词的层数
    unsigned int    nextNum;        //当前单词的下一层转换单词的数量
    unsigned int*   nextIndex;      //存储当前单词的下一层转换单词
} WordSearch;

//记录输出信息
typedef struct outPut {
    char**              str;        //存储每个最短转换序列
    struct outPut*      next;       //指向下一个结果
} OutPutList;

WordAdj*        g_wordAdjInfo       = NULL;         //用于记录字典中每个单词的转换单词
WordSearch*     g_wordSearchInfo    = NULL;         //用于BFS搜索记录层次信息
OutPutList*     g_outPutStr         = NULL;         //用于记录最短转换序列结果
unsigned int    g_outPutStrNum      = 0;            //最短转换序列数

#if (PRT_SW == 1)
#define     DebugPrt    printf
#else
#define     DebugPrt
#endif

//函数一：内存申请
int MallocMem(char*** newWordList, unsigned int totalWordNum){
    unsigned int    i   = 0;

    *newWordList = (char**)malloc(sizeof(char*) * totalWordNum);
    if(NULL == (*newWordList)) return -1;

    g_wordAdjInfo = (WordAdj*)malloc(sizeof(WordAdj) * totalWordNum);
    if(NULL == g_wordAdjInfo) return -1;

    g_wordSearchInfo = (WordSearch*)malloc(sizeof(WordSearch) * totalWordNum);
    if(NULL == g_wordSearchInfo) return -1;

    g_outPutStr = (OutPutList*)malloc(sizeof(OutPutList));
    if(NULL == g_outPutStr) return -1;
    g_outPutStr->next = NULL;

    for(i = 0; i < totalWordNum; i++)
    {
        g_wordAdjInfo[i].adjNum = 0;
        g_wordAdjInfo[i].adjIndex = (unsigned int*)malloc(sizeof(unsigned int) * totalWordNum);
        if(NULL == g_wordAdjInfo[i].adjIndex) return -1;

        g_wordSearchInfo[i].isOk = 0;
        g_wordSearchInfo[i].minLen = INVALID_INDEX;
        g_wordSearchInfo[i].nextNum = 0;
        g_wordSearchInfo[i].nextIndex = (unsigned int*)malloc(sizeof(unsigned int) * totalWordNum);
        if(NULL == g_wordSearchInfo[i].nextIndex) return -1;
    }
    return 0;
}

//函数二：内存释放
void FreeMem(char** newWordList, unsigned int totalWordNum){
    unsigned int    i       = 0;
    OutPutList*     pTmp    = NULL;
    OutPutList*     pRel    = NULL;

    for(i = 0; i < totalWordNum; i++)
    {
        free(g_wordAdjInfo[i].adjIndex);
        g_wordAdjInfo->adjIndex = NULL;

        free(g_wordSearchInfo[i].nextIndex);
        g_wordSearchInfo->nextIndex = NULL;
    }

    free(newWordList);
    newWordList = NULL;

    free(g_wordAdjInfo);
    g_wordAdjInfo = NULL;

    free(g_wordSearchInfo);
    g_wordSearchInfo = NULL;

    pTmp = g_outPutStr;
    while((NULL != pTmp) && (i < g_outPutStrNum + 1))
    {
        pRel = pTmp;
        pTmp = pTmp->next;
        free(pRel);
        pRel = NULL;
        i += 1;
    }

    free(g_outPutStr);
    g_outPutStr = NULL;
    return;
}

//函数二：重构字典列表，将 beginWord 单词加入字典为首单词
int RebuildNewWordList(char * beginWord, char ** wordList, int wordListSize, char** newWordList){
    int     i           = 0;
    int     iNum        = 0;

    newWordList[0] = beginWord;
    iNum += 1;
    for(i = 0; i < wordListSize; i++)
    {
        if(0 != strcmp(wordList[i], beginWord))
        {
            newWordList[iNum++] = wordList[i];
        }
    }

    return iNum;
}

//函数四：获取 endWord 在字典中的下标，endWord 不在字典中则返回空列表
int CheckEndWord(char* endWord, char** wordList, int wordListSize, unsigned int* endWordIndex){
    unsigned int    i   = 0;

    for(i = 0; i < wordListSize; i++)
    {
        if(0 == strcmp(endWord, wordList[i]))
        {
            *endWordIndex = i;
            return 0;
        }
    }
    return -1;
}

//函数五：判断两个单词是否可以转换
int CheckIsAdjWord(char* word1, char* word2){
    unsigned int    i           = 0;
    unsigned int    diffNum     = 0;
    unsigned int    len         = strlen(word1);
    while(i < len)
    {
        if(word1[i] != word2[i])
        {
            diffNum += 1;
        }
        i += 1;
        if(diffNum > 1) return -1;
    }
    if(diffNum == 1) return 0;
    return -1;
}

//函数六：构造字典中所有单词的转换关系 g_wordAdjInfo
int CreateWordAdj(char** newWordList, unsigned int totalWordNum){
    unsigned int    i   = 0;
    unsigned int    j   = 0;
    for(i = 0; i < totalWordNum - 1; i++)
    {
        for(j = i + 1; j < totalWordNum; j++)
        {
            if(0 == CheckIsAdjWord(newWordList[i], newWordList[j]))
            {
                g_wordAdjInfo[i].adjIndex[g_wordAdjInfo[i].adjNum++] = j;

                if(0 == i) continue;

                g_wordAdjInfo[j].adjIndex[g_wordAdjInfo[j].adjNum++] = i;
            }
        }
    }
    return 0;
}

//函数七：BFS广度优先搜索
//1,使用队列先进先出实现BFS广度优先搜索，适合大范围寻找
//2,将当前层元素依次压入队列
//3,利用队列先进先出，依次取出当前层节点，将当前节点的所有下层节点，依次压入队列
//4,直到队列为空，遍历完所有节点，可以参照树的层次遍历
//5,此题可以不用完全遍历，当遍历到 endWord 所在的层便可结束
int BfsSearch(char** newWordList, unsigned int totalWordNum, unsigned int endWordIndex, unsigned int* minLen){
    unsigned int        i           = 0;
    unsigned int        j           = 0;
    unsigned int        adjIndex    = 0;
    unsigned int        currIndex   = 0;
    unsigned int        findFlag    = 0;
    unsigned int        iHead       = 0;
    unsigned int        iTail       = 0;
    unsigned int        iLevelNum   = 0;

    unsigned int*       searchList      = NULL;
    WordAdj*            wordAdjInfo     = g_wordAdjInfo;
    WordSearch*         wordSearchInfo  = g_wordSearchInfo;

    searchList = (unsigned int*)malloc(sizeof(unsigned int) * totalWordNum);
    if(NULL == searchList) return -1;

    //1,将字典首元素 starWord 加入队列
    searchList[iTail++] = 0;
    iLevelNum = 1;

    wordSearchInfo[0].isOk = 1;
    wordSearchInfo[0].minLen = 1;

    while(iHead < iTail)
    {
        iLevelNum = iTail - iHead;
        //2,遍历当前层所有元素
        for(i = 0; i < iLevelNum; i++)
        {
            //3,将当前层所有元素的子节点压入队列
            currIndex = searchList[iHead++];
            for(j = 0; j < wordAdjInfo[currIndex].adjNum; j++)
            {
                adjIndex = wordAdjInfo[currIndex].adjIndex[j];
                wordSearchInfo[currIndex].nextIndex[wordSearchInfo[currIndex].nextNum++] = adjIndex;

                if(0 == wordSearchInfo[adjIndex].isOk)
                {
                    wordSearchInfo[adjIndex].isOk = 1;
                    wordSearchInfo[adjIndex].minLen = wordSearchInfo[currIndex].minLen + 1;
                    searchList[iTail++] = adjIndex;
                }
                if(adjIndex == endWordIndex)
                {
                    findFlag = 1;
                }
            }
        }

        if(1 == findFlag)
        {
            //4,遍历到 endWord 层，即可结束遍历
            free(searchList);
            *minLen = wordSearchInfo[endWordIndex].minLen;
            return 0;
        }
    }

    free(searchList);
    return -1;
}

//函数八：将一个最短转换序列结果加入输出结果 g_outPutStr 中
int PushRetToOutList(char** newWordList, unsigned int* oneList, unsigned int oneListNum){
    unsigned int    i           = 0;
    char**          OutStr      = NULL;
    char*           charstr     = NULL;
    OutPutList*     node        = NULL;

    OutStr = (char**)malloc(sizeof(char*) * oneListNum);
    if(NULL == OutStr) return -1;

    node = (OutPutList*)malloc(sizeof(OutPutList));
    if(NULL == node) return -1;

    for(i = 0; i < oneListNum; i++)
    {
        charstr = (char*)malloc(sizeof(char) * (strlen(newWordList[oneList[i]]) + 1));
        if(NULL == charstr) return -1;
        strcpy(charstr, newWordList[oneList[i]]);
        OutStr[i] = charstr;
    }

    node->str = OutStr;
    node->next = g_outPutStr->next;
    g_outPutStr->next = node;
    g_outPutStrNum += 1;
    return 0;
}

//函数九：DFS 深度优先遍历算法
void DfsSearch(char** newWordList, unsigned int endWordIndex, unsigned int* oneList, unsigned int oneListNum, unsigned int minLen){
    unsigned int    i           = 0;
    unsigned int    lastIndex   = 0;
    unsigned int    nextIndex   = 0;
    WordSearch* wordSearchInfo  = g_wordSearchInfo;

    //1,结束条件一：当前遍历层次大于最小层次即可结束
    if(oneListNum > minLen) return;

    //2,结束条件二：找到 endWord 得到一个解
    lastIndex = oneList[oneListNum - 1];
    if(lastIndex == endWordIndex)
    {
        PushRetToOutList(newWordList, oneList, oneListNum);
        return;
    }

    //3,在当前节点的有效子节点中递归处理
    for(i = 0; i < wordSearchInfo[lastIndex].nextNum; i++)
    {
        nextIndex = wordSearchInfo[lastIndex].nextIndex[i];
        if((wordSearchInfo[nextIndex].minLen == oneListNum + 1) && (oneListNum < minLen))
        {
            oneList[oneListNum] = nextIndex;
            DfsSearch(newWordList, endWordIndex, oneList, oneListNum + 1, minLen);
        }
    }
    return;
}

//函数十：使用 DFS 深度优先遍历寻找最短转换序列
int CalcResultByDfs(char** newWordList, unsigned int endWordIndex, unsigned int minLen){
    unsigned int*   oneList     = NULL;
    unsigned int    oneListNum  = 0;

    oneList = (unsigned int*)malloc(sizeof(unsigned int) * minLen);
    if(NULL == oneList) return -1;

    oneListNum = 1;
    oneList[0] = 0;
    DfsSearch(newWordList, endWordIndex, oneList, oneListNum, minLen);

    free(oneList);
    oneList = NULL;
    return 0;
}

//函数十一：输出处理
char*** OutPutHandle(unsigned int minLen, int* returnSize, int** returnColumnSizes){
    unsigned int    i       = 0;
    unsigned int    j       = 0;
    char*** outPutAll       = NULL;
    OutPutList* pTmp        = NULL;

    outPutAll = (char ***)malloc(sizeof(char**) * g_outPutStrNum);
    if(NULL == outPutAll) return NULL;

    *returnSize = g_outPutStrNum;
    *returnColumnSizes = (int*)malloc(sizeof(int) * g_outPutStrNum);
    if(NULL == *returnColumnSizes) return NULL;

    pTmp = g_outPutStr->next;

    for(i = 0; i < g_outPutStrNum; i++)
    {
        (*returnColumnSizes)[i] = minLen;

        if(NULL != pTmp)
        {
            outPutAll[i] = pTmp->str;
            pTmp = pTmp->next;
        }
    }

/*
    for(i = 0; i < g_outPutStrNum; i++)
    {
        DebugPrt("[%d]:", i);
        for(j = 0; j < minLen; j++)
        {
            DebugPrt(" %s", outPutAll[i][j]);
        }
        DebugPrt("\n");
    }
*/
    return outPutAll;
}

//主函数
char *** findLadders(char * beginWord, char * endWord, char ** wordList, int wordListSize, int* returnSize, int** returnColumnSizes){
    int         mallocColumnSizes       = 0;
    int         totalWordNum            = wordListSize + 1;
    int         endWordIndex            = 0;
    char**      newWordList             = NULL;                 //用于记录重新记录字典
    char***     outPutAll               = NULL;

    *returnSize = 0;
    g_outPutStrNum = 0;

    //1,初始化
    if(0 != MallocMem(&newWordList, (wordListSize + 1)))
    {
        FreeMem(newWordList, (wordListSize + 1));
        return NULL;
    }

    //2，构造新的字典,将 beginword 加入字典 为首单词
    totalWordNum = RebuildNewWordList(beginWord, wordList, wordListSize, newWordList);

    //3,获取 endWord 在字典中的下标
    if(0 != CheckEndWord(endWord, newWordList, totalWordNum, &endWordIndex))
    {
        FreeMem(newWordList, (wordListSize + 1));
        return NULL;
    }

    //4,构造字典中单词的相邻关系
    if(0 != CreateWordAdj(newWordList, totalWordNum))
    {
        FreeMem(newWordList, (wordListSize + 1));
        return NULL;
    }

    //5,BFS广度优先搜索，获取最短转换序列层数 mallocColumnSizes
    if(0 != BfsSearch(newWordList, totalWordNum, endWordIndex, &mallocColumnSizes))
    {
        FreeMem(newWordList, (wordListSize + 1));
        return NULL;
    }

    //6,DFS深度优先搜索
    if(0 != CalcResultByDfs(newWordList, endWordIndex, mallocColumnSizes))
    {
        FreeMem(newWordList, (wordListSize + 1));
        return NULL;
    }

    //7,输出处理
    outPutAll = OutPutHandle(mallocColumnSizes, returnSize, returnColumnSizes);

    //8,释放空间
    FreeMem(newWordList, (wordListSize + 1));
    return outPutAll;
}

/*
675. 为高尔夫比赛砍树
你被请来给一个要举办高尔夫比赛的树林砍树. 树林由一个非负的二维数组表示， 在这个数组中：

0 表示障碍，无法触碰到.
1 表示可以行走的地面.
比 1 大的数 表示一颗允许走过的树的高度.
每一步，你都可以向上、下、左、右四个方向之一移动一个单位，如果你站的地方有一棵树，那么你可以决定是否要砍倒它。

你被要求按照树的高度从低向高砍掉所有的树，每砍过一颗树，树的高度变为 1 。

你将从（0，0）点开始工作，你应该返回你砍完所有树需要走的最小步数。 如果你无法砍完所有的树，返回 -1 。

可以保证的是，没有两棵树的高度是相同的，并且你至少需要砍倒一棵树。



示例 1:

输入:
[
 [1,2,3],
 [0,0,4],
 [7,6,5]
]
输出: 6
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct strPara_ {
    int i;
    int j;
    int value;
}strPara;
#define Q 1000
typedef struct queuePara_ {
    int front;
    int rear;
    strPara que[Q];
}queuePara;
queuePara queue;
void init(queuePara *q)
{
    q->front = 0;
    q->rear = 0;
    memset(q, 0, sizeof(q));
}

int emQueue(queuePara *q, int i, int j)
{
    if ((q->rear + 1 + Q) % Q == q->front) {
        return 0;
    }
    q->que[q->rear].j = j;
    q->que[q->rear].i = i;
    q->rear = (q->rear + 1) % Q;
    return 1;
}
int isEmpty(queuePara *q)
{
    if (q->rear == q->front) {
        return 1;
    }
    return 0;
}

int getSize(queuePara *q)
{
    return (q->rear + Q - q->front) % Q;
}
#define M 100
#define N 100
strPara arr[M*N];
int visit[M][N];
#if 0
int forest[M][N] = {
    {2,3,4},
    {0,0,5},
    {8,7,6}
};
#endif
int compare(const void * a, const void *b)
{
    strPara *aa = (strPara *)a;
    strPara *bb = (strPara *)b;
    return (aa->value - bb->value);
}
int sort (int ** forest,int forestSize, int* forestColSize)
{
    int i, j;
    int k = 0;
    for (i = 0; i < forestSize; i++) {
        for (j = 0 ; j < *forestColSize; j++) {
            if (forest[i][j] == 0) {
                continue;
            }
            arr[k].i = i;
            arr[k].j = j;
            arr[k].value = forest[i][j];
            k++;
        }
    }
    qsort(arr, k, sizeof(strPara), compare);
    return k;
}
int bfs(strPara *start, strPara *target, int **forest,int forestSize, int forestColSize)
{
    int i, j, k;
    int di[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    int cnt = 0;
    queuePara *q = &queue;
    init(q);
    emQueue(q, start->i, start->j);
    memset(visit, 0, sizeof(visit));
    visit[start->i][start->j] = 1;
    while(!isEmpty(q)) {
        k = getSize(q);
        for (i = 0; i < k; i++) {
            int x = q->que[q->front].i;
            int y = q->que[q->front].j;
            q->front = (q->front + 1) % Q;
            if (x == target->i && y == target->j) {
                return cnt;
            }
            for (j = 0; j < 4; j++) {
                int nx = x + di[j][0];
                int ny = y + di[j][1];
                if (nx >=0 && nx < forestSize && ny >=0 && ny < forestColSize &&
                    visit[nx][ny] == 0 && forest[nx][ny] != 0) {
                    emQueue(q, nx, ny);
                    visit[nx][ny] = 1;
                }
            }
        }
        cnt++;
    }
    return -1;
}
int cutOffTree(int **forest,int forestSize, int* forestColSize){
    int i, j, k;
    int cnt = 0;
    int sum = 0;
    if (forest == NULL || forestSize == 0 || *forestColSize == 0 || forest[0][0] == 0) {
        return -1;
    }
    k = sort(forest, forestSize, forestColSize);
    strPara start;
    start.i = 0;
    start.j = 0;
    start.value = forest[0][0];

    for (i = 0; i < k; i++) {
        if (start.i == arr[i].i && start.j == arr[i].j) {
            continue;
        }
        cnt = bfs(&start, &arr[i],forest, forestSize, *forestColSize);
        if (cnt == -1) {
            return -1;
        }
        start.i = arr[i].i;
        start.j = arr[i].j;
        start.value = arr[i].value;
        sum += cnt;
    }
   // printf("%d\n", sum);
    return sum;
}
/*
比较水的题吧。先遍历一遍图，把是树的点和树的高度记录下来，然后按照树的高度排序一下。那么答案就是从起点(0,0)到第一棵树，第一棵树到第二棵树，第二棵树到第三棵树...的最短距离之和每两点之间的距离用BFS计算即可，如果有任意两点之间无法到达，说明答案就是NO。作者：7QQQQQQQ链接：https://leetcode-cn.com/problems/cut-off-trees-for-golf-event/solution/bfs-by-7qqqqqqq/来源：力扣（LeetCode）著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

/*
909. 蛇梯棋
N x N 的棋盘 board 上，按从 1 到 N*N 的数字给方格编号，编号 从左下角开始，每一行交替方向。

例如，一块 6 x 6 大小的棋盘，编号如下：


r 行 c 列的棋盘，按前述方法编号，棋盘格中可能存在 “蛇” 或 “梯子”；如果 board[r][c] != -1，那个蛇或梯子的目的地将会是 board[r][c]。

玩家从棋盘上的方格 1 （总是在最后一行、第一列）开始出发。

每一回合，玩家需要从当前方格 x 开始出发，按下述要求前进：

选定目标方格：选择从编号 x+1，x+2，x+3，x+4，x+5，或者 x+6 的方格中选出一个目标方格 s ，目标方格的编号 <= N*N。
该选择模拟了掷骰子的情景，无论棋盘大小如何，你的目的地范围也只能处于区间 [x+1, x+6] 之间。
传送玩家：如果目标方格 S 处存在蛇或梯子，那么玩家会传送到蛇或梯子的目的地。否则，玩家传送到目标方格 S。
注意，玩家在每回合的前进过程中最多只能爬过蛇或梯子一次：就算目的地是另一条蛇或梯子的起点，你也不会继续移动。

返回达到方格 N*N 所需的最少移动次数，如果不可能，则返回 -1。



示例：

输入：[
[-1,-1,-1,-1,-1,-1],
[-1,-1,-1,-1,-1,-1],
[-1,-1,-1,-1,-1,-1],
[-1,35,-1,-1,13,-1],
[-1,-1,-1,-1,-1,-1],
[-1,15,-1,-1,-1,-1]]
输出：4
解释：
首先，从方格 1 [第 5 行，第 0 列] 开始。
你决定移动到方格 2，并必须爬过梯子移动到到方格 15。
然后你决定移动到方格 17 [第 3 行，第 5 列]，必须爬过蛇到方格 13。
然后你决定移动到方格 14，且必须通过梯子移动到方格 35。
然后你决定移动到方格 36, 游戏结束。
可以证明你需要至少 4 次移动才能到达第 N*N 个方格，所以答案是 4。
*/

/*
这道题给了一个 NxN 大小的二维数组，从左下角从1开始，蛇形游走，到左上角或者右上角到数字为 NxN，中间某些位置会有梯子，就如同传送门一样，直接可以到达另外一个位置。现在就如同玩大富翁 Big Rich Man 一样，有一个骰子，可以走1到6内的任意一个数字，现在奢侈一把，有无限个遥控骰子，每次都可以走1到6以内指定的步数，问最小能用几步快速到达终点 NxN 位置。开始做这道题的时候，看是求极值，以为是一道动态规划 Dynamic Programming 的题，结果发现木有办法重现子问题，没法写出状态转移方程，只得作罢。但其实忽略了一点，求最小值还有一大神器，广度优先搜索 BFS，最直接的应用就是在迷宫遍历的问题中，求从起点到终点的最少步数，也可以用在更通用的场景，只要是存在确定的状态转移的方式，可能也可以使用。这道题基本就是类似迷宫遍历的问题，可以走的1到6步可以当作六个方向，这样就可以看作是一个迷宫了，唯一要特殊处理的就是遇见梯子的情况，要跳到另一个位置。这道题还有另一个难点，就是数字标号和数组的二维坐标的转换，这里起始点是在二维数组的左下角，且是1，而代码中定义的二维数组的 (0, 0) 点是在左上角，需要转换一下，还有就是这道题的数字是蛇形环绕的，即当行号是奇数的时候，是从右往左遍历的，转换的时候要注意一下。

难点基本都提到了，现在开始写代码吧，既然是 BFS，就需要用队列 queue 来辅助，初始时将数字1放入，然后还需要一个 visited 数组，大小为 nxn+1。在 while 循环中进行层序遍历，取出队首数字，判断若等于 nxn 直接返回结果 minStep。否则就要遍历1到6内的所有数字i，则 num+i 就是下一步要走的距离，需要将其转为数组的二维坐标位置，这个操作放到一个单独的子函数中，后边再讲。有了数组的坐标，就可以看该位置上是否有梯子，有的话，需要换成梯子能到达的位置，没有的话还是用 num+i。有了下一个位置，再看 visited 中的值，若已经访问过了直接跳过，否则标记为 true，并且加入队列 queue 中即可，若 while 循环退出了，表示无法到达终点，返回 -1。将数字标号转为二维坐标位置的子函数也不算难，首先应将数字标号减1，因为这里是从1开始的，而代码中的二维坐标是从0开始的，然后除以n得到横坐标，对n取余得到纵坐标。但这里得到的横纵坐标都还不是正确的，因为前面说了数字标记是蛇形环绕的，当行号是奇数的时候，列数需要翻转一下，即用 n-1 减去当前列数。又因为代码中的二维数组起点位置在左上角，同样需要翻转一样，这样得到的才是正确的横纵坐标，返回即可，
*/

/*
    将棋盘数字标号(1,2,3,...,N*N)转为二维坐标位置:
    (1)首先应将数字标号减1，因为棋盘是从1开始的，而代码中的二维坐标是从0开始的，
    (2)然后除以n得到横坐标，对n取余得到纵坐标。
    (3)但这里得到的横纵坐标都还不是正确的，因为前面说了数字标记是蛇形环绕的，
       当行号是奇数的时候，列数需要翻转一下，即用 n-1 减去当前列数
*/
int  getNextBoardValue(int **board,int boardSize,int num)
{
    if(board == NULL)
    {
        return -1;
    }

    int n = boardSize;

    int x = (num - 1)/n;
    int y = (num - 1)%n;

    if(x % 2 != 0)// if x is odd number
    {
        y = (n - 1) - y;//只有x位于奇行数(从下往上数),y走向是从右向左，所以y要翻转
    }

    x = (n - 1) - x;//x是从下往上走的，所以要一直翻转

    return board[x][y];
}

int snakesAndLadders(int** board, int boardSize, int* boardColSize){
    if(board == NULL || boardSize == 0 || boardColSize == NULL)
    {
        return -1;
    }

    int n = boardSize;
    int c = boardColSize[0];
    int minStep = 0;
    int q[n*n];//create a queue
    int visited[n*n+1];

    memset(q,0,sizeof(q));
    memset(visited,0,sizeof(visited));
    int cur = 0;
    int next = 0;

    int front = 0;
    int rear  = 0;

    /*begin with the left lower corner of the chessboard*/
    q[rear++] = 1;//enqueue
    //visited[n - 1][0] = true;//
    int layerNum = 0;

    while(rear != front)
    {
        //printf("cur = %d\n",cur);


        layerNum = rear - front;

        for(int l = 0;l<layerNum;l++)
        {
            cur = q[front++];//dequeue
            if(cur == n*n)
            {
                return minStep;
            }
            for(int i = 1;i <= 6 && cur + i <= n*n ;i++)
            {
                next = getNextBoardValue(board,boardSize,cur+i);
                if(next == -1)
                {
                    next = cur + i;
                }

                if(visited[next])
                {
                    continue;
                }
                visited[next] = true;
                q[rear++] = next;
            }
        }
        minStep++;

    }
    return -1;
}