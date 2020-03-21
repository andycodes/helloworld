/*
���ݷ��Ļ���˼�룺

����������⣬��������Ľ�ռ䣻
ȷ�����������Ľ�ռ�ṹ��
��������ȷ�ʽ������ռ䣬
���������������ü�֦����������Ч������


���ݷ���������Ľ⣬
ʹ�õ���DFS�����������������
��DFS�Ĺ����з��ֲ�������Ľ⣬
��ô�Ϳ�ʼ���ݵ���һ�������һ���ڵ㡣
DFS�Ǳ������������ռ䣬
�������Ƿ�������Ľ⡣
���Ը����û��ݷ���DFS��һ��Ӧ�ã�
DFS������һ�ֹ��ߡ�

result = []
def backtrack(·��, ѡ���б�):
    if ���㡸����������:
        result.add(��·����)
        return

    for ѡ�� in ��ѡ���б���:  (����N����)
        #��ѡ��
	 ����ѡ���ѡ���б��Ƴ�
	 ��·����.add(ѡ��)
        backtrack(·��, ѡ���б�)
        #����ѡ��
        ��·����.remove(ѡ��)
    	 ����ѡ���ټ���ѡ���б�
*/


/*
1219                                                                                                                                                                                                . �ƽ��
��Ҫ����һ����󣬵��ʿ���ѧ���Ѿ�̽����
��������е���Դ�ֲ������ô�СΪ m * n ������
grid �����˱�ע��ÿ����Ԫ���е������ͱ�ʾ��һ
��Ԫ���еĻƽ�����������õ�Ԫ���ǿյģ���ô���� 0��

Ϊ��ʹ������󻯣�����Ҫ�����¹��������ɻƽ�

ÿ���󹤽���һ����Ԫ���ͻ��ռ��õ�Ԫ���е����лƽ�
��ÿ�ο��Դӵ�ǰλ�������������ĸ������ߡ�
ÿ����Ԫ��ֻ�ܱ����ɣ����룩һ�Ρ�
���ÿ��ɣ����룩�ƽ���ĿΪ 0 �ĵ�Ԫ��
�󹤿��Դ������� ����һ�� �лƽ�ĵ�Ԫ�����������ֹͣ��


ʾ�� 1��

���룺grid = [[0,6,0],[5,8,7],[0,9,0]]
�����24
���ͣ�
[[0,6,0],
 [5,8,7],
 [0,9,0]]
һ���ռ����ƽ��·���ǣ�9 -> 8 -> 7��
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



/*ȫ����*/
void backtrack(int source[], int start, int end, int *resSize, int **res)
{
	// �ҵ�һ������
	if (start == end) {
		res[*resSize] = (int *)calloc(end, sizeof(int));
		memcpy(res[*resSize], source, sizeof(int) * end);
		(*resSize)++;
	} else {
		// û������һ�����У��������������һ��Ԫ��
		for (int i = start; i < end; i++) {
			if (start != i) {// ��������
				swap(source[start], source[i]);
			}

			// �ݹ�����ʣ��Ĵ�start+1��end��Ԫ��
			backtrack(source, start + 1, end, resSize, res);

			if (start != i) {// ����ʱ��ԭ
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
401. �������ֱ�
�������ֱ������� 4 �� LED ����Сʱ��0-11����
�ײ��� 6 �� LED �������ӣ�0-59����
ÿ�� LED ����һ�� 0 �� 1�����λ���Ҳࡣ

���磬����Ķ������ֱ���ȡ "3:25"��

����һ���Ǹ����� n ������ǰ LED ���ŵ�������
�������п��ܵ�ʱ�䡣

����:

����: n = 1
����: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
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
��ʵ�����Ŀ���Թ����ж��� n��1�Ķ�������ϡ�
ת��Ϊ�ַ������ɡ�
���ｫ 0 - 9������һ��
0 - 5 �� ����
6 - 9 ��Сʱ���㡣
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


