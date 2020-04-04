/*
回溯法的基本思想：

针对所给问题，定义问题的解空间；
确定易于搜索的解空间结构；
以深度优先方式搜索解空间，
并在搜索过程中用剪枝函数避免无效搜索。


回溯法是求问题的解，
使用的是DFS（深度优先搜索）。
在DFS的过程中发现不是问题的解，
那么就开始回溯到上一层或者上一个节点。
DFS是遍历整个搜索空间，
而不管是否是问题的解。
所以更觉得回溯法是DFS的一种应用，
DFS更像是一种工具。

result = []
def backtrack(路径, 选择列表):
    if 满足「结束条件」:
        result.add(「路径」)
        return

    for 选择 in 「选择列表」:  (类似N叉树)
        #做选择
	 将该选择从选择列表移除
	 「路径」.add(选择)
        backtrack(路径, 选择列表)
        #撤销选择
        「路径」.remove(选择)
    	 将该选择再加入选择列表
*/


/*
1219                                                                                                                                                                                                . 黄金矿工
你要开发一座金矿，地质勘测学家已经探明了
这座金矿中的资源分布，并用大小为 m * n 的网格
grid 进行了标注。每个单元格中的整数就表示这一
单元格中的黄金数量；如果该单元格是空的，那么就是 0。

为了使收益最大化，矿工需要按以下规则来开采黄金：

每当矿工进入一个单元，就会收集该单元格中的所有黄金。
矿工每次可以从当前位置向上下左右四个方向走。
每个单元格只能被开采（进入）一次。
不得开采（进入）黄金数目为 0 的单元格。
矿工可以从网格中 任意一个 有黄金的单元格出发或者是停止。


示例 1：

输入：grid = [[0,6,0],[5,8,7],[0,9,0]]
输出：24
解释：
[[0,6,0],
 [5,8,7],
 [0,9,0]]
一种收集最多黄金的路线是：9 -> 8 -> 7。
*/

int backtrack(int ** grid, int gridSize, int* gridColSize,int i, int j)
{
	if (i < 0 || i >= gridSize || j < 0 || j >= gridColSize[0] || grid[i][j] == 0)
		return 0;

	int curVal = grid[i][j];
	grid[i][j] = 0;
	int ret = 0;

	int d[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
	for(int k = 0; k < 4; k++) {
		int nX = i + d[k][0];
		int nY = j + d[k][1];
		ret = fmax(ret, curVal + backtrack(grid,gridSize,gridColSize,nX,nY));
	}

	grid[i][j] = curVal;

	return ret;
}


int getMaximumGold(int** grid, int gridSize, int* gridColSize)
{
	if (grid == NULL || gridSize < 0 || gridColSize == NULL)
		return 0;

	int sumMax = 0;
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridColSize[i]; j++) {
			sumMax = fmax(sumMax, backtrack(grid, gridSize, gridColSize, i, j));
		}
	}

	return sumMax;
}

int main(int argc, char* argv[])
{
	int ** grid = (int **)calloc(3, sizeof(int *));
	int * gridColSize = (int *)calloc(3, sizeof(int));
	for (int i = 0; i < 3; i++) {
			grid[i] = (int *)calloc(3, sizeof(int));
			gridColSize[i] = 3;
	}

	grid[0][0] = 0;
	grid[0][1] = 6;
	grid[0][2] = 0;

	grid[1][0] = 5;
	grid[1][1] = 8;
	grid[1][2] = 7;

	grid[2][0] = 0;
	grid[2][1] = 9;
	grid[2][2] = 0;

	int ret = getMaximumGold(grid, 3, gridColSize);
	printf("ret = %d\n", ret);
}



