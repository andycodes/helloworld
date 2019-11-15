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





