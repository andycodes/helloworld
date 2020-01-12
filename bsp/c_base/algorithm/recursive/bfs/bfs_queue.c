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

struct queue_blk{
	int count;
	int size;
	struct queue_load load[0];
};


struct queue_blk * create_array_queue(int sz)
{
	struct queue_blk * queue;

	queue = (struct queue_blk * )malloc(sizeof(struct queue_blk) + sz*sizeof(struct queue_load));
	if(queue == NULL) {
		printf(" malloc error!");
		return  NULL;
	}

	queue->count = 0;
	queue->size = sz;

	return queue;
}


void destroy_array_queue(struct queue_blk * queue)
{
	if (queue) {
		free((void*)queue);
		queue = NULL;
	}
}


void push(struct queue_blk * queue,struct queue_load load)
{
	queue->load[queue->count++] = load;
	if (queue->count > queue->size) {
		printf("[%s] push count[%d] too big\n", __func__, queue->count);
		queue->count = queue->count % queue->size;
		return;
	}
}


struct queue_load  front(struct queue_blk * queue)
{
	return  queue->load[0];
}


// 返回并删除“队列开头元素”
struct queue_load pop(struct queue_blk * queue)
{
	int i = 0;

	struct queue_load head = queue->load[0];

	queue->count--;
	while (i++<queue->count)
		queue->load[i-1] = queue->load[i];

	return head;
}


// 返回“队列”的大小
int size(struct queue_blk * queue)
{
	return queue->count;
}

// 返回“队列”是否为空
int is_empty(struct queue_blk * queue)
{
	return queue->count==0;
}



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


	int d[4][2] = {
			{0,1},
			{1,0},
			{0,-1},
			{-1,0},
	};

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


