/*
DFSģ��

dfs���ڣ��������������˳�

����

�ݹ飬���Ž�һ��DFS
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
��һ���Զ�ά���������ʾ��ͼ����ÿһ��������ʾ��ͼ��������ֵ��С����ֵ�� 0 �� 65535 ֮�䡣

����һ������ (sr, sc) ��ʾͼ����Ⱦ��ʼ������ֵ���� ���У���һ���µ���ɫֵ newColor������������ɫ���ͼ��

Ϊ�������ɫ�������ӳ�ʼ���꿪ʼ����¼��ʼ��������������ĸ�����������ֵ���ʼ������ͬ���������ص㣬�����ټ�¼���ĸ������Ϸ������������ص������Ƕ�Ӧ�ĸ�����������ֵ���ʼ������ͬ���������ص㣬�������ظ��ù��̡��������м�¼�����ص����ɫֵ��Ϊ�µ���ɫֵ��

��󷵻ؾ�����ɫ��Ⱦ���ͼ��

����:
image = [[1,1,1],[1,1,0],[1,0,1]]
sr = 1, sc = 1, newColor = 2
���: [[2,2,2],[2,2,0],[2,0,1]]
����:
��ͼ������м䣬(����(sr,sc)=(1,1)),
��·�������з������������ص����ɫ�������ĳ�2��
ע�⣬���½ǵ�����û�и���Ϊ2��
��Ϊ�����������������ĸ����������ʼ�����������ص㡣

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

