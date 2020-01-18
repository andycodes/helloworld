/*
�������������Depth-First-Search��DFS����һ��
���ڱ�������������ͼ���㷨��
����������ȱ������Ľڵ㣬
����������������ķ�֧��
���ڵ�v�����ڱ߶�����̽Ѱ����
���������ݵ����ֽڵ�v����
���ߵ���ʼ�ڵ㡣
��һ����һֱ���е��ѷ��ִ�Դ�ڵ�ɴ�
�����нڵ�Ϊֹ�����������δ�����ֵĽڵ㣬
��ѡ������һ����ΪԴ�ڵ㲢�ظ����Ϲ��̣�
�������̷�������ֱ�����нڵ㶼������Ϊֹ��

DFSģ��

result = []
def dfs(·��, ѡ���б�):
    if ���㡸����������:
        result.add(��·����)
        return

    for ѡ�� in ��ѡ���б�:  (����N����)
        #��ѡ��
	 ����ѡ���ѡ���б��Ƴ�
	 ��·����.add(ѡ��)
        dfs(·��, ѡ���б�)
	 (ע������ݲ���:û�з��ڳ�������֦)

*/



/*
733. ͼ����Ⱦ
��һ���Զ�ά���������ʾ��ͼ����
ÿһ��������ʾ��ͼ��������ֵ��С��
��ֵ�� 0 �� 65535 ֮�䡣
����һ������ (sr, sc) ��ʾͼ����Ⱦ��ʼ������ֵ���� ���У�
��һ���µ���ɫֵ newColor������������ɫ���ͼ��

Ϊ�������ɫ�������ӳ�ʼ���꿪ʼ��
��¼��ʼ��������������ĸ�����������ֵ���ʼ��
����ͬ���������ص㣬�����ټ�¼���ĸ������Ϸ�����
�������ص������Ƕ�Ӧ�ĸ�����������ֵ���ʼ������ͬ
���������ص㣬�������ظ��ù��̡�
�������м�¼�����ص����ɫֵ��Ϊ�µ���ɫֵ��

��󷵻ؾ�����ɫ��Ⱦ���ͼ��

����:
image = [
[1,1,1],
[1,1,0],
[1,0,1]
]
sr = 1, sc = 1, newColor = 2
���: [[2,2,2],[2,2,0],[2,0,1]]
����:
��ͼ������м䣬(����(sr,sc)=(1,1)),
��·�������з������������ص����ɫ�������ĳ�2��
ע�⣬���½ǵ�����û�и���Ϊ2��
��Ϊ�����������������ĸ����������ʼ�����������ص㡣

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
200. ��������
����һ���� '1'��½�أ��� '0'��ˮ����ɵĵĶ�ά����
���㵺���������һ������ˮ��Χ��
��������ͨ��ˮƽ�����ֱ���������ڵ�½�����Ӷ��ɵġ�
����Լ���������ĸ��߾���ˮ��Χ��

ʾ�� 1:

����:
11110
11010
11000
00000

���: 1

};
*/
void dfs(char** grid, int gridSize, int gridColSize, int x ,int y)
{
	if (x < 0 || x >= gridSize || y < 0 || y >= gridColSize || grid[x][y] == '0')
		return;

	grid[x][y] = '0';//ǰ�����

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

