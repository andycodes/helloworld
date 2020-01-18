/*
深度优先搜索（Depth-First-Search，DFS）是一种
用于遍历或搜索树或图的算法。
沿着树的深度遍历树的节点，
尽可能深的搜索树的分支。
当节点v的所在边都己被探寻过，
搜索将回溯到发现节点v的那
条边的起始节点。
这一过程一直进行到已发现从源节点可达
的所有节点为止。如果还存在未被发现的节点，
则选择其中一个作为源节点并重复以上过程，
整个进程反复进行直到所有节点都被访问为止。

DFS模板

result = []
def dfs(路径, 选择列表):
    if 满足「结束条件」:
        result.add(「路径」)
        return

    for 选择 in 「选择列表」:  (类似N叉树)
        #做选择
	 将该选择从选择列表移除
	 「路径」.add(选择)
        dfs(路径, 选择列表)
	 (注意跟回溯差异:没有反悔撤销而剪枝)

*/



/*
733. 图像渲染
有一幅以二维整数数组表示的图画，
每一个整数表示该图画的像素值大小，
数值在 0 到 65535 之间。
给你一个坐标 (sr, sc) 表示图像渲染开始的像素值（行 ，列）
和一个新的颜色值 newColor，让你重新上色这幅图像。

为了完成上色工作，从初始坐标开始，
记录初始坐标的上下左右四个方向上像素值与初始坐
标相同的相连像素点，接着再记录这四个方向上符合条
件的像素点与他们对应四个方向上像素值与初始坐标相同
的相连像素点，……，重复该过程。
将所有有记录的像素点的颜色值改为新的颜色值。

最后返回经过上色渲染后的图像。

输入:
image = [
[1,1,1],
[1,1,0],
[1,0,1]
]
sr = 1, sc = 1, newColor = 2
输出: [[2,2,2],[2,2,0],[2,0,1]]
解析:
在图像的正中间，(坐标(sr,sc)=(1,1)),
在路径上所有符合条件的像素点的颜色都被更改成2。
注意，右下角的像素没有更改为2，
因为它不是在上下左右四个方向上与初始点相连的像素点。

*/
void changeValue(int** image, int imageSize, int* imageColSize,
int sr, int sc, int newColor, int** res, bool** visited, int* returnSize, int** returnColumnSizes, int value) {

	if ( sr < 0 || sr >= imageSize || sc < 0 ||
		sc >= imageColSize[sr] || image[sr][sc] != value || visited[sr][sc])
		return;

	res[sr][sc] = newColor;
	visited[sr][sc] = true;

	int d[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
	for (int k = 0; k < 4; k++) {
		int nX = sr + d[k][0];
		int nY = sc + d[k][1];
		  changeValue(image, imageSize, imageColSize,
				nX, nY, newColor, res, visited, returnSize, returnColumnSizes, value);
	}
}



int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc,
	int newColor, int* returnSize, int** returnColumnSizes){
	int** res = malloc(sizeof(int*) * imageSize);
	bool** visited = malloc(sizeof(bool*) * imageSize);

	*returnSize = imageSize;
	*returnColumnSizes = malloc(sizeof(int) * imageSize);

	for (int i = 0; i < imageSize; i++) {
		res[i] = malloc(sizeof(int) * imageColSize[i]);
		visited[i] = malloc(sizeof(bool) * imageColSize[i]);
		memset(res[i], 0, sizeof(int) * imageColSize[i]);
		memset(visited[i], 0, sizeof(bool) * imageColSize[i]);
		(*returnColumnSizes)[i] = imageColSize[i];
	}

	changeValue(image, imageSize, imageColSize, sr, sc, newColor,
	res, visited, returnSize, returnColumnSizes, image[sr][sc]);

	for (int i = 0; i < imageSize; i++) {
		for (int j = 0; j < imageColSize[i]; j++) {
			if (visited[i][j] == false)
				res[i][j] = image[i][j];
		}
		free(visited[i]);
	}

	free(visited);
	return res;
}


/*
200. 岛屿数量
给定一个由 '1'（陆地）和 '0'（水）组成的的二维网格，
计算岛屿的数量。一个岛被水包围，
并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。
你可以假设网格的四个边均被水包围。

示例 1:

输入:
11110
11010
11000
00000

输出: 1

};
*/
void dfs(char** grid, int gridSize, int gridColSize, int x ,int y)
{
	if (x < 0 || x >= gridSize || y < 0 || y >= gridColSize || grid[x][y] == '0')
		return;

	grid[x][y] = '0';//前序操作

	int d[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
	for(int k = 0; k < 4; k++) {
		int nX = x + d[k][0];
		int nY = y + d[k][1];
		dfs(grid,gridSize,gridColSize,nX,nY);
	}
}


int numIslands(char** grid, int gridSize, int* gridColSize){
	int num = 0;

	if(grid == NULL  || gridSize == 0 || gridColSize == NULL)
		return num;

	for (int i = 0; i < gridSize; i++) {
		for(int j = 0; j < *gridColSize; j++) {
			if (grid[i][j] == '1') {
				num++;
				dfs(grid,gridSize,*gridColSize,i,j);
			}
		}
	}

	return num;
}