/*全排列*/
void backtrack(int source[], int start, int end, int *resSize, int **res)
{
	// 找到一个排列
	if (start == end) {
		res[*resSize] = (int *)calloc(end, sizeof(int));
		memcpy(res[*resSize], source, sizeof(int) * end);
		(*resSize)++;
	} else {
		// 没有找完一个排列，则继续往下找下一个元素
		for (int i = start; i < end; i++) {
			if (start != i) {// 两两交换
				swap(source[start], source[i]);
			}

			// 递归排列剩余的从start+1到end的元素
			backtrack(source, start + 1, end, resSize, res);

			if (start != i) {// 回溯时还原
				swap(source[start], source[i]);
			}
		}
	}
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be calloc ed, assume caller calls free().
 */
int** permute(int* nums, int numsSize, int* returnSize,
			     int** returnColumnSizes)
{
	int **res = (int **)calloc (17000,  sizeof(int *));
	int resSize = 0;

	backtrack(nums, 0, numsSize, &resSize, res);

	*returnSize = resSize;
	*returnColumnSizes = (int *)calloc(17000, sizeof(int));
	for (int i = 0; i < resSize; i++) {
		(*returnColumnSizes)[i] = numsSize;
	}

	return res;
}


/*
401. 二进制手表
二进制手表顶部有 4 个 LED 代表小时（0-11），
底部的 6 个 LED 代表分钟（0-59）。
每个 LED 代表一个 0 或 1，最低位在右侧。

例如，上面的二进制手表读取 "3:25"。

给定一个非负整数 n 代表当前 LED 亮着的数量，
返回所有可能的时间。

案例:

输入: n = 1
返回: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
*/

void backtrack(int num, char ** res, int* returnSize,
int curH, int curM, int pos)
{
	if (num == 0) {
		res[*returnSize] = (char *)calloc(10, sizeof(char *));
		sprintf(res[*returnSize] , "%d:%02d", curH, curM);
		(*returnSize)++;
		return;
	}
/*
其实这个题目可以归于有多少 n个1的二进制组合。
转换为字符串即可。
这里将 0 - 9，划分一下
0 - 5 是 分钟
6 - 9 是小时计算。
*/
	for (int i = pos; i < 10; i++) {
		if (i <= 5) {
			curM += (1 << i);
			if (curM > 59) {
				curM -= (1 << i);
				continue;
			}
		} else {
			curH += (1 << i - 6);
			if (curH > 11)
				return;
		}

		backtrack(num -1, res,  returnSize, curH,  curM, i + 1);

		if (i <= 5)
			curM -= (1 << i);
		else
			curH -= (1 << i - 6);
	}
}


char ** readBinaryWatch(int num, int* returnSize)
{
	char ** res = (char **)calloc(1024, sizeof(char *));

	*returnSize = 0;
	backtrack(num, res, returnSize, 0, 0, 0);

	return res;
}

/*
面试题 08.02. 迷路的机器人
难度中等13
设想有个机器人坐在一个网格的左上角，网格 r 行 c 列。机器人只能向下或向右移动，但不能走到一些被禁止的网格（有障碍物）。设计一种算法，寻找机器人从左上角移动到右下角的路径。

网格中的障碍物和空位置分别用 1 和 0 来表示。
返回一条可行的路径，路径由经过的网格的行号和列号组成。左上角为 0 行 0 列。
示例 1:
输入:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
输出: [[0,0],[0,1],[0,2],[1,2],[2,2]]
解释:
输入中标粗的位置即为输出表示的路径，即
0行

*/

bool dfs(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize, int row, int col,
int **ret, int *returnSize,  bool visited[][100], int** returnColumnSizes)
{
	if(row >= obstacleGridSize || col >= obstacleGridColSize[row] || obstacleGrid[row][col] == 1 || visited[row][col])
		return false;

	visited[row][col] = 1;
	ret[*returnSize] = (int *)calloc(2, sizeof(int));
	ret[*returnSize][0] = row;
	ret[*returnSize][1] = col;
	(*returnColumnSizes)[*returnSize] = 2;
	(*returnSize)++;

	if(row == (obstacleGridSize - 1) && col == (obstacleGridColSize[row] - 1)) {
		return true;
	}

	if (dfs(obstacleGrid, obstacleGridSize, obstacleGridColSize, row, col + 1, ret, returnSize, visited, returnColumnSizes) ||
		dfs(obstacleGrid, obstacleGridSize, obstacleGridColSize, row + 1, col, ret, returnSize, visited, returnColumnSizes)) {
		return true;
	}

	if (ret[*returnSize] != NULL) {
		free(ret[*returnSize]);
		ret[*returnSize] = NULL;

	}

	(*returnSize)--;

	return false;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pathWithObstacles(int** obstacleGrid, int obstacleGridSize,
int* obstacleGridColSize, int* returnSize, int** returnColumnSizes){
	*returnSize = 0;
	int **ret = calloc(200, sizeof(int *));
	bool visited[100][100];
	memset(visited, 0, sizeof(visited));
	*returnColumnSizes = calloc(200, sizeof(int));
	bool  arrived = dfs(obstacleGrid, obstacleGridSize, obstacleGridColSize,
	0, 0, ret, returnSize, visited, returnColumnSizes);
	if(arrived == false) {
		*returnSize = 0;
	}

	return ret;
}

