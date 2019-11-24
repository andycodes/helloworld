/*
DFS模板

dfs出口，不满足条件就退出

操作

递归，接着进一步DFS
*/

void dfs(int** M, int MColSize, int* visited, int i) {
        for (int j = 0; j < MColSize; j++) {
            if (M[i][j] == 1 && visited[j] == 0) {
                visited[j] = 1;
                dfs(M, MColSize,visited, j);
            }
        }
}

int findCircleNum(int** M, int MSize, int* MColSize){

	int *visited = malloc(MSize * sizeof(visited));
	int count = 0;
	memset((void*)visited,0,MSize * sizeof(visited));
	for (int i = 0; i < MSize; i++){
		if(visited[i] == 0){
			dfs(M,MColSize[i],visited,i);
			count++;
		}
	}

	return count;
}


/*
有一幅以二维整数数组表示的图画，每一个整数表示该图画的像素值大小，数值在 0 到 65535 之间。

给你一个坐标 (sr, sc) 表示图像渲染开始的像素值（行 ，列）和一个新的颜色值 newColor，让你重新上色这幅图像。

为了完成上色工作，从初始坐标开始，记录初始坐标的上下左右四个方向上像素值与初始坐标相同的相连像素点，接着再记录这四个方向上符合条件的像素点与他们对应四个方向上像素值与初始坐标相同的相连像素点，……，重复该过程。将所有有记录的像素点的颜色值改为新的颜色值。

最后返回经过上色渲染后的图像。

输入:
image = [[1,1,1],[1,1,0],[1,0,1]]
sr = 1, sc = 1, newColor = 2
输出: [[2,2,2],[2,2,0],[2,0,1]]
解析:
在图像的正中间，(坐标(sr,sc)=(1,1)),
在路径上所有符合条件的像素点的颜色都被更改成2。
注意，右下角的像素没有更改为2，
因为它不是在上下左右四个方向上与初始点相连的像素点。

*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
void changeValue(int** image, int imageSize, int* imageColSize, int sr, int sc, int newColor, int** res, bool** flag, int* returnSize, int** returnColumnSizes) {

	res[sr][sc] = newColor;

	if (sr > 0 && image[sr - 1][sc] == image[sr][sc] && !flag[sr - 1][sc])  {
	    flag[sr - 1][sc] = true;
	    changeValue(image, imageSize, imageColSize, sr - 1, sc, newColor, res, flag, returnSize, returnColumnSizes);
	}
	if (sc > 0 && image[sr][sc - 1] == image[sr][sc] && !flag[sr][sc - 1])  {
	    flag[sr][sc - 1] = true;
	    changeValue(image, imageSize, imageColSize, sr, sc - 1, newColor, res, flag, returnSize, returnColumnSizes);
	}
	if (sr < imageSize - 1 && image[sr + 1][sc] == image[sr][sc] && !flag[sr + 1][sc])  {
	    flag[sr + 1][sc] = true;
	    changeValue(image, imageSize, imageColSize, sr + 1, sc, newColor, res, flag, returnSize, returnColumnSizes);
	}
	if (sc < imageColSize[sr] - 1 && image[sr][sc + 1] == image[sr][sc] && !flag[sr][sc + 1])  {
	    flag[sr][sc + 1] = true;
	    changeValue(image, imageSize, imageColSize, sr, sc + 1, newColor, res, flag, returnSize, returnColumnSizes);
	}
}

int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int newColor, int* returnSize, int** returnColumnSizes){
    int** res = malloc(sizeof(int*) * imageSize);
    bool** flag = malloc(sizeof(bool*) * imageSize);
    *returnSize = imageSize;
    *returnColumnSizes = malloc(sizeof(int) * imageSize);

    for (int i = 0; i < imageSize; i++) {
        res[i] = malloc(sizeof(int) * imageColSize[i]);
        flag[i] = malloc(sizeof(bool) * imageColSize[i]);
        memset(res[i], 0, sizeof(int) * imageColSize[i]);
        memset(flag[i], 0, sizeof(bool) * imageColSize[i]);
        (*returnColumnSizes)[i] = imageColSize[i];
    }
    flag[sr][sc] = true;
    changeValue(image, imageSize, imageColSize, sr, sc, newColor, res, flag, returnSize, returnColumnSizes);
    for (int i = 0; i < imageSize; i++) {
        for (int j = 0; j < imageColSize[i]; j++) {
            if (flag[i][j] == false) res[i][j] = image[i][j];
        }
        free(flag[i]);
    }
    free(flag);
    return res;
}

